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

Vector2f Vector2f::operator+(const Vector2f &other) const {
    return Vector2f(x + other.x, y + other.y);
}

Vector2f Vector2f::operator-(const Vector2f &other) const {
    return Vector2f(x - other.x, y - other.y);
}

Vector2f Vector2f::operator*(const float &a) const {
    return Vector2f(x * a, y * a);
}

void Vector2f::normalize() {
    float magnitude = norm();
    x /= magnitude;
    y /= magnitude;
}

float Vector2f::dot(const Vector2f &other) {
    float dot_product = x * other.x + y * other.y;
    return dot_product;
}

Vector2f Vector2f::reflect(Vector2f normal) {
    normal.normalize();
    return *this - normal * (2 * this->dot(normal));
}

float Vector2f::norm() {
    return (float) sqrt(x * x + y * y);
}
