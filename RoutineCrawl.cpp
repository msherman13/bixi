#include <algorithm>

#include "RoutineCrawl.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"

CRoutineCrawl::CRoutineCrawl(CPixelArray* pixels,
                             CRGB         base_color,
                             size_t       width,
                             size_t       start_offset,
                             bool         forward,
                             uint32_t     period_sec) :
    CRoutine(pixels),
    m_forward(forward),
    m_delay_ms((period_sec * 1000) / m_pixels->GetSize())
{
    m_pixels->SetAllPixels(CRGB::Black);

    for(size_t i=start_offset;i<width+start_offset;i++)
    {
        m_pixels->SetPixel(i, base_color);
    }

    m_last_run = millis();
}

CRoutineCrawl::~CRoutineCrawl()
{
}

void CRoutineCrawl::Continue()
{
    uint32_t now = millis();
    if(now - m_last_run < m_delay_ms)
    {
        return;
    }
    m_last_run = now;

    m_pixels->Shift(m_forward, 1);
}
