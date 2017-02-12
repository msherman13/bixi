#include "PixelArray.h"
#include "Logging.h"

CPixelArray::CPixelArray(int size) :
    m_size(size),
    m_pPixels(new CPixel[size])
{
}

CPixelArray::~CPixelArray()
{
    for(int i=0;i<GetSize();i++)
        delete &m_pPixels[i];
}

bool CPixelArray::ValidateIndex(int index)
{
    return index >= 0 && index < GetSize();
}

CPixel* CPixelArray::GetPixel(int index)
{
    if(!ValidateIndex(index))
        return nullptr;

    return &m_pPixels[index];
}

bool CPixelArray::SetPixel(int index, CRGB rgb)
{
    if(!ValidateIndex(index))
        return false;

    m_pPixels[index].SetRGB(rgb);
    return true;
}

void CPixelArray::Reset()
{
    for(int i=0;i<GetSize();i++)
    {
        m_pPixels[i].SetRGB(CRGB::Black);
        m_pPixels[i].SetIsPopulated(false);
    }
}

void CPixelArray::Shift(bool forward, int amount)
{
    for(int it=0;it<amount;it++)
    {
        CPixel pixel = m_pPixels[GetSize()-1];
        CPixel buff;

        for(int i=0;i<GetSize();i++)
        {
            buff = m_pPixels[i];
            m_pPixels[i] = pixel;
            pixel = buff;
        }
    }
}

void CPixelArray::SmartCopy(CPixelArray& rhs, int size, int offset)
{
    for(int i=0;i<size;i++)
    {
        int index = (i + offset) % GetSize();
        m_pPixels[index] = *rhs.GetPixel(i);
    }
}
