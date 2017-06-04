#pragma once

#include "stdint.h"

#include "Routine.h"

class CRoutineTest : public CRoutine
{
    public:
        static constexpr size_t c_interval_ms = 50;

    public:
        CRoutineTest(CPixelArray* pixels);
        ~CRoutineTest();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Test"; }

    private:
        uint32_t m_last_run = 0;
};
