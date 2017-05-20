#include "FastLED.h"
#include "Arduino.h"

#include <cstdio>
#include <unistd.h>

CFastLED::CFastLED()
{
    m_file.open("sim.csv");
}

void CFastLED::show()
{
    m_file << millis();
    for(size_t i=0;i<m_numLeds;i++)
    {
        char logstr[16];
        sprintf(logstr, "0x%02X%02X%02X", m_leds[i].r, m_leds[i].g, m_leds[i].b);
        m_file << "," << logstr;
    }
    m_file << std::endl;

    // fake the refresh rate
    increment_time(c_sleep_time_ms);
}

CFastLED FastLED;

CHSV rgb2hsv_approximate(const CRGB& rgb)
{
    FRGB frgb;
    frgb.r = (double)rgb.r / 255;
    frgb.g = (double)rgb.g / 255;
    frgb.b = (double)rgb.b / 255;

    FHSV hsv;
    frgb2fhsv(frgb.r, frgb.g, frgb.b, hsv.h, hsv.s, hsv.v);

    CHSV ret;
    ret.h = (hsv.h / 360) * 255;
    ret.s = hsv.s * 255;
    ret.v = hsv.v * 255;

    return ret;
}

void frgb2fhsv(double fR, double fG, double fB, double& fH, double& fS, double& fV)
{
  double fCMax = std::max(std::max(fR, fG), fB);
  double fCMin = std::min(std::min(fR, fG), fB);
  double fDelta = fCMax - fCMin;

  if(fDelta > 0) {
    if(fCMax == fR) {
      fH = 60 * (fmod(((fG - fB) / fDelta), 6));
    } else if(fCMax == fG) {
      fH = 60 * (((fB - fR) / fDelta) + 2);
    } else if(fCMax == fB) {
      fH = 60 * (((fR - fG) / fDelta) + 4);
    }

    if(fCMax > 0) {
      fS = fDelta / fCMax;
    } else {
      fS = 0;
    }

    fV = fCMax;
  } else {
    fH = 0;
    fS = 0;
    fV = fCMax;
  }

  if(fH < 0) {
    fH = 360 + fH;
  }
}
