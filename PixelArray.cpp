#include "PixelArray.h"
#include "FastLED.h"
#include "Routine.h"
#include "RoutineGlare.h"

CPixelArray::CPixelArray(size_t len) :
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
        CRGB& pixel = m_pixels[GetSize()-1];
        CRGB  buff;

        for(size_t i=0;i<GetSize();i++)
        {   
            buff = m_pixels[i];
            m_pixels[i] = pixel;
            pixel = buff;
        }   
    }   
}

void CPixelArray::SmartCopy(CPixelArray& rhs, size_t size, size_t offset)
{
    for(size_t i=0;i<size;i++)
    {   
        size_t index = (i + offset) % GetSize();
        m_pixels[index] = rhs.GetPixel(i);
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

void CPixelArray::StartRoutineGlare(CRGB base_color, bool forward, uint32_t period_sec)
{
    ExitRoutine();

    m_routine = new CRoutineGlare(this, base_color, forward, period_sec);
}

void CPixelArray::Continue()
{
    if(m_routine == nullptr)
    {
        return;
    }

    m_routine->Continue();
}
