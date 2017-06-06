#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"

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

    /*
    size_t leg_offset = 0;
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i] = new CPixelArray(this,
                                      DomeMappings::c_shape_length[i],
                                      DomeMappings::c_shape_start[i],
                                      DomeMappings::c_shape_num_legs[i],
                                      leg_offset);
        leg_offset += DomeMappings::c_shape_num_legs[i];
    }
    */

    //StartRoutineTest();
    //StartRoutineSolid(CRGB::Blue);
    //StartRoutineBall(40, 2);
    //StartRoutineBalls(10);
    //StartRoutineFire();
    //StartRoutineGlare(ColorPallete::ChromeBlue, 4, true, 10);

    /*
    for(size_t shape=0;shape<DomeMappings::c_num_shapes;shape++)
    {
        m_shapes[shape]->StartRoutineGlare(ColorPallete::Turquoise, 4, true, 1);
    }
    */
    
    /*
    for(size_t shape=0;shape<DomeMappings::c_num_shapes;shape++)
    {
        m_shapes[shape]->StartRoutineGlareLegs(CRGB(ColorPallete::Turquoise), 4, true, 1);
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

void CDome::ShutdownRoutine()
{
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->ShutdownRoutine();
    }

    CPixelArray::ShutdownRoutine();
}

bool CDome::RoutineDone()
{
    if(RunningRoutine() == true)
    {
        return CPixelArray::RoutineDone();
    }

    bool ret = true;
    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        ret &= m_shapes[i]->RoutineDone();
    }
    return ret;
}

void CDome::Continue()
{
    if(RoutineDone() == true)
    {
        ExitRoutine();
        StartRoutineBalls(8);
    }

    if(millis() - m_routine_start_ms > 5000)
    {
        for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
        {
            m_shapes[i]->ShutdownRoutine();
        }

        ShutdownRoutine();
    }

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}
