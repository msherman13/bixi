#include "Bixi.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "Dome.h"
#include "Grid.h"

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

    // geometry
#ifdef GEOM_DOME
    CLogging::log("CBixi::CBixi: Geometry = GEOM_DOME");
    m_geometry = new CDome();
#elif GEOM_GRID
    CLogging::log("CBixi::CBixi: Geometry = GEOM_GRID");
    m_geometry = new CGrid();
#else
    CLogging::log("CBixi::CBixi: ERROR no geometry is defined. Exiting");
    exit(-1);
#endif

    // Parallel Output
    FastLED.addLeds<WS2813_PORTD, Addressing::c_num_strands>(m_geometry->GetRaw(), m_geometry->GetRawSize() / Addressing::c_num_strands);
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

#ifdef LOG_REFRESH_RATE
    size_t cont = millis();
#endif

    Show(m_geometry);

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn   = !m_indicatorOn;
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }

#ifdef LOG_REFRESH_RATE
    size_t timer = millis();
    char logString[128];
    sprintf(logString, "CBixi::Continue: Calculations took %u ms, Show took %u ms, Total %u ms",
            cont - now, timer - cont, timer - now);
    CLogging::log(logString);
#endif
}
