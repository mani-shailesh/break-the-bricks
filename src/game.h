//
// Contains declarations for Game class.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include "objects.h"

// constants for bricks
const float BRICK_WIDTH = 0.3, BRICK_HEIGHT = 0.1;
const float ROWS = 5, COLUMNS = 7;
const float GAP = 0.006;

// constants for ball
const float RADIUS = 0.05;
const float SPEED = 0.05;

// constants for platform
const float PLATFORM_WIDTH = 0.5, PLATFORM_HEIGHT = 0.05;

enum {
    SPACE_KEY, LEFT_KEY, RIGHT_KEY
};


class Game {
private:
    std::vector<GameObject *> _game_objects;
    Vector2f _left_bottom, _right_top;
    bool _paused;
    bool _keys[3];
public:
    Game();

    void reshape(Vector2f left_bottom, Vector2f right_top);

    ~Game();

    void setup();

    void update();

    void draw();

    void toggle_pause();
};

#endif //BREAK_THE_BRICKS_GAME_H
