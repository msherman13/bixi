#pragma once

#include <stdlib.h>

#include "PixelArray.h"
#include "MemoryPool.h"

struct CRGB;

class CRoutine
{
    public:
        CRoutine(CPixelArray* pixels);
        virtual ~CRoutine();

    public:
        enum State
        {
            Running,
            ShuttingDown,
            Stopped,
        };

    public:
        virtual void        Continue() = 0;
        virtual const char* GetName()  = 0;
        virtual void        Shutdown();
        virtual bool        Done()      { return m_state == Stopped; }
        CPixelArray*        GetPixels() { return m_pixels; }

    protected:
        CPixelArray* m_pixels           = nullptr;
        State        m_state            = Running;
        uint32_t     m_shutdown_time_ms = 0;
};
