//
//  Contains declarations for GameObjects.
//

#ifndef BREAK_THE_BRICKS_OBJECTS_H
#define BREAK_THE_BRICKS_OBJECTS_H

#include "util.h"

class GameObject {
private:
    Vector2f _pos;
public:
    GameObject();

    virtual void draw() = 0;

    virtual void update() = 0;
};

class Ball : public GameObject {
private:
    float radius;
    Vector2f _velocity;
public:
    Ball();

    void update();

    void draw();
};

class Brick : public GameObject {
private:
    Vector2f _size;
    bool _active;
public:
    Brick();

    void draw();

    void update();

    bool check_collision(const Ball &);
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
