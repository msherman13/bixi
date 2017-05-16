#include "RoutineSparkle.h"
#include "PixelArray.h"
#include "Logging.h"

CRoutineSparkle::CRoutineSparkle(CPixelArray& pixels) :
    CRoutine(pixels),
    m_lastRun(0)
{
    char logString[256];
    sprintf(logString, "CRoutineSparkle::CRoutineSparkle: Constructing routine");
    CLogging::log(logString);
}

CRoutineSparkle::~CRoutineSparkle()
{
}

void CRoutineSparkle::Start()
{
    char logString[256];
    sprintf(logString, "CRoutineSparkle::Start: Entering routine");
    CLogging::log(logString);

    SetRandomPixels();
}

void CRoutineSparkle::Continue()
{
    uint32_t now = millis();
    if(now - m_lastRun < 100)
        return;

    SetRandomPixels();
    m_lastRun = now;
}

void CRoutineSparkle::SetRandomPixels()
{
    m_pixels.Reset();
    for(size_t i=0;i<GetSize();i++)
    {
        bool setThisPixel = rand() % 30 == 0;
        if(setThisPixel)
            m_pixels.SetPixel(i, GetColor());
        else
            m_pixels.SetPixel(i, CRGB::Black);
    }
}
