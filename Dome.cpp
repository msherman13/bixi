#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineSolid.h"

CMemoryPool<CDome, 1> CDome::s_pool;

CDome::CDome() :
    CPixelArray(DomeMappings::c_num_physical_pixels, DomeMappings::c_num_logical_pixels)
{
    // manually override locations and coordinates
    for(size_t i=0;i<GetSize();i++)
    {
        SetLocation(i, DomeMappings::GetLocation(i));
        SetCoordinate(i, DomeMappings::GetCoordinate(i));
    }

    //TransitionTo(new CRoutineRain(this, 5000, ColorPallete::Turquoise));
    TransitionTo(new CRoutineBalls(this, 5000, 8));
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
