#pragma once

#include <stdlib.h>
#include "PixelArray.h"

class CRoutine;

class CDome : public CPixelArray
{
    public:
        static constexpr size_t c_num_shapes = 4;

    public:
        CDome(CRGB* leds);
        ~CDome();

    public:
        virtual void Continue() override;

    private:
        CPixelArray* m_shapes[c_num_shapes] = {};
        Config       s_config;
};
