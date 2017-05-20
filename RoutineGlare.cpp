#include <algorithm>

#include "RoutineGlare.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"

CRoutineGlare::CRoutineGlare(CPixelArray* pixels,
                             CRGB         base_color,
                             bool         forward,
                             uint32_t     period_sec) :
    CRoutine(pixels),
    m_base_color(rgb2hsv_approximate(base_color)),
    m_forward(forward),
    m_period_sec(period_sec)
{
}

CRoutineGlare::~CRoutineGlare()
{
}

void CRoutineGlare::Continue()
{
    uint32_t now = millis();

    double move_by = (double)(now - m_last_run) / (PeriodSec() * 1000);

    if(Forward() == true)
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

    m_last_run = now;

    CHSV hsv = m_base_color;

    for(size_t i=0;i<m_pixels.GetSize();i++)
    {
        double this_index = (double)i / m_pixels.GetSize();
        double ratio = std::max<double>(1 - fabs(this_index - m_midpoint), 0.0001);
        ratio = fabs(ratio - 0.50) * 2;
        ratio = pow(ratio, 5);
        hsv.val = std::min<double>(255, 255 * ratio);
        if(hsv.val < 15)
            hsv.val = 0;

        m_pixels.SetPixel(i, hsv);
    }
}
