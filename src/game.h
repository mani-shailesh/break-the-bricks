//
// Created by shailesh on 11/10/16.
//

#ifndef BREAK_THE_BRICKS_GAME_H
#define BREAK_THE_BRICKS_GAME_H

#include <vector>

class Brick;

class Game {
private:
    std::vector<Brick *> _bricks;
    bool _paused;
public:
    Game();

    ~Game();

    void update();

    void draw();

    void toggle_pause();
};

#endif //BREAK_THE_BRICKS_GAME_H
