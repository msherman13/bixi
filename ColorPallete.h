#pragma once

namespace ColorPallete
{
    enum Color : uint32_t
    {
        ChromeBlue  = 0x3c61d9,
        Turquoise   = 0x00935a,
        LightPurple = 0x940096,

        Qty         = 3,
        Black       = 0x0,
    };

    constexpr Color s_colors[Qty] = { ChromeBlue, Turquoise, LightPurple };
};
