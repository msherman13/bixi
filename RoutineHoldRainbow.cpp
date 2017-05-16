#include "RoutineHoldRainbow.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

CRoutineHoldRainbow::CRoutineHoldRainbow(CPixelArray& pixels) :
    CRoutine(pixels)
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

    const double multiplier = 255.0 / (GetSize()/2-1);
    for(size_t i=0;i<GetSize()/2;i++)
    {
        hsv.hue = i * multiplier;
        m_pixels.SetPixel(i, CRGB(hsv));
    }
    for(size_t i=0;i<GetSize()/2;i++)
    {
        hsv.hue = 255 - i * (double)(255.0 / (GetSize()/2-1));
        m_pixels.SetPixel(i + GetSize()/2, CRGB(hsv));
    }
}

void CRoutineHoldRainbow::Continue()
{
    return;
}
