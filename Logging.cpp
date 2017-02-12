#include "Logging.h"
#include "Arduino.h"

void CLogging::Init()
{
    Serial.begin(9600);
    while(!Serial)
    {
        ;
    }
}

void CLogging::log(const char* buff)
{
    Serial.println(buff);
}
