#ifndef MASTERKEYS_GEOMETRY_H
#define MASTERKEYS_GEOMETRY_H

template <typename T>
struct Point {
    T x, y;
    Point(T x, T y) : x(x), y(y) {};
};

template <typename T>
struct Bound {
    T x1, y1, x2, y2;
    Bound(T x1, T y1, T x2, T y2) : x1(x1), y1(y1), x2(x2), y2(y2) {};
};

template <typename T>
struct Shape {
    virtual inline bool in(T x, T y) { return false; };
    virtual inline bool in(Point<T> p) { return in(p.x, p.y); };
    virtual inline Bound<T> bound() { return {0, 0, 0, 0}; };
};

template <typename T>
struct Rect : Bound<T>, Shape<T> {
    Rect(T x1, T y1, T x2, T y2) : Bound<T>(x1, y1, x2, y2) {}
    Rect(Point<T> p1, Point<T> p2) : Bound<T>(p1.x, p1.y, p2.x, p2.y) {}
    inline T width() { return this->x2 - this->x1; }
    inline T height() { return this->x2 - this->x1; }
    inline bool in(T x, T y) override {
        return this->x1 <= x && x < this->x2 && this->y1 <= y && y < this->y2;
    }
    inline Bound<T> bound() override {
        return *this;
    }
};

template <typename T>
struct Circle : Shape<T> {
    T cx, cy, r;
    Circle(T cx, T cy, T r) : cx(cx), cy(cy), r(r) {};
    Circle(Point<T> p, T r) : cx(p.x), cy(p.y), r(r) {};
    inline bool in(T x, T y) override {
        return (cx - x) * (cx - x) + (cy - y) * (cy - y) <= r * r;
    }
    inline Bound<T> bound() override {
        return Bound<T>{cx - r - 1, cy - r - 1, cx + r + 1, cy + r + 1};
    }
};


#endif //MASTERKEYS_GEOMETRY_H
