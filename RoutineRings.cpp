#include <algorithm>
#include <cmath>

#include "RoutineRings.h"
#include "PixelArray.h"
#include "Math.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineRings, CRoutineRings::c_alloc_qty> CRoutineRings::s_pool;

CRoutineRings::CRoutineRings(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_last_run = millis();

    for(size_t i=0;i<c_num_circles;i++)
    {
        m_radius[i] = i * c_max_radius / c_num_circles;
        m_color[i]  = ColorPallete::s_colors[i];
    }

    m_midpoint.x = (float)(rand() % (int)(c_max_midpoint_x * 100)) / 100.0;
    m_midpoint.y = (float)(rand() % (int)(c_max_midpoint_y * 100)) / 100.0;
}

CRoutineRings::~CRoutineRings()
{
}

void CRoutineRings::RecalculateRadius()
{
    size_t now = millis();

    float move_by = (float)(now - m_last_run) * c_radius_delta;

    for(size_t i=0;i<c_num_circles;i++)
    {
        m_radius[i] += move_by;
        if(m_radius[i] > c_max_radius)
        {
            m_radius[i] = -0.20 + 0.01 * (rand() % 10);
            m_color[i]  = ColorPallete::s_colors[rand() % ColorPallete::Qty];
        }
    }

    m_last_run = millis();
}

CRGB CRoutineRings::RecalculateColor(size_t index)
{
    CRGB rgb(0, 0, 0);

    CPixelArray::Coordinate coord = GetCoordinate(index);

    float x_dist = std::max<float>(fabs(coord.x - m_midpoint.x), 0.0001);
    float y_dist = std::max<float>(fabs(coord.y - m_midpoint.y), 0.0001);

    float distance_from_midpoint = Math::fast_sqrt(powf(x_dist, 2) + powf(y_dist, 2));

    for(size_t i=0;i<c_num_circles;i++)
    {
        float radius   = m_radius[i];
        float distance = fabs(radius - distance_from_midpoint);
        if(distance < c_thickness)
        {
            rgb = m_color[i];
            break;
        }
    }

    return rgb;
}

void CRoutineRings::Continue()
{
    RecalculateRadius();

    for(size_t i=0;i<GetSize();i++)
    {
        CRGB rgb = RecalculateColor(i);
        SetPixel(i, rgb);
    }
}
