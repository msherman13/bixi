#pragma once

#include <stdint.h>
#include <string>

#include "RoutineHoldRainbow.h"

class CRoutineCycleRainbow : public CRoutineHoldRainbow
{
    public:
        CRoutineCycleRainbow(std::string name);
        ~CRoutineCycleRainbow();

    public:
        virtual void Continue() override;

    private:
        uint32_t m_lastMove;
};
