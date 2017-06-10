#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineGlare : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = CPixelArray::c_max_num_legs;

    public:
        CRoutineGlare(CPixelArray* pixels,
                      CRGB         base_color,
                      size_t       q,
                      bool         forward,
                      size_t     period_sec);
        ~CRoutineGlare();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Glare"; }

    public:
        CRGB     BaseColorRGB() { return CRGB(m_base_color); }
        CHSV     BaseColor()    { return m_base_color; }
        bool     Forward()      { return m_forward; }
        size_t PeriodSec()    { return m_period_sec; }

    private:
        CHSV         m_base_color;
        size_t       m_q;
        bool         m_forward    = true;
        size_t     m_period_sec = 10;
        size_t     m_last_run   = 0;
        float        m_midpoint   = 0.0;

    private:
        static CMemoryPool<CRoutineGlare, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineGlare*>(ptr));
        }   
};
