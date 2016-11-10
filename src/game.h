//
// Contains declarations for Game class.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include "objects.h"

// constants for game window
const int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;

// constants for bricks
const float BRICK_WIDTH = 0.3, BRICK_HEIGHT = 0.1;
const float ROWS = 5, COLUMNS = 7;
const float GAP = 0.006;

// constants for ball
const float RADIUS = 0.05;
const float SPEED = 0.05;

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
