#include "RoutineCycleRainbow.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

CRoutineCycleRainbow::CRoutineCycleRainbow(CPixelArray& pixels) :
    CRoutineHoldRainbow(pixels),
    m_lastMove(0)
{
    char logString[256];
    sprintf(logString, "CRoutineCycleRainbow::CRoutineCycleRainbow: Constructing routine");
    CLogging::log(logString);
}

CRoutineCycleRainbow::~CRoutineCycleRainbow()
{
}

void CRoutineCycleRainbow::Continue()
{
    uint32_t now = millis();
    if(now - m_lastMove < 200)
        return;

    m_pixels.Shift(true, 1);
    m_lastMove = now;
}
