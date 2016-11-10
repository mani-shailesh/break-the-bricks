//
// Created by shailesh on 11/10/16.
//

#include <GL/gl.h>
#include "objects.h"

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


Ball::Ball(Vector2f pos, float radius, float speed) : GameObject(pos) {
    _radius = radius;
    _velocity = Vector2f(1, 1);
    _velocity.normalize();
    _velocity = _velocity * speed;
}