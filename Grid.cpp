#include "Grid.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "GridMappings.h"

CGrid::CGrid() :
    CPixelArray(GridMappings::Mappings())
{
    //StartRoutineBall(20, 2);
    StartRoutineBalls(5);
//    StartRoutineGlare(ColorPallete::ChromeBlue, 4, true, 10);

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
