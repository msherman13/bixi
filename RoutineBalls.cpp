#include <algorithm>

#include "RoutineBall.h"
#include "RoutineBalls.h"

CRoutineBalls::CRoutineBalls(CPixelArray* pixels, size_t num_balls) :
    CRoutine(pixels),
    m_num_balls(num_balls > c_max_num_balls ? c_max_num_balls : num_balls),
    m_buffer(*pixels)
{
    InitBalls();
}

void CRoutineBalls::InitBalls()
{
    for(size_t i=0;i<m_num_balls;i++)
    {
        size_t q      = c_min_q + (rand() % (c_max_q - c_min_q + 1));
        size_t period = c_min_period + (rand() % (c_max_period - c_min_period + 1));
        m_balls[i]    = new CRoutineBall(&m_buffer, q, period);
    }
}

CRoutineBalls::~CRoutineBalls()
{
    for(size_t i=0;i<m_num_balls;i++)
    {
        delete m_balls[i];
    }
}

void CRoutineBalls::Continue()
{
    m_pixels->SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_num_balls;i++)
    {
        m_balls[i]->Continue();
        m_pixels->SmartCopy(&m_buffer, m_buffer.GetSize());
    }
}
