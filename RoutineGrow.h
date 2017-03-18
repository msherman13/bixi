#pragma once

#include "Routine.h"
#include "stdint.h"

class CRoutineGrow : public CRoutine
{
    public:
        CRoutineGrow(size_t size);
        ~CRoutineGrow();

    public:
        virtual void Start() override;
        virtual void Continue() override;
        virtual RoutineType GetType() override { return Grow; }

    private:
        uint32_t m_lastRun;
        size_t m_head;
        bool m_up;
};
