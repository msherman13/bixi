#pragma once

#include "stdint.h"

#include "Routine.h"
#include "DoubleHex.h"

class CRoutineCycleHex : public CRoutine
{
    public:
        static constexpr size_t c_num_hexagons = 1;

    public:
        CRoutineCycleHex(CPixelArray& pixels);
        ~CRoutineCycleHex();

    public:
        virtual void        Start()    override;
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "CycleHex"; }

    private:
        CDoubleHex* m_hex = nullptr;
};
