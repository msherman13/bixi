#pragma once

#include "RoutineSparkle.h"

class CRoutineRainbowSparkle : public CRoutineSparkle
{
    public:
        static const size_t c_iterationsPerColor = 5;
    public:
        CRoutineRainbowSparkle(size_t size);
        ~CRoutineRainbowSparkle();

    public:
        virtual CRGB GetColor() { return CRGB(m_currHsv); }
        virtual RoutineType GetType() override { return RainbowSparkle; }

    protected:
        virtual void SetRandomPixels() override;

    private:
        CHSV m_currHsv;
        size_t m_numIterationsSinceChange;
};
