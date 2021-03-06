//
// Created by shailesh on 11/10/16.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "objects.h"
#include "constants.h"

#define PI 3.14159265f
using namespace std;

// Definitions for GameObject
GameObject::GameObject(Vector2f pos) {
    _pos = pos;
    _texture = 0;
}

Vector2f *GameObject::get_collision_normal(Ball &ball) {
    return 0;
}

void GameObject::set_texture(Texture *texture) {
    _texture = texture;
}

// Definitions for Rectangle
Rectangle::Rectangle(Vector2f pos, Vector2f size) : GameObject(pos) {
    _size = size;
}

void Rectangle::draw() {
    glPushMatrix();
    if (_texture && _texture->is_loaded()){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _texture->get_id());

        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            glVertex2f(_pos.get_x() - _size.get_x()/2, _pos.get_y() + _size.get_y()/2);
            glTexCoord2f(1.0, 0);
            glVertex2f(_pos.get_x() + _size.get_x()/2, _pos.get_y() + _size.get_y()/2);
            glTexCoord2f(1.0, 1.0);
            glVertex2f(_pos.get_x() + _size.get_x()/2, _pos.get_y() - _size.get_y()/2);
            glTexCoord2f(0.0, 1.0);
            glVertex2f(_pos.get_x() - _size.get_x()/2, _pos.get_y() - _size.get_y()/2);
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }else{
        glRectf(
                _pos.get_x() - _size.get_x() / 2,
                _pos.get_y() - _size.get_y() / 2,
                _pos.get_x() + _size.get_x() / 2,
                _pos.get_y() + _size.get_y() / 2
        );
    }
    glPopMatrix();
}

void Rectangle::update(Vector2f left_bottom, Vector2f right_top, bool *keys) {}


Vector2f *Rectangle::get_collision_normal(Ball &ball) {
    Vector2f diff1 = ball._pos - _pos;
    Vector2f clamped_diff1 = diff1.clamp(_size * -0.5, _size * 0.5);

    Vector2f closest_point = _pos + clamped_diff1;

    Vector2f diff2 = closest_point - ball._pos;
    if (diff2.norm() <= ball._radius) {
        if (abs(diff2.get_x()) > abs(diff2.get_y()))
            return new Vector2f(diff1.get_x(), 0);
        else if (abs(diff2.get_x()) < abs(diff2.get_y()))
            return new Vector2f(0, diff1.get_y());
        else
            return new Vector2f(diff1.get_x(), diff1.get_y());
    }
    return 0;
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
        return 0;
    Vector2f *normal = Rectangle::get_collision_normal(ball);
    if (normal)
        _active = false;
    return normal;
}


// Definitions for Platform
Platform::Platform(Vector2f pos, Vector2f size, float speed) : Rectangle(pos, size) {
    _speed = speed;
}

/*
    Function to update the position of the platform.
*/
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

/*
    Function to return the common normal in case of a collision.
*/
Vector2f *Platform::get_collision_normal(Ball &ball) {
    Vector2f *normal = Rectangle::get_collision_normal(ball);
    if (normal) {
        float distance_x = 2 * (ball.get_pos().get_x() - _pos.get_x()) / _size.get_x();
        Vector2f velocity = ball.get_velocity();
        float speed = velocity.norm();
        velocity.normalize();
        Vector2f new_velocity(velocity.get_x() + distance_x * speed, velocity.get_y());
        ball.set_velocity_dir(new_velocity);
        return normal;
    }
    return 0;
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

    bool draw_texture = _texture && _texture->is_loaded();

    if (draw_texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _texture->get_id());
    }

    glTranslatef(_pos.get_x(), _pos.get_y(), 0.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);       // Center of circle
    int numSegments = 500;
    GLfloat angle;
    for (int i = 0; i <= numSegments; i++) { // Last vertex same as first vertex
        angle = i * 2.0f * PI / numSegments;  // 360 deg for all segments
        if(draw_texture)
            glTexCoord2f(cosf(angle) * 0.5f + 0.5f, sinf(angle) * 0.5f + 0.5f);
        glVertex2f(cosf(angle) * _radius, sinf(angle) * _radius);
    }
    glEnd();

    if (draw_texture) {
        glDisable(GL_TEXTURE_2D);
    }

    glPopMatrix();
}

/*
    Function to update the velocity according to the collision.
*/
void Ball::update(Vector2f left_bottom, Vector2f right_top, bool *keys) {
    _pos = _pos + _velocity;
    if (_pos.get_x() + _radius >= right_top.get_x())
        _velocity = _velocity.reflect(Vector2f(-1, 0));
    if (_pos.get_x() - _radius <= left_bottom.get_x())
        _velocity = _velocity.reflect(Vector2f(1, 0));
    if (_pos.get_y() + _radius >= right_top.get_y())
        _velocity = _velocity.reflect(Vector2f(0, -1));
}

/*
    Function to set the direction of the velocity vector.
*/
void Ball::set_velocity_dir(Vector2f velocity) {
    velocity.normalize();
    _velocity = velocity * _velocity.norm();
}

/*
    Function to set the speed of the ball.
*/
void Ball::set_speed(float speed) {
    _velocity.normalize();
    _velocity = _velocity * speed;
}