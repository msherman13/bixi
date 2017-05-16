#pragma once

#include <stdlib.h>

struct CRGB;

class CPixelArray
{
    public:
        CPixelArray(size_t len); // new underlying pixels
        CPixelArray(CRGB* rgb, size_t len); // reference to external pixels
        ~CPixelArray();

    public:
        size_t GetSize() { return m_length; }

    public:
        CRGB& GetPixel(size_t index);
        void  SetPixel(size_t index, CRGB rgb);
        void  Reset();

    public:
        void Shift(bool forward, size_t amount);

    public:
        void SmartCopy(CPixelArray& rhs, size_t size, size_t offset=0);

    private:
        CRGB*  m_pixels = nullptr;
        size_t m_length = 0;
};
