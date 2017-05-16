#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"

CRoutine::CRoutine() :
    m_pixelArray(Addressing::c_effective_length)
{
}

CRoutine::~CRoutine()
{
    Exit();
}

void CRoutine::GetRGB(size_t index, CRGB& dest)
{
    dest = m_pixelArray.GetPixel(index);
}

size_t CRoutine::GetSize()
{
    return m_pixelArray.GetSize();
}

void CRoutine::Exit()
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_pixelArray.Reset();
    }
}

