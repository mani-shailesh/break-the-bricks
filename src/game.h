//
// Contains declarations for Game class.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>
#include "objects.h"


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

    void key_pressed(int key);
};

#endif //BREAK_THE_BRICKS_GAME_H
