#include <algorithm>

#include "RoutineSolid.h"
#include "PixelArray.h"

CMemoryPool<CRoutineSolid, CRoutineSolid::c_alloc_qty> CRoutineSolid::s_pool;

CRoutineSolid::CRoutineSolid(CPixelArray* pixels, size_t transition_time_ms, CRGB rgb) :
    CRoutine(pixels, transition_time_ms),
    m_color(rgb)
{
}

CRoutineSolid::~CRoutineSolid()
{
}

void CRoutineSolid::Continue()
{
    SetAllPixels(m_color);
}
