#pragma once

#include "FastLED.h"
#include "PixelArray.h"

class CDome;

class CBixi
{
    public:
        static constexpr size_t c_indicatorPin     = 13;
        static constexpr size_t c_indicatorDelayMs = 5000;
        static constexpr size_t c_num_shapes       = 4;

    public: // singleton
        static CBixi& Instance();
        CBixi();
        ~CBixi();

    public:
        void Continue();

    protected:
        virtual void Show(CPixelArray* pixels);

    private:
        CPixelArray  m_pixels;
        size_t       m_lastIndicator = 0;
        bool         m_indicatorOn   = false;
        CPixelArray* m_geometry      = nullptr;
};
