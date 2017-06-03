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
CBixi::CBixi()
{
    CLogging::log("CBixi::CBixi: Initializing Bixi");

    // indicator
    pinMode(c_indicatorPin, OUTPUT);

    // Parallel Output
    FastLED.addLeds<WS2813_PORTD, Addressing::c_num_strands>(m_leds, Addressing::c_effective_strand_length);

#ifdef GEOM_DOME
    CLogging::log("CBixi::CBixi: Geometry = GEOM_DOME");
    m_geometry = new CDome(m_leds);
#endif
}

CBixi::~CBixi()
{
    CLogging::log("CBixi::~CBixi: Destructing");

    ShutDown();

    delete m_geometry;
}

void CBixi::Show(CPixelArray* pixels)
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
