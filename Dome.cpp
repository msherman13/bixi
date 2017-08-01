#ifdef GEOM_DOME

#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineGlare.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineSparkle.h"
#include "RoutineRings.h"
#include "RoutineSpin.h"
#include "RoutineSolid.h"
#include "RoutineCrawl.h"
#include "RoutineStars.h"
#include "RoutineTest.h"
#include "RoutineRubics.h"
#include "RoutineIdle.h"
#include "RoutineCyclePallete.h"

CMemoryPool<CDome, 1>  CDome::s_pool;
DomeMappings::Mappings CDome::s_mappings;

CDome::CDome() :
    CPixelArrayLegs("Dome", dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    // initialize all shapes
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        size_t len        = DomeMappings::ShapeEndIndex(i) - DomeMappings::ShapeStartIndex(i) + 1;
        size_t offset     = DomeMappings::ShapeStartIndex(i);
        size_t num_legs   = DomeMappings::ShapeEndLeg(i) - DomeMappings::ShapeStartLeg(i) + 1;
        size_t leg_offset = DomeMappings::ShapeStartLeg(i);

        char name[16];
        sprintf(name, "DomeShape%u", i);
        m_shapes[i] = new CPixelArrayLegs(name, this, len, offset, num_legs, leg_offset);
    }

    // start at black, immediately transition out
    SetRoutine(new CRoutineSolid(this, CRGB::Black));
    m_dome_routine = RoutineSolid;
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->SetRoutine(new CRoutineIdle(m_shapes[i]));
    }
}

CDome::~CDome()
{
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        delete m_shapes[i];
    }
}

bool CDome::IsShapeRoutine(Routine routine)
{
    switch(routine)
    {
        case RoutineGlareShapes:
        case RoutineCrawlHex:
        case RoutineStars:
            return true;

        default:
            return false;
    }
}

void CDome::Continue()
{
    if(millis() >= m_routine_end_ms)
    {
        AdvanceRoutine();
    }

    // hack: this is only necessary so the transition blending doesn't do a hard overwrite
    if(IsShapeRoutine(m_dome_routine) == true)
    {
        for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
        {
            m_shapes[i]->Continue();
        }

        CPixelArray::Continue();
    }
    else
    {
        CPixelArray::Continue();

        for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
        {
            m_shapes[i]->Continue();
        }
    }
}

CDome::Routine CDome::GetNextRoutine()
{
    Routine ret = m_dome_routine;

    while(ret == m_dome_routine)
    {
        switch(m_dome_routine)
        {
            case RoutineBalls:
                return RoutineSolid;

            case RoutineCyclePallete:
            case RoutineCyclePalleteDimensional:
            case RoutineCyclePalleteShapes:
            case RoutineSolid:
                ret = static_cast<Routine>(c_solid_routine_qty + (rand() % c_complex_routine_qty));
                break;

            default:
                ret = static_cast<Routine>(rand() % c_solid_routine_qty);
                break;
        }
    }

    return ret;
}

void CDome::TransitionOut()
{
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        if(m_shapes[i]->InTransition() == false)
        {
            m_shapes[i]->TransitionTo(new CRoutineIdle(this), c_transition_time_ms);
        }
    }

    if(InTransition() == false)
    {
        TransitionTo(new CRoutineIdle(this), c_transition_time_ms);
    }
}

void CDome::AdvanceRoutine()
{
    m_dome_routine = GetNextRoutine();

    switch(m_dome_routine)
    {
        case RoutineSolid:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineSolid(this, rgb), c_transition_time_ms);
            }
            break;

        case RoutineCyclePallete:
            TransitionTo(new CRoutineCyclePallete(this, true, 15), c_transition_time_ms);
            break;

        case RoutineCyclePalleteDimensional:
            TransitionTo(new CRoutineCyclePallete(this, true, 40, true), c_transition_time_ms);
            break;

        case RoutineCyclePalleteShapes:
            TransitionTo(new CRoutineCyclePallete(this, true, 15, false), c_transition_time_ms);
            break;

        case RoutineSpin:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineSpin(this, rgb), c_transition_time_ms);
            }
            break;

        case RoutineRubics:
            TransitionTo(new CRoutineRubics(this), c_transition_time_ms);
            break;

        case RoutineBalls:
            TransitionTo(new CRoutineBalls(this, 6), c_transition_time_ms);
            break;

        case RoutineRain:
            {
                CRGB rgb(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                TransitionTo(new CRoutineRain(this, rgb), c_transition_time_ms);
            }
            break;

        case RoutineRings:
            TransitionTo(new CRoutineRings(this), c_transition_time_ms);
            break;

        case RoutineTest:
            TransitionTo(new CRoutineTest(this), c_transition_time_ms);
            break;

        case RoutineGlareShapes:
            for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
            {
                CRGB color(ColorPallete::s_colors[i % ColorPallete::Qty]);
                m_shapes[i]->TransitionTo(new CRoutineGlare(m_shapes[i],
                                                            color,
                                                            2,
                                                            true,
                                                            5), c_transition_time_ms);
            }
            break;

        case RoutineCrawlHex:
            {
                CRGB crawl_color(ColorPallete::s_colors[rand() % ColorPallete::Qty]);
                for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
                {
                    if(DomeMappings::ShapeIsHex(i))
                    {
                        m_shapes[i]->TransitionTo(new CRoutineCrawl(m_shapes[i],
                                                                    crawl_color,
                                                                    m_shapes[i]->GetSize() / 4,
                                                                    i == 6 || i == 7 || i == 15 || i == 16 ? m_shapes[i]->GetSize()/2 : 0,
                                                                    true,
                                                                    10), c_transition_time_ms);
                    }
                    else
                    {
                        m_shapes[i]->TransitionTo(new CRoutineSparkle(m_shapes[i], CRGB::White), c_transition_time_ms);
                    }
                }
            }
            break;

        case RoutineStars:
            {
                for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
                {
                    m_shapes[i]->TransitionTo(new CRoutineStars(m_shapes[i]), c_transition_time_ms);
                }
            }
            break;

        default:
            char logstr[256];
            sprintf(logstr, "CDome::AdvanceRoutine: ERROR invalid routine (%d), exiting", m_dome_routine);
            CLogging::log(logstr);
            exit(-1);
            break;
    }

    TransitionOut();

    m_routine_end_ms = millis() + (rand() % (c_max_routine_time_ms - c_min_routine_time_ms)) + c_min_routine_time_ms;
}

#endif // GEOM_DOME
