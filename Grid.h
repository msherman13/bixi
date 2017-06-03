#pragma once

#include <stdlib.h>
#include "PixelArray.h"

class CRoutine;

class CGrid : public CPixelArray
{
    public:
        CGrid(CRGB* leds);
        ~CGrid();
};
