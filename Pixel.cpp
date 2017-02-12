#include "Pixel.h"
#include "Logging.h"

CPixel::CPixel() :
    m_isPopulated(false),
    m_rgb(0, 0, 0)
{
}

CPixel::~CPixel()
{
}

bool CPixel::GetRGB(CRGB& dest)
{
    if(!GetIsPopulated())
        return false;

    dest = m_rgb;
    return true;
}

void CPixel::SetRGB(CRGB source)
{
    m_rgb = source;
    SetIsPopulated(true);
}

void CPixel::SetBlack()
{
    SetRGB(CRGB::Black);
}
