#ifdef GEOM_HEAD

#include <algorithm>

#include "RoutineTraverseNose.h"
#include "RoutineCyclePallete.h"
#include "PixelArray.h"

CMemoryPool<CRoutineTraverseNose, CRoutineTraverseNose::c_alloc_qty> CRoutineTraverseNose::s_pool;

CRoutineTraverseNose::CRoutineTraverseNose(CHead* head, CPixelArrayLegs* nose) :
    CRoutine(nose),
    m_head(head),
    m_next_run(GetNextRunRand())
{
    m_cycle = new CRoutineCyclePallete(nose, true, 60, false);
}

CRoutineTraverseNose::~CRoutineTraverseNose()
{
}

void CRoutineTraverseNose::Continue()
{
    m_cycle->Continue();

    size_t now = millis();

    if(m_run_done == true)
    {
        m_next_run = GetNextRunRand();
        m_run_done = false;
        m_in_run   = false;
    }
    else if(m_in_run == false && now >= m_next_run)
    {
        m_top = !m_top;
        m_in_run = true;
        m_curr_shape_off = 0;
        m_last_step_ms = now;
        m_run_done = false;
    }

    //SetAllPixels(m_color);

    if(m_in_run == true)
    {
        if(now - m_last_step_ms >= c_traversal_time_ms)
        {
            m_last_step_ms = now;
            m_curr_shape_off++;
        }

        if(m_curr_shape_off == m_head->GetNoseTop()->NumLegs())
        {
            m_run_done = true;
            return;
        }

        CPixelArrayLegs* shapes[2] = {};
        if(m_top == true)
        {
            shapes[0] = m_head->GetNoseTop();
            shapes[1] = nullptr;
        }
        else
        {
            shapes[0] = m_head->GetNoseLeft();
            shapes[1] = m_head->GetNoseRight();
        }

        for(size_t i=0;i<2;i++)
        {
            if(shapes[i] == nullptr)
            {
                continue;
            }

            CPixelArray* shape = shapes[i]->GetLeg(m_curr_shape_off);

            CPixelArray* buff = GetPixels();
            SetPixels(shape);
            SetAllPixels(CRGB::Black);
            SetPixels(buff);
        }
    }
}

size_t CRoutineTraverseNose::GetNextRunRand()
{
    return millis() + c_min_delay_time_ms + (rand() % (c_max_delay_time_ms - c_min_delay_time_ms));
}

#endif // GEOM_HEAD
