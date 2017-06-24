#include <algorithm>

#include "RoutineCyclePallete.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "Logging.h"
#include "Math.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineCyclePallete, CRoutineCyclePallete::c_alloc_qty> CRoutineCyclePallete::s_pool;

CRoutineCyclePallete::CRoutineCyclePallete(CPixelArray* pixels,
                                           bool         forward,
                                           size_t       period_sec,
                                           bool         dimensional) :
    CRoutine(pixels),
    m_forward(forward),
    m_period_sec(period_sec),
    m_dimensional(dimensional)
{
    m_last_run = millis();
}

CRoutineCyclePallete::~CRoutineCyclePallete()
{
}

void CRoutineCyclePallete::Continue()
{
    size_t now = millis();

    float move_by = (float)(now - m_last_run) / (m_period_sec * 1000);

    if(m_forward == true)
    {
        m_midpoint += move_by;
        if(m_midpoint > 1.0)
        {
            m_midpoint -= 1.0;
        }
    }
    else
    {
        m_midpoint -= move_by;
        if(m_midpoint < 0.0)
        {
            m_midpoint += 1.0;
        }
    }

    m_last_run = now;

    for(size_t i=0;i<GetSize();i++)
    {
        float this_index;
        if(m_dimensional)
        {
            this_index = (GetCoordinate(i).x + 1.00) / 2.00;
        }
        else
        {
            this_index = (float)i / GetSize();
        }

        CRGB color;

        for(size_t color_index=0;color_index<ColorPallete::Qty;color_index++)
        {
            float color_loc = (float)color_index / ColorPallete::Qty + m_midpoint;

            float distance = fabs(this_index - color_loc);
            float weight   = fabs(1.0 - distance);
            weight = fabs(weight - 0.50) * 2;
            weight *= weight;
            weight *= weight;
            color = CPixelArray::Blend(color, ColorPallete::s_colors[color_index], weight);
        }

        SetPixel(i, color);
    }
}
