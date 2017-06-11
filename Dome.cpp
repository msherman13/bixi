#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineRain.h"

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

    SetRoutine(new CRoutineRain(this, 0, ColorPallete::Turquoise));
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
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}
