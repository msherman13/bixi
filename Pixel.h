#pragma once

#include "FastLED.h"

class CPixel
{
    public:
        CPixel();
        ~CPixel();

    private:
        bool m_isPopulated;
        CRGB m_rgb;

    public:
        // returns false if not populated
        // won't copy if not populated
        bool GetRGB(CRGB& dest);
        void SetRGB(CRGB source);
        void SetIsPopulated(bool val) { m_isPopulated = val; }
        bool GetIsPopulated() { return m_isPopulated; }

    public:
        void SetBlack();
};
