#pragma once

#include "Routine.h"
#include "FastLED.h"

class CRoutineIdle : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = CPixelArray::c_max_num_legs;

    public:
        CRoutineIdle(CPixelArray* pixels);
        ~CRoutineIdle();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Idle"; }

    private:
        static CMemoryPool<CRoutineIdle, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineIdle*>(ptr));
        }   
};
