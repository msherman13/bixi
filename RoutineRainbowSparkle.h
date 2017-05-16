#pragma once

#include "RoutineSparkle.h"

class CRoutineRainbowSparkle : public CRoutineSparkle
{
    public:
        static const size_t c_iterationsPerColor = 5;
    public:
        CRoutineRainbowSparkle(CPixelArray& pixels);
        ~CRoutineRainbowSparkle();

    public:
        virtual CRGB GetColor() override { return CRGB(m_currHsv); }

    protected:
        virtual void        SetRandomPixels() override;
        virtual const char* GetName()         override { return "RainbowSparkle"; }

    private:
        CHSV m_currHsv;
        size_t m_numIterationsSinceChange;
};
