#include <algorithm>

#include "DoubleHex.h"
#include "Arduino.h"

CDoubleHex::CDoubleHex(CPixelArray& pixels, Config& config) :
    m_pixels(pixels),
    m_config(config)
{
    for(size_t i=0;i<c_num_plains;i++)
    {
        CPlain::Config plain_config;
        plain_config.m_num_legs  = c_num_legs_per_plain;
        plain_config.m_start[0]  = m_config.m_start_outer[i];
        plain_config.m_end[0]    = m_config.m_end_outer[i];
        plain_config.m_start[1]  = m_config.m_start_inner[i];
        plain_config.m_end[1]    = m_config.m_end_inner[i];

        m_plains[i] = new CPlain(pixels, plain_config);
    }
}

CDoubleHex::~CDoubleHex()
{
    for(size_t i=0;i<c_num_plains;i++)
    {
        delete m_plains[i];
    }
}

void CDoubleHex::Start()
{
    m_lastRun = 0;

    switch(m_mode)
    {
        case ModeBlink:
        case ModeOff:
            for(size_t i=0;i<c_num_plains;i++)
            {
                m_plains[i]->SetColor(CRGB::Black);
            }
            break;

        case ModeSolid:
            for(size_t i=0;i<c_num_plains;i++)
            {
                m_plains[i]->SetColor(m_base_color);
            }
            break;

        case ModeCycle:
            m_cycle_count = 0;
            ContinueCycle();
            break;

        case ModeRainbow:
            for(size_t i=0;i<c_num_legs;i++)
            {
                for(size_t j=0;j<LengthOuter(i);j++)
                {
                    CRGB rgb = ColorPallete::s_colors[j % ColorPallete::Qty];
                    m_pixels.SetPixel(m_config.m_start_outer[i] + j, rgb);
                }
                for(size_t j=0;j<LengthInner(i);j++)
                {
                    CRGB rgb = ColorPallete::s_colors[j % ColorPallete::Qty];
                    m_pixels.SetPixel(m_config.m_start_inner[i] + j, rgb);
                }
            }
            break;

        case ModeGlare:
            ContinueGlare();
            break;

        default:
            break;
    }

    m_lastRun = millis();
}

void CDoubleHex::Continue()
{
    switch(m_mode)
    {
        case ModeCycle:
            ContinueCycle();
            break;

        case ModeBlink:
            ContinueBlink();
            break;

        case ModeRainbow:
            {
                uint32_t now = millis();
                if(now - m_lastRun < 500)
                    return;
                m_lastRun = now;

                ShiftPlains();
                break;
            }

        case ModeGlare:
            ContinueGlare();
            break;

        default:
            break;
    }
}

void CDoubleHex::ContinueCycle()
{
    uint32_t now = millis();
    if(now - m_lastRun < 2000)
        return;
    m_lastRun = now;

    for(size_t i=0;i<c_num_plains;i++)
    {   
        bool on_off = (m_cycle_count + i) % 3 == 0;
        CRGB rgb = m_base_color;
        if(on_off == false)
        {
            rgb = CRGB::Black;
        }
        m_plains[i]->SetColor(rgb);
    }   

    m_cycle_count++;
}

void CDoubleHex::ContinueBlink()
{
    uint32_t now = millis();
    if(now - m_lastRun < 2000)
        return;
    m_lastRun = now;

    bool on_off = m_cycle_count % 2 == 0;

    for(size_t i=0;i<c_num_plains;i++)
    {
        CRGB rgb = m_base_color;
        if(on_off == false)
        {
            rgb = CRGB::Black;
        }
        m_plains[i]->SetColor(rgb);
    }   

    m_cycle_count++;
}

void CDoubleHex::ShiftPlains()
{
    for(size_t i=0;i<c_num_legs;i++)
    {
        size_t start_index = std::min<size_t>(m_config.m_start_inner[i], m_config.m_end_inner[i]);
        CRGB* start = &m_pixels.GetRawArray()[start_index];
        CPixelArray inner(start, LengthInner(i));
        inner.Shift(m_clockwise, 1);

        size_t amount = round((double)LengthOuter(i) / LengthInner(i));
        start_index = std::min<size_t>(m_config.m_start_outer[i], m_config.m_end_outer[i]);
        start = &m_pixels.GetRawArray()[start_index];
        CPixelArray outer(start, LengthOuter(i));
        outer.Shift(m_clockwise, amount);
    }
}

void CDoubleHex::ContinueGlare()
{
    uint32_t now = millis();

    double move_by = (double)(now - m_lastRun) / (c_glare_period_sec * 1000);

    if(m_clockwise == true)
    {
        m_midpoint += move_by;
        if(m_midpoint > 1.00)
        {
            m_midpoint -= 1.00;
        }
    }
    else
    {
        m_midpoint -= move_by;
        if(m_midpoint < 0.00)
        {
            m_midpoint += 1.00;
        }
    }

    m_lastRun = now;

    CHSV hsv = rgb2hsv_approximate(m_base_color);

    for(size_t i=0;i<c_num_legs;i++)
    {
        for(size_t j=0;j<LengthOuter(i);j++)
        {
            bool aligned = m_config.m_start_outer[i] < m_config.m_end_outer[i];
            double this_index = (double)j / LengthOuter(i);
            double ratio = std::max<double>(1 - fabs(this_index - m_midpoint), 0.0001);
            ratio = fabs(ratio - 0.50) * 2;
            ratio = pow(ratio, 5);
            hsv.val = std::min<double>(255, 255 * ratio);
            if(hsv.val < 15)
                hsv.val = 0;

            m_pixels.SetPixel(m_config.m_start_outer[i] + (aligned ? j : -j), hsv);
        }

        for(size_t j=0;j<LengthInner(i);j++)
        {
            bool aligned = m_config.m_start_outer[i] < m_config.m_end_outer[i];
            double this_index = (double)j / LengthInner(i);
            double ratio = std::max<double>(1 - fabs(this_index - m_midpoint), 0.0001);
            ratio = fabs(ratio - 0.50) * 2;
            ratio = pow(ratio, 5);
            hsv.val = std::min<double>(255, 255 * ratio);
            if(hsv.val < 15)
                hsv.val = 0;

            m_pixels.SetPixel(m_config.m_start_inner[i] + (aligned ? j : -j), hsv);
        }
    }
}
