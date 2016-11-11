//
// Created by shailesh on 11/10/16.
//

#include <GL/glut.h>
#include <iostream>
#include "game.h"

using namespace std;

Game::Game() {
    state = ACTIVE;
    _left_bottom = Vector2f(-1, -1);
    _right_top = Vector2f(1, 1);
    total_time = 0;
    num_active_bricks = 0;
}

void Game::reshape(Vector2f left_bottom, Vector2f right_top) {
    _left_bottom = left_bottom;
    _right_top = right_top;
}

Game::~Game() {
    free_all();
}

void Game::reset() {
    free_all();
    setup();
    total_time = 0;
    num_active_bricks = 0;
}

void Game::free_all(){
    if(_bg)
        delete(_bg);
    while (_game_objects.size() > 0) {
        GameObject *gameObject = _game_objects.back();
        _game_objects.pop_back();
        delete (gameObject);
    }
    while (_textures.size() > 0) {
        Texture *texture = _textures.back();
        _textures.pop_back();
        delete (texture);
    }
    if(_ball)
        delete (_ball);
}

void Game::setup() {

    // Add background to the scene
    Texture *bg_texture = new Texture(RES_DIR + "bg.bmp", 500, 300);
    bg_texture->load_texture();
    _textures.push_back(bg_texture);

    Vector2f background_pos = (_left_bottom + _right_top) * 0.5;
    Vector2f background_size = _right_top - _left_bottom;
    _bg = new Rectangle(background_pos, background_size);
    _bg->set_texture(bg_texture);

    // Adding bricks to the scene
    Vector2f init_pos(_left_bottom.get_x(), _right_top.get_y() / 2);

    Vector2f size(BRICK_WIDTH, BRICK_HEIGHT);

    Texture *brick_texture = new Texture(RES_DIR + "brick.bmp", 300, 100);
    brick_texture->load_texture();
    _textures.push_back(brick_texture);

    for (int ii = 0; ii < ROWS; ii++) {
        Vector2f pos;
        if(ii%2 == 0)
            pos = Vector2f(BRICK_WIDTH / 2, ii * (BRICK_HEIGHT + GAP));
        else
            pos = Vector2f(0, ii * (BRICK_HEIGHT + GAP));

        for (int jj = 0; jj < COLUMNS; jj++) {
            Brick *brick = new Brick(init_pos + pos, size);
            brick->set_texture(brick_texture);
            _game_objects.push_back(brick);
            num_active_bricks ++;
            pos = pos + Vector2f(BRICK_WIDTH + GAP, 0);
        }
    }

    // Adding platform to the scene
    Texture *platform_texture = new Texture(RES_DIR + "ball.bmp", 300, 300);
    platform_texture->load_texture();
    _textures.push_back(platform_texture);

    Vector2f platform_pos(0, _left_bottom.get_y() + PLATFORM_HEIGHT / 2);
    Vector2f platform_size(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    Platform *platform = new Platform(platform_pos, platform_size, PLATFORM_SPEED);
    platform->set_texture(platform_texture);
    _game_objects.push_back(platform);

    // Adding ball to the scene
    Texture *ball_texture = new Texture(RES_DIR + "ball.bmp", 300, 300);
    ball_texture->load_texture();
    _textures.push_back(ball_texture);

    Vector2f pos(0, platform_pos.get_y() + PLATFORM_HEIGHT / 2 + RADIUS);
    _ball = new Ball(pos, RADIUS, BALL_SPEED);
    _ball->set_texture(ball_texture);
}

void Game::update() {
    update_state();
    vector<GameObject *>::iterator it;
    switch(state){
        case ACTIVE:
            for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
                (*it)->update(_left_bottom, _right_top, _keys);
            }

            check_collisions();
            _ball->update(_left_bottom, _right_top, _keys);
            total_time += 1;
            break;
        case WON:
            break;
        case LOST:
            break;
        default:
            break;
    }
}

void Game::draw() {
    _bg->draw();

    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        (*it)->draw();
    }
    _ball->draw();

    draw_scoreboard();
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
            if(state != ACTIVE)
                state = ACTIVE;
            else
                state = PAUSED;
            break;
        case 'r':
        case 'R':
            if (_keys[RESET_KEY]) {
                reset();
                state = PAUSED;
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

void Game::update_state(){
    if(num_active_bricks == 0)   // only platform remains
        state = WON;

    Vector2f ball_pos = _ball->get_pos();
    if(ball_pos.get_y() < _left_bottom.get_y() + PLATFORM_HEIGHT)
        state = LOST;
}

void Game::check_collisions() {
    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        Vector2f *normal = (*it)->get_collision_normal(*_ball);
        if (normal) {
            _ball->set_velocity_dir(_ball->get_velocity().reflect(*normal));
            _ball->set_speed(_ball->get_speed() + BALL_DELTA_SPEED);
            num_active_bricks--;
            break;
        }
    }
}

void Game::draw_scoreboard() {

    string time_text = "Time " + to_string((total_time * REFRESH_MILLI_SEC)/1000);
    string left_text;
    string right_text;

    switch (state){
        case ACTIVE:
            left_text = time_text;
            break;
        case PAUSED:
            left_text = time_text;
            right_text = "PAUSED!";
            break;
        case LOST:
            right_text = "GAME OVER!";
            break;
        case WON:
            left_text = time_text;
            right_text = "YOU WON!";
            break;
    }

    glPushMatrix();

    glTranslatef(_left_bottom.get_x(), 0, 0);
    glScalef(FONT_SCALING_FACTOR, FONT_SCALING_FACTOR, FONT_SCALING_FACTOR);

    for(int i=0; i<left_text.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, left_text[i]);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(_right_top.get_x() - right_text.size() * FONT_WIDTH * FONT_SCALING_FACTOR, 0, 0);
    glScalef(FONT_SCALING_FACTOR, FONT_SCALING_FACTOR, FONT_SCALING_FACTOR);

    for(int i=0; i<right_text.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, right_text[i]);

    glPopMatrix();
}