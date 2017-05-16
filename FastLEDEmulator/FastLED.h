#pragma once

#include "pixeltypes.h"
#include <iostream>
#include <fstream>

#define WS2811_PORTD 1
#define WS2813_PORTD 2

class CFastLED
{
    public:
        static constexpr size_t c_refresh_rate  = 60; // frames per second
        static constexpr size_t c_sleep_time_ms = (1.00 / c_refresh_rate) * 1000;

    public:
        CFastLED();

    public:
        template <size_t TYPE, size_t NUM_PINS>
        void addLeds(CRGB* leds, size_t numLedsPerPin)
        {
            m_numLeds = NUM_PINS * numLedsPerPin;
            m_leds = leds;

            m_file << "time_ms";
            for(size_t i=0;i<m_numLeds;i++)
            {
                m_file << ",pixel_" << i;
            }
            m_file << std::endl;
        }
        void show();

    private:
        size_t m_numLeds = 0;
        CRGB* m_leds = nullptr;
        std::ofstream m_file;
};

extern CFastLED FastLED;
