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
    GameObject(Vector2f);

    virtual void draw() = 0;

    virtual void update() = 0;
};

class Ball : public GameObject {
private:
    float _radius;
    Vector2f _velocity;
public:
    Ball(Vector2f pos, float radius, float speed);

    void update();

    void draw();
};

class Brick : public GameObject {
private:
    Vector2f _size;
    bool _active;
public:
    Brick(Vector2f pos, Vector2f size);

    virtual void draw();

    virtual void update();

    bool check_collision(const Ball &);
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
