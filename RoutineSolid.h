#pragma once

#include "Routine.h"
#include "FastLED.h"

class CRoutineSolid : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty   = 32;

    public:
        CRoutineSolid(CPixelArray* pixels, size_t transition_time_ms, CRGB rgb);
        ~CRoutineSolid();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Solid"; }

    private:
        CRGB m_color;

    private:
        static CMemoryPool<CRoutineSolid, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineSolid*>(ptr));
        }   
};
