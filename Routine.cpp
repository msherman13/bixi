#include "Routine.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

const char* CRoutine::sRoutineType(RoutineType type)
{
    switch(type)
    {
        case ROUTINE_HOLD_RAINBOW: return "ROUTINE_HOLD_RAINBOW";
        case ROUTINE_CYCLE_RAINBOW: return "ROUTINE_CYCLE_RAINBOW";
        case ROUTINE_SPARKLE: return "ROUTINE_SPARKLE";
        case ROUTINE_RAINBOW_SPARKLE: return "ROUTINE_RAINBOW_SPARKLE";
        default: return "ROUTINE_UNKNOWN";
    }
}

CRoutine::CRoutine(int size) :
    m_pPixelArray(new CPixelArray(size))
{
}

CRoutine::~CRoutine()
{
    Exit();
}

bool CRoutine::GetRGB(int index, CRGB& dest)
{
    CPixel* pPixel = m_pPixelArray->GetPixel(index);
    if(!pPixel)
        return false;

    return pPixel->GetRGB(dest);
}

int CRoutine::GetSize()
{
    return m_pPixelArray->GetSize();
}

void CRoutine::Exit()
{
    for(int i=0;i<GetSize();i++)
    {
        m_pPixelArray->Reset();
    }
}

