#pragma once

#include "Routine.h"
#include "FastLED.h"
#include <stdint.h>

class CRoutineSparkle : public CRoutine
{
    public:
        static constexpr CRGB::HTMLColorCode c_color = CRGB::WhiteSmoke;

    public:
        CRoutineSparkle(size_t size);
        ~CRoutineSparkle();

    public:
        virtual void Start() override;
        virtual void Continue() override;
        virtual RoutineType GetType() override { return Sparkle; }
        virtual CRGB GetColor() { return c_color; }

    protected:
        virtual void SetRandomPixels();

    private:
        uint32_t m_lastRun;
};
