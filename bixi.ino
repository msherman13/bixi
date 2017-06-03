#include "Bixi.h"
#include "Logging.h"

void setup()
{
    CLogging::Init();
    CBixi::Instance();

    CLogging::log("Bixi is initialized");
}

void loop()
{ 
    while(true)
    {
        CBixi::Instance().Continue();
    }
}

int main()
{
    setup();
    loop();

    return 0;
}
