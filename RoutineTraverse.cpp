#ifdef GEOM_LEGS_NECK

#include <algorithm>

#include "RoutineTraverse.h"
#include "PixelArray.h"

CMemoryPool<CRoutineTraverse, CRoutineTraverse::c_alloc_qty> CRoutineTraverse::s_pool;

CRoutineTraverse::CRoutineTraverse(CLegsAndNeck* pixels, CRGB rgb) :
    CRoutine(pixels),
    m_color(rgb),
    m_next_run(GetNextRunRand())
{
}

CRoutineTraverse::~CRoutineTraverse()
{
}

void CRoutineTraverse::Continue()
{
    size_t now = millis();

    if(m_run_done == true)
    {
        m_next_run = GetNextRunRand();
        m_run_done = false;
        m_in_run   = false;
        for(size_t i=0;i<LegsAndNeckMappings::c_num_neck_shapes+1;i++)
        {
            m_shapes_in_run[i] = nullptr;
        }
    }
    else if(m_in_run == false && now >= m_next_run)
    {
        m_in_run = true;
        m_curr_shape_off = -1;
        m_last_step_ms = now;
        m_run_done = false;
        size_t unit = rand() % (LegsAndNeckMappings::c_num_legs + LegsAndNeckMappings::c_num_necks);
        if(unit < LegsAndNeckMappings::c_num_legs)
        {
            for(size_t i=0;i<LegsAndNeckMappings::c_shapes_per_leg;i++)
            {
                m_shapes_in_run[i] = reinterpret_cast<CLegsAndNeck*>(GetPixels())->GetLegShape(unit, i);
            }
        }
        else
        {
            for(size_t i=0;i<LegsAndNeckMappings::c_shapes_per_neck;i++)
            {
                m_shapes_in_run[i] =
                    reinterpret_cast<CLegsAndNeck*>(GetPixels())->GetNeckShape(unit - LegsAndNeckMappings::c_num_legs, i);
            }
        }
    }

    SetAllPixels(m_color);

    if(m_in_run == true)
    {
        if(m_curr_shape_off < 0)
        {
            for(size_t i=0;i<LegsAndNeckMappings::c_shapes_per_neck;i++)
            {
                if(m_shapes_in_run[i] != nullptr)
                {
                    m_shapes_in_run[i]->SetAllPixels(CRGB::Black);
                }
            }
        }

        if(now - m_last_step_ms >= c_traversal_time_ms)
        {
            m_last_step_ms = now;
            m_curr_shape_off++;
        }

        if(m_curr_shape_off < 0)
        {
            return;
        }

        CPixelArray* shape = m_shapes_in_run[m_curr_shape_off];

        if(shape == nullptr)
        {
            m_run_done = true;
            return;
        }

        for(size_t i=0;i<LegsAndNeckMappings::c_shapes_per_neck;i++)
        {
            if(m_shapes_in_run[i] != nullptr)
            {
                m_shapes_in_run[i]->SetAllPixels(CRGB::Black);
            }
        }

        CPixelArray* buff = GetPixels();
        SetPixels(shape);
        SetAllPixels(m_color);
        SetPixels(buff);
    }
}

size_t CRoutineTraverse::GetNextRunRand()
{
    return millis() + c_min_delay_time_ms + (rand() % (c_max_delay_time_ms - c_min_delay_time_ms));
}

#endif // GEOM_LEGS_NECK
