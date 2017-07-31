#include <algorithm>
#include <cmath>

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
    CRoutineSparkle(pixels, CRGB::White),
    m_forward(forward),
    m_period_sec(period_sec),
    m_start((float)(start_offset) / GetSize()),
    m_width(width),
    m_color(rgb2hsv_approximate(base_color))
{
    m_last_run = millis();
}

CRoutineCrawl::~CRoutineCrawl()
{
}

void CRoutineCrawl::Advance()
{
    size_t now = millis();

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

CRGB CRoutineCrawl::CalculateColor(size_t index, bool& in_range)
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

    if(relative_index % 3 == 0)
    {
        CHSV color = m_color;
        color.v = ((float)relative_index / m_width) * 255;
        return color;
    }

    return CRGB::Black;
}

void CRoutineCrawl::Continue()
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
