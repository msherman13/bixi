#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineGlare.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineRings.h"
#include "RoutineSpin.h"
#include "RoutineSolid.h"
#include "RoutineCyclePallete.h"

CMemoryPool<CDome, 1>  CDome::s_pool;
DomeMappings::Mappings CDome::s_mappings;

CDome::CDome() :
    CPixelArrayLegs(dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    // initialize all shapes
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        size_t len        = DomeMappings::ShapeEndIndex(i) - DomeMappings::ShapeStartIndex(i) + 1;
        size_t offset     = DomeMappings::ShapeStartIndex(i);
        size_t num_legs   = DomeMappings::ShapeEndLeg(i) - DomeMappings::ShapeStartLeg(i) + 1;
        size_t leg_offset = DomeMappings::ShapeStartLeg(i);

        m_shapes[i] = new CPixelArrayLegs(this, len, offset, num_legs, leg_offset);
    }

    // initialize hexagon containers
    for(size_t i=0;i<DomeMappings::c_num_double_hex;i++)
    {
        m_inner_hex[i] = m_shapes[DomeMappings::c_inner_hex_index[i]];
        m_outer_hex[i] = m_shapes[DomeMappings::c_outer_hex_index[i]];
    }

    // non hex
    size_t index = 0;
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        bool is_hex = false;
        for(size_t j=0;j<DomeMappings::c_num_double_hex;j++)
        {
            is_hex |= i == DomeMappings::c_inner_hex_index[j];
            is_hex |= i == DomeMappings::c_outer_hex_index[j];
        }

        if(is_hex == false)
        {
            m_non_hex[index++] = m_shapes[i];
        }
    }

    SetRoutine(new CRoutineRings(this, 0));
    m_routine_end_ms = -1;
}

CDome::~CDome()
{
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        delete m_shapes[i];
    }
}

void CDome::ExitRoutine()
{
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->ExitRoutine();
    }

    CPixelArray::ExitRoutine();
}

void CDome::Continue()
{
    if(millis() >= m_routine_end_ms)
    {
        AdvanceRoutine();
    }

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}

CDome::Routine CDome::GetNextRoutine()
{
    Routine ret = m_dome_routine;

    while(ret == m_dome_routine)
    {
        switch(m_dome_routine)
        {
            case RoutineCyclePallete:
            case RoutineCyclePalleteDimensional:
            case RoutineCyclePalleteShapes:
            case RoutineRandomSolid:
                ret = static_cast<Routine>(c_solid_routine_qty + (rand() % c_complex_routine_qty));
                break;

            default:
                ret = static_cast<Routine>(rand() % c_solid_routine_qty);
                break;
        }
    }

    return ret;
}

void CDome::AdvanceRoutine()
{
    m_dome_routine = GetNextRoutine();

    switch(m_dome_routine)
    {
        case RoutineRandomSolid:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineSolid(this, c_transition_time_ms, rgb));
            }
            break;

        case RoutineCyclePallete:
            TransitionTo(new CRoutineCyclePallete(this, c_transition_time_ms, true, 15));
            break;

        case RoutineCyclePalleteDimensional:
            TransitionTo(new CRoutineCyclePallete(this, c_transition_time_ms, true, 40, true));
            break;

        case RoutineCyclePalleteShapes:
            TransitionTo(new CRoutineCyclePallete(this, c_transition_time_ms, true, 15, false));
            break;

        case RoutineSpin:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineSpin(this, c_transition_time_ms, rgb));
            }
            break;

        case RoutineBalls:
            TransitionTo(new CRoutineBalls(this, c_transition_time_ms, 8));
            break;

        case RoutineRain:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineRain(this, c_transition_time_ms, rgb));
            }
            break;

        case RoutineRings:
            {
                TransitionTo(new CRoutineRings(this, c_transition_time_ms));
            }
            break;
    }

    m_routine_end_ms = millis() + (rand() % (c_max_routine_time_ms - c_min_routine_time_ms)) + c_min_routine_time_ms;
}
