#pragma once

#include <stdlib.h>

#include "PixelArray.h"
#include "FastLED.h"

class CPolygon
{
    public:
        static constexpr size_t c_max_num_legs = 6;

    public:
        struct Config
        {
            size_t m_num_legs = 0;
            size_t m_start[c_max_num_legs];
            size_t m_end[c_max_num_legs];
        };

    public:
        CPolygon(CPixelArray* pixels, Config& config);
        ~CPolygon();

    public:
        void Solid(CRGB rgb);
        void Glare(CRGB base_color, bool forward, uint32_t period_sec);
        void GlareLegs(CRGB base_color, bool forward, uint32_t period_sec);
        void Continue();

    public:
        size_t NumLegs()          { return m_num_legs; }
        size_t Length(size_t leg) { return m_legs[leg]->GetSize(); }
        size_t Perimeter()        { return m_virtual_pixels->GetSize(); }

    private:
        void Show();
        void ClearRoutines();

    private:
        CPixelArray         m_pixels;
        size_t              m_num_legs             = 0;
        size_t*             m_locations            = nullptr;
        CPixelArray*        m_virtual_pixels       = nullptr;
        CPixelArray*        m_legs[c_max_num_legs] = {};
};
