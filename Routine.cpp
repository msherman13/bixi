#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"
#include "Arduino.h"

CRoutine::CRoutine(CPixelArray* pixels) :
    m_pixels(pixels),
    m_start_time_ms(millis())
{
}

CRoutine::~CRoutine()
{
}

void CRoutine::TransitionOut(size_t duration_ms)
{
    m_transition_time_ms = duration_ms;
    m_transition_start_ms = millis();
}

bool CRoutine::InTransition()
{
    return millis() - m_transition_start_ms < m_transition_time_ms;
}

void CRoutine::SetPixel(size_t index, CRGB rgb)
{
    if(InTransition() == true)
    {
        double weight =
            std::max<float>(0.0, 1.0 - (float)(millis() - m_transition_start_ms) / (m_transition_time_ms - 200));

        m_pixels->BlendPixel(index, rgb, weight);
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
