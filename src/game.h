//
// Contains declarations for Game class.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include "objects.h"

const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

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
