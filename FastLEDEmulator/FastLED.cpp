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
CFastLED LEDS;

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

void CFastLED::countFPS(int nFrames) {
  static int br = 0;
  static uint32_t lastframe = 0; // millis();

  if(br++ >= nFrames) {
		uint32_t now = millis();
		now -= lastframe;
		m_nFPS = (br * 1000) / now;
    br = 0;
    lastframe = millis();
  }
}


/*
CHSV rgb2hsv_approximate(const CRGB& rgb)
{
  float r, g, b, h = 0.0, s = 0.0, v; //this function works with floats between 0 and 1
  r = rgb.r / 256.0;
  g = rgb.g / 256.0;
  b = rgb.b / 256.0;

  float maxColor = std::max(r, std::max(g, b));
  float minColor = std::min(r, std::min(g, b));

  v = maxColor;

  if(maxColor != 0.0) //avoid division by zero when the color is black
  {
    s = (maxColor - minColor) / maxColor;
  }

  if(s == 0.0)
  {
    h = 0.0; //it doesn't matter what value it has
  }
  else
  {
    if(r == maxColor) h = (g - b) / (maxColor - minColor);
    if(g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
    if(b == maxColor) h = 4.0 + (r - g) / (maxColor - minColor);

    h /= 6.0; //to bring it to a number between 0 and 1
    if(h < 0.0) h++;
  }

  CHSV hsv;
  hsv.h = h * 255.0;
  hsv.s = s * 255.0;
  hsv.v = v * 255.0;
  return hsv;
}
*/

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
