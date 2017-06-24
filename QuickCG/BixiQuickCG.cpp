#include "BixiQuickCG.h"
#include "quickcg.h"
#include "GammaCorrection.h"

CBixiQuickCG& CBixiQuickCG::Instance()
{
    static CBixiQuickCG bixi;
    return bixi;
}

CBixiQuickCG::CBixiQuickCG() :
    CBixi()
{
    QuickCG::screen(c_pixels_x, c_pixels_y, 0, "Bixi");

    GammaCorrection::Init(1.5);
}

CBixiQuickCG::~CBixiQuickCG()
{
}

void CBixiQuickCG::Show(CPixelArray* pixels)
{
    if(QuickCG::done())
    {
        ShutDown();
        return;
    }

    for(size_t i=0;i<pixels->GetSize();i++)
    {
        CRGB                    rgb   = pixels->GetPixel(i);
        CPixelArray::Coordinate coord = pixels->GetCoordinate(i);

        size_t x = ((coord.x + 1.0) / 2) * c_pixels_x;
        size_t y = ((coord.y + 1.0) / 2) * c_pixels_y;

        for(size_t x_w=0;x_w<c_pixel_width;x_w++)
        {
            for(size_t y_w=0;y_w<c_pixel_width;y_w++)
            {
                QuickCG::pset(x+x_w, y+y_w, QuickCG::ColorRGB(rgb.r, rgb.g, rgb.b));
            }
        }
    }

    QuickCG::redraw();
}
