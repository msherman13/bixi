#pragma once

#include <stdint.h>

#include "RoutineHoldRainbow.h"

class CRoutineCycleRainbow : public CRoutineHoldRainbow
{
    public:
        CRoutineCycleRainbow(CPixelArray& pixels);
        ~CRoutineCycleRainbow();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "HoldRainbow"; }

    private:
        uint32_t m_lastMove;
};
