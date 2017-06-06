#include "Grid.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "GridMappings.h"

CMemoryPool<CGrid, 1> CGrid::s_pool;

CGrid::CGrid() :
    CPixelArrayLegs(GridMappings::Mappings())
{
//    StartRoutineBall(20, 2);
    //StartRoutineFire();
    //StartRoutineBalls(8);
//    StartRoutineGlare(ColorPallete::ChromeBlue, 40, true, 10);

    /*
    for(size_t shape=0;shape<c_num_shapes;shape++)
    {
        m_shapes[shape]->StartRoutineGlare(ColorPallete::Turquoise, 4, true, 1);
    }
    */
    
    /*
    for(size_t shape=0;shape<c_num_shapes;shape++)
    {
        m_shapes[shape]->StartRoutineGlareLegs(CRGB(ColorPallete::Turquoise), 4, true, 1);
    }
    */
}

CGrid::~CGrid()
{
}

void CGrid::Continue()
{
    if(RoutineDone() == true)
    {
        ExitRoutine();
        StartRoutineBalls(8);
    }

    if(millis() - m_routine_start_ms > 5000)
    {
        ShutdownRoutine();
    }

    CPixelArrayLegs::Continue();
}
