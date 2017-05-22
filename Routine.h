#pragma once

#include <stdlib.h>

#include "PixelArray.h"

struct CRGB;

class CRoutine
{
    public:
        static constexpr size_t c_max_num_arrays = 32;

    public:
        CRoutine(CPixelArray* pixels);
        CRoutine(size_t num_arrays, CPixelArray* arrays);
        CRoutine(size_t num_arrays, CPixelArray** arrays);
        virtual ~CRoutine();

    public:
        virtual void        Continue() = 0;
        virtual const char* GetName() = 0;

    protected:
        CPixelArray* m_pixels;
        size_t       m_num_arrays               = 0;
        CPixelArray* m_arrays[c_max_num_arrays] = {};
};
