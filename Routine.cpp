#include "Routine.h"
#include "Logging.h"

CRoutine::CRoutine()
{
}

CRoutine::~CRoutine()
{
    Exit();
}

bool CRoutine::GetRGB(size_t index, CRGB& dest)
{
    CPixel& pixel = m_pixelArray.GetPixel(index);

    return pixel.GetRGB(dest);
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

