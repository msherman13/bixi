#include "Plain.h"

CPlain::CPlain(CPixelArray& pixels, Config& config) :
    m_pixels(pixels),
    m_config(config)
{
}

CPlain::~CPlain()
{
}

void CPlain::SetColor(CRGB rgb)
{
    for(size_t leg=0;leg<NumLegs();leg++)
    {
        for(size_t i=0;i<LegLength(leg);i++)
        {
            size_t index = LegStart(leg) + i;
            m_pixels.SetPixel(index, rgb);
        }
    }
}
