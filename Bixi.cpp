#include "Bixi.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "Routine2dSwipe.h"

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

    // indicator
    pinMode(c_indicatorPin, OUTPUT);

    // Parallel Output
    FastLED.addLeds<WS2813_PORTD, Addressing::c_num_strands>(m_pixels.GetRaw(), m_pixels.GetSize());

    m_pixels.SetAllPixels(CRGB::Black);
    Show();

    // init shapes
    CPixelArray::Config config;
    config.m_num_legs = 6;
    config.m_start[0]  = 14;
    config.m_end[0]    = 0;
    config.m_start[1]  = 89;
    config.m_end[1]    = 75;
    config.m_start[2]  = 74;
    config.m_end[2]    = 60;
    config.m_start[3]  = 59;
    config.m_end[3]    = 45;
    config.m_start[4]  = 44;
    config.m_end[4]    = 30;
    config.m_start[5]  = 29;
    config.m_end[5]    = 15;

    m_shapes[0] = new CPixelArray(&m_pixels, config);
//    m_shapes[0]->StartRoutineSwipe(5, 5);

    config.m_scale     = 0.75;
    config.m_start[0]  = 97;
    config.m_end[0]    = 90;
    config.m_start[1]  = 137;
    config.m_end[1]    = 130;
    config.m_start[2]  = 129;
    config.m_end[2]    = 122;
    config.m_start[3]  = 121;
    config.m_end[3]    = 114;
    config.m_start[4]  = 113;
    config.m_end[4]    = 106;
    config.m_start[5]  = 105;
    config.m_end[5]    = 98;

    m_shapes[1] = new CPixelArray(&m_pixels, config);
//    m_shapes[1]->StartRoutineGlare(ColorPallete::ChromeBlue, 5, true, 5);
//    m_shapes[1]->StartRoutineSwipe(5, 5);

    m_routine = new CRoutine2dSwipe(2, &m_shapes[0], 15, 5);
}

CBixi::~CBixi()
{
}

void CBixi::Show()
{
    FastLED.show();
}

void CBixi::Continue()
{
    size_t now = millis();

    for(size_t i=0;i<c_num_shapes;i++)
    {
        m_shapes[i]->Continue();
    }

    m_routine->Continue();

    Show();

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn   = !m_indicatorOn;
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }

#ifdef LOG_REFRESH_RATE
    size_t timer = millis() - now;
    char logString[128];
    sprintf(logString, "CBixi::Continue: This iteration took %u ms", timer);
    CLogging::log(logString);
#endif
}
