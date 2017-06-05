#include <algorithm>

#include "RoutineTest.h"
#include "PixelArray.h"
#include "FastLED.h"
#include "Arduino.h"

CMemoryPool<CRoutineTest, CRoutineTest::c_alloc_qty> CRoutineTest::s_pool;

CRoutineTest::CRoutineTest(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_pixels->SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_pixels->GetSize();i++)
    {
        CHSV hsv(((float)i / m_pixels->GetSize()) * 255, 255, 255);
        m_pixels->SetPixel(i, hsv);
    }

    m_last_run = millis();
}

CRoutineTest::~CRoutineTest()
{
}

void CRoutineTest::Continue()
{
    uint32_t now = millis();
    if(now - m_last_run < c_interval_ms)
    {
        return;
    }
    m_last_run = now;

    m_pixels->Shift(true, 1);
}
