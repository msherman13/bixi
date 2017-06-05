#pragma once

#include "stdint.h"

#include "Routine.h"
#include "FastLED.h"

class CRoutineCrawl : public CRoutine
{
    public:
        static constexpr size_t c_alloc_qty = 1;

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
