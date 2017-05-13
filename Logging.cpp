#include "Logging.h"

void CLogging::Init()
{
    Serial.begin(9600);
    int startMillis = millis();
    while(!Serial && millis() - startMillis < c_initTimeoutMs)
    {
        ;
    }
}

void CLogging::log(const char* buff)
{
    if(!Serial)
        return;

    Serial.println(buff);
}
