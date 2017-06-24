#include <algorithm>

#include "RoutineSolid.h"
#include "PixelArray.h"

CMemoryPool<CRoutineSolid, CRoutineSolid::c_alloc_qty> CRoutineSolid::s_pool;

CRoutineSolid::CRoutineSolid(CPixelArray* pixels, CRGB rgb) :
    CRoutine(pixels),
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
