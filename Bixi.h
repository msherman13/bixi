#pragma once

#include "FastLED.h"
#include "PixelArray.h"

class CPolygon;

class CBixi
{
    public:
        static constexpr size_t c_indicatorPin     = 13;
        static constexpr size_t c_indicatorDelayMs = 5000;
        static constexpr size_t c_num_polygons     = 2;

    public: // singleton
        static CBixi& Instance();
        ~CBixi();

    private:
        CBixi();

    public:
        void Continue();

    private:
        void Show();

    private:
        CPixelArray m_pixels;
        size_t      m_lastIndicator            = 0;
        bool        m_indicatorOn              = false;
        CPolygon*   m_polygons[c_num_polygons] = {};

};
