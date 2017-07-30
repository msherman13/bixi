#include <algorithm>

#include "RoutineCrawl.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"

CMemoryPool<CRoutineCrawl, CRoutineCrawl::c_alloc_qty> CRoutineCrawl::s_pool;

CRoutineCrawl::CRoutineCrawl(CPixelArray* pixels,
                             CRGB         base_color,
                             size_t       width,
                             size_t       start_offset,
                             bool         forward,
                             size_t       period_sec) :
    CRoutine(pixels),
    m_forward(forward),
    m_period_sec(period_sec),
    m_start((float)(start_offset) / GetSize()),
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

    int start = m_start * GetSize();

    for(int i=0;i<m_width;i++)
    {
        size_t index = (start + i) % GetSize();
        if(i % 3 == 0)
        {
            SetPixel(index, m_color);
        }
    }

    float move_by = (float)(now - m_last_run) / (m_period_sec * 1000);

    if(m_forward == true)
    {
        m_start += move_by;
        if(m_start > 1.00)
        {
            m_start = 0.00;
        }
    }
    else
    {
        m_start -= move_by;
        if(m_start < 0.00)
        {
            m_start = 1.00;
        }
    }

    m_last_run = now;
}
