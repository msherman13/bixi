#include <algorithm>

#include "RoutineGlare.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "Logging.h"

CMemoryPool<CRoutineGlare, CRoutineGlare::c_alloc_qty> CRoutineGlare::s_pool;

CRoutineGlare::CRoutineGlare(CPixelArray* pixels,
                             CRGB         base_color,
                             size_t       q,
                             bool         forward,
                             size_t     period_sec) :
    CRoutine(pixels),
    m_base_color(rgb2hsv_approximate(base_color)),
    m_q(q),
    m_forward(forward),
    m_period_sec(period_sec)
{
    m_last_run = millis();
}

CRoutineGlare::~CRoutineGlare()
{
    CLogging::log("CRoutineGlare::~CRoutineGlare");
}

void CRoutineGlare::Continue()
{
    size_t now = millis();

    float move_by = (float)(now - m_last_run) / (PeriodSec() * 1000);

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

    for(size_t i=0;i<GetSize();i++)
    {
        float this_index = (float)i / GetSize();
        float ratio = std::max<float>(1 - fabs(this_index - m_midpoint), 0.0001);
        ratio = fabs(ratio - 0.50) * 2;
        ratio = powf(ratio, m_q);
        hsv.val = std::min<float>(255, 255 * ratio);
        if(hsv.val < 15)
            hsv.val = 0;

        SetPixel(i, hsv);
    }
}
