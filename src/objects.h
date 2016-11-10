//
//  Contains declarations for GameObjects.
//

#ifndef BREAK_THE_BRICKS_OBJECTS_H
#define BREAK_THE_BRICKS_OBJECTS_H

#include "util.h"

class Ball;

class GameObject {
protected:
    Vector2f _pos;
public:
    GameObject(Vector2f pos);

    virtual void draw() = 0;

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys) = 0;

    virtual Vector2f *get_collision_normal(const Ball &ball);
};

class Rectangle : public GameObject {
protected:
    Vector2f _size;
public:
    Rectangle(Vector2f pos, Vector2f size);

    virtual void draw();

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    virtual Vector2f *get_collision_normal(const Ball &ball);
};


class Brick : public Rectangle {
private:
    bool _active;
public:
    Brick(Vector2f pos, Vector2f size);

    Vector2f *get_collision_normal(const Ball &ball);

    void draw();
};


class Platform : public Rectangle {
private:
    float _speed;
public:
    Platform(Vector2f pos, Vector2f size, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);
};


class Ball : public GameObject {
private:
    float _radius;
    Vector2f _velocity;
public:
    Ball(Vector2f pos, float radius, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    void draw();

    friend Vector2f *Rectangle::get_collision_normal(const Ball &ball);
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
