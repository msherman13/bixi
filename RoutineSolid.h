#pragma once

#include "Routine.h"
#include "FastLED.h"

class CRoutineSolid : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty   = 32;

    public:
        CRoutineSolid(CPixelArray* pixels, CRGB rgb);
        ~CRoutineSolid();

    public:
        virtual const char* GetName()  override { return "Solid"; }

    protected:
        virtual void        Continue() override;

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
