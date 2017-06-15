#pragma once

#include "FastLED.h"

namespace ColorPallete
{
    enum Color : uint32_t
    {
        Mint        = 0x7CC69D,
        Purple      = 0x666699,
        Blue        = 0x33669A,
        DarkPink    = 0x996699,

        Qty         = 4,
    };

    constexpr Color s_colors[Qty] = { Mint, Purple, Blue, DarkPink };
};
