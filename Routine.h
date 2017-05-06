#pragma once

#include <stdlib.h>
#include <string>

#include "Addressing.h"
#include "PixelArray.h"

class CPixel;
struct CRGB;

class CRoutine
{
    public:
        CRoutine(std::string name);
        virtual ~CRoutine();

    public:
        virtual void Start() = 0;
        virtual void Continue() = 0;
        virtual void Exit();

    public:
        std::string& GetName() { return m_name; }

    public:
        size_t GetSize();
        bool GetRGB(size_t index, CRGB& dest);

    protected:
        CPixelArray<Addressing::c_length> m_pixelArray;

    private:
        std::string m_name;
};
