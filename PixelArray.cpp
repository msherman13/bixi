#include "PixelArray.h"
#include "FastLED.h"
#include "Routine.h"
#include "RoutineGlare.h"
#include "RoutineCrawl.h"
#include "RoutineSticks.h"

CPixelArray::CPixelArray(size_t len) :
    m_owner(true),
    m_pixels(new CRGB[len]),
    m_length(len)
{
}

CPixelArray::CPixelArray(CRGB* rgb, size_t len) :
    m_pixels(rgb),
    m_length(len)
{
}

CPixelArray::CPixelArray(CPixelArray* rhs) :
    CPixelArray(rhs->GetRaw(), rhs->GetSize())
{
}

CPixelArray::~CPixelArray()
{
    if(m_owner)
    {
        delete m_pixels;
    }
}

CRGB CPixelArray::GetPixel(size_t index)
{
    return m_pixels[index];
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    m_pixels[index] = rgb;
}

void CPixelArray::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

void CPixelArray::Shift(bool forward, size_t amount)
{
    for(size_t it=0;it<amount;it++)
    {   
        CRGB& pixel = forward ? m_pixels[GetSize()-1] : m_pixels[0];
        CRGB  buff;

        for(size_t i=0;i<GetSize();i++)
        {   
            size_t index = forward ? i : GetSize() - i - 1;
            buff = m_pixels[index];
            m_pixels[index] = pixel;
            pixel = buff;
        }   
    }   
}

void CPixelArray::SmartCopy(CPixelArray* rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        CRGB   rgb = rhs->GetPixel(i);
        if(GetPixel(index) == CRGB(CRGB::Black))
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

    delete m_routine;
}

void CPixelArray::StartRoutineSolid(CRGB rgb)
{
    ExitRoutine();

    SetAllPixels(rgb);
}

void CPixelArray::StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec)
{
    ExitRoutine();

    m_routine = new CRoutineGlare(this, base_color, q, forward, period_sec);
}

void CPixelArray::StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec)
{
    ExitRoutine();

    m_routine = new CRoutineCrawl(this, base_color, width, start_offset, forward, period_sec);
}

void CPixelArray::StartRoutineSticks(size_t num_sticks)
{
    ExitRoutine();

    m_routine = new CRoutineSticks(this, num_sticks);
}

void CPixelArray::Continue()
{
    if(m_routine == nullptr)
    {
        return;
    }

    m_routine->Continue();
}

CRGB* CPixelArray::GetRaw(size_t index)
{
    return &m_pixels[index];
}
