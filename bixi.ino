#include "Bixi.h"
#include "Logging.h"

void setup()
{
    CLogging::Init();
    CBixi::Instance();
}

void loop()
{ 
    while(true)
    {
        CBixi::Instance().Continue();
    }
}
