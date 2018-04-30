#include <stdexcept>
#include <algorithm>
#include <iostream>

#include "KeyboardCanvas.h"
#include "utils/ColorUtils.h"

KeyboardCanvas::KeyboardCanvas(unsigned int width, unsigned int height)
    : width(width), height(height) {
    canvas = new uint32_t[width * height];
}

KeyboardCanvas::~KeyboardCanvas() {
    delete[] canvas;
}

uint32_t KeyboardCanvas::get(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return 0;
    }
    return canvas[y * width + x];
}

uint32_t KeyboardCanvas::get(Shape<int> &shape) const {
    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    uint32_t n = 0;
    uint32_t color;

    for (int y = std::max(0, shape.bound().y1);
         y < std::min((int) height - 1, shape.bound().y2); ++y) {
        for (int x = std::max(0, shape.bound().x1);
             x < std::min((int) width - 1, shape.bound().x2); ++x) {
//            if (!(x % 4 == 0 || x % 4 == 3) || !(y % 4 == 0 || y % 4 == 3)) continue;
            if (shape.in(x, y)) {
                color = get(x, y);
                red   +=   color::red(color);
                green += color::green(color);
                blue  +=  color::blue(color);
                n++;
            }
        }
    }

    if (n == 0) { return color::BLACK; }
    return color::rgb(
            static_cast<const uint8_t>(red / n),
            static_cast<const uint8_t>(green / n),
            static_cast<const uint8_t>(blue / n)
    );
}

void KeyboardCanvas::set(int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return;
    }
    canvas[y * width + x] = color;
}

void KeyboardCanvas::set(Shape<int> &shape, uint32_t color) {
    for (int y = std::max(0, shape.bound().y1);
         y < std::min((int) height - 1, shape.bound().y2); ++y) {
        for (int x = std::max(0, shape.bound().x1);
             x < std::min((int) width - 1, shape.bound().x2); ++x) {
            if (shape.in(x, y)) {
                set(x, y, color);
            }
        }
    }
}

void KeyboardCanvas::add(int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return;
    }
    canvas[y * width + x] = color::add(canvas[y * width + x], color);
}

void KeyboardCanvas::add(Shape<int> &shape, uint32_t color) {
    for (int y = std::max(0, shape.bound().y1);
         y < std::min((int) height - 1, shape.bound().y2); ++y) {
        for (int x = std::max(0, shape.bound().x1);
             x < std::min((int) width - 1, shape.bound().x2); ++x) {
            if (shape.in(x, y)) {
                add(x, y, color);
            }
        }
    }
}

void KeyboardCanvas::subtract(int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return;
    }
    canvas[y * width + x] = color::subtract(canvas[y * width + x], color);
}

void KeyboardCanvas::subtract(Shape<int> shape, uint32_t color) {
    for (int x = std::min(0, shape.bound().x1);
         x < std::max((int) width - 1, shape.bound().x2); ++x) {
        for (int y = std::min(0, shape.bound().y1);
             y < std::max((int) height - 1, shape.bound().y2); ++y) {
            if (shape.in(x, y)) {
                subtract(x, y, color);
            }
        }
    }
}

void KeyboardCanvas::clear() {
    fill(color::BLACK);
}

void KeyboardCanvas::fill(uint32_t color) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            canvas[y * width + x] = color;
        }
    }
}

