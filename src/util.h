//
// Contains declarations for utility classes.
//

#ifndef BREAK_THE_BRICKS_UTIL_H
#define BREAK_THE_BRICKS_UTIL_H

#include <algorithm>

class Vector2f {
private:
    float x, y;
public:
    Vector2f();

    Vector2f(float x, float y);

    inline float get_x() { return x; }

    inline float get_y() { return y; }

    Vector2f operator-(const Vector2f &) const;

    Vector2f operator+(const Vector2f &) const;

    Vector2f operator*(const float &) const;

    float dot(const Vector2f &);

    void normalize();

    float norm();

    Vector2f reflect(Vector2f normal);

    Vector2f clamp(Vector2f min, Vector2f max);
};


// Some other utility functions

inline float clampf(float num, float a, float b) {
    return std::max(a, std::min(b, num));
}

#endif //BREAK_THE_BRICKS_UTIL_H
