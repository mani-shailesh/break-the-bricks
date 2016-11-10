//
// Created by shailesh on 11/10/16.
//

#include "game.h"

using namespace std;

Game::Game() {
    _paused = true;
}

Game::~Game() {
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        delete (*it);
    }
}

void Game::setup() {

    // Adding bricks to the scene
    Vector2f init_pos(-1.0, 0.5);  // TODO: Make them dynamic based on screen size

    Vector2f size(BRICK_WIDTH, BRICK_HEIGHT);

    for (int ii = 0; ii < ROWS; ii++) {
        Vector2f pos(0 + BRICK_WIDTH / 2, ii * (BRICK_HEIGHT + GAP));
        for (int jj = 0; jj < COLUMNS; jj++) {
            _game_objects.push_back(new Brick(init_pos + pos, size));
            pos = pos + Vector2f(BRICK_WIDTH + GAP, 0);
        }
    }

    // Adding ball to the scene
    Vector2f pos(0, -1 + RADIUS);
    _game_objects.push_back(new Ball(pos, RADIUS, SPEED));
}

void Game::update() {
    if (_paused)
        return;
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        (*it)->update();
    }
}

void Game::draw() {
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        (*it)->draw();
    }
}

void Game::toggle_pause() {
    _paused = !_paused;
}