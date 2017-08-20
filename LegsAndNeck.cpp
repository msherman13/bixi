#ifdef GEOM_LEGS_NECK

#include "LegsAndNeck.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineGlare.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineRings.h"
#include "RoutineSpin.h"
#include "RoutineSolid.h"
#include "RoutineIdle.h"
#include "RoutineCyclePallete.h"
#include "RoutineTraverse.h"
#include "RoutineSparkle.h"
#include "RoutineTest.h"

CMemoryPool<CLegsAndNeck, 1>  CLegsAndNeck::s_pool;
LegsAndNeckMappings::Mappings CLegsAndNeck::s_mappings;

CLegsAndNeck::CLegsAndNeck() :
    CPixelArrayLegs("LegsAndNeck", dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    // initialize legs
    for(size_t i=0;i<LegsAndNeckMappings::c_num_legs;i++)
    {
        for(size_t j=0;j<LegsAndNeckMappings::c_shapes_per_leg;j++)
        {
            m_leg_shapes[i][j] = GetLeg(i * LegsAndNeckMappings::c_shapes_per_leg + j);

            char name[32];
            sprintf(name, "Leg%uShape%u", i, j);
            m_leg_shapes[i][j]->SetName(name);
        }
    }

    for(size_t i=0;i<LegsAndNeckMappings::c_num_necks;i++)
    {
        for(size_t j=0;j<LegsAndNeckMappings::c_shapes_per_neck;j++)
        {
            size_t index = LegsAndNeckMappings::c_num_leg_shapes +
                           (i * LegsAndNeckMappings::c_shapes_per_neck + j);
            m_neck_shapes[i][j] = GetLeg(index);

            char name[32];
            sprintf(name, "Neck%uShape%u", i, j);
            m_neck_shapes[i][j]->SetName(name);
        }
    }

    // start at black
    m_curr_routine = RoutineSolid;
    SetRoutine(new CRoutineSolid(this, CRGB::Black));
}

CLegsAndNeck::~CLegsAndNeck()
{
}

void CLegsAndNeck::Continue()
{
    if(millis() >= m_routine_end_ms)
    {
        AdvanceRoutine();
    }

    CPixelArray::Continue();
}

CLegsAndNeck::Routine CLegsAndNeck::GetNextRoutine()
{
    Routine ret = m_curr_routine;

    while(ret == m_curr_routine)
    {
        ret = static_cast<Routine>(rand() % RoutineQty);
    }

    return ret;
}

void CLegsAndNeck::AdvanceRoutine()
{
    m_curr_routine = GetNextRoutine();

    switch(m_curr_routine)
    {
        case RoutineSolid:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineSolid(this, rgb), c_transition_time_ms);
            }
            break;

        case RoutineSparkle:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineSparkle(this, rgb), c_transition_time_ms);
            }
            break;

        case RoutineTraverse:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineTraverse(this, rgb), c_transition_time_ms);
            }
            break;

        case RoutineTest:
            TransitionTo(new CRoutineTest(this), c_transition_time_ms);
            break;

        default:
            CLogging::log("CLegsAndNeck::AdvanceRoutine: ERROR invalid routine type. exiting");
            exit(-1);
            break;
    }

    m_routine_end_ms = millis() + (rand() % (c_max_routine_time_ms - c_min_routine_time_ms)) + c_min_routine_time_ms;
}

CPixelArray* CLegsAndNeck::GetLegShape(size_t leg, size_t shape)
{
    return m_leg_shapes[leg][shape];
}

CPixelArray* CLegsAndNeck::GetNeckShape(size_t neck, size_t shape)
{
    return m_neck_shapes[neck][shape];
}

#endif // GEOM_LEGS_NECK
