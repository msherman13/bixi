#pragma once

#include "FastLED.h"

#include "PixelArray.h"

class CPlain
{
    public:
        struct Config
        {
            static constexpr size_t c_max_num_legs = 8;

            size_t m_num_legs               = 0;
            size_t m_start[c_max_num_legs]  = {};
            size_t m_length[c_max_num_legs] = {};
        };

    public:
        CPlain(CPixelArray& pixels, Config& config);
        ~CPlain();

    public:
        size_t NumLegs()               { return m_config.m_num_legs; }
        size_t LegLength(size_t index) { return m_config.m_length[index]; }
        size_t LegStart(size_t index)  { return m_config.m_start[index]; }

    public:
        void SetColor(CRGB rgb);

    private:
        CPixelArray& m_pixels;
        Config       m_config;
};
