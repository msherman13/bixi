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
        //Mint        = 0x00C658,
        //Purple      = 0x303099,
        //Blue        = 0x004C9A,
        //DarkPink    = 0x990C99,

        Qty         = 4,
    };

    constexpr Color s_colors[Qty] = { Mint, Purple, Blue, DarkPink };
};
