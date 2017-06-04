#pragma once

#include "Routine.h"
#include "FastLED.h"

class C2dRoutine : public CRoutine
{
    public:
        static constexpr size_t c_resolution     = 128;
        static constexpr float  c_max_axis_coord = 1.00;

    public:
        C2dRoutine(CPixelArray* pixels);
        C2dRoutine(size_t num_arrays, CPixelArray* arrays);
        C2dRoutine(size_t num_arrays, CPixelArray** arrays);
        virtual ~C2dRoutine();

    protected:
        void   ClearScreen();
        void   Set2dPixel(size_t x, size_t y, CRGB rgb);
        void   Redraw();
        size_t CoordTo2d(float coord) { return (coord + c_max_axis_coord) * c_resolution; }

    protected:
        CRGB m_2d_pixels[c_resolution][c_resolution];
};
