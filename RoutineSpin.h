#pragma once

#include <cmath>

#include "Routine.h"
#include "FastLED.h"

class CRoutineSpin : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty    = 32;
        static constexpr size_t c_period_ms    = 40000;
        static constexpr float  c_max_theta    = 2 * M_PI;
        static constexpr float  c_theta_delta  = c_max_theta / c_period_ms;
        static constexpr float  c_q            = 60;
        static constexpr size_t c_num_spokes   = 6;

    public:
        CRoutineSpin(CPixelArray* pixels, CRGB rgb);
        ~CRoutineSpin();

    public:
        virtual const char* GetName()  override { return "Spin"; }

    protected:
        virtual void        Continue() override;

    private:
        void  RecalculateThetas();
        CHSV  RecalculateColor(size_t index);

    private:
        CHSV   m_color;
        float  m_theta[c_num_spokes] = {};
        size_t m_last_run = 0;

    private:
        static CMemoryPool<CRoutineSpin, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineSpin*>(ptr));
        }   
};
