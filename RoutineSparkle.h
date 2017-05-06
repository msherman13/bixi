#pragma once

#include <stdint.h>
#include <string>

#include "Routine.h"
#include "FastLED.h"

class CRoutineSparkle : public CRoutine
{
    public:
        static constexpr CRGB::HTMLColorCode c_color = CRGB::WhiteSmoke;

    public:
        CRoutineSparkle(std::string name);
        ~CRoutineSparkle();

    public:
        virtual void Start() override;
        virtual void Continue() override;
        virtual CRGB GetColor() { return c_color; }

    protected:
        virtual void SetRandomPixels();

    private:
        uint32_t m_lastRun;
};
