//
//  Contains declarations for GameObjects.
//

#ifndef BREAK_THE_BRICKS_OBJECTS_H
#define BREAK_THE_BRICKS_OBJECTS_H

#include "util.h"

class GameObject {
protected:
    Vector2f _pos;
public:
    GameObject(Vector2f pos);

    virtual void draw() = 0;

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys) = 0;
};

class Ball;

class Brick : public GameObject {
private:
    bool _active;
protected:
    Vector2f _size;
public:
    Brick(Vector2f pos, Vector2f size);

    virtual void draw();

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    Vector2f *get_collision_normal(const Ball &ball);
};

class Ball : public GameObject {
private:
    float _radius;
    Vector2f _velocity;
public:
    Ball(Vector2f pos, float radius, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    void draw();

    friend Vector2f *Brick::get_collision_normal(const Ball &ball);
};

class Platform : public Brick {
private:
    float _speed;
public:
    Platform(Vector2f pos, Vector2f size, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
