#pragma once

#include "stdint.h"

#include "Routine.h"

class CRoutineGrow : public CRoutine
{
    public:
        CRoutineGrow(CPixelArray& pixels);
        ~CRoutineGrow();

    public:
        virtual void        Start()    override;
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Grow"; }

    private:
        uint32_t m_lastRun;
        size_t m_head;
        bool m_up;
};
