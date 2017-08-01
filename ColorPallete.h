#pragma once

#include "FastLED.h"

namespace ColorPallete
{
    enum Color : uint32_t
    {
#ifdef SIM
        Mint        = 0x7CC69D,
        Purple      = 0x666699,
        Blue        = 0x33669A,
        DarkPink    = 0x996699,
#else
        Mint        = 0x00B43C,
        Purple      = 0x760096,
        Blue        = 0x0A00B4,
        DarkPink    = 0xC30032,
#endif

        Qty         = 4,
    };

    constexpr Color s_colors[Qty] = { Mint, Purple, Blue, DarkPink };
};
