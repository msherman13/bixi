#include "Routine.h"
#include "PixelArray.h"
#include "Logging.h"
#include "FastLED.h"

const char* CRoutine::sRoutineType(RoutineType type)
{
    switch(type)
    {
        case HoldRainbow: return "HoldRainbow";
        case CycleRainbow: return "CycleRainbow";
        case Sparkle: return "Sparkle";
        case RainbowSparkle: return "RainbowSparkle";
        default: return "RoutineUnknown";
    }
}

CRoutine::CRoutine(size_t size) :
    m_pPixelArray(new CPixelArray(size))
{
}

CRoutine::~CRoutine()
{
    Exit();
}

bool CRoutine::GetRGB(size_t index, CRGB& dest)
{
    CPixel* pPixel = m_pPixelArray->GetPixel(index);
    if(!pPixel)
        return false;

    return pPixel->GetRGB(dest);
}

size_t CRoutine::GetSize()
{
    return m_pPixelArray->GetSize();
}

void CRoutine::Exit()
{
    for(size_t i=0;i<GetSize();i++)
    {
        m_pPixelArray->Reset();
    }
}

