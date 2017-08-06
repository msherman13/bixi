#include <algorithm>
#include <cmath>

#include "RoutineTurn.h"
#include "PixelArrayLegs.h"

CMemoryPool<CRoutineTurn, CRoutineTurn::c_alloc_qty> CRoutineTurn::s_pool;

CRoutineTurn::CRoutineTurn(CPixelArrayLegs* pixels, CRGB rgb, size_t num_shapes_lit) :
    CRoutine(pixels),
    m_color(rgb),
    m_last_run(millis()),
    m_num_lit(num_shapes_lit)
{
    size_t index = 0;
    size_t mod   = GetPixelLegs()->NumLegs() / m_num_lit;
    for(size_t i=0;i<GetPixelLegs()->NumLegs();i++)
    {
        if(i % mod == 0)
        {
            m_legs_lit[index++] = i;
        }
    }
}

CRoutineTurn::~CRoutineTurn()
{
}

CPixelArrayLegs* CRoutineTurn::GetPixelLegs()
{
    return reinterpret_cast<CPixelArrayLegs*>(GetPixels());
}

void CRoutineTurn::Continue()
{
    size_t now = millis();

    if(now - m_last_run >= c_delay_ms)
    {
        for(size_t i=0;i<m_num_lit;i++)
        {
            m_legs_lit[i] = (m_legs_lit[i] + 1) % (GetPixelLegs()->NumLegs());
        }
        m_last_run = now;
    }

    SetAllPixels(CRGB::Black);

    for(size_t i=0;i<m_num_lit;i++)
    {
        CPixelArray* leg = GetPixelLegs()->GetLeg(m_legs_lit[i]);
        leg->SetAllPixels(m_color);
    }
}
