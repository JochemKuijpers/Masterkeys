#ifndef MASTERKEYS_COLORUTILS_H
#define MASTERKEYS_COLORUTILS_H

#include <cstdint>
#include "Utils.h"

namespace color {

    inline uint8_t red(const uint32_t color) {
        return static_cast<uint8_t>(color >> 16);
    }

    inline uint8_t green(const uint32_t color) {
        return static_cast<uint8_t>(color >> 8);
    }

    inline uint8_t blue(const uint32_t color) {
        return static_cast<uint8_t>(color);
    }

    inline uint32_t rgb(const uint8_t red, const uint8_t green, const uint8_t blue) {
        return static_cast<uint32_t>(
                clamp<uint32_t>(0, red, 255) << 16 |
                clamp<uint32_t>(0, green, 255) << 8 |
                clamp<uint32_t>(0, blue, 255)
        );
    }

    inline uint32_t blend(const uint32_t color1, const uint32_t color2, float blend) {
        blend = clamp<float>(0.0f, blend, 1.0f);
        return rgb(
                static_cast<const uint8_t>(  red(color1) * (1 - blend) +   red(color2) * blend),
                static_cast<const uint8_t>(green(color1) * (1 - blend) + green(color2) * blend),
                static_cast<const uint8_t>( blue(color1) * (1 - blend) +  blue(color2) * blend)
        );
    }

    inline uint32_t multiply(const uint32_t color, float factor) {
        return rgb(
                static_cast<const uint8_t>(  red(color) * factor),
                static_cast<const uint8_t>(green(color) * factor),
                static_cast<const uint8_t>( blue(color) * factor)
        );
    }

    inline uint32_t add(const uint32_t color1, const uint32_t color2) {
        return rgb(
                clamp<uint8_t>(0,   red(color1) +   red(color2), 255),
                clamp<uint8_t>(0, green(color1) + green(color2), 255),
                clamp<uint8_t>(0,  blue(color1) +  blue(color2), 255)
        );
    }

    inline uint32_t subtract(const uint32_t color1, const uint32_t color2) {
        return rgb(
                clamp<uint8_t>(0,   red(color1) -   red(color2), 255),
                clamp<uint8_t>(0, green(color1) - green(color2), 255),
                clamp<uint8_t>(0,  blue(color1) -  blue(color2), 255)
        );
    }

    inline float toFloat(const uint8_t i) {
        return clamp<float>(0.f, i / 255.f, 1.f);
    }

    inline uint8_t toInt(const float f) {
        return clamp<uint8_t>(0, f * 256, 255);
    }

    const uint32_t RED      = 0x00FF0000;
    const uint32_t ORANGE   = 0x00FF8000;
    const uint32_t YELLOW   = 0x00FFFF00;
    const uint32_t LIME     = 0x0080FF00;
    const uint32_t GREEN    = 0x0000FF00;
    const uint32_t AQUA     = 0x0000FFFF;
    const uint32_t BLUE     = 0x000000FF;
    const uint32_t PURPLE   = 0x008000FF;
    const uint32_t PINK     = 0x00FF00FF;

    const uint32_t WHITE    = 0x00FFFFFF;
    const uint32_t LTGRAY   = 0x00C0C0C0;
    const uint32_t GRAY     = 0x00808080;
    const uint32_t DKGRAY   = 0x00404040;
    const uint32_t BLACK    = 0x00000000;

}

#endif //MASTERKEYS_COLORUTILS_H
