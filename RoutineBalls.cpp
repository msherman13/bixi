#include <algorithm>

#include "RoutineBall.h"
#include "RoutineBalls.h"

CRoutineBalls::CRoutineBalls(CPixelArray* pixels, size_t num_balls) :
    CRoutine(pixels),
    m_num_balls(num_balls),
    m_buffer(pixels->GetRaw(), pixels->GetSize())
{
    InitBalls();
}

void CRoutineBalls::InitBalls()
{
    size_t m_num_balls = std::min<size_t>(m_num_balls, size_t(c_max_num_balls));

    for(size_t i=0;i<m_num_balls;i++)
    {
        size_t q      = c_min_q + (rand() % (c_max_q - c_min_q + 1));
        size_t period = c_min_period + (rand() % (c_max_period - c_min_period + 1));
        m_balls[i]    = new CRoutineBall(m_pixels, q, period);
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
    m_buffer.SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_num_balls;i++)
    {
        m_balls[i]->Continue();
        m_buffer.SmartCopy(m_balls[i]->GetPixels(), m_balls[i]->GetPixels()->GetSize());
    }
    m_pixels->Copy(&m_buffer, m_buffer.GetSize());
}
