#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineGlare.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineSpin.h"
#include "RoutineSolid.h"

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

    /*
    for(size_t i=1;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->TransitionTo(new CRoutineSolid(m_shapes[i], 5000, ColorPallete::DarkPink));
    }
    m_shapes[0]->TransitionTo(new CRoutineSolid(m_shapes[0], 5000, CRGB::White));
    */
    //TransitionTo(new CRoutineSolid(this, 10000, ColorPallete::DarkPink));
    //TransitionTo(new CRoutineBalls(this, 10000, 8));
    TransitionTo(new CRoutineSpin(this, 10000, ColorPallete::DarkPink));
    /*
    for(size_t i=0;i<DomeMappings::c_num_double_hex;i++)
    {
        m_inner_hex[i]->TransitionTo(new CRoutineSolid(m_inner_hex[i], 10000, ColorPallete::Mint));
        m_outer_hex[i]->TransitionTo(new CRoutineSolid(m_outer_hex[i], 10000, ColorPallete::Mint));
    }

    for(size_t i=0;i<DomeMappings::c_num_non_hex;i++)
    {
        m_non_hex[i]->TransitionTo(new CRoutineSpin(m_non_hex[i], 10000, ColorPallete::DarkPink));
    }
    */
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
    //if(InTransition() == false && millis() - m_routine->StartMs() > 20000)
    //{
    //    TransitionTo(new CRoutineSpin(this, 10000, ColorPallete::Mint));
    //}

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}
