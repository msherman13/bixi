#pragma once

#include "stdint.h"
#include <string>

#include "Routine.h"

class CRoutineGrow : public CRoutine
{
    public:
        CRoutineGrow(std::string name);
        ~CRoutineGrow();

    public:
        virtual void Start() override;
        virtual void Continue() override;

    private:
        uint32_t m_lastRun;
        size_t m_head;
        bool m_up;
};
