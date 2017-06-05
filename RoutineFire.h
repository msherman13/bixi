#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CPixelArray;

class CRoutineFire : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty           = 1;
        static constexpr size_t c_num_colors          = 256;
        static constexpr int    c_num_pixels_per_axis = 100;
        static constexpr double c_max_axis_val        = 1.00;

    public:
        CRoutineFire(CPixelArray* pixels);
        ~CRoutineFire();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Fire"; }

    private:
        void Init();

    private:
        CRGB     m_colors[c_num_colors];
        uint32_t m_fire[c_num_pixels_per_axis][c_num_pixels_per_axis] = {};
        uint32_t m_last_run = 0;

        /*
    private:
        static CMemoryPool<CRoutineFire, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineFire*>(ptr));
        }
        */
};
