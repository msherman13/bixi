#include <algorithm>

#include "RoutineSticks.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "Logging.h"

CRoutineSticks::CRoutineSticks(CPixelArray* pixels,
                               size_t       num_sticks) :
    CRoutine(pixels),
    m_num_sticks(num_sticks)
{
    for(size_t i=0;i<num_sticks;i++)
    {
        m_arrays[i]        = new CPixelArray(m_pixels->GetSize());
        uint32_t period    = (rand() % (c_max_period_sec - c_min_period_sec + 1)) + c_min_period_sec;
        double   width_pct = fmod(rand(), (c_max_width_pct - c_min_width_pct + 0.01)) + c_min_width_pct;
        size_t   width     = width_pct * m_pixels->GetSize();
        size_t   offset    = rand() % m_pixels->GetSize();
        auto     color     = ColorPallete::s_colors[i % ColorPallete::Qty];
        m_arrays[i]->StartRoutineCrawl(color, width, offset, i % 2 == 0, period);
    }
}

CRoutineSticks::~CRoutineSticks()
{
    for(size_t i=0;i<m_num_sticks; i++)
    {
        delete m_arrays[i];
    }
}

void CRoutineSticks::Continue()
{
    m_pixels->SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_num_sticks;i++)
    {
        m_arrays[i]->Continue();
        m_pixels->SmartCopy(m_arrays[i], m_arrays[i]->GetSize(), 0);
    }
}
