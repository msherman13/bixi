#include "Bixi.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "Dome.h"

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

    m_geometry = new CDome(&m_pixels);

    m_geometry->StartRoutineSwipe();
    //m_geometry->StartRoutineFire();
    //m_geometry->StartRoutineSolid(CRGB(255, 0, 0));
}

CBixi::~CBixi()
{
}

void CBixi::Show(CPixelArray*)
{
    FastLED.show();
}

void CBixi::Continue()
{
    size_t now = millis();

    m_geometry->Continue();

    Show(m_geometry);

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
