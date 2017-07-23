#pragma once

#include <stdlib.h>

#include "PixelArray.h"
#include "MemoryPool.h"

struct CRGB;

class CRoutine
{
    public:
        static constexpr float c_transition_q = 2.0;

    public:
        CRoutine(CPixelArray* pixels);
        virtual ~CRoutine();

    public:
        virtual void            Continue() = 0;
        virtual const char*     GetName()  = 0;
        size_t                  StartMs()   { return m_start_time_ms; }
        void                    TransitionOut(size_t duration_ms);
        bool                    InTransition();
        bool                    TransitionDone();
        void                    SetAllPixels();
        void                    SetPixel(size_t index, CRGB rgb);
        void                    SetAllPixels(CRGB rgb);
        CRGB                    GetPixel(size_t index);
        CPixelArray*            GetPixels() { return m_pixels; }
        void                    SetPixels(CPixelArray* pixels) { m_pixels = pixels; }
        size_t                  GetSize();
        CPixelArray::Coordinate GetCoordinate(size_t index);
        const char*             GetPixelName();

    private:
        CPixelArray* m_pixels              = nullptr;
        size_t       m_start_time_ms       = 0;
        size_t       m_transition_start_ms = 0;
        size_t       m_transition_time_ms  = 0;
        float        m_transition_weight   = 0.0;
        bool         m_in_transition       = false;
        size_t       m_last_iteration      = 0;
};
