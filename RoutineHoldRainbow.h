#pragma once

#include "Routine.h"

class CRoutineHoldRainbow : public CRoutine
{
    public:
        CRoutineHoldRainbow(int size);
        ~CRoutineHoldRainbow();

    public:
        virtual void Start() override;
        virtual void Continue() override;
        virtual RoutineType GetType() override { return ROUTINE_HOLD_RAINBOW; }
};
