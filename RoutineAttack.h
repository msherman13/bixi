#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CDome;

class CRoutineAttack : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty  = 24;
        static constexpr size_t c_attack     = 1;

    public:
        CRoutineAttack(CPixelArray* pixels);
        ~CRoutineAttack();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Attack"; }
        void                Advance();
        CRGB                CalculateColor();

    private:
        size_t    m_streak_start = 0;
        size_t    m_streak_duration = 0;
        size_t    m_next_streak_start = 0;
        CHSV      m_color;

    private:
        static CMemoryPool<CRoutineAttack, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineAttack*>(ptr));
        }
};
