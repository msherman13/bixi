#include <algorithm>
#include <math.h>

#include "RoutineFire.h"
#include "PixelArray.h"
#include "ColorPallete.h"
#include "FastLED.h"
#include "Arduino.h"

CRoutineFire::CRoutineFire(CPixelArray* arrays) :
    CRoutine(arrays)
{
    Init();
}

CRoutineFire::CRoutineFire(size_t num_arrays, CPixelArray** arrays) :
    CRoutine(num_arrays, arrays)
{
    Init();
}

CRoutineFire::~CRoutineFire()
{
}

void CRoutineFire::Init()
{
    for(size_t i=0;i<m_pixels->GetSize();i++)
    {
        m_pixels->SetPixel(i, CRGB::Black);
    }

  
    //generate the palette
    for(size_t i = 0;i < c_num_colors;i++)
    {
      //Hue goes from 0 to 85: red to yellow
      //Saturation is always the maximum: 255
      //Lightness is 0..255 for x=0..128, and 255 for x=128..255
      CHSV hsv(i / 3, 255, std::min<size_t>(255, i * 2));
      m_colors[i] = CRGB(hsv);
    }
}

void CRoutineFire::Continue()
{
    uint32_t now = millis();

    if(m_last_run - now < 50)
    {
        return;
    }

    m_last_run = now;

    //randomize the bottom row of the fire buffer
    for(int x = 0; x < c_num_pixels_per_axis; x++)
    {
        m_fire[c_num_pixels_per_axis - 1][x] = abs(32768 + rand()) % 256;
    }
    for(int y=0;y<c_num_pixels_per_axis;y++)
    {
        for(int x=0;x<c_num_pixels_per_axis;x++)
        {
            m_fire[y][x] =
                ((m_fire[(y + 1) % c_num_pixels_per_axis][(x - 1 + c_num_pixels_per_axis) % c_num_pixels_per_axis]
                + m_fire[(y + 1) % c_num_pixels_per_axis][(x) % c_num_pixels_per_axis]
                + m_fire[(y + 1) % c_num_pixels_per_axis][(x + 1) % c_num_pixels_per_axis]
                + m_fire[(y + 2) % c_num_pixels_per_axis][(x) % c_num_pixels_per_axis])
                * 32) / 129;
        }
    }

    for(size_t array=0;array<m_num_arrays;array++)
    {
        for(size_t i=0;i<m_arrays[array]->GetSize();i++)
        {
            CPixelArray::Coordinate coord = m_arrays[array]->GetCoordinate(i);
            size_t x_pixel = ((coord.x + c_max_axis_val) / 2) * c_num_pixels_per_axis;
            size_t y_pixel = ((coord.y + c_max_axis_val) / 2) * c_num_pixels_per_axis;
            m_arrays[array]->SetPixel(i, m_colors[m_fire[y_pixel][x_pixel]]);
        }
    }
}
