#ifdef GEOM_HEAD

#include <algorithm>

#include "RoutineTraverseNose.h"
#include "RoutineCyclePallete.h"
#include "RoutineSolid.h"
#include "PixelArray.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineTraverseNose, CRoutineTraverseNose::c_alloc_qty> CRoutineTraverseNose::s_pool;

CRoutineTraverseNose::CRoutineTraverseNose(CHead* head) :
    CRoutine(head),
    m_head(head),
    m_next_run(GetNextRunRand())
{
}

CRoutineTraverseNose::~CRoutineTraverseNose()
{
}

CRGB CRoutineTraverseNose::GetColor(size_t shape_index)
{
    switch(shape_index)
    {
        case 0:
            [[fallthrough]]

        case 1:
            return ColorPallete::Mint;

        default:
            return ColorPallete::Blue;
    }
}

void CRoutineTraverseNose::Continue()
{
    for(size_t i=0;i<m_head->GetNoseLeft()->GetSize();i++)
    {
        size_t index = i + m_head->GetNoseLeft()->GetOffset();
        SetPixel(index, GetColor(0));
    }
    for(size_t i=0;i<m_head->GetNoseRight()->GetSize();i++)
    {
        size_t index = i + m_head->GetNoseRight()->GetOffset();
        SetPixel(index, GetColor(1));
    }
    for(size_t i=0;i<m_head->GetNoseTop()->GetSize();i++)
    {
        size_t index = i + m_head->GetNoseTop()->GetOffset();
        SetPixel(index, GetColor(2));
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
        m_curr_shape_off = -1;
        m_last_step_ms = now;
        m_run_done = false;
    }

    CPixelArrayLegs* shapes[3] = {};
    shapes[0] = m_head->GetNoseLeft();
    shapes[1] = m_head->GetNoseRight();
    shapes[2] = m_head->GetNoseTop();

    if(m_in_run == true)
    {
        if(m_curr_shape_off < 0)
        {
            for(size_t i=0;i<3;i++)
            {
                shapes[i]->SetAllPixels(CRGB::Black);
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

        if(m_curr_shape_off == m_head->GetNoseTop()->NumLegs())
        {
            m_run_done = true;
            return;
        }

        for(size_t i=0;i<3;i++)
        {
            shapes[i]->SetAllPixels(CRGB::Black);

            if(m_curr_shape_off >= shapes[i]->NumLegs())
            {
                continue;
            }

            CPixelArray* shape = shapes[i]->GetLeg(m_curr_shape_off);
            for(size_t j=0;j<shape->GetSize();j++)
            {
                size_t index = j + shape->GetOffset();
                SetPixel(index, GetColor(i));
            }
        }
    }
}

size_t CRoutineTraverseNose::GetNextRunRand()
{
    return millis() + c_min_delay_time_ms + (rand() % (c_max_delay_time_ms - c_min_delay_time_ms));
}

#endif // GEOM_HEAD
