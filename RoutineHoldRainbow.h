#pragma once

#include "Routine.h"

class CRoutineHoldRainbow : public CRoutine
{
    public:
        CRoutineHoldRainbow();
        ~CRoutineHoldRainbow();

    public:
        virtual void        Start()    override;
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "HoldRainbow"; }
};
