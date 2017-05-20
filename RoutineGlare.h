#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineGlare : public CRoutine
{
    public:
        CRoutineGlare(CPixelArray* pixels,
                      CRGB         base_color,
                      size_t       q,
                      bool         forward,
                      uint32_t     period_sec);
        ~CRoutineGlare();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Glare"; }

    public:
        CRGB     BaseColorRGB() { return CRGB(m_base_color); }
        CHSV     BaseColor()    { return m_base_color; }
        bool     Forward()      { return m_forward; }
        uint32_t PeriodSec()    { return m_period_sec; }

    private:
        CHSV         m_base_color;
        size_t       m_q;
        bool         m_forward    = true;
        uint32_t     m_period_sec = 10;
        uint32_t     m_last_run   = 0;
        double       m_midpoint   = 0.0;
};
