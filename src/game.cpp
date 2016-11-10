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
    // TODO: Create GameObjects and set up the scene
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