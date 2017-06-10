#include "Logging.h"
#include "Arduino.h"

void CLogging::Init()
{
    Serial.begin(9600);
    int startMillis = millis();
    while(!Serial && millis() - startMillis < c_initTimeoutMs)
    {
        ;
    }

    log("*** Begin Session***");
}

void CLogging::log(const char* buff)
{
    if(!Serial)
        return;

    char logstr[512];
    sprintf(logstr, "[%u]: %s", millis(), buff);

    Serial.println(logstr);
}
