#pragma once

#include "Routine.h"
#include "FastLED.h"

class CBixi
{
    public:
        static const int c_numLeds = 60;
        static const int c_dataPin = 6;

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
        CRoutine* m_routines[CRoutine::ROUTINE_QTY];
        CRoutine* m_currRoutine;

};
