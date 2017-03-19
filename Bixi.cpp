#include "Bixi.h"
#include "RoutineHoldRainbow.h"
#include "RoutineCycleRainbow.h"
#include "RoutineSparkle.h"
#include "RoutineRainbowSparkle.h"
#include "RoutineGrow.h"
#include "Logging.h"

#define DRIVER WS2812B
#define ORDER GRB
//#define LOG_REFRESH_RATE

CBixi& CBixi::Instance()
{
    static CBixi bixi;
    return bixi;
}

// FastLED::ParallelOutput:
//     Pins 2, 14, 7, 8, 6, 20, 21, 5
CBixi::CBixi()
{
    CLogging::log("CBixi::CBixi: Initializing Bixi");

    SetState(State::Initializing);

    // indicator
    pinMode(c_indicatorPin, OUTPUT);

    // construct routines
    m_routines[CRoutine::HoldRainbow]    = new CRoutineHoldRainbow(c_numLeds);
    m_routines[CRoutine::CycleRainbow]   = new CRoutineCycleRainbow(c_numLeds);
    m_routines[CRoutine::Sparkle]        = new CRoutineSparkle(c_numLeds);
    m_routines[CRoutine::RainbowSparkle] = new CRoutineRainbowSparkle(c_numLeds);
    m_routines[CRoutine::Grow]           = new CRoutineGrow(c_numLeds);

    // Parallel Output
    FastLED.addLeds<WS2811_PORTD, c_numPins>(m_leds, c_numLedsPerPin);

    SetAllBlack();
    Show();

    SetState(State::Running);
}

CBixi::~CBixi()
{
    delete m_currRoutine;
}

const char* CBixi::sState(State state)
{
    switch(state)
    {
        case State::Stopped: return "Stopped";
        case State::Running: return "Running";
        default: return "Undef";
    }
}

void CBixi::SetState(State state)
{
    m_state = state;

    char logString[128];
    sprintf(logString, "CBixi::SetState: %s", sState(state));
    CLogging::log(logString);
}

CRoutine* CBixi::GetRoutine(CRoutine::RoutineType type)
{
    return m_routines[type];
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

    m_currRoutine = GetRoutine(type);
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
    if(!m_currRoutine || GetState() == State::Stopped)
    {
        return false;
    }

    size_t now = millis();

    m_currRoutine->Continue();
    ShowCurrRoutine();

#ifdef LOG_REFRESH_RATE
    size_t timer = millis() - now;
    char logString[128];
    sprintf(logString, "CBixi::Continue: This iteration took %lu ms", timer);
    CLogging::log(logString);
#endif

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn = !m_indicatorOn;
        if(GetState() != State::Running)
        {
            m_indicatorOn = false;
        }
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }

    return true;
}
