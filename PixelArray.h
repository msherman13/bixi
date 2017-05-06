#pragma once

#include "FastLED.h"
#include "Pixel.h"

template <size_t SIZE> class CPixelArray
{
    public:
        CPixelArray()
        {
            Reset();
        }
        ~CPixelArray();

    public:
        size_t GetSize() { return SIZE; }

    public:
        CPixel& GetPixel(size_t index)
        {
            return m_pixels[index];
        }

        void SetPixel(size_t index, CRGB rgb)
        {
            m_pixels[index].SetRGB(rgb);
        }

        void Reset()
        {
            for(size_t i=0;i<GetSize();i++)
            {
                m_pixels[i].SetRGB(CRGB::Black);
                m_pixels[i].SetIsPopulated(false);
            }
        }

    public:
        void Shift(bool forward, size_t amount)
        {
            for(size_t it=0;it<amount;it++)
            {
                CPixel pixel = m_pixels[GetSize()-1];
                CPixel buff;

                for(size_t i=0;i<GetSize();i++)
                {
                    buff = m_pixels[i];
                    m_pixels[i] = pixel;
                    pixel = buff;
                }
            }
        }

    public:
        void SmartCopy(CPixelArray& rhs, size_t size, size_t offset=0)
        {
            for(size_t i=0;i<size;i++)
            {
                size_t index = (i + offset) % GetSize();
                m_pixels[index] = *rhs.GetPixel(i);
            }
        }

    private:
        CPixel m_pixels[SIZE];
};
