#pragma once

#include "Routine.h"
#include "FastLED.h"
#include <stdint.h>

class CRoutineSparkle : public CRoutine
{
    public:
        static const CRGB::HTMLColorCode c_color = CRGB::WhiteSmoke;

    public:
        CRoutineSparkle(int size);
        ~CRoutineSparkle();

    public:
        virtual void Start() override;
        virtual void Continue() override;
        virtual RoutineType GetType() override { return ROUTINE_SPARKLE; }
        virtual CRGB GetColor() { return c_color; }

    protected:
        virtual void SetRandomPixels();

    private:
        uint32_t m_lastRun;
};
