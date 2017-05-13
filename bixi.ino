#include "Bixi.h"
#include "Logging.h"

void setup()
{
    CLogging::Init();
}

void runRoutine(CBixi::RoutineType type, unsigned long durationSec)
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
        for(int i=0;i<CBixi::RoutineQty;i++)
        {
            runRoutine(CBixi::CycleRainbow, 1000);
        }
    }
}

int main()
{
    loop();
    return 0;
}
