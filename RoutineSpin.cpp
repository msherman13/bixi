#include <algorithm>
#include <cmath>

#include "RoutineSpin.h"
#include "PixelArray.h"
#include "Math.h"
#include "fixmath.h"

CMemoryPool<CRoutineSpin, CRoutineSpin::c_alloc_qty> CRoutineSpin::s_pool;

CRoutineSpin::CRoutineSpin(CPixelArray* pixels, size_t transition_time_ms, CRGB rgb) :
    CRoutine(pixels, transition_time_ms),
    m_color(rgb2hsv_approximate(rgb))
{
    m_last_run = millis();

    for(size_t i=0;i<c_num_spokes;i++)
    {
        m_theta[i] = i * c_max_theta / c_num_spokes;
    }
}

CRoutineSpin::~CRoutineSpin()
{
}

void CRoutineSpin::RecalculateThetas()
{
    size_t now = millis();

    float move_by = (float)(now - m_last_run) * c_theta_delta;

    for(size_t i=0;i<c_num_spokes;i++)
    {
        m_theta[i] += move_by;
        if(m_theta[i] > c_max_theta)
        {
            m_theta[i] -= c_max_theta;
        }
    }

    m_last_run = millis();
}

CHSV CRoutineSpin::RecalculateColor(size_t index)
{
    CHSV hsv = m_color;

    CPixelArray::Coordinate coord = GetCoordinate(index);

    float x = fabs(coord.x) < 0.0001 ? 0.0001 : coord.x;

    float theta = fix16_to_float(fix16_atan(fix16_from_float(coord.y / x)));
    if(coord.x < 0 && coord.y > 0)
    {
        theta += M_PI;
    }
    else if(coord.x < 0 && coord.y < 0)
    {
        theta += M_PI;
    }
    else if(coord.x > 0 && coord.y < 0)
    {
        theta += 2 * M_PI;
    }

    float brightness = 0;
    for(size_t i=0;i<c_num_spokes;i++)
    {
        float distance = std::min<float>(fabs(m_theta[i] - theta), fabs(m_theta[i] + c_max_theta - theta));
        distance       = std::min<float>(distance, fabs(m_theta[i] - c_max_theta - theta));
        //brightness    += Math::fast_pow((c_max_theta - distance) / c_max_theta, c_q);
        brightness    += Math::exp_by_squaring((c_max_theta - distance) / c_max_theta, c_q);
        //brightness = distance;
    }

    brightness = std::min<float>(brightness, 1.0);

    hsv.val = brightness * 255;
    if(hsv.val < 15)
        hsv.val = 0;

    return hsv;
}

void CRoutineSpin::Continue()
{
    RecalculateThetas();

    for(size_t i=0;i<GetSize();i++)
    {
        CHSV hsv = RecalculateColor(i);
        SetPixel(i, hsv);
    }
}
