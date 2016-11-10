//
// Created by shailesh on 11/10/16.
//

#include <GL/glut.h>
#include "game.h"

using namespace std;

Game::Game() {
    _paused = true;
    _left_bottom = Vector2f(-1, -1);
    _right_top = Vector2f(1, 1);
}

void Game::reshape(Vector2f left_bottom, Vector2f right_top) {
    _left_bottom = left_bottom;
    _right_top = right_top;
}

Game::~Game() {
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        delete (*it);
    }
    delete (ball);
}

void Game::reset() {
    _paused = true;
    while (_game_objects.size() > 0) {
        GameObject *gameObject = _game_objects.back();
        _game_objects.pop_back();
        delete (gameObject);
    }
    delete (ball);

    setup();
}

void Game::setup() {

    // Adding bricks to the scene
    Vector2f init_pos(_left_bottom.get_x(), _right_top.get_y() / 2);

    Vector2f size(BRICK_WIDTH, BRICK_HEIGHT);

    for (int ii = 0; ii < ROWS; ii++) {
        Vector2f pos(0 + BRICK_WIDTH / 2, ii * (BRICK_HEIGHT + GAP));
        for (int jj = 0; jj < COLUMNS; jj++) {
            _game_objects.push_back(new Brick(init_pos + pos, size));
            pos = pos + Vector2f(BRICK_WIDTH + GAP, 0);
        }
    }

    // Adding platform to the scene
    Vector2f platform_pos(0, _left_bottom.get_y() + PLATFORM_HEIGHT / 2);
    Vector2f platform_size(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    _game_objects.push_back(new Platform(platform_pos, platform_size, PLATFORM_SPEED));

    // Adding ball to the scene
    Vector2f pos(0, platform_pos.get_y() + PLATFORM_HEIGHT / 2 + RADIUS);
    ball = new Ball(pos, RADIUS, BALL_SPEED);
}

void Game::update() {
    if (_paused)
        return;
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        (*it)->update(_left_bottom, _right_top, _keys);
    }
    ball->update(_left_bottom, _right_top, _keys);
}

void Game::draw() {
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        (*it)->draw();
    }
    ball->draw();
}

void Game::toggle_pause() {
    _paused = !_paused;
}

void Game::key_pressed(int key) {
    switch (key) {
        case GLUT_KEY_LEFT:
            _keys[LEFT_KEY] = true;
            break;
        case GLUT_KEY_RIGHT:
            _keys[RIGHT_KEY] = true;
            break;
        case ' ':
            toggle_pause();
            break;
        case 'r':
        case 'R':
            if (_keys[RESET_KEY]) {
                reset();
                _keys[RESET_KEY] = false;
            } else {
                _keys[RESET_KEY] = true;
            }
            break;
        default:
            break;
    }

    if (key != 'r' && key != 'R')
        _keys[RESET_KEY] = false;
}