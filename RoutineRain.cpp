#include <algorithm>
#include <cmath>

#include "RoutineRain.h"
#include "PixelArray.h"
#include "Math.h"

CMemoryPool<CRoutineRain, CRoutineRain::c_alloc_qty> CRoutineRain::s_pool;

CRoutineRain::CRoutineRain(CPixelArray* pixels, CRGB rgb) :
    CRoutine(pixels),
    m_color(rgb2hsv_approximate(rgb))
{
    m_last_run = millis();

    for(size_t i=0;i<c_num_circles;i++)
    {
        m_radius[i] = i * c_max_radius / c_num_circles;
    }

    m_midpoint.x = (float)(rand() % (int)(c_max_midpoint_x * 100)) / 100.0;
    m_midpoint.y = (float)(rand() % (int)(c_max_midpoint_y * 100)) / 100.0;
}

CRoutineRain::~CRoutineRain()
{
}

void CRoutineRain::RecalculateRadius()
{
    size_t now = millis();

    float move_by = (float)(now - m_last_run) * c_radius_delta;

    for(size_t i=0;i<c_num_circles;i++)
    {
        m_radius[i] += move_by;
        if(m_radius[i] > c_max_radius)
        {
            m_radius[i] = -0.20 + 0.01 * (rand() % 10);
        }
    }

    m_last_run = millis();
}

CHSV CRoutineRain::RecalculateColor(size_t index)
{
    CHSV hsv = m_color;

    CPixelArray::Coordinate coord = GetCoordinate(index);

    float x_dist = std::max<float>(fabs(coord.x - m_midpoint.x), 0.0001);
    float y_dist = std::max<float>(fabs(coord.y - m_midpoint.y), 0.0001);

    float brightness = 0;
    float distance_from_midpoint = sqrtf(powf(x_dist, 2) + powf(y_dist, 2));

    for(size_t i=0;i<c_num_circles;i++)
    {
        float radius   = m_radius[i];
        float distance = fabs(radius - distance_from_midpoint);
        brightness    += Math::fast_pow(1.0 - distance, c_q);
    }

    brightness = std::min<float>(brightness, 1.0);

    hsv.val = brightness * 255;
    if(hsv.val < 15)
        hsv.val = 0;

    return hsv;
}

void CRoutineRain::Continue()
{
    RecalculateRadius();

    for(size_t i=0;i<GetSize();i++)
    {
        CHSV hsv = RecalculateColor(i);
        SetPixel(i, hsv);
    }
}
