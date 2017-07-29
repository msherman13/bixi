#ifdef GEOM_HEAD

#pragma once

#include "Routine.h"
#include "FastLED.h"
#include "Head.h"

class CRoutineTraverseNose : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty         = 8;
        static constexpr size_t c_min_delay_time_ms = 10 * 1000;
        static constexpr size_t c_max_delay_time_ms = 20 * 1000;
        static constexpr size_t c_traversal_time_ms = 100;

    public:
        CRoutineTraverseNose(CHead* head, CPixelArrayLegs* nose);
        ~CRoutineTraverseNose();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "TraverseNose"; }

    private:
        size_t GetNextRunRand();

    private:
        CHead* m_head = nullptr;
        size_t m_next_run  = 0;
        bool   m_in_run    = false;
        bool   m_run_done  = false;
        bool   m_top       = true;
        size_t m_curr_shape_off = 0;
        size_t m_last_step_ms = 0;
        CRoutine* m_cycle = nullptr;

    private:
        static CMemoryPool<CRoutineTraverseNose, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineTraverseNose*>(ptr));
        }   
};

#endif // GEOM_HEAD
