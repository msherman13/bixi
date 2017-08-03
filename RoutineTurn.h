#pragma once

#include <cmath>

#include "Routine.h"
#include "FastLED.h"

class CPixelArrayLegs;

class CRoutineTurn : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = 32;
        static constexpr size_t c_delay_ms  = 1000;
        static constexpr size_t c_max_num_lit = 4;

    public:
        CRoutineTurn(CPixelArrayLegs* pixels, CRGB rgb, size_t num_shapes_lit);
        ~CRoutineTurn();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Turn"; }

    private:
        CRGB    m_color;
        size_t  m_last_run = 0;
        size_t  m_legs_lit[c_max_num_lit] = {};
        size_t  m_num_lit = 0;

    private:
        CPixelArrayLegs* GetPixelLegs();

    private:
        static CMemoryPool<CRoutineTurn, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineTurn*>(ptr));
        }   
};
