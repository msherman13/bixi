#include "Bixi.h"

class CPixelArray;

class CBixiQuickCG : public CBixi
{
    public:
        static constexpr size_t c_pixels_x = 512;
        static constexpr size_t c_pixels_y = 512;
        static constexpr size_t c_pixel_width = 4;

    public:
        static CBixiQuickCG& Instance();
        ~CBixiQuickCG();
        CBixiQuickCG();

    protected:
        virtual void Show(CPixelArray* pixels) override;
};
