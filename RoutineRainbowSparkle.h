#pragma once

#include "RoutineSparkle.h"

class CRoutineRainbowSparkle : public CRoutineSparkle
{
    public:
        static const int c_iterationsPerColor = 5;
    public:
        CRoutineRainbowSparkle(int size);
        ~CRoutineRainbowSparkle();

    public:
        virtual CRGB GetColor() { return CRGB(m_currHsv); }

    protected:
        virtual void SetRandomPixels() override;

    private:
        CHSV m_currHsv;
        int m_numIterationsSinceChange;
};
