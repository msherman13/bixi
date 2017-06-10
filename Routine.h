#pragma once

#include <stdlib.h>

#include "PixelArray.h"
#include "MemoryPool.h"

struct CRGB;

class CRoutine
{
    public:
        CRoutine(CPixelArray* pixels, size_t transition_time_ms=0);
        virtual ~CRoutine();

    public:
        virtual void            Continue() = 0;
        virtual const char*     GetName()  = 0;
        size_t                  StartMs()   { return m_start_time_ms; }
        bool                    InTransition();
        void                    SetAllPixels();
        void                    SetPixel(size_t index, CRGB rgb);
        void                    SetAllPixels(CRGB rgb);
        CRGB                    GetPixel(size_t index);
        size_t                  GetSize();
        CPixelArray::Coordinate GetCoordinate(size_t index);

    private:
        CPixelArray* m_pixels             = nullptr;
        size_t       m_start_time_ms      = 0;
        size_t       m_transition_time_ms = 0;
};
