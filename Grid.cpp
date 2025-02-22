#include "Grid.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineSolid.h"
#include "RoutineBall.h"
#include "RoutineCrawl.h"
#include "RoutineRain.h"

CMemoryPool<CGrid, 1>  CGrid::s_pool;
GridMappings::Mappings CGrid::s_mappings;

CGrid::CGrid() :
    CPixelArrayLegs("Grid", dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    if(InTransition() == false)
    {
        SetRoutine(new CRoutineRain(this, ColorPallete::Mint));
        //TransitionTo(new CRoutineCrawl(this, 5000, CRGB::Blue, 16, 0, true, 20));
        //TransitionTo(new CRoutineSolid(this, 5000, CRGB::Blue));
    }
}

CGrid::~CGrid()
{
}

void CGrid::Continue()
{
    CPixelArrayLegs::Continue();
}
