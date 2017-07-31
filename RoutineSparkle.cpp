#include <algorithm>
#include <cmath>

#include "RoutineSparkle.h"
#include "PixelArray.h"

CMemoryPool<CRoutineSparkle, CRoutineSparkle::c_alloc_qty> CRoutineSparkle::s_pool;

CRoutineSparkle::CRoutineSparkle(CPixelArray* pixels, CRGB rgb) :
    CRoutine(pixels),
    m_color(rgb2hsv_approximate(rgb))
{
    m_last_run = millis();
    m_num_lit = c_max_num_lit;
    m_num_lit = std::min<size_t>(GetSize() / 5, m_num_lit);

    for(size_t i=0;i<m_num_lit;i++)
    {
        m_release_ms[i] = rand() % c_release_ms;
        m_lit[i] = rand() % GetSize();
    }
}

CRoutineSparkle::~CRoutineSparkle()
{
}

void CRoutineSparkle::Continue()
{
    size_t now = millis();

    SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_num_lit;i++)
    {
        if(m_release_ms[i] <= now - m_last_run)
        {
            m_release_ms[i] = c_release_ms;
            m_lit[i]        = rand() % GetSize();
        }
        else
        {
            m_release_ms[i] -= now - m_last_run;
        }

        float brightness_mod = (float)(m_release_ms[i]) / c_release_ms;
        CHSV color = m_color;
        color.v = brightness_mod * 255;

        SetPixel(m_lit[i], color);
    }

    m_last_run = now;
}
