#include <algorithm>

#include "Logging.h"
#include "RoutineBall.h"
#include "RoutineBalls.h"

CMemoryPool<CRoutineBalls, CRoutineBalls::c_alloc_qty> CRoutineBalls::s_pool;

CRoutineBalls::CRoutineBalls(CPixelArray* pixels, size_t num_balls) :
    CRoutine(pixels),
    m_num_balls(num_balls > c_max_num_balls ? c_max_num_balls : num_balls)
{
    InitBalls();
}

void CRoutineBalls::InitBalls()
{
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
    for(size_t i=0;i<m_num_balls;i++)
    {
        m_balls[i]->RecalculateMidpoint();
    }
    for(size_t i=0;i<m_pixels->GetSize();i++)
    {
        for(size_t j=0;j<m_num_balls;j++)
        {
            CHSV hsv = m_balls[j]->RecalculateColor(i);
            if(j == 0 || hsv.v > 50)
            {
                m_pixels->SetPixel(i, hsv);
            }
        }
    }
}
