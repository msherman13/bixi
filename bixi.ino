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
    runRoutine(CRoutine::RainbowSparkle, 600);
    while(true)
    {
        for(int i=0;i<CRoutine::RoutineQty;i++)
        {
            CRoutine::RoutineType type = (CRoutine::RoutineType)i;
            runRoutine(type, 10);
        }
    }
}
