//
// Created by shailesh on 11/10/16.
//

#include <cmath>
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

void Vector2f::normalize() {
    float magnitude = sqrt(x * x + y * y);
    x /= magnitude;
    y /= magnitude;
}

float Vector2f::dot(const Vector2f &other) {
    float dot_product = x * other.x + y * other.y;
    return dot_product;
}
