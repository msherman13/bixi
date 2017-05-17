#pragma once

#include "stdint.h"

#include "Routine.h"
#include "Plain.h"

class CRoutinePlainTest : public CRoutine
{
    public:
        static constexpr size_t c_num_plains         = 4;
        static constexpr size_t c_num_legs_per_plain = 4;
        static constexpr size_t c_leg_length         = 52;

    public:
        CRoutinePlainTest(CPixelArray& pixels);
        ~CRoutinePlainTest();

    public:
        virtual void        Start()    override;
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "PlainTest"; }

    protected:
        void TogglePlain(size_t index, bool on_off);

    private:
        uint32_t m_lastRun              = 0;
        CPlain*  m_plains[c_num_plains] = {};
        bool     m_evenOdd              = false;
};
