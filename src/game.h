//
// Contains declarations for Game class.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include "objects.h"
#include "constants.h"


class Game {
private:
    std::vector<GameObject *> _game_objects;
    Ball *_ball;
    Vector2f _left_bottom, _right_top;
    int state;
    int total_time;
    bool _keys[NUM_KEYS];
    int num_active_bricks;

    void update_state();

    void draw_scoreboard();
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
