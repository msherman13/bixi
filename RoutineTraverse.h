#ifdef GEOM_LEGS_NECK

#pragma once

#include "Routine.h"
#include "FastLED.h"
#include "LegsAndNeck.h"

class CRoutineTraverse : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty   = 8;
        static constexpr size_t c_min_delay_time_ms = 10 * 1000;
        static constexpr size_t c_max_delay_time_ms = 20 * 1000;
        static constexpr size_t c_traversal_time_ms = 500;

    public:
        CRoutineTraverse(CLegsAndNeck* pixels, CRGB rgb);
        ~CRoutineTraverse();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Traverse"; }

    private:
        size_t GetNextRunRand();

    private:
        CRGB   m_color;
        size_t m_next_run  = 0;
        bool   m_in_run    = false;
        bool   m_run_done  = false;
        CPixelArray* m_shapes_in_run[LegsAndNeckMappings::c_num_neck_shapes+1] = {};
        size_t m_curr_shape_off = 0;
        size_t m_last_step_ms = 0;

    private:
        static CMemoryPool<CRoutineTraverse, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineTraverse*>(ptr));
        }   
};

#endif // GEOM_LEGS_NECK
