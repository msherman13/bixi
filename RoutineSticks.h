#pragma once

#include "stdint.h"

#include "FastLED.h"
#include "RoutineCrawl.h"

class CRoutineSticks : public CRoutine
{
    public:
        static constexpr size_t   c_alloc_qty      = 1;
        static constexpr size_t   c_max_num_sticks = 32;
        static constexpr uint32_t c_min_period_sec = 20;
        static constexpr uint32_t c_max_period_sec = 40;
        static constexpr float   c_min_width_pct  = 0.02;
        static constexpr float   c_max_width_pct  = 0.10;

    public:
        CRoutineSticks(CPixelArray* pixels, size_t num_sticks);
        ~CRoutineSticks();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Sticks"; }

    private:
        size_t       m_num_sticks                 = 0;
        CPixelArray* m_arrays[c_max_num_sticks]   = {};

    private:
        static CMemoryPool<CRoutineSticks, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineSticks*>(ptr));
        }
};
