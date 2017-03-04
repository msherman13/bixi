#pragma once

#include "RoutineHoldRainbow.h"
#include <stdint.h>

class CRoutineCycleRainbow : public CRoutineHoldRainbow
{
    public:
        CRoutineCycleRainbow(size_t size);
        ~CRoutineCycleRainbow();

    public:
        virtual void Continue() override;
        virtual RoutineType GetType() override { return CycleRainbow; }

    private:
        uint32_t m_lastMove;
};
