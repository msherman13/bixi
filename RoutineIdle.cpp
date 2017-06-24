#include <algorithm>

#include "RoutineIdle.h"
#include "PixelArray.h"

CMemoryPool<CRoutineIdle, CRoutineIdle::c_alloc_qty> CRoutineIdle::s_pool;

CRoutineIdle::CRoutineIdle(CPixelArray* pixels) :
    CRoutine(pixels)
{
}

CRoutineIdle::~CRoutineIdle()
{
}

void CRoutineIdle::Continue()
{
}
