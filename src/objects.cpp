//
// Created by shailesh on 11/10/16.
//

#include <GL/gl.h>
#include <cmath>
#include <vector>
#include "objects.h"
#include "constants.h"

#define PI 3.14159265f
using namespace std;

// Definitions for GameObject
GameObject::GameObject(Vector2f pos) {
    _pos = pos;
}

Vector2f *GameObject::get_collision_normal(Ball &ball) {
    return nullptr;
}


// Definitions for Rectangle
Rectangle::Rectangle(Vector2f pos, Vector2f size) : GameObject(pos) {
    _size = size;
}

void Rectangle::draw() {
    glRectf(
            _pos.get_x() - _size.get_x() / 2,
            _pos.get_y() - _size.get_y() / 2,
            _pos.get_x() + _size.get_x() / 2,
            _pos.get_y() + _size.get_y() / 2
    );
}

void Rectangle::update(Vector2f left_bottom, Vector2f right_top, bool *keys) {}


Vector2f *Rectangle::get_collision_normal(Ball &ball) {
    Vector2f diff1 = ball._pos - _pos;
    Vector2f clamped_diff1 = diff1.clamp(_size * -0.5, _size * 0.5);

    Vector2f closest_point = _pos + clamped_diff1;

    Vector2f diff2 = closest_point - ball._pos;
    if (diff2.norm() <= ball._radius) {
        if (abs(diff2.get_x()) > abs(diff2.get_y()))
            return new Vector2f(diff2.get_x(), 0);
        else if (abs(diff2.get_x()) < abs(diff2.get_y()))
            return new Vector2f(0, diff2.get_y());
        else
            return new Vector2f(diff2.get_x(), diff2.get_y());
    }
    return nullptr;
}


// Definitions for Brick
Brick::Brick(Vector2f pos, Vector2f size) : Rectangle(pos, size) {
    _active = true;
}

void Brick::draw() {
    if (!_active)
        return;
    Rectangle::draw();
}

Vector2f *Brick::get_collision_normal(Ball &ball) {
    if (!_active)
        return nullptr;
    Vector2f *normal = Rectangle::get_collision_normal(ball);
    if (normal)
        _active = false;
    return normal;
}


// Definitions for Platform
Platform::Platform(Vector2f pos, Vector2f size, float speed) : Rectangle(pos, size) {
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

Vector2f *Platform::get_collision_normal(Ball &ball) {
    Vector2f *normal = Rectangle::get_collision_normal(ball);
    if (normal) {
        float distance_x = 2 * (ball.get_pos().get_x() - _pos.get_x()) / _size.get_x();
        Vector2f velocity = ball.get_velocity();
        velocity.normalize();
        Vector2f new_velocity(velocity.get_x() + distance_x * VEL_DELTA_X, abs(velocity.get_y()));
        ball.set_velocity_dir(new_velocity);
    }
    return nullptr;
}


// Definitions for Ball
Ball::Ball(Vector2f pos, float radius, float speed) : GameObject(pos) {
    srand(time(NULL));
    _radius = radius;
    _velocity = Vector2f(rand() % 7 + 3, rand() % 7 + 3);
    _velocity.normalize();
    _velocity = _velocity * speed;
}

void Ball::draw() {
    glPushMatrix();

    glTranslatef(_pos.get_x(), _pos.get_y(), 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);       // Center of circle
    int numSegments = 500;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
        glVertex2f(cosf(angle) * _radius, sinf(angle) * _radius);
    }
    glEnd();

    glPopMatrix();
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

void Ball::check_collisions(std::vector<GameObject *> &game_objects) {
    vector<GameObject *>::iterator it;
    for (it = game_objects.begin(); it != game_objects.end(); it++) {
        Vector2f *normal = (*it)->get_collision_normal(*this);
        if (normal) {
            _velocity = _velocity.reflect(*normal);
            break;
        }
    }
}

void Ball::set_velocity_dir(Vector2f velocity) {
    velocity.normalize();
    _velocity = velocity * _velocity.norm();
}