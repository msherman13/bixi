#pragma once

#include <cmath>

#include "Routine.h"
#include "FastLED.h"

class CRoutineRings : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty      = 32;
        static constexpr size_t c_period_ms      = 20000;
        static constexpr float  c_max_radius     = sqrt(2);
        static constexpr float  c_radius_delta   = c_max_radius / c_period_ms;
        static constexpr float  c_thickness      = 0.15;
        static constexpr size_t c_num_circles    = 3;
        static constexpr float  c_max_midpoint_x = 0.50;
        static constexpr float  c_max_midpoint_y = 0.50;

    public:
        CRoutineRings(CPixelArray* pixels);
        ~CRoutineRings();

    public:
        virtual const char* GetName()  override { return "Rings"; }

    protected:
        virtual void        Continue() override;

    private:
        void  RecalculateRadius();
        CRGB  RecalculateColor(size_t index);

    private:
        CPixelArray::Coordinate m_midpoint;
        CRGB                    m_color[c_num_circles];
        float                   m_radius[c_num_circles]   = {};
        size_t                  m_last_run = 0;

    private:
        static CMemoryPool<CRoutineRings, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineRings*>(ptr));
        }   
};
