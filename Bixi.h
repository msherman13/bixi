#pragma once

#include "Routine.h"
#include "FastLED.h"

class CBixi
{
    public:
        // indicator
        static constexpr size_t c_indicatorPin = 13;
        static constexpr size_t c_indicatorDelayMs = 5000;

        // data output
        static constexpr size_t c_maxNumPins = 8;
        static constexpr size_t c_numLedsPerPin = 1000;
        //static constexpr size_t c_numPins = 4;
        static constexpr size_t c_numPins = 1;
        static constexpr size_t c_numLeds = c_numLedsPerPin * c_numPins;

    public: // singleton
        static CBixi& Instance();

    private:
        CBixi();

    public:
        ~CBixi();

    public:
        enum class State
        {
            Stopped,
            Initializing,
            Running,

            Qty,
            Undef,
        };
        static const char* sState(State state);

    public:
        bool StartRoutine(CRoutine::RoutineType type);
        bool Continue();
        bool ExitCurrRoutine();
        State GetState() { return m_state; }

    private:
        void SetAllBlack();
        bool ShowCurrRoutine();
        void Show();
        CRoutine* GetRoutine(CRoutine::RoutineType type);
        void SetState(State state);

    private:
        CRGB m_leds[c_numLeds];
        CRoutine* m_routines[CRoutine::RoutineQty];
        CRoutine* m_currRoutine = nullptr;
        size_t m_lastIndicator = 0;
        bool m_indicatorOn = false;
        State m_state = State::Undef;

};
