#pragma once

#include "Routine.h"
#include "FastLED.h"

class CRoutineTest : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty   = 24;

    public:
        CRoutineTest(CPixelArray* pixels);
        ~CRoutineTest();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Test"; }

    private:
        size_t m_index    = 0;
        size_t m_last_run = 0;
        bool   m_forward  = true;
        CRGB   m_color;

    private:
        static CMemoryPool<CRoutineTest, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineTest*>(ptr));
        }   
};
