#include "PixelArray.h"
#include "FastLED.h"

CPixelArray::CPixelArray(size_t len) :
    m_pixels(new CRGB[len]),
    m_length(len)
{
    Reset();
}

CPixelArray::CPixelArray(CRGB* rgb, size_t len) :
    m_pixels(rgb),
    m_length(len)
{
}

CPixelArray::~CPixelArray()
{
}

CRGB& CPixelArray::GetPixel(size_t index)
{
    return m_pixels[index];
}

void CPixelArray::SetPixel(size_t index, CRGB rgb)
{
    m_pixels[index] = rgb;
}

void CPixelArray::Reset()
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, CRGB::Black);
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
