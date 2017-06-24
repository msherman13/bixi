#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineCyclePallete : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = CPixelArray::c_max_num_legs;

    public:
        CRoutineCyclePallete(CPixelArray* pixels,
                             size_t       transition_time_ms,
                             bool         forward,
                             size_t       period_sec,
                             bool         dimensional=false);
        ~CRoutineCyclePallete();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "CyclePallete"; }

    private:
        size_t m_last_run    = 0;
        bool   m_forward     = true;
        size_t m_period_sec  = 0;
        float  m_midpoint    = 0.0;
        bool   m_dimensional = false;

    private:
        static CMemoryPool<CRoutineCyclePallete, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineCyclePallete*>(ptr));
        }   
};
