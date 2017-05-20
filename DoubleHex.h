#pragma once

#include "Plain.h"
#include "ColorPallete.h"

class CPixelArray;

class CDoubleHex
{
    public:
        static constexpr size_t c_num_legs           = 6;
        static constexpr size_t c_num_plains         = c_num_legs;
        static constexpr size_t c_num_legs_per_plain = 2; // actually 4 but we only light 2
        static constexpr size_t c_glare_period_sec   = 10;

    public:
        struct Config
        {
            // always start at the top-left corner and go clockwis
            size_t m_start_outer[c_num_legs];
            size_t m_end_outer[c_num_legs];
            size_t m_start_inner[c_num_legs];
            size_t m_end_inner[c_num_legs];
        };
        enum Mode
        {
            ModeOff,
            ModeSolid,
            ModeBlink,
            ModeCycle,
            ModeRainbow,
            ModeGlare,

            ModeQty,
            ModeUndef,
        };

    public:
        CDoubleHex(CPixelArray& pixels, Config& config);
        ~CDoubleHex();

    public:
        void SetMode(Mode mode) { m_mode = mode; }
        void SetBaseColorIndex(ColorPallete::Color color) { m_base_color = color; }
        void SetDirection(bool clockwise) { m_clockwise = clockwise; }
        void Start();
        void Continue();

    public:
        size_t LengthOuter(size_t index)
        {
            return abs((int)m_config.m_start_outer[index] - (int)m_config.m_end_outer[index]) + 1;
        }
        size_t LengthInner(size_t index)
        {
            return abs((int)m_config.m_start_inner[index] - (int)m_config.m_end_inner[index]) + 1;
        }

    private:
        void ContinueCycle();
        void ContinueBlink();
        void ContinueGlare();
        void ShiftPlains();

    private:
        CPixelArray&        m_pixels;
        Config              m_config;
        CPlain*             m_plains[c_num_plains] = {};
        Mode                m_mode                 = ModeOff;
        uint32_t            m_lastRun              = 0;
        ColorPallete::Color m_base_color           = ColorPallete::ChromeBlue;
        size_t              m_cycle_count          = 0;
        bool                m_clockwise            = true;
        double              m_midpoint             = 0.5;
};
