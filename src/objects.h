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

class Ball : public GameObject {
private:
    float _radius;
    Vector2f _velocity;
public:
    Ball(Vector2f pos, float radius, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    void draw();
};

class Brick : public GameObject {
private:
    bool _active;
protected:
    Vector2f _size;
public:
    Brick(Vector2f pos, Vector2f size);

    virtual void draw();

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    bool check_collision(const Ball &);
};

class Platform : public Brick {
private:
    float _speed;
public:
    Platform(Vector2f pos, Vector2f size, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
