#pragma once

#include <stdlib.h>

#include "PixelArray.h"
#include "MemoryPool.h"

struct CRGB;

class CRoutine
{
    public:
        CRoutine(CPixelArray* pixels);
        virtual ~CRoutine();

    public:
        void                    onIteration();
        virtual const char*     GetName()  = 0;
        size_t                  StartMs()   { return m_start_time_ms; }
        void                    TransitionOut(size_t duration_ms);
        bool                    InTransition();
        void                    RecalculateTransition();
        void                    SetAllPixels();
        void                    SetPixel(size_t index, CRGB rgb);
        void                    SetAllPixels(CRGB rgb);
        CRGB                    GetPixel(size_t index);
        CPixelArray*            GetPixels() { return m_pixels; }
        void                    SetPixels(CPixelArray* pixels) { m_pixels = pixels; }
        size_t                  GetSize();
        CPixelArray::Coordinate GetCoordinate(size_t index);
        const char*             GetPixelName();

    protected:
        virtual void            Continue() = 0;

    private:
        CPixelArray* m_pixels              = nullptr;
        size_t       m_start_time_ms       = 0;
        size_t       m_transition_start_ms = 0;
        size_t       m_transition_time_ms  = 0;
        bool         m_in_transition       = false;
        float        m_max_y_pixel         = 0.0;
};
