#ifndef MASTERKEYS_KEYDATA_H
#define MASTERKEYS_KEYDATA_H

#include "utils/Geometry.h"

class KeyData {
    Rect<int> rect;
    Point<int> id;
public:
    KeyData() : rect(0, 0, 0, 0), id(0, 0) {}

    Rect<int> getRect() const { return rect; }
    void setRect(Rect<int> rect) { this->rect = rect; }

    Point<int> getId() const { return id; }
    void setId(Point<int> id) { this->id = id; }
};

#endif //MASTERKEYS_KEYDATA_H
