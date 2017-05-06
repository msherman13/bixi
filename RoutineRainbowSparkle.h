#pragma once

#include <string>

#include "RoutineSparkle.h"

class CRoutineRainbowSparkle : public CRoutineSparkle
{
    public:
        static const size_t c_iterationsPerColor = 5;
    public:
        CRoutineRainbowSparkle(std::string name);
        ~CRoutineRainbowSparkle();

    public:
        virtual CRGB GetColor() { return CRGB(m_currHsv); }

    protected:
        virtual void SetRandomPixels() override;

    private:
        CHSV m_currHsv;
        size_t m_numIterationsSinceChange;
};
