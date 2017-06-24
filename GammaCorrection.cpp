#include "GammaCorrection.h"
#include "Logging.h"

uint8_t GammaCorrection::s_lut[256] = {};
bool    GammaCorrection::s_initialized = false;

void GammaCorrection::Init(float factor)
{
    const int max_in = 255;
    const int max_out = 255;

    for(int i=0; i<=max_in; i++)
    {
        s_lut[i] = (int)(powf((float)i / (float)max_in, factor) * max_out + 0.5);
    }

    s_initialized = true;
}

CRGB GammaCorrection::CorrectGamma(CRGB rgb)
{
    if(s_initialized == false)
    {
        CLogging::log("GammaCorrection::CorrectGamma: Not initialized. Exiting...");
        exit(0);
    }

    return CRGB(s_lut[rgb.r], s_lut[rgb.g], s_lut[rgb.b]);
}
