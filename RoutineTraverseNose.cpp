#ifdef GEOM_HEAD

#include <algorithm>

#include "RoutineTraverseNose.h"
#include "RoutineCyclePallete.h"
#include "RoutineSolid.h"
#include "PixelArray.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineTraverseNose, CRoutineTraverseNose::c_alloc_qty> CRoutineTraverseNose::s_pool;

CRoutineTraverseNose::CRoutineTraverseNose(CHead* head, CPixelArrayLegs* nose) :
    CRoutine(nose),
    m_head(head),
    m_next_run(GetNextRunRand())
{
}

CRoutineTraverseNose::~CRoutineTraverseNose()
{
}

void CRoutineTraverseNose::Continue()
{
    //m_cycle->Continue();
    for(size_t i=0;i<m_head->GetNoseLeft()->GetSize();i++)
    {
        size_t index = i + m_head->GetNoseLeft()->GetOffset() - GetPixels()->GetOffset();
        SetPixel(index, ColorPallete::Mint);
    }
    for(size_t i=0;i<m_head->GetNoseRight()->GetSize();i++)
    {
        size_t index = i + m_head->GetNoseRight()->GetOffset() - GetPixels()->GetOffset();
        SetPixel(index, ColorPallete::Mint);
    }
    for(size_t i=0;i<m_head->GetNoseTop()->GetSize();i++)
    {
        size_t index = i + m_head->GetNoseTop()->GetOffset() - GetPixels()->GetOffset();
        SetPixel(index, ColorPallete::DarkPink);
    }

    size_t now = millis();

    if(m_run_done == true)
    {
        m_next_run = GetNextRunRand();
        m_run_done = false;
        m_in_run   = false;
    }
    else if(m_in_run == false && now >= m_next_run)
    {
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

        CPixelArrayLegs* shapes[3] = {};
        shapes[0] = m_head->GetNoseLeft();
        shapes[1] = m_head->GetNoseRight();
        shapes[2] = m_head->GetNoseTop();

        for(size_t i=0;i<3;i++)
        {
            CPixelArray* shape = shapes[i]->GetLeg(m_curr_shape_off);
            for(size_t i=0;i<shape->GetSize();i++)
            {
                size_t index = i + shape->GetOffset() - GetPixels()->GetOffset();
                SetPixel(index, CRGB::Black);
            }
        }
    }
}

size_t CRoutineTraverseNose::GetNextRunRand()
{
    return millis() + c_min_delay_time_ms + (rand() % (c_max_delay_time_ms - c_min_delay_time_ms));
}

#endif // GEOM_HEAD
