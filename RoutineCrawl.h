#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineCrawl : public CRoutine
{
    public:
        CRoutineCrawl(CPixelArray* pixels,
                      CRGB         base_color,
                      size_t       width,
                      size_t       start_offset,
                      bool         forward,
                      uint32_t     period_sec);
        ~CRoutineCrawl();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Crawl"; }

    private:
        bool     m_forward  = true;
        uint32_t m_delay_ms = 0;
        uint32_t m_last_run = 0;
};
