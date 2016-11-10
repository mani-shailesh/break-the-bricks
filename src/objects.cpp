//
// Created by shailesh on 11/10/16.
//

#include <GL/gl.h>
#include <cmath>
#include "objects.h"

#define PI 3.14159265f

GameObject::GameObject(Vector2f pos) {
    _pos = pos;
}


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

void Brick::update() {}


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
        glVertex2f(cos(angle) * _radius, sin(angle) * _radius);
    }
    glEnd();
}

void Ball::update() {
    _pos = _pos + _velocity;
}