#include <algorithm>
#include <cmath>

#include "RoutineAttack.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineAttack, CRoutineAttack::c_alloc_qty> CRoutineAttack::s_pool;

CRoutineAttack::CRoutineAttack(CPixelArray* pixels) :
    CRoutine(pixels)
{
}

CRoutineAttack::~CRoutineAttack()
{
}

void CRoutineAttack::Advance()
{
    size_t now = millis();

    if(now - m_streak_start > m_streak_duration + c_attack && now > m_next_streak_start)
    {
        m_streak_start    = now;
        m_streak_duration = c_attack + ((rand() % 3) + 3) * 1000;
        m_next_streak_start = now + m_streak_duration + (rand() % 3000);
        m_color           = rgb2hsv_approximate(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
    }
}

CRGB CRoutineAttack::CalculateColor()
{
    CHSV color = m_color;
    size_t now = millis();

    if((float)now - m_streak_start < c_attack)
    {
        color.v *= ((float)now - m_streak_start) / c_attack;
    }
    else if(now - m_streak_start > m_streak_duration + c_attack)
    {
        return CRGB::Black;
    }
    else
    {
        color.v *= std::max<float>(0.0, powf(1.0 - (float)(now - m_streak_start) / (m_streak_duration + c_attack), 2));
    }
    return color;
}

void CRoutineAttack::Continue()
{
    SetAllPixels(CalculateColor());

    Advance();
}
