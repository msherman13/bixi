#include <cmath>
#include <algorithm>

#include "PixelArray.h"
#include "Logging.h"
#include "Routine.h"
#include "Math.h"

CMemoryPool<CPixelArray::Block, CPixelArray::Block::c_num_blocks> CPixelArray::Block::s_pool;
CMemoryPool<CPixelArray, CPixelArray::c_alloc_qty>                CPixelArray::s_pool;

CPixelArray::CPixelArray(const CPixelArray& rhs) :
    CPixelArray(rhs.GetName(), rhs.GetConfig())
{
    m_offset = rhs.GetOffset();
}

CPixelArray::CPixelArray(const char* name, Config* config) :
    m_block(new Block),
    m_owner(true),
    m_pixels(m_block->m_pixels),
    m_length(config->m_logical_size),
    m_raw_length(config->m_physical_size),
    m_config(config)
{
    for(size_t i=0;i<GetRawSize();i++)
    {
        SetPixelRaw(i, CRGB::Black);
    }

    SetName(name);
}

CPixelArray::CPixelArray(const char* name, CPixelArray* pixels, size_t len, size_t offset) :
    m_pixels(pixels->GetRaw()),
    m_length(len == 0 ? pixels->GetSize() : len),
    m_raw_length(pixels->GetRawSize() - offset),
    m_config(pixels->GetConfig()),
    m_offset(offset)
{
    SetName(name);
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
    return GetPixelRaw(GetLocation(index));
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    SetPixelRaw(GetLocation(index), rgb);
}

CRGB CPixelArray::GetPixelRaw(size_t index)
{
    return m_pixels[index];
}

void CPixelArray::SetPixelRaw(size_t index, CRGB rgb)
{
    m_pixels[index] = rgb;
}

CRGB CPixelArray::Blend(const CRGB& lhs, const CRGB& rhs, float rhs_weight)
{
    rhs_weight = std::min<float>(rhs_weight, 1.00);
    rhs_weight = std::max<float>(rhs_weight, 0.00);

    float nweight = 1.0 - rhs_weight;

    CRGB ret;

#if 1
    ret.r = Math::fast_sqrt((nweight * lhs.r) * (nweight * lhs.r) + (rhs_weight * rhs.r) * (rhs_weight * rhs.r));
    ret.g = Math::fast_sqrt((nweight * lhs.g) * (nweight * lhs.g) + (rhs_weight * rhs.g) * (rhs_weight * rhs.g));
    ret.b = Math::fast_sqrt((nweight * lhs.b) * (nweight * lhs.b) + (rhs_weight * rhs.b) * (rhs_weight * rhs.b));
#else
    ret.r = sqrtf((nweight * lhs.r) * (nweight * lhs.r) + (rhs_weight * rhs.r) * (rhs_weight * rhs.r));
    ret.g = sqrtf((nweight * lhs.g) * (nweight * lhs.g) + (rhs_weight * rhs.g) * (rhs_weight * rhs.g));
    ret.b = sqrtf((nweight * lhs.b) * (nweight * lhs.b) + (rhs_weight * rhs.b) * (rhs_weight * rhs.b));
#endif

    return ret;
}

void CPixelArray::BlendPixel(size_t index, CRGB rgb, float weight)
{
    CRGB pixel = GetPixel(index);

    SetPixel(index, Blend(pixel, rgb, weight));
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
    sprintf(logstr, "CPixelArray(%s)::ExitRoutine: Exiting routine [%s]", m_name, m_routine->GetName());
    CLogging::log(logstr);

    delete m_routine;

    m_routine = nullptr;
}

void CPixelArray::SetRoutine(CRoutine* routine)
{
    ExitRoutine();

    char logstr[256];
    sprintf(logstr, "CPixelArray(%s)::SetRoutine: Setting routine to [%s]", m_name, routine->GetName());
    CLogging::log(logstr);

    m_routine = routine;
}

void CPixelArray::TransitionTo(CRoutine* routine, size_t duration_ms)
{
    char logstr[256];
    sprintf(logstr, "CPixelArray(%s)::TransitionTo: Transitioning to [%s]", m_name, routine->GetName());
    CLogging::log(logstr);

    if(InTransition() == true)
    {
        CLogging::log("CPixelArray::TransitionTo: ERROR Already in transition");
        return;
    }

    if(m_routine != nullptr)
    {
        sprintf(logstr, "CPixelArray(%s)::TransitionTo: Transitioning out of [%s]", m_name, m_routine->GetName());
        CLogging::log(logstr);
        m_routine->TransitionOut(duration_ms);
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
    sprintf(logstr, "CPixelArray(%s)::FinishTransition: Transition to [%s] is complete",
            m_name, m_next_routine->GetName());
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
    if(InTransition() == true && m_routine->TransitionDone() == true)
    {
        FinishTransition();
    }

    if(InTransition() == true)
    {
        m_next_routine->Continue();
    }

    if(InRoutine() == true)
    {
        m_routine->Continue();
    }
}
