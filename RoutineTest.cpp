#include <algorithm>

#include "RoutineTest.h"
#include "PixelArray.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineTest, CRoutineTest::c_alloc_qty> CRoutineTest::s_pool;

CRoutineTest::CRoutineTest(CPixelArray* pixels) :
    CRoutine(pixels),
    m_last_run(millis())
{
    int random = rand() % 3;
    switch(random)
    {
        case 0: m_color = CRGB::Red;
        case 1: m_color = CRGB::Blue;
        case 2: m_color = CRGB::Green;
    }
}

CRoutineTest::~CRoutineTest()
{
}

void CRoutineTest::Continue()
{
    size_t now = millis();

    if(now - m_last_run < 1)
    {
        return;
    }

    m_last_run = now;

    for(size_t i=0;i<GetSize();i++)
    {
        if(i > m_index)
        {
            SetPixel(i, CRGB::Black);
        }
        else
        {
            SetPixel(i, CRGB::White);
        }
    }

    m_index = m_forward ? m_index + 1 : m_index - 1;

    if(m_index == GetSize() - 1 || m_index == 0)
    {
        m_forward = !m_forward;
    }
}
