#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"
#include "Arduino.h"

CRoutine::CRoutine(CPixelArray* pixels, size_t transition_time_ms) :
    m_pixels(pixels),
    m_start_time_ms(millis()),
    m_transition_time_ms(transition_time_ms)
{
}

CRoutine::~CRoutine()
{
}

bool CRoutine::InTransition()
{
    return millis() - StartMs() < m_transition_time_ms;
}

void CRoutine::SetPixel(size_t index, CRGB rgb)
{
    if(InTransition() == true)
    {
        m_pixels->BlendPixel(index, rgb, (float)(millis() - StartMs()) / (m_transition_time_ms - 200));
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
