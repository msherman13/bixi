#include <algorithm>
#include <cmath>

#include "RoutineStars.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineStars, CRoutineStars::c_alloc_qty> CRoutineStars::s_pool;

CRoutineStars::CRoutineStars(CPixelArray* pixels) :
    CRoutineSparkle(pixels, CRGB::White)
{
    m_last_run = millis();
}

CRoutineStars::~CRoutineStars()
{
}

void CRoutineStars::Advance()
{
    size_t now = millis();

    if(now - m_streak_start > m_streak_duration + c_attack)// && rand() % 1000 == 0)
    {
        m_streak_start    = now;
        m_streak_duration = c_attack + ((rand() % 5) + 1) * 1000;
        m_width           = std::min<size_t>(GetSize() / 5, (rand() % 40) + 10);
        m_start           = (float)(rand() % GetSize()) / GetSize();
        m_forward         = rand() % 2 == 0;
        m_color           = rgb2hsv_approximate(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
    }
    else
    {
        float max     = 10.0 / GetSize();
        float move_by = max * powf((float)(m_streak_duration + c_attack - (now - m_streak_start)) / (m_streak_duration + c_attack), 8);

        if(m_forward == true)
        {
            m_start += move_by;
            if(m_start > 1.0)
            {
                m_start = 0.00;
            }
        }
        else
        {
            m_start -= move_by;
            if(m_start < 0.00)
            {
                m_start = 1.0;
            }
        }
    }

    m_last_run = now;
}

CRGB CRoutineStars::CalculateColor(size_t index, bool& in_range)
{
    int start = m_start * GetSize();
    int relative_index = index - start;
    if(relative_index < 0)
    {
        relative_index += GetSize();
    }
    if(relative_index >= m_width)
    {
        in_range = false;
        return CRGB::Black;
    }

    in_range = true;

    CHSV color = m_color;
    color.v = ((float)relative_index / m_width) * 255;
    if(m_forward == false)
    {
        color.v = 255 - color.v;
    }
    if((float)millis() - m_streak_start < c_attack)
    {
        color.v *= ((float)millis() - m_streak_start) / c_attack;
    }
    else if(millis() > m_streak_start + m_streak_duration + c_attack)
    {
        in_range = false;
        return CRGB::Black;
    }
    else
    {
        color.v *= 1.0 - ((float)millis() - m_streak_start - c_attack) / m_streak_duration;
    }
    return color;
}

void CRoutineStars::Continue()
{
    CRoutineSparkle::Continue();

    for(int i=0;i<GetSize();i++)
    {
        bool in_range;
        CRGB color = CalculateColor(i, in_range);

        if(in_range == false)
        {
            continue;
        }

        SetPixel(i, color);
    }

    Advance();
}
