#include "RoutinePlainTest.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

CRoutinePlainTest::CRoutinePlainTest(CPixelArray& pixels) :
    CRoutine(pixels)
{
    char logString[256];
    sprintf(logString, "CRoutinePlainTest::CRoutinePlainTest: Constructing routine");
    CLogging::log(logString);

    for(size_t i=0;i<c_num_plains;i++)
    {
        CPlain::Config config;

        config.m_num_legs = c_num_legs_per_plain;

        for(size_t j=0;j<c_num_legs_per_plain;j++)
        {
            config.m_start[j]  = i * c_leg_length;
            config.m_length[j] = c_leg_length;
        }

        m_plains[i] = new CPlain(m_pixels, config);
    }
}

CRoutinePlainTest::~CRoutinePlainTest()
{
    for(size_t i=0;i<c_num_plains;i++)
    {
        delete m_plains[i];
    }
}

void CRoutinePlainTest::TogglePlain(size_t index, bool on_off)
{
    m_plains[index]->SetColor(on_off ? CRGB::Blue : CRGB::Black);
}

void CRoutinePlainTest::Start()
{
    char logString[256];
    sprintf(logString, "CRoutinePlainTest::Start: Entering routine");
    CLogging::log(logString);

    m_pixels.Reset();

    for(size_t i=0;i<c_num_plains;i++)
    {
        if(i % 2 == 0)
        {
            TogglePlain(i, true);
        }
    }

    m_evenOdd = true;
}

void CRoutinePlainTest::Continue()
{
    uint32_t now = millis();
    if(now - m_lastRun < 1000)
        return;
    m_lastRun = now;

    m_evenOdd = !m_evenOdd;

    for(size_t i=0;i<c_num_plains;i++)
    {
        TogglePlain(i, m_evenOdd == (i % 2 == 0));
    }
}
