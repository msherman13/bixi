#pragma once

#include "stdint.h"

#include "Routine.h"

class CRoutineBall;
class CPixelArray;

class CRoutineBalls : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty     = 2;
        static constexpr size_t c_max_num_balls = 16;
        static constexpr size_t c_min_q         = 20;
        static constexpr size_t c_max_q         = 40;
        static constexpr size_t c_min_period    = 10;
        static constexpr size_t c_max_period    = 20;

    public:
        CRoutineBalls(CPixelArray* pixels, size_t transition_time_ms, size_t num_balls);
        ~CRoutineBalls();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Balls"; }

    private:
        size_t        m_num_balls = 0;
        CRoutineBall* m_balls[c_max_num_balls] = {};

    private:
        static CMemoryPool<CRoutineBalls, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineBalls*>(ptr));
        }

};
