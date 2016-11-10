//
// Created by shailesh on 11/10/16.
//

#include <GL/gl.h>
#include <cmath>
#include "objects.h"
#include "constants.h"

#define PI 3.14159265f

// Definitions for GameObject
GameObject::GameObject(Vector2f pos) {
    _pos = pos;
}


// Definitions for Brick
Brick::Brick(Vector2f pos, Vector2f size) : GameObject(pos) {
    _size = size;
    _active = true;
}

void Brick::draw() {
    if (!_active)
        return;
    glRectf(
            _pos.get_x() - _size.get_x() / 2,
            _pos.get_y() - _size.get_y() / 2,
            _pos.get_x() + _size.get_x() / 2,
            _pos.get_y() + _size.get_y() / 2
    );
}

void Brick::update(Vector2f left_bottom, Vector2f right_top, bool *keys) {

}

float minimum(float a, float b) {
    if (a <= b)
        return a;
    return b;
}

float maximum(float a, float b) {
    if (a >= b)
        return a;
    return b;
}

float clamp(float num, float a, float b) {
    return maximum(a, minimum(b, num));
}

Vector2f *Brick::get_collision_normal(const Ball &ball) {
    if (!_active)
        return nullptr;

    Vector2f diff1 = ball._pos - _pos;

    float half_brick_width = _size.get_x() / 2;
    float half_brick_height = _size.get_y() / 2;
    float diff1_x = diff1.get_x();
    float diff1_y = diff1.get_y();

    float clamped_diff1_x = clamp(diff1_x, minimum(half_brick_height, half_brick_width),
                                  maximum(half_brick_height, half_brick_width));
    float clamped_diff1_y = clamp(diff1_y, minimum(half_brick_height, half_brick_width),
                                  maximum(half_brick_height, half_brick_width));

    Vector2f closest_point(clamped_diff1_x, clamped_diff1_y);

    Vector2f diff2 = closest_point - ball._pos;
    if (diff2.norm <= ball._radius) {
        Vector2f *normal = new Vector2f(diff1.get_x(), diff1.get_y());
        return normal;
    }
    return nullptr;
}

// Definitions for Ball
Ball::Ball(Vector2f pos, float radius, float speed) : GameObject(pos) {
    _radius = radius;
    _velocity = Vector2f(1, 1);
    _velocity.normalize();
    _velocity = _velocity * speed;
}

void Ball::draw() {
    glTranslatef(_pos.get_x(), _pos.get_y(), 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);       // Center of circle
    int numSegments = 100;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
        glVertex2f(cosf(angle) * _radius, sinf(angle) * _radius);
    }
    glEnd();
}

void Ball::update(Vector2f left_bottom, Vector2f right_top, bool *keys) {
    _pos = _pos + _velocity;
    if (_pos.get_x() + _radius >= right_top.get_x())
        _velocity = _velocity.reflect(Vector2f(-1, 0));
    if (_pos.get_x() - _radius <= left_bottom.get_x())
        _velocity = _velocity.reflect(Vector2f(1, 0));
    if (_pos.get_y() + _radius >= right_top.get_y())
        _velocity = _velocity.reflect(Vector2f(0, -1));
}

// Definitions for Platform
Platform::Platform(Vector2f pos, Vector2f size, float speed) : Brick(pos, size) {
    _speed = speed;
}

void Platform::update(Vector2f left_bottom, Vector2f right_top, bool *keys) {
    if (keys[LEFT_KEY]) {
        if (_pos.get_x() - _size.get_x() / 2 > left_bottom.get_x())
            _pos = _pos - Vector2f(PLATFORM_SPEED, 0);
        keys[LEFT_KEY] = false;
    } else if (keys[RIGHT_KEY]) {
        if (_pos.get_x() + _size.get_x() / 2 < right_top.get_x())
            _pos = _pos + Vector2f(PLATFORM_SPEED, 0);
        keys[RIGHT_KEY] = false;
    }
}