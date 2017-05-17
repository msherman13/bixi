#include "RoutineCycleHex.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

CRoutineCycleHex::CRoutineCycleHex(CPixelArray& pixels) :
    CRoutine(pixels),
    m_color(0, 255, 255)
{
    char logString[256];
    sprintf(logString, "CRoutineCycleHex::CRoutineCycleHex: Constructing routine");
    CLogging::log(logString);

    CPlain::Config config;
    config.m_num_legs  = 2;

    // top
    config.m_start[0]  = 0;
    config.m_length[0] = 15;
    config.m_start[1]  = 90;
    config.m_length[1] = 8;
    m_plains[0] = new CPlain(m_pixels, config);
    // top-left
    config.m_start[0]  = 15;
    config.m_length[0] = 15;
    config.m_start[1]  = 98;
    config.m_length[1] = 8;
    m_plains[1] = new CPlain(m_pixels, config);
    // bottom-left
    config.m_start[0]  = 30;
    config.m_length[0] = 15;
    config.m_start[1]  = 106;
    config.m_length[1] = 8;
    m_plains[2] = new CPlain(m_pixels, config);
    // bottom
    config.m_start[0]  = 45;
    config.m_length[0] = 15;
    config.m_start[1]  = 114;
    config.m_length[1] = 8;
    m_plains[3] = new CPlain(m_pixels, config);
    // bottom-right
    config.m_start[0]  = 60;
    config.m_length[0] = 15;
    config.m_start[1]  = 122;
    config.m_length[1] = 8;
    m_plains[4] = new CPlain(m_pixels, config);
    // top-right
    config.m_start[0]  = 75;
    config.m_length[0] = 15;
    config.m_start[1]  = 130;
    config.m_length[1] = 8;
    m_plains[5] = new CPlain(m_pixels, config);
}

CRoutineCycleHex::~CRoutineCycleHex()
{
    for(size_t i=0;i<c_num_plains;i++)
    {
        delete m_plains[i];
    }
}

void CRoutineCycleHex::TogglePlain(size_t index, bool on_off)
{
    m_plains[index]->SetColor(on_off ? CRGB(m_color) : CRGB::Black);
}

void CRoutineCycleHex::Start()
{
    char logString[256];
    sprintf(logString, "CRoutineCycleHex::Start: Entering routine");
    CLogging::log(logString);

    m_pixels.Reset();

    Continue();
}

void CRoutineCycleHex::Continue()
{
    m_color.hue++;

    uint32_t now = millis();
    if(now - m_lastRun < 2000)
        return;
    m_lastRun = now;

    m_count++;

    for(size_t i=0;i<c_num_plains;i++)
    {
        TogglePlain(i, (m_count + i) % 3 == 0);
    }
}
