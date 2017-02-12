#pragma once

#include "RoutineHoldRainbow.h"
#include <stdint.h>

class CRoutineCycleRainbow : public CRoutineHoldRainbow
{
    public:
        CRoutineCycleRainbow(int size);
        ~CRoutineCycleRainbow();

    public:
        virtual void Continue() override;
        virtual RoutineType GetType() override { return ROUTINE_CYCLE_RAINBOW; }

    private:
        uint32_t m_lastMove;
};
