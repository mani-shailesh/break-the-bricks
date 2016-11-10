//
// Created by shailesh on 11/10/16.
//

#ifndef BREAK_THE_BRICKS_UTIL_H
#define BREAK_THE_BRICKS_UTIL_H

class Vector2f {
private:
    float x, y;
public:
    Vector2f();

    Vector2f(float x, float y);

    Vector2f operator-(const Vector2f &);

    Vector2f operator+(const Vector2f &);

    float dot(const Vector2f &);

    void normalize();
};

#endif //BREAK_THE_BRICKS_UTIL_H
