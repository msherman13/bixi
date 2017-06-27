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
#include "RoutineTraverse.h"
#include "RoutineFire.h"

CMemoryPool<CHead, 1>  CHead::s_pool;
HeadMappings::Mappings CHead::s_mappings;

CHead::CHead() :
    CPixelArrayLegs("Head", dynamic_cast<CPixelArray::Config*>(&s_mappings))
{
    // initialize legs
    m_mouth_left = GetLeg(0);
    m_mouth_left->SetName("HeadMouthLeft");
    m_mouth_left->SetRoutine(new CRoutineSolid(m_mouth_left, CRGB::Black));
    m_mouth_left->TransitionTo(new CRoutineCyclePallete(m_mouth_left, true, 15), c_transition_time_ms);
    m_mouth_right = GetLeg(1);
    m_mouth_right->SetName("HeadMouthRight");
    m_mouth_right->SetRoutine(new CRoutineSolid(m_mouth_right, CRGB::Black));
    m_mouth_right->TransitionTo(new CRoutineCyclePallete(m_mouth_right, true, 15), c_transition_time_ms);
    m_nose_left = GetLeg(2);
    m_nose_left->SetName("HeadNoseLeft");
    m_nose_left->SetRoutine(new CRoutineSolid(m_nose_left, CRGB::Black));
    m_nose_left->TransitionTo(new CRoutineCyclePallete(m_nose_left, true, 15), c_transition_time_ms);
    m_nose_right = GetLeg(3);
    m_nose_right->SetName("HeadNoseRight");
    m_nose_right->SetRoutine(new CRoutineSolid(m_nose_right, CRGB::Black));
    m_nose_right->TransitionTo(new CRoutineCyclePallete(m_nose_right, true, 15), c_transition_time_ms);
    m_side_left = GetLeg(4);
    m_side_left->SetName("HeadSideLeft");
    m_side_left->SetRoutine(new CRoutineSolid(m_side_left, CRGB::Black));
    m_side_left->TransitionTo(new CRoutineCyclePallete(m_side_left, true, 15), c_transition_time_ms);
    m_side_right = GetLeg(5);
    m_side_right->SetName("HeadSideRight");
    m_side_right->SetRoutine(new CRoutineSolid(m_side_right, CRGB::Black));
    m_side_right->TransitionTo(new CRoutineCyclePallete(m_side_right, true, 15), c_transition_time_ms);
    //m_side_right->SetRoutine(new CRoutineSolid(m_side_right, ColorPallete::Purple));
    m_flame_left = GetLeg(6);
    m_flame_left->SetName("HeadFlameLeft");
    m_flame_left->SetRoutine(new CRoutineFire(m_flame_left));
    m_flame_right = GetLeg(7);
    m_flame_right->SetName("HeadFlameRight");
    m_flame_right->SetRoutine(new CRoutineFire(m_flame_right));
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
    m_nose_left->Continue();
    m_nose_right->Continue();
    m_side_left->Continue();
    m_side_right->Continue();

#if 0
    int now = millis();
    if(now - last_run > 1000)
    {
        CHSV hsv = rgb2hsv_approximate(ColorPallete::DarkPink);
        hsv.s = 255;
        hsv.v = 255 - (((float)now - (float)first_run) / 1000) * 10;
        CRGB rgb(hsv);
        //rgb.r = 255 - (((float)now - (float)first_run) / 1000) * 10;
        m_side_right->SetRoutine(new CRoutineSolid(m_side_right, rgb));
        char logstr[256];
        sprintf(logstr, "MILES_DEBUG: setting val to %u", hsv.v);
        CLogging::log(logstr);
        m_side_right->Continue();
        last_run = now;
    }
#endif
    m_flame_left->Continue();
    m_flame_right->Continue();
}
#endif // GEOM_HEAD
