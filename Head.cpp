#ifdef GEOM_HEAD

#include "Head.h"
#include "Logging.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "RoutineGlare.h"
#include "RoutineBalls.h"
#include "RoutineRain.h"
#include "RoutineRings.h"
#include "RoutineSpin.h"
#include "RoutineSolid.h"
#include "RoutineIdle.h"
#include "RoutineCyclePallete.h"
#include "RoutineFire.h"
#include "RoutineTraverseNose.h"
#include "RoutineTest.h"

CMemoryPool<CHead, 1>  CHead::s_pool;
HeadMappings::Mappings CHead::s_mappings;

const char* CHead::sShape(Shape shape)
{
    switch(shape)
    {
        case MouthLeft:     return "MouthLeft";
        case MouthRight:    return "MouthRight";
        case NoseLeft:      return "NoseLeft";
        case CheekLeft:     return "CheekLeft";
        case NoseRight:     return "NoseRight";
        case CheekRight:    return "CheekRight";
        case NoseTop:       return "NoseTop";
        case FlameLeft:     return "FlameLeft";
        case EyeLeft:       return "EyeLeft";
        case BrowLeft:      return "BrowLeft";
        case FlameRight:    return "FlameRight";
        case EyeRight:      return "EyeRight";
        case BrowRight:     return "BrowRight";
        default:            return "Undef";
    }
}

CHead::CHead() :
    CPixelArrayLegs("Head", dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    // initialize shapes
    size_t leg_offset = 0;
    for(size_t i=0;i<ShapeQty;i++)
    {
        size_t len = HeadMappings::ShapeSize(i);
        size_t offset = HeadMappings::ShapeStartIndex(i);
        size_t num_legs = HeadMappings::ShapeNumLegs(i);
        m_shapes[i] = new CPixelArrayLegs(sShape(static_cast<Shape>(i)),
                                          this,
                                          len,
                                          offset,
                                          num_legs,
                                          leg_offset);
        leg_offset += num_legs;
    }

    // start fire shapes
    m_shapes[FlameLeft]->SetRoutine(new CRoutineFire(m_shapes[FlameLeft]));
    m_shapes[FlameRight]->SetRoutine(new CRoutineFire(m_shapes[FlameRight]));
    m_shapes[BrowLeft]->SetRoutine(new CRoutineFire(m_shapes[BrowLeft]));
    m_shapes[BrowRight]->SetRoutine(new CRoutineFire(m_shapes[BrowRight]));
    m_shapes[CheekLeft]->SetRoutine(new CRoutineFire(m_shapes[CheekLeft]));
    m_shapes[CheekRight]->SetRoutine(new CRoutineFire(m_shapes[CheekRight]));

    SetRoutine(new CRoutineTraverseNose(this));
    m_shapes[EyeLeft]->SetRoutine(new CRoutineSolid(m_shapes[EyeLeft], ColorPallete::Blue));
    m_shapes[EyeRight]->SetRoutine(new CRoutineSolid(m_shapes[EyeRight], ColorPallete::Blue));
    m_shapes[MouthLeft]->SetRoutine(new CRoutineSolid(m_shapes[MouthLeft], ColorPallete::DarkPink));
    m_shapes[MouthRight]->SetRoutine(new CRoutineSolid(m_shapes[MouthRight], ColorPallete::DarkPink));
}

CHead::~CHead()
{
}

void CHead::Continue()
{
    for(size_t i=0;i<ShapeQty;i++)
    {
        m_shapes[i]->Continue();
    }

    CPixelArray::Continue();
}
#endif // GEOM_HEAD
