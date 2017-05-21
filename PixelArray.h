#pragma once

#include <stdlib.h>
#include <stdint.h>

struct CRGB;
class  CRoutine;

class CPixelArray
{
    public:
        CPixelArray(size_t len); // new underlying pixels
        CPixelArray(CRGB* rgb, size_t len); // reference to external pixels
        CPixelArray(CPixelArray* rhs); // reference to external pixels (no copy!)
        ~CPixelArray();

    public:
        void StartRoutineSolid(CRGB rgb);
        void StartRoutineGlare(CRGB base_color, size_t q, bool forward, uint32_t period_sec);
        void StartRoutineCrawl(CRGB base_color, size_t width, size_t start_offset, bool forward, uint32_t period_sec);
        void StartRoutineSticks(size_t num_sticks);

    public:
        void ExitRoutine();
        void Continue();

    public:
        size_t GetSize()              { return m_length; }
        CRGB*  GetRaw(size_t index=0);

    public:
        CRGB   GetPixel(size_t index);
        void   SetPixel(size_t index, CRGB rgb);
        void   SetAllPixels(CRGB rgb);
        void   Shift(bool forward, size_t amount);
        void   SmartCopy(CPixelArray* rhs, size_t size, size_t offset=0);

    private:
        bool      m_owner      = false;
        CRGB*     m_pixels     = nullptr;
        size_t    m_length     = 0;
        CRoutine* m_routine    = nullptr;
};
