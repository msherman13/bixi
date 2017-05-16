#pragma once

#include <stdlib.h>

#include "Addressing.h"
#include "PixelArray.h"

class CPixel;
struct CRGB;

class CRoutine
{
    public:
        CRoutine(CPixelArray& pixels);
        virtual ~CRoutine();

    public:
        virtual void Start() = 0;
        virtual void Continue() = 0;
        virtual void Exit();
        virtual const char* GetName() = 0;

    public:
        size_t GetSize();
        void GetRGB(size_t index, CRGB& dest);

    protected:
        CPixelArray m_pixels;
};
