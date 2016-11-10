//
// Created by shailesh on 11/10/16.
//

#include "util.h"

Vector2f::Vector2f() {
    x = 0;
    y = 0;
}

Vector2f::Vector2f(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2f Vector2f::operator+(const Vector2f &other) {
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f &other) {
    return Vector2f(x - other.x, y - other.y);
}