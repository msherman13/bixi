#pragma once

#include <cmath>

#include "Routine.h"
#include "FastLED.h"

class CRoutineRain : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty    = 32;
        static constexpr size_t c_period_ms    = 10000;
        static constexpr float  c_max_radius   = sqrt(2);
        static constexpr float  c_radius_delta = c_max_radius / c_period_ms;
        static constexpr float  c_q            = 20;
        static constexpr size_t c_num_circles  = 8;
        static constexpr float  c_midpoint_x   = 0.15;
        static constexpr float  c_midpoint_y   = 0.10;

    public:
        CRoutineRain(CPixelArray* pixels, size_t transition_time_ms, CRGB rgb);
        ~CRoutineRain();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Rain"; }

    private:
        void  RecalculateRadius();
        CHSV  RecalculateColor(size_t index);

    private:
        CHSV   m_color;
        float  m_radius[c_num_circles]   = {};
        size_t m_last_run = 0;

    private:
        static CMemoryPool<CRoutineRain, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineRain*>(ptr));
        }   
};
