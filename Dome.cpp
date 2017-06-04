#include "Dome.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "DomeMappings.h"

CDome::CDome() :
    CPixelArray(DomeMappings::Mappings())
{
    auto config = DomeMappings::Mappings();

    size_t leg_offset = 0;
    for(size_t i=0;i<DomeMappings::Mappings::c_num_shapes;i++)
    {
        m_shapes[i] = new CPixelArray(this,
                                      config.m_shape_length[i],
                                      config.m_shape_start[i],
                                      config.m_shape_num_legs[i],
                                      leg_offset);
        leg_offset += config.m_shape_num_legs[i];
    }

    //StartRoutineSolid(CRGB::Red);
    //StartRoutineBall(40, 2);
    //StartRoutineBalls(4);
    StartRoutineFire();
    //StartRoutineGlare(ColorPallete::ChromeBlue, 4, true, 10);

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

CDome::~CDome()
{
    for(size_t i=0;i<c_num_shapes;i++)
    {
        delete m_shapes[i];
    }
}

void CDome::Continue()
{
    for(size_t i=0;i<c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}
