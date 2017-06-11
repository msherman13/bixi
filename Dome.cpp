#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineSolid.h"

CMemoryPool<CDome, 1> CDome::s_pool;

CDome::CDome() :
    CPixelArrayLegs(DomeMappings::Mappings())
{
    // manually override coordinates since projection is incompatible with auto-map
    for(size_t i=0;i<GetSize();i++)
    {
        SetCoordinate(i, DomeMappings::GetCoordinate(i));
    }

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        size_t len        = DomeMappings::ShapeEndIndex(i) - DomeMappings::ShapeStartIndex(i) + 1;
        size_t offset     = DomeMappings::ShapeStartIndex(i);
        size_t num_legs   = DomeMappings::ShapeEndLeg(i) - DomeMappings::ShapeStartLeg(i) + 1;
        size_t leg_offset = DomeMappings::ShapeStartLeg(i);

        m_shapes[i] = new CPixelArrayLegs(this, len, offset, num_legs, leg_offset);
    }
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
    if(InTransition() == false && millis() - RoutineStartMs() > 20000)
    {
        TransitionTo(new CRoutineRain(this, 10000, ColorPallete::Turquoise));
    }

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}
