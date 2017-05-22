#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"

CRoutine::CRoutine(CPixelArray* pixels) :
    m_num_arrays(1)
{
    m_arrays[0] = pixels;
    m_pixels = m_arrays[0];
}

CRoutine::CRoutine(size_t num_arrays, CPixelArray** arrays) :
    m_num_arrays(num_arrays)
{
    for(size_t i=0;i<num_arrays;i++)
    {
        m_arrays[i] = arrays[i];
    }

    m_pixels = m_arrays[0];
}

CRoutine::~CRoutine()
{
}
