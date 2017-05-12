#pragma once

#include <stdint.h>

#include "Routine.h"
#include "FastLED.h"

class CRoutineSparkle : public CRoutine
{
    public:
        static constexpr CRGB::HTMLColorCode c_color = CRGB::WhiteSmoke;

    public:
        CRoutineSparkle();
        ~CRoutineSparkle();

    public:
        virtual void        Start()    override;
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Sparkle"; }
        virtual CRGB        GetColor() { return c_color; }

    protected:
        virtual void SetRandomPixels();

    private:
        uint32_t m_lastRun;
};
