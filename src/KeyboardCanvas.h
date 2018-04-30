//
// Created by Jochem on 13/04/2018.
//

#ifndef MASTERKEYS_KEYBOARDCANVAS_H
#define MASTERKEYS_KEYBOARDCANVAS_H

#include <cstdint>
#include "utils/Geometry.h"

class KeyboardCanvas {
private:
    const unsigned int width;
    const unsigned int height;
    uint32_t * canvas;

public:
    KeyboardCanvas(unsigned int width, unsigned int height);
    ~KeyboardCanvas();

    const unsigned int getWidth() { return width; }
    const unsigned int getHeight() { return height; }

    uint32_t get(int x, int y) const;
    uint32_t get(Shape<int> &shape) const;
    void set(int x, int y, uint32_t color);
    void set(Shape<int> &shape, uint32_t color);
    void add(int x, int y, uint32_t color);
    void add(Shape<int> &shape, uint32_t color);
    void subtract(int x, int y, uint32_t color);
    void subtract(Shape<int> shape, uint32_t color);

    void clear();

    void fill(uint32_t color);
};


#endif //MASTERKEYS_KEYBOARDCANVAS_H
