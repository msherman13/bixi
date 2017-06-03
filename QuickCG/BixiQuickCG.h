#include "Bixi.h"

class CPixelArray;

class CBixiQuickCG : public CBixi
{
    public:
        static constexpr size_t c_pixels_x = 1024;
        static constexpr size_t c_pixels_y = 1024;
        static constexpr size_t c_pixel_width = 2;

    public:
        static CBixiQuickCG& Instance();
        ~CBixiQuickCG();
        CBixiQuickCG();

    protected:
        virtual void Show(CPixelArray* pixels) override;

    private:
        uint32_t m_buffer[c_pixels_y][c_pixels_x] = {};
};
