#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"
#include "Arduino.h"
#include "Bixi.h"

#include <algorithm>

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
    m_in_transition = true;
}

bool CRoutine::InTransition()
{
    return m_in_transition;
}

bool CRoutine::TransitionDone()
{
    return millis() > m_transition_start_ms + m_transition_time_ms;
}

void CRoutine::SetPixel(size_t index, CRGB rgb)
{
    if(InTransition() == true)
    {
        size_t iteration = CBixi::Iteration();
        if(iteration != m_last_iteration)
        {
            m_transition_weight = (float)(millis() - m_transition_start_ms) / (m_transition_time_ms - 200);
            m_transition_weight = powf(m_transition_weight, c_transition_q);
            m_transition_weight = 1.0 - m_transition_weight;
            m_transition_weight = std::max<float>(0.0, m_transition_weight);
            m_last_iteration = iteration;
        }

        m_pixels->BlendPixel(index, rgb, m_transition_weight);
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
