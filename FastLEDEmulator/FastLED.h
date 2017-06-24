#pragma once

#include "pixeltypes.h"
#include <iostream>
#include <fstream>

#define WS2811_PORTD 1
#define WS2813_PORTD 2
#define OCTOWS2813 3

class CFastLED
{
    public:
        static constexpr size_t c_refresh_rate  = 60; // frames per second
        static constexpr size_t c_sleep_time_ms = (1.00 / c_refresh_rate) * 1000;

    public:
        CFastLED();

    public:
        template <size_t TYPE, size_t NUM_PINS>
        void addLeds(CRGB* leds, size_t numLedsPerPin)
        {
        }
        template <size_t TYPE>
        void addLeds(CRGB* leds, size_t numLedsPerPin)
        {
        }
        void show();
        void countFPS(int nFrames=25);
        uint16_t getFPS() { return m_nFPS; }
        void setBrightness(int val) {}

    private:
        size_t m_numLeds = 0;
        CRGB* m_leds = nullptr;
        std::ofstream m_file;
        uint16_t m_nFPS = 0;
};

extern CFastLED FastLED;
extern CFastLED LEDS;

struct FRGB
{
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
};

struct FHSV
{
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
};

void frgb2fhsv(double fR, double fG, double fB, double& fH, double& fS, double& fV);
CHSV rgb2hsv_approximate( const CRGB& rgb);
