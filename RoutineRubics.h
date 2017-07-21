#pragma once

#include "Routine.h"
#include "FastLED.h"
#include "PixelArray.h"

class CRoutineRubics : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty   = 8;
        static constexpr size_t c_swipe_duration_ms = 800;
        static constexpr float  c_swipe_distance_per_ms = 2.0 / c_swipe_duration_ms;
        static constexpr size_t c_time_between_swipes_ms = c_swipe_duration_ms + 3 * 1000;

    public:
        CRoutineRubics(CPixelArray* pixels);
        ~CRoutineRubics();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Rubics"; }

    private:
        void   InitSwipe();
        void   AdvanceSwipe();
        size_t Quadrant();

    private:
        size_t m_last_swipe  = 0;
        size_t m_last_run    = 0;
        CPixelArray::Coordinate m_midpoint;

    private:
        enum Direction
        {
            Left,
            Right,
            Up,
            Down,
        };
        Direction m_swipe_direction = Right;

    private:
        static CMemoryPool<CRoutineRubics, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineRubics*>(ptr));
        }   
};
