#include "RoutineHoldRainbow.h"
#include "PixelArray.h"
#include "Logging.h"

CRoutineHoldRainbow::CRoutineHoldRainbow(int size) :
    CRoutine(size)
{
    char logString[256];
    sprintf(logString, "CRoutineHoldRainbow::CRoutineHoldRainbow: Constructing routine");
    CLogging::log(logString);
}

CRoutineHoldRainbow::~CRoutineHoldRainbow()
{
}

void CRoutineHoldRainbow::Start()
{
    char logString[256];
    sprintf(logString, "CRoutineHoldRainbow::Start: Entering routine");
    CLogging::log(logString);

    CHSV hsv;
    hsv.hue = 0;
    hsv.sat = 240;
    hsv.val = 128;
    for(int i=0;i<GetSize();i++)
    {
        m_pPixelArray->SetPixel(i, CRGB(hsv));
        hsv.hue = i * (double)(255 / (GetSize()-1));
    }
}

void CRoutineHoldRainbow::Continue()
{
    return;
}
