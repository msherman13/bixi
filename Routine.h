#pragma once

#include <stdlib.h>

#include "PixelArray.h"

struct CRGB;

class CRoutine
{
    public:
        CRoutine(CPixelArray* pixels);
        virtual ~CRoutine();

    public:
        virtual void        Continue() = 0;
        virtual const char* GetName() = 0;

    protected:
        CPixelArray m_pixels;
};
