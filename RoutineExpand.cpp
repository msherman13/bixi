#include <algorithm>
#include <cmath>

#include "RoutineExpand.h"
#include "Dome.h"
#include "DomeMappings.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineExpand, CRoutineExpand::c_alloc_qty> CRoutineExpand::s_pool;

CRoutineExpand::CRoutineExpand(CPixelArray* pixels) :
    CRoutine(pixels),
    m_last_run(millis())
{
    m_color = rgb2hsv_approximate(CRGB(ColorPallete::s_colors[rand() % ColorPallete::Qty]));
}

CRoutineExpand::~CRoutineExpand()
{
}

CDome* CRoutineExpand::GetDome()
{
    return dynamic_cast<CDome*>(GetPixels());
}

void CRoutineExpand::Continue()
{
    size_t now = millis();

    if(m_shape_group == All && now - m_last_run >= c_delay_ms)
    {
        m_shape_group = InnerHex;
        m_last_run = now;
        m_color = rgb2hsv_approximate(CRGB(ColorPallete::s_colors[rand() % ColorPallete::Qty]));
    }
    else if(m_shape_group != All && now - m_last_run >= c_group_ms)
    {
        m_shape_group = static_cast<ShapeGroup>(static_cast<int>(m_shape_group) + 1);
        m_last_run = now;
    }

    SetAllPixels(CRGB::Black);

    float brightness;
    if(m_shape_group == All)
    {
        brightness = powf((float)(now - m_last_run) / (c_group_ms / 2), c_q);
        brightness = std::min<float>(brightness, 1.0);
    }
    else
    {
        float time_ms = now - m_last_run;
        if(time_ms < c_group_ms / 2)
        {
            brightness = powf((float)(now - m_last_run) / (c_group_ms / 2), c_q);
            brightness = std::min<float>(brightness, 1.0);
        }
        else
        {
            brightness = 1.0 - powf((float)(now - m_last_run + c_group_ms / 2) / (c_group_ms / 2), c_q);
            brightness = std::min<float>(brightness, 1.0);
        }
    }

    CHSV color = m_color;
    color.v *= brightness;

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        CPixelArrayLegs* shape = GetDome()->GetShape(i);
        bool lit = false;

        switch(m_shape_group)
        {
            case InnerHex:
                {
                    bool inner = false;
                    lit = DomeMappings::ShapeIsHex(i, inner) && inner;
                }
                break;

            case OuterHex:
                {
                    bool inner = false;
                    lit = DomeMappings::ShapeIsHex(i, inner) && !inner;
                }
                break;

            case Other:
                {
                    bool inner = false;
                    lit = DomeMappings::ShapeIsHex(i, inner) == false;
                }
                break;

            case All:
                lit = true;
                break;
        }

        if(lit == true)
        {
            for(size_t index=0;index<shape->GetSize();index++)
            {
                SetPixel(index - shape->GetOffset(), color);
            }
        }
    }
}
