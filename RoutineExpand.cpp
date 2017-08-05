#include <algorithm>
#include <cmath>

#include "RoutineExpand.h"
#include "Dome.h"
#include "DomeMappings.h"
#include "ColorPallete.h"

CMemoryPool<CRoutineExpand, CRoutineExpand::c_alloc_qty> CRoutineExpand::s_pool;

CRoutineExpand::CRoutineExpand(CPixelArray* pixels) :
    CRoutine(pixels)
{
    m_color_index = rand() % ColorPallete::Qty;
}

CRoutineExpand::~CRoutineExpand()
{
}

CDome* CRoutineExpand::GetDome()
{
    return dynamic_cast<CDome*>(GetPixels());
}

void CRoutineExpand::Advance()
{
    size_t now = millis();

    if(m_shape_group == All && now - m_last_run >= c_delay_ms)
    {
        m_shape_group = InnerHex;
        m_last_run = now;
    }
    else if(m_shape_group != All && now - m_last_run >= c_group_ms)
    {
        m_shape_group = static_cast<ShapeGroup>(static_cast<int>(m_shape_group) + 1);
        m_last_run = now;

        if(m_shape_group == All)
        {
            m_color_index++;
            m_color_index %= ColorPallete::Qty;
        }
    }
}

float CRoutineExpand::CalculateBrightness()
{
    size_t now = millis();

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
            brightness = 1.0 - powf((float)(now - m_last_run - c_group_ms / 2) / (c_group_ms / 2), c_q);
            brightness = std::max<float>(brightness, 0.0);
        }
    }
}

bool CRoutineExpand::isLit(size_t shape_index)
{
    switch(m_shape_group)
    {
        case InnerHex:
            {
                bool inner = false;
                return DomeMappings::ShapeIsHex(shape_index, inner) && inner;
            }

        case OuterHex:
            {
                bool inner = false;
                return DomeMappings::ShapeIsHex(shape_index, inner) && !inner;
            }

        case Other:
            {
                bool inner = false;
                return DomeMappings::ShapeIsHex(shape_index, inner) == false;
            }

        default:
            return true;
    }
}

void CRoutineExpand::Continue()
{
    SetAllPixels(CRGB::Black);

    Advance();

    CHSV color = rgb2hsv_approximate(ColorPallete::s_colors[m_color_index]);
    color.v *= CalculateBrightness();

    for(size_t i=0;i<DomeMappings::c_num_shapes;i++)
    {
        CPixelArrayLegs* shape = GetDome()->GetShape(i);

        if(isLit(i) == true)
        {
            for(size_t index=0;index<shape->GetSize();index++)
            {
                SetPixel(index + shape->GetOffset(), color);
            }
        }
    }
}
