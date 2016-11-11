//
//  Contains declarations for GameObjects.
//

#ifndef BREAK_THE_BRICKS_OBJECTS_H
#define BREAK_THE_BRICKS_OBJECTS_H

#include <vector>
#include "util.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Ball;

class GameObject {
protected:
    Vector2f _pos;

    Texture *_texture;
public:
    GameObject(Vector2f pos);

    inline Vector2f get_pos() { return _pos; };

    virtual void draw() = 0;

    void set_texture(Texture *texture);

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys) = 0;

    virtual Vector2f *get_collision_normal(Ball &ball);
};

class Rectangle : public GameObject {
protected:
    Vector2f _size;
public:
    Rectangle(Vector2f pos, Vector2f size);

    virtual void draw();

    virtual void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    virtual Vector2f *get_collision_normal(Ball &ball);
};


class Brick : public Rectangle {
private:
    bool _active;
public:
    Brick(Vector2f pos, Vector2f size);

    Vector2f *get_collision_normal(Ball &ball);

    void draw();
};


class Platform : public Rectangle {
private:
    float _speed;
public:
    Platform(Vector2f pos, Vector2f size, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    Vector2f *get_collision_normal(Ball &ball);
};


class Ball : public GameObject {
private:
    float _radius;
    Vector2f _velocity;
public:
    Ball(Vector2f pos, float radius, float speed);

    void update(Vector2f left_bottom, Vector2f right_top, bool *keys);

    void draw();

    friend Vector2f *Rectangle::get_collision_normal(Ball &ball);

    void set_velocity_dir(Vector2f velocity);

    inline Vector2f get_velocity(void) { return _velocity; }

    void set_speed(float speed);

    inline float get_speed(void){ return _velocity.norm(); }
};

#endif //BREAK_THE_BRICKS_OBJECTS_H
