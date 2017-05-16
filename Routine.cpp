#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"

CRoutine::CRoutine(CPixelArray& pixels) :
    m_pixels(pixels)
{
}

CRoutine::~CRoutine()
{
    Exit();
}

void CRoutine::GetRGB(size_t index, CRGB& dest)
{
    dest = m_pixels.GetPixel(index);
}

size_t CRoutine::GetSize()
{
    return m_pixels.GetSize();
}

void CRoutine::Exit()
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_pixels.Reset();
    }
}

