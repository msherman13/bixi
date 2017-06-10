#include <algorithm>

#include "RoutineCrawl.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"

CMemoryPool<CRoutineCrawl, CRoutineCrawl::c_alloc_qty> CRoutineCrawl::s_pool;

CRoutineCrawl::CRoutineCrawl(CPixelArray* pixels,
                             size_t       transition_time_ms,
                             CRGB         base_color,
                             size_t       width,
                             size_t       start_offset,
                             bool         forward,
                             size_t       period_sec) :
    CRoutine(pixels, transition_time_ms),
    m_forward(forward),
    m_period_sec(period_sec),
    m_midpoint((float)(start_offset + width/2) / GetSize()),
    m_width(width),
    m_color(base_color)
{
    m_last_run = millis();
}

CRoutineCrawl::~CRoutineCrawl()
{
}

void CRoutineCrawl::Continue()
{
    SetAllPixels(CRGB::Black);

    size_t now = millis();

    int mid = m_midpoint * GetSize();
    int start = mid - m_width / 2;
    int end = mid + m_width / 2;

    for(int i=start;i<end;i++)
    {
        size_t index = i < 0 ? i + GetSize() : i;
        SetPixel(index, m_color);
    }

    float move_by = (float)(now - m_last_run) / (m_period_sec * 1000);

    if(m_forward == true)
    {
        m_midpoint += move_by;
        if(m_midpoint > 1.00)
        {
            m_midpoint = 0.00;
        }
    }
    else
    {
        m_midpoint -= move_by;
        if(m_midpoint < 0.00)
        {
            m_midpoint = 1.00;
        }
    }

    m_last_run = now;
}
