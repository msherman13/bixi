#pragma once

namespace ColorPallete
{
    enum Color
    {
        Black       = 0x0,
        ChromeBlue  = 0x005c7e,
        Turquoise   = 0x00935a,
        LightPurple = 0x940096,

        Qty         = 3,
    };

    constexpr Color s_colors[Qty] = { ChromeBlue, Turquoise, LightPurple };
};
