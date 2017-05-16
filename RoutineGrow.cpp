#include "RoutineGrow.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

CRoutineGrow::CRoutineGrow() :
    CRoutine(),
    m_lastRun(0),
    m_head(0),
    m_up(true)
{
    char logString[256];
    sprintf(logString, "CRoutineGrow::CRoutineGrow: Constructing routine");
    CLogging::log(logString);
}

CRoutineGrow::~CRoutineGrow()
{
}

void CRoutineGrow::Start()
{
    char logString[256];
    sprintf(logString, "CRoutineGrow::Start: Entering routine");
    CLogging::log(logString);

    for(size_t i=0;i<GetSize();i++)
    {
        m_pixelArray.SetPixel(i, CRGB::Black);
    }

    m_pixelArray.SetPixel(m_head, CRGB::Blue);
}

void CRoutineGrow::Continue()
{
    uint32_t now = millis();
    if(now - m_lastRun < 100)
        return;
    m_lastRun = now;

    if(m_head == GetSize()-1)
    {
        m_up = false;
    }
    else if(m_head == 0)
    {
        m_up = true;
    }

    m_head = m_up ? m_head + 1 : m_head - 1;
    m_pixelArray.SetPixel(m_head, CRGB::Blue);
    if(!m_up)
    {
        m_pixelArray.SetPixel(m_head + 1, CRGB::Black);
    }
}
