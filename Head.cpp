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

CMemoryPool<CHead, 1>  CHead::s_pool;
HeadMappings::Mappings CHead::s_mappings;

CHead::CHead() :
    CPixelArrayLegs("Head", dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    // initialize shapes
    size_t len = HeadMappings::ShapeSize(MouthLeft);
    size_t offset = HeadMappings::ShapeStartIndex(MouthLeft);
    size_t num_legs = HeadMappings::ShapeNumLegs(MouthLeft);
    size_t leg_offset = 0;
    m_mouth_left = new CPixelArrayLegs("HeadMouthLeft", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(MouthRight);
    offset = HeadMappings::ShapeStartIndex(MouthRight);
    num_legs = HeadMappings::ShapeNumLegs(MouthRight);
    //leg_offset = 0;
    m_mouth_right = new CPixelArrayLegs("HeadMouthRight", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    offset = HeadMappings::ShapeStartIndex(NoseLeft);
    len = HeadMappings::ShapeSize(NoseLeft) +
          HeadMappings::ShapeSize(NoseRight) +
          HeadMappings::ShapeSize(NoseTop);
    num_legs = HeadMappings::ShapeNumLegs(NoseLeft) +
               HeadMappings::ShapeNumLegs(NoseRight) +
               HeadMappings::ShapeNumLegs(NoseTop);
    printf("MILES_DEBUG: offset = %u, leg_offset = %u, num_legs = %u\n", offset, leg_offset, num_legs);
    m_nose = new CPixelArrayLegs("HeadNose", this, len, offset, num_legs, leg_offset);

    len = HeadMappings::ShapeSize(NoseLeft);
    num_legs = HeadMappings::ShapeNumLegs(NoseLeft);
    m_nose_left = new CPixelArrayLegs("HeadNoseLeft", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(NoseRight);
    offset = HeadMappings::ShapeStartIndex(NoseRight);
    num_legs = HeadMappings::ShapeNumLegs(NoseRight);
    m_nose_right = new CPixelArrayLegs("HeadNoseRight", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(NoseTop);
    offset = HeadMappings::ShapeStartIndex(NoseTop);
    num_legs = HeadMappings::ShapeNumLegs(NoseTop);
    m_nose_top = new CPixelArrayLegs("HeadNoseTop", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(SideLeft);
    offset = HeadMappings::ShapeStartIndex(SideLeft);
    num_legs = HeadMappings::ShapeNumLegs(SideLeft);
    m_side_left = new CPixelArrayLegs("HeadSideLeft", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(SideRight);
    offset = HeadMappings::ShapeStartIndex(SideRight);
    num_legs = HeadMappings::ShapeNumLegs(SideRight);
    m_side_right = new CPixelArrayLegs("HeadSideRight", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(FlameLeft);
    offset = HeadMappings::ShapeStartIndex(FlameLeft);
    num_legs = HeadMappings::ShapeNumLegs(FlameLeft);
    m_flame_left = new CPixelArrayLegs("HeadFlameLeft", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    len = HeadMappings::ShapeSize(FlameRight);
    offset = HeadMappings::ShapeStartIndex(FlameRight);
    num_legs = HeadMappings::ShapeNumLegs(FlameRight);
    m_flame_right = new CPixelArrayLegs("HeadFlameRight", this, len, offset, num_legs, leg_offset);
    leg_offset += num_legs;

    m_mouth_left->SetRoutine(new CRoutineSolid(m_mouth_left, CRGB::Black));
    m_mouth_right->SetRoutine(new CRoutineSolid(m_mouth_right, CRGB::Black));
    m_nose->SetRoutine(new CRoutineSolid(m_nose, CRGB::Black));
//    m_nose_left->SetRoutine(new CRoutineSolid(m_nose_left, CRGB::Black));
//    m_nose_right->SetRoutine(new CRoutineSolid(m_nose_right, CRGB::Black));
//    m_nose_top->SetRoutine(new CRoutineSolid(m_nose_top, CRGB::Black));

    m_side_left->SetRoutine(new CRoutineFire(m_side_left));
    m_side_right->SetRoutine(new CRoutineFire(m_side_right));
    m_flame_left->SetRoutine(new CRoutineFire(m_flame_left));
    m_flame_right->SetRoutine(new CRoutineFire(m_flame_right));

    m_mouth_left->TransitionTo(new CRoutineCyclePallete(m_mouth_left, true, 15), c_transition_time_ms);
    m_mouth_right->TransitionTo(new CRoutineCyclePallete(m_mouth_right, true, 15), c_transition_time_ms);
    m_nose->TransitionTo(new CRoutineTraverseNose(this, m_nose), c_transition_time_ms);
//    m_nose_left->TransitionTo(new CRoutineRings(m_nose_left, CPixelArray::Coordinate(-0.4, 1.0)), c_transition_time_ms);
//    m_nose_right->TransitionTo(new CRoutineRings(m_nose_right, CPixelArray::Coordinate(0.4, 1.0)), c_transition_time_ms);
//    m_nose_top->TransitionTo(new CRoutineRings(m_nose_top, CPixelArray::Coordinate(0.0, 1.0)), c_transition_time_ms);
}

CHead::~CHead()
{
}

void CHead::Continue()
{
    static uint32_t first_run = millis();
    static uint32_t last_run = millis();

    m_mouth_left->Continue();
    m_mouth_right->Continue();
    m_nose->Continue();
    m_nose_left->Continue();
    m_nose_right->Continue();
    m_nose_top->Continue();
    m_side_left->Continue();
    m_side_right->Continue();
    m_flame_left->Continue();
    m_flame_right->Continue();
}
#endif // GEOM_HEAD
