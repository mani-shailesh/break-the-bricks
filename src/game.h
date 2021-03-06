//
// Contains declarations for Game class.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "objects.h"
#include "constants.h"


class Game {
private:
    std::vector<GameObject *> _game_objects;
    std::vector<Texture *> _textures;
    Ball *_ball;
    Rectangle *_bg;
    Vector2f _left_bottom, _right_top;
    int state;
    int _total_time;
    bool _keys[NUM_KEYS];
    int num_active_bricks;
    int _best_time;

    void update_state();

    void draw_scoreboard();

    void free_all();

    void read_best_time();

    void write_best_time();
public:
    Game();

    ~Game();

    void reset();

    void setup();

    void update();

    void draw();

    void key_pressed(int key);

    void reshape(Vector2f left_bottom, Vector2f right_top);

    void check_collisions();
};

#endif //BREAK_THE_BRICKS_GAME_H
