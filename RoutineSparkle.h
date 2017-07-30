#pragma once

#include <cmath>

#include "Routine.h"
#include "FastLED.h"

class CRoutineSparkle : public CRoutine
{
    public:
        static constexpr size_t  c_alloc_qty   = 64;
        static constexpr size_t  c_release_ms  = 2000;
        static constexpr size_t  c_max_num_lit = 10;

    public:
        CRoutineSparkle(CPixelArray* pixels, CRGB rgb);
        ~CRoutineSparkle();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Sparkle"; }

    private:
        CHSV    m_color;
        size_t  m_num_lit = 0;
        size_t  m_last_run = 0;
        size_t  m_release_ms[c_max_num_lit] = {};
        size_t  m_lit[c_max_num_lit] = {};

    private:
        static CMemoryPool<CRoutineSparkle, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineSparkle*>(ptr));
        }   
};
