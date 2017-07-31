#pragma once

#include "stdint.h"

#include "RoutineSparkle.h"
#include "FastLED.h"

class CRoutineStars : public CRoutineSparkle
{
    public:
        static constexpr size_t c_alloc_qty  = 8;
        static constexpr size_t c_attack     = 200;

    public:
        CRoutineStars(CPixelArray* pixels);
        ~CRoutineStars();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Stars"; }
        void                Advance();
        CRGB                CalculateColor(size_t index, bool& in_range);

    private:
        size_t    m_last_run   = 0;
        size_t    m_streak_start = 0;
        size_t    m_streak_duration = 0;
        size_t    m_next_streak_start = 0;
        float     m_start      = 0.0;
        size_t    m_width      = 0;
        bool      m_forward    = false;
        CHSV      m_color;

    private:
        static CMemoryPool<CRoutineStars, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineStars*>(ptr));
        }
};
