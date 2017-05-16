#include "Bixi.h"
#include "RoutineHoldRainbow.h"
#include "RoutineCycleRainbow.h"
#include "RoutineSparkle.h"
#include "RoutineRainbowSparkle.h"
#include "RoutineGrow.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"

//#define LOG_REFRESH_RATE

CBixi& CBixi::Instance()
{
    static CBixi bixi;
    return bixi;
}

// FastLED::ParallelOutput:
//     Pins 2, 14, 7, 8, 6, 20, 21, 5
CBixi::CBixi() :
    m_pixels(Addressing::c_effective_strand_length)
{
    CLogging::log("CBixi::CBixi: Initializing Bixi");

    SetState(State::Initializing);

    // indicator
    pinMode(c_indicatorPin, OUTPUT);

    // construct routines
    m_routines[HoldRainbow]    = new CRoutineHoldRainbow(m_pixels);
    m_routines[CycleRainbow]   = new CRoutineCycleRainbow(m_pixels);
    m_routines[Sparkle]        = new CRoutineSparkle(m_pixels);
    m_routines[RainbowSparkle] = new CRoutineRainbowSparkle(m_pixels);
    m_routines[Grow]           = new CRoutineGrow(m_pixels);

    // Parallel Output
    FastLED.addLeds<WS2813_PORTD, Addressing::c_num_strands>(m_pixels.GetRawArray(), m_pixels.GetSize());

    Show();

    SetState(State::Running);
}

CBixi::~CBixi()
{
    delete m_currRoutine;
}

const char* CBixi::sRoutineType(RoutineType type)
{
    switch(type)
    {
        case HoldRainbow:    return "HoldRainbow";
        case CycleRainbow:   return "CycleRainbow";
        case Sparkle:        return "Sparkle";
        case RainbowSparkle: return "RainbowSparkle";
        case Grow:           return "Grow";
        default:             return "RoutineUnknown";
    }
}

const char* CBixi::sState(State state)
{
    switch(state)
    {
        case State::Stopped: return "Stopped";
        case State::Running: return "Running";
        default:             return "Undef";
    }
}

void CBixi::SetState(State state)
{
    m_state = state;

    char logString[128];
    sprintf(logString, "CBixi::SetState: %s", sState(state));
    CLogging::log(logString);
}

CRoutine* CBixi::GetRoutine(RoutineType type)
{
    return m_routines[type];
}

bool CBixi::StartRoutine(RoutineType type)
{
    if(type >= RoutineQty)
        return false;

    if(m_currRoutine)
    {
        ExitCurrRoutine();
    }

    char logString[256];
    sprintf(logString, "CBixi::StartRoutine: Starting [%s]", sRoutineType(type));
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
    sprintf(logString, "CBixi::ExitCurrRoutine: Exiting [%s]", m_currRoutine->GetName());
    CLogging::log(logString);

    m_currRoutine = nullptr;

    return true;
}

bool CBixi::ShowCurrRoutine()
{
    if(!m_currRoutine)
    {
        return false;
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
