#include <cmath>
#include <algorithm>

#include "PixelArray.h"
#include "Logging.h"
#include "Routine.h"

CMemoryPool<CPixelArray::Block, CPixelArray::Block::c_num_blocks> CPixelArray::Block::s_pool;
CMemoryPool<CPixelArray, CPixelArray::c_alloc_qty>                CPixelArray::s_pool;

CPixelArray::CPixelArray(const CPixelArray& rhs) :
    CPixelArray(rhs.GetRawSize(), rhs.GetSize())
{
    m_length     = rhs.GetSize();
    m_raw_length = rhs.GetRawSize();
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i]   = rhs.GetLocation(i);
        m_coordinates[i] = rhs.GetCoordinate(i);
    }
}

CPixelArray::CPixelArray(size_t physical_len, size_t logical_len) :
    m_block(new Block),
    m_owner(true),
    m_pixels(m_block->m_pixels),
    m_length(logical_len),
    m_locations(m_block->m_locations),
    m_coordinates(m_block->m_coordinates)
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_locations[i] = i;
    }
}

CPixelArray::CPixelArray(CPixelArray* pixels, size_t len, size_t offset) :
    m_pixels(pixels->GetRaw()),
    m_length(len == 0 ? pixels->GetSize() : len),
    m_raw_length(pixels->GetRawSize() - offset),
    m_locations(pixels->m_locations + offset),
    m_coordinates(pixels->m_coordinates + offset)
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
    return m_pixels[m_locations[index]];
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    m_pixels[m_locations[index]] = rgb;
}

void CPixelArray::BlendPixel(size_t index, CRGB rgb, float weight)
{
    CRGB pixel = GetPixel(index);

    weight = std::min<float>(weight, 1.00);
    weight = std::max<float>(weight, 0.00);

    float nweight = 1.0 - weight;

    pixel.r = sqrtf(powf(nweight * pixel.r, 2) + powf(weight * rgb.r, 2));
    pixel.g = sqrtf(powf(nweight * pixel.g, 2) + powf(weight * rgb.g, 2));
    pixel.b = sqrtf(powf(nweight * pixel.b, 2) + powf(weight * rgb.b, 2));

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
