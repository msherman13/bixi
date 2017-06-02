#include "BixiQuickCG.h"
#include "quickcg.h"

CBixiQuickCG& CBixiQuickCG::Instance()
{
    static CBixiQuickCG bixi;
    return bixi;
}

CBixiQuickCG::CBixiQuickCG() :
    CBixi()
{
    QuickCG::screen(c_pixels_x, c_pixels_y, 0, "Bixi");
}

CBixiQuickCG::~CBixiQuickCG()
{
}

void CBixiQuickCG::Show(CPixelArray* pixels)
{
    for(size_t x=0;x<c_pixels_x;x++)
    {
        for(size_t y=0;y<c_pixels_y;y++)
        {
            QuickCG::pset(x, y, QuickCG::ColorRGB(0, 0, 0));
        }
    }

    for(size_t i=0;i<pixels->GetSize();i++)
    {
        CRGB                    rgb   = pixels->GetPixel(i);
        CPixelArray::Coordinate coord = pixels->GetCoordinate(i);

        size_t x = (coord.x + 0.5) * c_pixels_x;
        size_t y = (coord.y + 0.5) * c_pixels_y;

        for(size_t x_w=0;x_w<c_pixel_width;x_w++)
        {
            for(size_t y_w=0;y_w<c_pixel_width;y_w++)
            {
                QuickCG::pset(x + x_w, y + y_w, QuickCG::ColorRGB(rgb.r, rgb.g, rgb.b));
            }
        }
    }

    QuickCG::redraw();
}
