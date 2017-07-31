#pragma once

#include "stdint.h"

#include "RoutineSparkle.h"
#include "FastLED.h"

class CRoutineCrawl : public CRoutineSparkle
{
    public:
        static constexpr size_t c_alloc_qty = 16;

    public:
        CRoutineCrawl(CPixelArray* pixels,
                      CRGB         base_color,
                      size_t       width,
                      size_t       start_offset,
                      bool         forward,
                      size_t       period_sec);
        ~CRoutineCrawl();

    public:
        virtual void        Continue() override;
        virtual const char* GetName()  override { return "Crawl"; }
        void                Advance();
        CRGB                CalculateColor(size_t index, bool& in_range);

    private:
        bool      m_forward    = true;
        size_t    m_period_sec = 0;
        size_t    m_last_run   = 0;
        float     m_start      = 0.0;
        size_t    m_width      = 0;
        CHSV      m_color;

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
