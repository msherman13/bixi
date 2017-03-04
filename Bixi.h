#pragma once

#include "Routine.h"
#include "FastLED.h"

class CBixi
{
    public:
        static constexpr size_t c_maxNumPins = 4; // don't exceed this
        static constexpr size_t c_numLeds = 120;
        static constexpr size_t c_numPins = 4;
        static constexpr size_t c_dataPins[c_maxNumPins] = { 2, 3, 4, 5 };

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
        CRoutine* GetRoutine(CRoutine::RoutineType type);

    private:
        CRGB m_leds[c_numLeds];
        CRoutine* m_routines[CRoutine::RoutineQty];
        CRoutine* m_currRoutine;

};
