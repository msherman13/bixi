#include "Bixi.h"
#include "Routine.h"
#include "Logging.h"

void setup()
{
    CLogging::Init();
}

void runRoutine(CRoutine::RoutineType type, unsigned long durationSec)
{
    unsigned long startTimeUs = millis();
    CBixi::Instance().StartRoutine(type);

    while(millis() - startTimeUs < durationSec * 1000)
    {
        CBixi::Instance().Continue();
    }

    CBixi::Instance().ExitCurrRoutine();
}

void loop()
{ 
    while(true)
    {
        for(int i=0;i<CRoutine::ROUTINE_QTY;i++)
        {
            CRoutine::RoutineType type = (CRoutine::RoutineType)i;
            runRoutine(type, 10);
        }
    }
}

/*

void SetAllBlack()
{
    for(int i=0;i<NUM_LEDS;i++)
    {
        leds[i] = CRGB::Black;
    }
}

void SmartCopy(int startIndex, Strip* pStrip, int size=-1)
{
    if(size < 0)
        size = pStrip->GetSize();
    CRGB local[size];
    pStrip->Copy(local, size);
    for(int i=0;i<size;i++)
    {
        int index = (i + startIndex) % NUM_LEDS;
        if(index < 0)
            index = NUM_LEDS + index;
        leds[index] = local[i];
    }
}

void InitCrawl(int numStrips, int width=-1, int speedMs=-1)
{
    Strip* pAllStrips[numStrips];
    int speed[numStrips];
    int start[numStrips];
    for(int i=0;i<numStrips;i++)
    {
        start[i] = (NUM_LEDS / numStrips) * i;
        if(width > 0)
            pAllStrips[i] = new Strip(width);
        else
            pAllStrips[i] = new Strip(rand() % 15);
        pAllStrips[i]->Hold(0, rand() % 256, 128 + (rand() % 128), 128);
        if(speedMs > 0)
            speed[i] = speedMs;
        else
            speed[i] = rand() % 400;
        if(i % 2 != 0)
            speed[i] *= -1;
    }

    while(true)
    {
        SetAllBlack();
        for(int i=0;i<numStrips;i++)
        {
            pAllStrips[i]->Continue();
            SmartCopy(start[i] + ((int)millis() / speed[i]), pAllStrips[i]);
        }
        FastLED.show();
    }
}

*/
