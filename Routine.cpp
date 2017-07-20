#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"
#include "Arduino.h"

#include <algorithm>

CRoutine::CRoutine(CPixelArray* pixels) :
    m_pixels(pixels),
    m_start_time_ms(millis())
{
}

CRoutine::~CRoutine()
{
}

void CRoutine::onIteration()
{
    if(InTransition() == true)
    {
        RecalculateTransition();
    }

    Continue();
}

void CRoutine::TransitionOut(size_t duration_ms)
{
    m_transition_time_ms = duration_ms;
    m_transition_start_ms = millis();
    m_max_y_pixel = 1.0;
    m_in_transition = true;
}

bool CRoutine::InTransition()
{
    return m_in_transition;
}

void CRoutine::RecalculateTransition()
{
    m_in_transition = millis() - m_transition_start_ms < m_transition_time_ms;
    m_max_y_pixel = 1.0 - 2.0 * (float)(millis() - m_transition_start_ms) / (m_transition_time_ms);
}

void CRoutine::SetPixel(size_t index, CRGB rgb)
{
    if(InTransition() == true && GetCoordinate(index).y > m_max_y_pixel)
    {
        return;
    }

    m_pixels->SetPixel(index, rgb);
}

void CRoutine::SetAllPixels(CRGB rgb)
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, rgb);
    }
}

CRGB CRoutine::GetPixel(size_t index)
{
    return m_pixels->GetPixel(index);
}

size_t CRoutine::GetSize()
{
    return m_pixels->GetSize();
}

CPixelArray::Coordinate CRoutine::GetCoordinate(size_t index)
{
    return m_pixels->GetCoordinate(index);
}

const char* CRoutine::GetPixelName()
{
    return m_pixels->GetName();
}
