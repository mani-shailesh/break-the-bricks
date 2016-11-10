//
// Contains declarations for utility classes.
//

#ifndef BREAK_THE_BRICKS_UTIL_H
#define BREAK_THE_BRICKS_UTIL_H

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
};


// Some other utility functions
inline float minimum(float a, float b) {
    if (a <= b)
        return a;
    return b;
}

inline float maximum(float a, float b) {
    if (a >= b)
        return a;
    return b;
}

inline float clamp(float num, float a, float b) {
    return maximum(a, minimum(b, num));
}

#endif //BREAK_THE_BRICKS_UTIL_H
