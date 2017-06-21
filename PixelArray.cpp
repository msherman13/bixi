#include <cmath>
#include <algorithm>

#include "PixelArray.h"
#include "Logging.h"
#include "Routine.h"
#include "Math.h"

CMemoryPool<CPixelArray::Block, CPixelArray::Block::c_num_blocks> CPixelArray::Block::s_pool;
CMemoryPool<CPixelArray, CPixelArray::c_alloc_qty>                CPixelArray::s_pool;

CPixelArray::CPixelArray(const CPixelArray& rhs) :
    CPixelArray(rhs.GetConfig())
{
    m_offset     = rhs.GetOffset();
}

CPixelArray::CPixelArray(Config* config) :
    m_block(new Block),
    m_owner(true),
    m_pixels(m_block->m_pixels),
    m_length(config->m_logical_size),
    m_raw_length(config->m_physical_size),
    m_config(config)
{
}

CPixelArray::CPixelArray(CPixelArray* pixels, size_t len, size_t offset) :
    m_pixels(pixels->GetRaw()),
    m_length(len == 0 ? pixels->GetSize() : len),
    m_raw_length(pixels->GetRawSize() - offset),
    m_config(pixels->GetConfig()),
    m_offset(offset)
{
}

CPixelArray::~CPixelArray()
{
    ExitRoutine();

    if(m_owner == true)
    {
        delete m_block;
    }
}

CRGB CPixelArray::GetPixel(size_t index)
{
    return m_pixels[GetLocation(index)];
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    m_pixels[GetLocation(index)] = rgb;
}

void CPixelArray::BlendPixel(size_t index, CRGB rgb, float weight)
{
    CRGB pixel = GetPixel(index);

    weight = std::min<float>(weight, 1.00);
    weight = std::max<float>(weight, 0.00);

    float nweight = 1.0 - weight;

    pixel.r = sqrtf((nweight * pixel.r) * (nweight * pixel.r) + (weight * rgb.r) * (weight * rgb.r));
    pixel.g = sqrtf((nweight * pixel.g) * (nweight * pixel.g) + (weight * rgb.g) * (weight * rgb.g));
    pixel.b = sqrtf((nweight * pixel.b) * (nweight * pixel.b) + (weight * rgb.b) * (weight * rgb.b));

    SetPixel(index, pixel);
}

void CPixelArray::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

void CPixelArray::Copy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        SetPixel(index, rgb);
    }   
}

void CPixelArray::SmartCopy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        
        if(rgb == CRGB(CRGB::Black))
        {
            SetPixel(index, rgb);
        }
    }   
}

void CPixelArray::ExitRoutine()
{
    if(m_routine == nullptr)
    {
        return;
    }

    char logstr[256];
    sprintf(logstr, "CPixelArray::ExitRoutine: Exiting routine [%s]", m_routine->GetName());
    CLogging::log(logstr);

    delete m_routine;

    m_routine = nullptr;
}

void CPixelArray::SetRoutine(CRoutine* routine)
{
    ExitRoutine();

    char logstr[256];
    sprintf(logstr, "CPixelArray::SetRoutine: Setting routine to [%s]", routine->GetName());
    CLogging::log(logstr);

    m_routine      = routine;
}

void CPixelArray::TransitionTo(CRoutine* routine)
{
    char logstr[256];
    sprintf(logstr, "CPixelArray::TransitionTo: Transitioning to [%s]", routine->GetName());
    CLogging::log(logstr);

    if(InTransition() == true)
    {
        CLogging::log("CPixelArray::TransitionTo: ERROR Already in transition");
        return;
    }

    m_next_routine = routine;
}

void CPixelArray::FinishTransition()
{
    if(InTransition() == false)
    {
        return;
    }

    char logstr[256];
    sprintf(logstr, "CPixelArray::FinishTransition: Transition to [%s] is complete",
            m_next_routine->GetName());
    CLogging::log(logstr);

    SetRoutine(m_next_routine);
    m_next_routine = nullptr;
}

size_t CPixelArray::RoutineStartMs()
{
    return !InRoutine() ? 0 : m_routine->StartMs();
}

void CPixelArray::Continue()
{
    if(InTransition() == true && m_next_routine->InTransition() == false)
    {
        FinishTransition();
    }

    if(InRoutine() == true)
    {
        m_routine->Continue();
    }

    if(InTransition() == true)
    {
        m_next_routine->Continue();
    }
}
