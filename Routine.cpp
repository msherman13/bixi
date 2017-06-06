#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"

CRoutine::CRoutine(CPixelArray* pixels) :
    m_pixels(pixels)
{
}

CRoutine::~CRoutine()
{
}

void CRoutine::Shutdown()
{
    if(m_state != Running)
    {
        return;
    }

    char logstr[256];
    sprintf(logstr, "CRoutine::Shutdown: Routine [%s] shutting down", GetName());
    CLogging::log(logstr);

    m_state            = ShuttingDown;
    m_shutdown_time_ms = millis();
}
