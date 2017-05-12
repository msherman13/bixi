#include "RoutineCycleRainbow.h"
#include "PixelArray.h"
#include "Logging.h"

CRoutineCycleRainbow::CRoutineCycleRainbow(size_t size) :
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
    m_pPixelArray->Shift(true, 2);
}
