#include <algorithm>
#include <cmath>

#include "RoutineFire.h"
#include "PixelArray.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "Arduino.h"

CMemoryPool<CRoutineFire, CRoutineFire::c_alloc_qty> CRoutineFire::s_pool;

CRoutineFire::CRoutineFire(CPixelArray* pixels) :
    CRoutine(pixels)
{
    Init();
}

CRoutineFire::~CRoutineFire()
{
}

void CRoutineFire::Init()
{
    for(size_t i=0;i<GetSize();i++)
    {
        SetPixel(i, CRGB::Black);
    }
  
    //generate the palette
    for(size_t i = 0;i < c_num_colors;i++)
    {
      //Hue goes from 0 to 85: red to yellow
      //Saturation is always the maximum: 255
      //Lightness is 0..255 for x=0..128, and 255 for x=128..255
      CHSV hsv(i / 3, 255, std::min<size_t>(255, i * 2));
      m_colors[i] = hsv;
    }

    m_last_run = millis();
}

void CRoutineFire::Continue()
{
    size_t now = millis();

    if(now - m_last_run < 60)
    {
        return;
    }

    m_last_run = now;

    //randomize the bottom row of the fire buffer
    for(int x = 0; x < 1; x++)
    {
        m_fire[c_y_pixels - 1][x] = abs(32768 + rand()) % 256;
        if(m_fire[c_y_pixels - 1][x] < 100)
            m_fire[c_y_pixels - 1][x] = 100;
    }
    for(int y=0;y<c_y_pixels;y++)
    {
        for(int x=0;x<c_x_pixels;x++)
        {
            m_fire[y][x] =
                ((m_fire[(y + 1) % c_y_pixels][(x - 1 + c_x_pixels) % c_x_pixels]
                + m_fire[(y + 1) % c_y_pixels][(x) % c_x_pixels]
                + m_fire[(y + 1) % c_y_pixels][(x + 1) % c_x_pixels]
                + m_fire[(y + 2) % c_y_pixels][(x) % c_x_pixels])
                * 32) / 129;
        }
    }

    for(size_t i=0;i<GetSize();i++)
    {
        CPixelArray::Coordinate coord(0.0, (float)i / GetSize());
        size_t x_pixel = ((coord.x + c_max_axis_val) / 2) * c_x_pixels;
        size_t y_pixel = ((coord.y + c_max_axis_val) / 2) * c_y_pixels;
        CHSV color = m_colors[m_fire[c_y_pixels - 1 - y_pixel][c_x_pixels - 1 - x_pixel]];
        color.s = color.s * 0.70;
        if(color.s < 100)
            color.s = 100;
        color.v = std::min<uint8_t>(255, color.v * 1.70);
        SetPixel(i, color);
    }
}
