#pragma once

#include "pixeltypes.h"

#define WS2811_PORTD 1

class CFastLED
{
    public:
        CFastLED();

    public:
        template <size_t TYPE, size_t NUM_PINS>
        void addLeds(CRGB* leds, size_t numLedsPerPin)
        {
            m_numLeds = NUM_PINS * numLedsPerPin;
            m_leds = leds;
        }
        void show();

    private:
        size_t m_numLeds = 0;
        CRGB* m_leds = nullptr;
};

extern CFastLED FastLED;
