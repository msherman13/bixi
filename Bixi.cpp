#include "Bixi.h"
#include "Strip.h"
#include "RoutineHoldRainbow.h"
#include "RoutineCycleRainbow.h"
#include "RoutineSparkle.h"
#include "RoutineRainbowSparkle.h"
#include "Logging.h"

#define DRIVER WS2812B
#define ORDER GRB

CBixi& CBixi::Instance()
{
    static CBixi bixi;
    return bixi;
}

CBixi::CBixi() :
    m_currRoutine(nullptr)
{
    CLogging::log("CBixi::CBixi: Initializing Bixi");

    // init FastLED for static strip
    FastLED.addLeds<DRIVER, c_dataPin, ORDER>(m_leds, c_numLeds);
    SetAllBlack();
    Show();
}

CBixi::~CBixi()
{
    delete m_currRoutine;
}

CRoutine* CBixi::ConstructRoutine(CRoutine::RoutineType type)
{
    switch(type)
    {
        case CRoutine::HoldRainbow:    return new CRoutineHoldRainbow(c_numLeds);
        case CRoutine::CycleRainbow:   return new CRoutineCycleRainbow(c_numLeds);
        case CRoutine::Sparkle:        return new CRoutineSparkle(c_numLeds);
        case CRoutine::RainbowSparkle: return new CRoutineRainbowSparkle(c_numLeds);
        default:                       return nullptr;
    }
}

bool CBixi::StartRoutine(CRoutine::RoutineType type)
{
    if(type >= CRoutine::RoutineQty)
        return false;

    if(m_currRoutine)
    {
        ExitCurrRoutine();
    }

    char logString[256];
    sprintf(logString, "CBixi::StartRoutine: Starting [%s]",
            CRoutine::sRoutineType(type));
    CLogging::log(logString);

    m_currRoutine = ConstructRoutine(type);
    m_currRoutine->Start();

    return true;
}

bool CBixi::ExitCurrRoutine()
{
    if(!m_currRoutine)
    {
        return false;
    }

    char logString[256];
    sprintf(logString, "CBixi::ExitCurrRoutine: Exiting [%s]",
            CRoutine::sRoutineType(m_currRoutine->GetType()));
    CLogging::log(logString);

    delete m_currRoutine;
    m_currRoutine = nullptr;

    return true;
}

void CBixi::SetAllBlack()
{
    for(size_t i=0;i<c_numLeds;i++)
    {
        m_leds[i] = CRGB::Black;
    }
}

bool CBixi::ShowCurrRoutine()
{
    if(!m_currRoutine)
    {
        return false;
    }

    for(size_t i=0;i<m_currRoutine->GetSize();i++)
    {
        m_currRoutine->GetRGB(i, m_leds[i]);
    }

    Show();

    return true;
}

void CBixi::Show()
{
    FastLED.show();
}

bool CBixi::Continue()
{
    if(!m_currRoutine)
    {
        return false;
    }

    SetAllBlack();
    m_currRoutine->Continue();
    ShowCurrRoutine();

    return true;
}
