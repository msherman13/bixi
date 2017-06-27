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
        Mint        = 0x003F1C,
        Purple      = 0x29004C,
        Blue        = 0x003871,
        DarkPink    = 0x990099,
#endif

        Qty         = 4,
    };

    constexpr Color s_colors[Qty] = { Mint, Purple, Blue, DarkPink };
};
