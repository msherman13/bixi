#pragma once

#define USE_OCTOWS2811
#include "OctoWS2811.h"
#include "FastLED.h"
#include "PixelArray.h"
#include "Addressing.h"

class CBixi
{
    public:
        static constexpr size_t c_indicatorPin     = 13;
        static constexpr size_t c_indicatorDelayMs = 1000;
        static constexpr size_t c_num_shapes       = 22;

    public: // singleton
        static CBixi& Instance();
        CBixi();
        ~CBixi();

    public:
        void Continue();
        void ShutDown() { m_shutting_down = true; }
        bool ShuttingDown() { return m_shutting_down; }

    protected:
        virtual void Show(CPixelArray* pixels);

    private:
        size_t       m_lastIndicator = 0;
        bool         m_indicatorOn   = false;
        CPixelArray* m_geometry      = nullptr;
        bool         m_shutting_down = false;
};
