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

    Vector2f operator-(const Vector2f &);

    Vector2f operator+(const Vector2f &);

    Vector2f operator*(const float &);

    float dot(const Vector2f &);

    void normalize();

    void reflect(Vector2f normal);
};

#endif //BREAK_THE_BRICKS_UTIL_H
