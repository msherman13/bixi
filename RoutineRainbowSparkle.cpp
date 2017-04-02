#include "RoutineRainbowSparkle.h"
#include "PixelArray.h"
#include "Logging.h"

CRoutineRainbowSparkle::CRoutineRainbowSparkle(size_t size) :
    CRoutineSparkle(size),
    m_currHsv(0, 240, 128),
    m_numIterationsSinceChange(0)
{
    char logString[256];
    sprintf(logString, "CRoutineRainbowSparkle::CRoutineRainbowSparkle: Constructing routine");
    CLogging::log(logString);
}

CRoutineRainbowSparkle::~CRoutineRainbowSparkle()
{
}

void CRoutineRainbowSparkle::SetRandomPixels()
{
    CRoutineSparkle::SetRandomPixels();
    if(++m_numIterationsSinceChange < c_iterationsPerColor)
        return;
    m_currHsv.hue++;
    m_numIterationsSinceChange = 0;
}