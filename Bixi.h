#pragma once

#include "Routine.h"
#include "FastLED.h"

class CBixi
{
    public:
        static constexpr size_t c_numLeds = 210;
        static constexpr size_t c_dataPin = 3;

    public: // singleton
        static CBixi& Instance();

    public:
        bool StartRoutine(CRoutine::RoutineType type);
        bool Continue();
        bool ExitCurrRoutine();

    private:
        CBixi();

    public:
        ~CBixi();

    private:
        void SetAllBlack();
        bool ShowCurrRoutine();
        void Show();
        CRoutine* ConstructRoutine(CRoutine::RoutineType type);

    private:
        CRGB m_leds[c_numLeds];
        CRoutine* m_routines[CRoutine::RoutineQty];
        CRoutine* m_currRoutine;

};
