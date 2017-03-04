#pragma once

#include "Routine.h"

class CRoutineHoldRainbow : public CRoutine
{
    public:
        CRoutineHoldRainbow(size_t size);
        ~CRoutineHoldRainbow();

    public:
        virtual void Start() override;
        virtual void Continue() override;
        virtual RoutineType GetType() override { return HoldRainbow; }
};
