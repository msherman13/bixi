#include "RoutineCycleRainbow.h"
#include "PixelArray.h"
#include "Logging.h"

CRoutineCycleRainbow::CRoutineCycleRainbow(int size) :
    CRoutineHoldRainbow(size),
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

    m_pPixelArray->Shift(true, 1);
    m_lastMove = now;
}
