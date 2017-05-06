#pragma once

#include <string>

#include "Routine.h"

class CRoutineHoldRainbow : public CRoutine
{
    public:
        CRoutineHoldRainbow(std::string name);
        ~CRoutineHoldRainbow();

    public:
        virtual void Start() override;
        virtual void Continue() override;
};
