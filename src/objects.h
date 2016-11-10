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

    virtual void update(Vector2f left_bottom, Vector2f right_top) = 0;
};

class Ball : public GameObject {
private:
    float _radius;
    Vector2f _velocity;
public:
    Ball(Vector2f pos, float radius, float speed);

    void update(Vector2f left_bottom, Vector2f right_top);

    void draw();
};

class Brick : public GameObject {
private:
    Vector2f _size;
    bool _active;
public:
    Brick(Vector2f pos, Vector2f size);

    virtual void draw();

    virtual void update(Vector2f left_bottom, Vector2f right_top);

    bool check_collision(const Ball &);
};

class Platform : public Brick {
public:
    Platform(Vector2f pos, Vector2f size);

    void update(Vector2f left_bottom, Vector2f right_top);
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
