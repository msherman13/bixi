#include "Bixi.h"
#include "RoutineHoldRainbow.h"
#include "RoutineCycleRainbow.h"
#include "RoutineSparkle.h"
#include "RoutineRainbowSparkle.h"
#include "RoutineGrow.h"
#include "Logging.h"

#define DRIVER WS2812B
#define ORDER GRB
#define LOG_REFRESH_RATE

CBixi& CBixi::Instance()
{
    static CBixi bixi;
    return bixi;
}

// FastLED::ParallelOutput:
//     Pins 2, 14, 7, 8, 6, 20, 21, 5
CBixi::CBixi() :
    m_currRoutine(nullptr)
{
    CLogging::log("CBixi::CBixi: Initializing Bixi");

    // construct routines
    m_routines[CRoutine::HoldRainbow]    = new CRoutineHoldRainbow(c_numLeds);
    m_routines[CRoutine::CycleRainbow]   = new CRoutineCycleRainbow(c_numLeds);
    m_routines[CRoutine::Sparkle]        = new CRoutineSparkle(c_numLeds);
    m_routines[CRoutine::RainbowSparkle] = new CRoutineRainbowSparkle(c_numLeds);
    m_routines[CRoutine::Grow]           = new CRoutineGrow(c_numLeds);

    // Parallel Output
    FastLED.addLeds<WS2811_PORTD, c_numPins>(m_leds, c_numLedsPerPin);

    // init FastLED for static strip
    /*
    for(size_t i=0;i<c_numPins;i++)
    {
        const size_t start = i * c_numLeds / c_numPins;
        const size_t len = i < c_numPins - 1 ?
                           c_numLeds / c_numPins :
                           c_numLeds - start;

        char logString[128];
        sprintf(logString,
                "CBixi::CBixi: Pin %u will drive %u pixels starting at index %u",
                i, len, start);
        CLogging::log(logString);

        // TODO: there's gotta be a better way to do this
        switch(i)
        {
            case 0:
                FastLED.addLeds<DRIVER, c_dataPins[0], ORDER>(&m_leds[start], len); 
                break;
            case 1:
                FastLED.addLeds<DRIVER, c_dataPins[1], ORDER>(&m_leds[start], len); 
                break;
            case 2:
                FastLED.addLeds<DRIVER, c_dataPins[2], ORDER>(&m_leds[start], len); 
                break;
            case 3:
                FastLED.addLeds<DRIVER, c_dataPins[3], ORDER>(&m_leds[start], len); 
                break;
        }
    }
    */
    SetAllBlack();
    Show();
}

CBixi::~CBixi()
{
    delete m_currRoutine;
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
    if(!m_currRoutine)
    {
        return false;
    }

#ifdef LOG_REFRESH_RATE
    unsigned long timer = millis();
#endif

    m_currRoutine->Continue();
    ShowCurrRoutine();

#ifdef LOG_REFRESH_RATE
    timer = millis() - timer;
    char logString[128];
    sprintf(logString, "CBixi::Continue: This iteration took %lu ms", timer);
    CLogging::log(logString);
#endif

    return true;
}
