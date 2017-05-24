#pragma once

#include <stdint.h>
#include <cmath>
#include <string>

struct CHSV;
struct CRGB;

struct CHSV {
    union {
		struct {
		    union {
		        uint8_t hue;
		        uint8_t h; };
		    union {
		        uint8_t saturation;
		        uint8_t sat;
		        uint8_t s; };
		    union {
		        uint8_t value;
		        uint8_t val;
		        uint8_t v; };
		};
		uint8_t raw[3];
	};

    CHSV() {}

    /// allow copy construction
    CHSV(const CHSV& rhs)
    {
        h = rhs.h;
        s = rhs.s;
        v = rhs.v;
    }

    CHSV(uint8_t hloc, uint8_t sloc, uint8_t vloc) :
        h(hloc),
        s(sloc),
        v(vloc)
    {
    }
};

#define APPLY_DIMMING(X) (X)
#define HSV_SECTION_6 (0x20)
#define HSV_SECTION_3 (0x40)

struct CRGB
{
    CRGB() :
        r(0),
        g(0),
        b(0)
    {
    }
    CRGB(uint8_t rloc, uint8_t gloc, uint8_t bloc) :
        r(rloc),
        g(gloc),
        b(bloc)
    {
    }
    CRGB(CHSV& hsv)
    {
        // Convert hue, saturation and brightness ( HSV/HSB ) to RGB
        // "Dimming" is used on saturation and brightness to make
        // the output more visually linear.

        // Apply dimming curves
        uint8_t value = APPLY_DIMMING(hsv.val);
        uint8_t saturation = hsv.sat;

        // The brightness floor is minimum number that all of
        // R, G, and B will be set to.
        uint8_t invsat = APPLY_DIMMING(255 - saturation);
        uint8_t brightness_floor = (value * invsat) / 256;

        // The color amplitude is the maximum amount of R, G, and B
        // that will be added on top of the brightness_floor to
        // create the specific hue desired.
        uint8_t color_amplitude = value - brightness_floor;

        // Figure out which section of the hue wheel we're in,
        // and how far offset we are withing that section
        uint8_t section = hsv.hue / HSV_SECTION_3; // 0..2
        uint8_t offset = hsv.hue % HSV_SECTION_3;  // 0..63

        uint8_t rampup = offset; // 0..63
        uint8_t rampdown = (HSV_SECTION_3 - 1) - offset; // 63..0

        // We now scale rampup and rampdown to a 0-255 range -- at least
        // in theory, but here's where architecture-specific decsions
        // come in to play:
        // To scale them up to 0-255, we'd want to multiply by 4.
        // But in the very next step, we multiply the ramps by other
        // values and then divide the resulting product by 256.
        // So which is faster?
        //   ((ramp * 4) * othervalue) / 256
        // or
        //   ((ramp    ) * othervalue) /  64
        // It depends on your processor architecture.
        // On 8-bit AVR, the "/ 256" is just a one-cycle register move,
        // but the "/ 64" might be a multicycle shift process. So on AVR
        // it's faster do multiply the ramp values by four, and then
        // divide by 256.
        // On ARM, the "/ 256" and "/ 64" are one cycle each, so it's
        // faster to NOT multiply the ramp values by four, and just to
        // divide the resulting product by 64 (instead of 256).
        // Moral of the story: trust your profiler, not your insticts.

        // Since there's an AVR assembly version elsewhere, we'll
        // assume what we're on an architecture where any number of
        // bit shifts has roughly the same cost, and we'll remove the
        // redundant math at the source level:

        //  // scale up to 255 range
        //  //rampup *= 4; // 0..252
        //  //rampdown *= 4; // 0..252

        // compute color-amplitude-scaled-down versions of rampup and rampdown
        uint8_t rampup_amp_adj   = (rampup   * color_amplitude) / (256 / 4);
        uint8_t rampdown_amp_adj = (rampdown * color_amplitude) / (256 / 4);

        // add brightness_floor offset to everything
        uint8_t rampup_adj_with_floor   = rampup_amp_adj   + brightness_floor;
        uint8_t rampdown_adj_with_floor = rampdown_amp_adj + brightness_floor;


        if( section ) {
            if( section == 1) {
                // section 1: 0x40..0x7F
                r = brightness_floor;
                g = rampdown_adj_with_floor;
                b = rampup_adj_with_floor;
            } else {
                // section 2; 0x80..0xBF
                r = rampup_adj_with_floor;
                g = brightness_floor;
                b = rampdown_adj_with_floor;
            }
        } else {
            // section 0: 0x00..0x3F
            r = rampdown_adj_with_floor;
            g = rampup_adj_with_floor;
            b = brightness_floor;
        }
    }

    union {
        struct {
            union {
                uint8_t r;
                uint8_t red;
            };
            union {
                uint8_t g;
                uint8_t green;
            };
            union {
                uint8_t b;
                uint8_t blue;
            };
        };
        uint8_t raw[3];
    };

    bool operator==(const CRGB& rhs)
    {
        return rhs.r == r && rhs.g == g && rhs.b == b;
    }

    typedef enum {
        AliceBlue=0xF0F8FF,
        Amethyst=0x9966CC,
        AntiqueWhite=0xFAEBD7,
        Aqua=0x00FFFF,
        Aquamarine=0x7FFFD4,
        Azure=0xF0FFFF,
        Beige=0xF5F5DC,
        Bisque=0xFFE4C4,
        Black=0x000000,
        BlanchedAlmond=0xFFEBCD,
        Blue=0x0000FF,
        BlueViolet=0x8A2BE2,
        Brown=0xA52A2A,
        BurlyWood=0xDEB887,
        CadetBlue=0x5F9EA0,
        Chartreuse=0x7FFF00,
        Chocolate=0xD2691E,
        Coral=0xFF7F50,
        CornflowerBlue=0x6495ED,
        Cornsilk=0xFFF8DC,
        Crimson=0xDC143C,
        Cyan=0x00FFFF,
        DarkBlue=0x00008B,
        DarkCyan=0x008B8B,
        DarkGoldenrod=0xB8860B,
        DarkGray=0xA9A9A9,
        DarkGrey=0xA9A9A9,
        DarkGreen=0x006400,
        DarkKhaki=0xBDB76B,
        DarkMagenta=0x8B008B,
        DarkOliveGreen=0x556B2F,
        DarkOrange=0xFF8C00,
        DarkOrchid=0x9932CC,
        DarkRed=0x8B0000,
        DarkSalmon=0xE9967A,
        DarkSeaGreen=0x8FBC8F,
        DarkSlateBlue=0x483D8B,
        DarkSlateGray=0x2F4F4F,
        DarkSlateGrey=0x2F4F4F,
        DarkTurquoise=0x00CED1,
        DarkViolet=0x9400D3,
        DeepPink=0xFF1493,
        DeepSkyBlue=0x00BFFF,
        DimGray=0x696969,
        DimGrey=0x696969,
        DodgerBlue=0x1E90FF,
        FireBrick=0xB22222,
        FloralWhite=0xFFFAF0,
        ForestGreen=0x228B22,
        Fuchsia=0xFF00FF,
        Gainsboro=0xDCDCDC,
        GhostWhite=0xF8F8FF,
        Gold=0xFFD700,
        Goldenrod=0xDAA520,
        Gray=0x808080,
        Grey=0x808080,
        Green=0x008000,
        GreenYellow=0xADFF2F,
        Honeydew=0xF0FFF0,
        HotPink=0xFF69B4,
        IndianRed=0xCD5C5C,
        Indigo=0x4B0082,
        Ivory=0xFFFFF0,
        Khaki=0xF0E68C,
        Lavender=0xE6E6FA,
        LavenderBlush=0xFFF0F5,
        LawnGreen=0x7CFC00,
        LemonChiffon=0xFFFACD,
        LightBlue=0xADD8E6,
        LightCoral=0xF08080,
        LightCyan=0xE0FFFF,
        LightGoldenrodYellow=0xFAFAD2,
        LightGreen=0x90EE90,
        LightGrey=0xD3D3D3,
        LightPink=0xFFB6C1,
        LightSalmon=0xFFA07A,
        LightSeaGreen=0x20B2AA,
        LightSkyBlue=0x87CEFA,
        LightSlateGray=0x778899,
        LightSlateGrey=0x778899,
        LightSteelBlue=0xB0C4DE,
        LightYellow=0xFFFFE0,
        Lime=0x00FF00,
        LimeGreen=0x32CD32,
        Linen=0xFAF0E6,
        Magenta=0xFF00FF,
        Maroon=0x800000,
        MediumAquamarine=0x66CDAA,
        MediumBlue=0x0000CD,
        MediumOrchid=0xBA55D3,
        MediumPurple=0x9370DB,
        MediumSeaGreen=0x3CB371,
        MediumSlateBlue=0x7B68EE,
        MediumSpringGreen=0x00FA9A,
        MediumTurquoise=0x48D1CC,
        MediumVioletRed=0xC71585,
        MidnightBlue=0x191970,
        MintCream=0xF5FFFA,
        MistyRose=0xFFE4E1,
        Moccasin=0xFFE4B5,
        NavajoWhite=0xFFDEAD,
        Navy=0x000080,
        OldLace=0xFDF5E6,
        Olive=0x808000,
        OliveDrab=0x6B8E23,
        Orange=0xFFA500,
        OrangeRed=0xFF4500,
        Orchid=0xDA70D6,
        PaleGoldenrod=0xEEE8AA,
        PaleGreen=0x98FB98,
        PaleTurquoise=0xAFEEEE,
        PaleVioletRed=0xDB7093,
        PapayaWhip=0xFFEFD5,
        PeachPuff=0xFFDAB9,
        Peru=0xCD853F,
        Pink=0xFFC0CB,
        Plaid=0xCC5533,
        Plum=0xDDA0DD,
        PowderBlue=0xB0E0E6,
        Purple=0x800080,
        Red=0xFF0000,
        RosyBrown=0xBC8F8F,
        RoyalBlue=0x4169E1,
        SaddleBrown=0x8B4513,
        Salmon=0xFA8072,
        SandyBrown=0xF4A460,
        SeaGreen=0x2E8B57,
        Seashell=0xFFF5EE,
        Sienna=0xA0522D,
        Silver=0xC0C0C0,
        SkyBlue=0x87CEEB,
        SlateBlue=0x6A5ACD,
        SlateGray=0x708090,
        SlateGrey=0x708090,
        Snow=0xFFFAFA,
        SpringGreen=0x00FF7F,
        SteelBlue=0x4682B4,
        Tan=0xD2B48C,
        Teal=0x008080,
        Thistle=0xD8BFD8,
        Tomato=0xFF6347,
        Turquoise=0x40E0D0,
        Violet=0xEE82EE,
        Wheat=0xF5DEB3,
        White=0xFFFFFF,
        WhiteSmoke=0xF5F5F5,
        Yellow=0xFFFF00,
        YellowGreen=0x9ACD32,

        // LED RGB color that roughly approximates
        // the color of incandescent fairy lights,
        // assuming that you're using FastLED
        // color correction on your LEDs (recommended).
        FairyLight=0xFFE42D,
        // If you are using no color correction, use this
        FairyLightNCC=0xFF9D2A

    } HTMLColorCode;
    CRGB(uint32_t colorcode)
    : r((colorcode >> 16) & 0xFF), g((colorcode >> 8) & 0xFF), b((colorcode >> 0) & 0xFF)
    {
    }
};
