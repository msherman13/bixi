#include "Bixi.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "Dome.h"
#include "Grid.h"
#include "FreeRam.h"
#include "GammaCorrection.h"

#define GEOM_DOME

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

    m_show = new CPixelArray(*m_geometry);

    // Parallel Output
    LEDS.addLeds<OCTOWS2813>(m_show->GetRaw(), m_show->GetRawSize() / Addressing::c_num_strands);
    LEDS.setBrightness(255);

    GammaCorrection::Init(3.5);

    char logstr[256];
    sprintf(logstr, "CBixi::CBixi: Initial allocations complete, %u byte remaining", FreeRam());
    CLogging::log(logstr);
}

CBixi::~CBixi()
{
    CLogging::log("CBixi::~CBixi: Destructing");

    ShutDown();

    delete m_geometry;
}

void CBixi::Show(CPixelArray* pixels)
{
    LEDS.show();
}

void CBixi::Continue()
{
    size_t now = millis();

    m_geometry->Continue();

    for(size_t i=0;i<m_geometry->GetRawSize();i++)
    {
        m_show->SetPixelRaw(i, GammaCorrection::CorrectGamma(m_geometry->GetPixelRaw(i)));
    }

    Show(m_show);

    FastLED.countFPS();

    static size_t last_log = 0;
    if(now - last_log >= 10000)
    {
        last_log = now;
        char logString[128];
        sprintf(logString, "CBixi::Continue: Frame rate for last 10 seconds is %u", FastLED.getFPS());
        CLogging::log(logString);
    }

    if(now - m_lastIndicator >= c_indicatorDelayMs)
    {
        m_indicatorOn   = !m_indicatorOn;
        m_lastIndicator = now;
        digitalWrite(c_indicatorPin, m_indicatorOn ? HIGH : LOW);
    }
}
