#include "Bixi.h"
#include "Logging.h"
#include "Addressing.h"
#include "Arduino.h"
#include "ColorPallete.h"
#include "Dome.h"
#include "Grid.h"
#include "LegsAndNeck.h"
#include "Head.h"
#include "FreeRam.h"
#include "GammaCorrection.h"

size_t CBixi::s_iteration = 0;

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
#elif GEOM_LEGS_NECK
    CLogging::log("CBixi::CBixi: Geometry = GEOM_LEGS_NECK");
    m_geometry = new CLegsAndNeck();
#elif GEOM_HEAD
    CLogging::log("CBixi::CBixi: Geometry = GEOM_HEAD");
    m_geometry = new CHead();
#elif GEOM_GRID
    CLogging::log("CBixi::CBixi: Geometry = GEOM_GRID");
    m_geometry = new CGrid();
#else
    CLogging::log("CBixi::CBixi: ERROR no geometry is defined. Exiting");
    exit(-1);
#endif

    m_show = new CPixelArray(*m_geometry);

    // Parallel Output
    if(m_geometry->PixelsPerStrand() * 8 != m_geometry->GetRawSize())
    {
        char logstr[256];
        sprintf(logstr, "CBixi::CBixi: ERROR geometry raw size (%u) != FastLED size (%u)",
                m_geometry->PixelsPerStrand() * 8, m_geometry->GetRawSize());
        CLogging::log(logstr);
        exit(-1);
    }
    LEDS.addLeds<OCTOWS2813>(m_show->GetRaw(), m_geometry->PixelsPerStrand());
    //LEDS.setBrightness(255);
    //LEDS.setCorrection(CRGB(255, 0, 0));

#ifdef SIM
    GammaCorrection::Init(1.00);
#else
    GammaCorrection::Init(1.50);
#endif

    m_geometry->SetAllPixels(CRGB::Black);
    Show(m_geometry);

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
    for(size_t i=0;i<pixels->GetSize();i++)
    {
        if(pixels->ApplyGamma(i))
        {
            m_show->SetPixel(i, GammaCorrection::CorrectGamma(pixels->GetPixel(i)));
        }
        else
        {
            m_show->SetPixel(i, pixels->GetPixel(i));
        }
    }

    LEDS.show();
}

void CBixi::Continue()
{
    s_iteration++;

    size_t now = millis();

    m_geometry->Continue();

    Show(m_geometry);

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
