#pragma once

#include "stdint.h"

#include "Routine.h"
#include "Plain.h"

class CRoutineCycleHex : public CRoutine
{
    public:
        static constexpr size_t c_num_hexagons = 1;
        static constexpr size_t c_num_plains   = c_num_hexagons * 6;

    public:
        CRoutineCycleHex(CPixelArray& pixels);
        ~CRoutineCycleHex();

    public:
        virtual void        Start()    override;
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "CycleHex"; }
        void                TogglePlain(size_t index, bool on_off);

    private:
        uint32_t m_lastRun                = 0;
        size_t   m_count                  = 0;
        CPlain*  m_plains[c_num_plains]   = {};
        CHSV     m_color;
};
