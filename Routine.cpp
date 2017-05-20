#include "Routine.h"
#include "Logging.h"
#include "FastLED.h"

CRoutine::CRoutine(CPixelArray* pixels) :
    m_pixels(pixels)
{
}

CRoutine::~CRoutine()
{
}
