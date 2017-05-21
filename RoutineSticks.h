#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineSticks : public CRoutine
{
    public:
        static constexpr size_t   c_max_num_sticks = 32;
        static constexpr uint32_t c_min_period_sec = 20;
        static constexpr uint32_t c_max_period_sec = 40;
        static constexpr double   c_min_width_pct  = 0.02;
        static constexpr double   c_max_width_pct  = 0.10;

    public:
        CRoutineSticks(CPixelArray* pixels, size_t num_sticks);
        ~CRoutineSticks();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Sticks"; }

    private:
        size_t       m_num_sticks                 = 0;
        CPixelArray* m_arrays[c_max_num_sticks]   = {};
};
