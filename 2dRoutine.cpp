#include "2dRoutine.h"

C2dRoutine::C2dRoutine(CPixelArray* pixels) :
    CRoutine(pixels)
{
}

C2dRoutine::C2dRoutine(size_t num_arrays, CPixelArray** arrays) :
    CRoutine(num_arrays, arrays)
{
}

C2dRoutine::~C2dRoutine()
{
}

void C2dRoutine::Set2dPixel(size_t x, size_t y, CRGB rgb)
{
    m_2d_pixels[x][y] = rgb;
}

void C2dRoutine::ClearScreen()
{
    for(size_t x=0;x<c_resolution;x++)
    {
        for(size_t y=0;y<c_resolution;y++)
        {
            Set2dPixel(x, y, CRGB::Black);
        }
    }
}

void C2dRoutine::Redraw()
{
    for(size_t array=0;array<m_num_arrays;array++)
    {
        for(size_t i=0;i<m_arrays[array]->GetSize();i++)
        {
            CPixelArray::Coordinate coord = m_arrays[array]->GetCoordinate(i);
            size_t x_pixel = ((coord.x + c_max_axis_coord) / 2) * c_resolution;
            size_t y_pixel = ((coord.y + c_max_axis_coord) / 2) * c_resolution;
            m_arrays[array]->SetPixel(i, m_2d_pixels[x_pixel][y_pixel]);
        }
    }
}
