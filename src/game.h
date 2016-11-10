//
// Created by shailesh on 11/10/16.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include "objects.h"

const float BRICK_WIDTH = 2, BRICK_HEIGHT = 0.5;
const float ROWS = 7;

class Game {
private:
    std::vector<GameObject *> _game_objects;
    bool _paused;
public:
    Game();

    ~Game();

    void setup();

    void update();

    void draw();

    void toggle_pause();
};

#endif //BREAK_THE_BRICKS_GAME_H
