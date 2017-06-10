#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineCrawl : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = 2;

    public:
        CRoutineCrawl(CPixelArray* pixels,
                      size_t       transition_time_ms,
                      CRGB         base_color,
                      size_t       width,
                      size_t       start_offset,
                      bool         forward,
                      size_t       period_sec);
        ~CRoutineCrawl();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Crawl"; }

    private:
        bool     m_forward    = true;
        size_t   m_period_sec = 0;
        size_t   m_last_run   = 0;
        float    m_midpoint   = 0.0;
        size_t   m_width      = 0;
        CRGB     m_color;

    private:
        static CMemoryPool<CRoutineCrawl, c_alloc_qty> s_pool;

    public:
        void* operator new(size_t)
        {
            return s_pool.alloc();
        }

        void operator delete(void* ptr)
        {
            s_pool.free(reinterpret_cast<CRoutineCrawl*>(ptr));
        }
};
