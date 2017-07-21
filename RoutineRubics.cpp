#include <algorithm>

#include "RoutineRubics.h"
#include "PixelArray.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineRubics, CRoutineRubics::c_alloc_qty> CRoutineRubics::s_pool;

CRoutineRubics::CRoutineRubics(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_last_run = millis();
    m_midpoint = CPixelArray::Coordinate(1.0, 1.0);
}

CRoutineRubics::~CRoutineRubics()
{
}

void CRoutineRubics::Continue()
{
    if(millis() - m_last_swipe >= c_time_between_swipes_ms)
    {
        InitSwipe();
    }

    AdvanceSwipe();

    for(size_t i=0;i<GetSize();i++)
    {
        CPixelArray::Coordinate coord = GetCoordinate(i);

        size_t color_index;
        if(coord.x <= m_midpoint.x && coord.y <= m_midpoint.y)
        {
            color_index = 0;
        }
        else if(coord.x >= m_midpoint.x && coord.y <= m_midpoint.y)
        {
            color_index = 1;
        }
        else if(coord.x >= m_midpoint.x && coord.y >= m_midpoint.y)
        {
            color_index = 2;
        }
        else if(coord.x <= m_midpoint.x && coord.y >= m_midpoint.y)
        {
            color_index = 3;
        }

        SetPixel(i, ColorPallete::s_colors[color_index]);
    }

    m_last_run = millis();
}

size_t CRoutineRubics::Quadrant()
{
    if(m_midpoint.x > 0.0 && m_midpoint.y > 0.0)
    {
        return 0;
    }
    else if(m_midpoint.x < 0.0 && m_midpoint.y > 0.0)
    {
        return 1;
    }
    else if(m_midpoint.x < 0.0 && m_midpoint.y < 0.0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void CRoutineRubics::InitSwipe()
{
    switch(Quadrant())
    {
        case 0:
            if(rand() % 2 == 0)
            {
                m_swipe_direction = Left;
            }
            else
            {
                m_swipe_direction = Down;
            }
            break;
        case 1:
            if(rand() % 2 == 0)
            {
                m_swipe_direction = Right;
            }
            else
            {
                m_swipe_direction = Down;
            }
            break;
        case 2:
            if(rand() % 2 == 0)
            {
                m_swipe_direction = Right;
            }
            else
            {
                m_swipe_direction = Up;
            }
            break;
        case 3:
            if(rand() % 2 == 0)
            {
                m_swipe_direction = Left;
            }
            else
            {
                m_swipe_direction = Up;
            }
            break;
    }

    m_last_swipe = millis();
}

void CRoutineRubics::AdvanceSwipe()
{
    switch(m_swipe_direction)
    {
        case Left:
            m_midpoint.x -= (millis() - m_last_run) * c_swipe_distance_per_ms;
            break;
        case Right:
            m_midpoint.x += (millis() - m_last_run) * c_swipe_distance_per_ms;
            break;
        case Up:
            m_midpoint.y += (millis() - m_last_run) * c_swipe_distance_per_ms;
            break;
        case Down:
            m_midpoint.y -= (millis() - m_last_run) * c_swipe_distance_per_ms;
            break;
    }

    if(m_midpoint.x > 1.0)
    {
        m_midpoint.x = 1.0;
    }

    if(m_midpoint.x < -1.0)
    {
        m_midpoint.x = -1.0;
    }

    if(m_midpoint.y > 1.0)
    {
        m_midpoint.y = 1.0;
    }

    if(m_midpoint.y < -1.0)
    {
        m_midpoint.y = -1.0;
    }
}
