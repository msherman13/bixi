#pragma once

#include "FastLED.h"
#include "Pixel.h"

class CPixelArray
{
    public:
        CPixelArray(int size);
        ~CPixelArray();

    public:
        int GetSize() { return m_size; }

    public:
        CPixel* GetPixel(int index);
        bool SetPixel(int index, CRGB rgb);
        void Reset();
        bool ValidateIndex(int index);

    public:
        void Shift(bool forward, int amount);

    public:
        void SmartCopy(CPixelArray& rhs, int size, int offset=0);

    private:
        int m_size;
        CPixel* m_pPixels;
};
