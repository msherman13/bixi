#ifdef GEOM_DOME

#pragma once

#include <cmath>

#include "Routine.h"
#include "FastLED.h"

class CDome;
class CPixelArray;

class CRoutineExpand : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = 1;
        static constexpr size_t c_delay_ms  = 10000;
        static constexpr size_t c_group_ms  = 1000;
        static constexpr float  c_q         = 3;

    public:
        CRoutineExpand(CPixelArray* pixels);
        ~CRoutineExpand();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Expand"; }

    public:
        enum ShapeGroup
        {
            InnerHex,
            OuterHex,
            Other,
            All,
        };

    private:
        size_t     m_color_index = 0;
        size_t     m_last_run = 0;
        ShapeGroup m_shape_group = All;

    private:
        CDome* GetDome();
        void   Advance();
        float  CalculateBrightness();
        bool   isLit(size_t shape_index);

    private:
        static CMemoryPool<CRoutineExpand, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineExpand*>(ptr));
        }   
};

#endif // GEOM_DOME
