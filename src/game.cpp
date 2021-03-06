//
// Created by shailesh on 11/10/16.
//

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <sys/stat.h>
#include "game.h"

using namespace std;

Game::Game() {
    state = ACTIVE;
    _left_bottom = Vector2f(-1, -1);
    _right_top = Vector2f(1, 1);
    _total_time = 0;
    num_active_bricks = 0;
    read_best_time();
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
    num_active_bricks = 0;
    setup();
    _total_time = 0;
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

/*
 * Setup the scene at start of each game.
 */

void Game::setup() {

    // Add background to the scene
    Texture *bg_texture = new Texture(RES_DIR + "bg.bmp", BG_WIDTH, BG_HEIGHT);
    bg_texture->load_texture();
    _textures.push_back(bg_texture);

    Vector2f background_pos = (_left_bottom + _right_top) * 0.5;
    Vector2f background_size = _right_top - _left_bottom;
    _bg = new Rectangle(background_pos, background_size);
    _bg->set_texture(bg_texture);

    // Adding bricks to the scene
    Vector2f init_pos(_left_bottom.get_x(), _right_top.get_y() / 2);

    Vector2f size(BRICK_WIDTH, BRICK_HEIGHT);

    Texture *brick_texture = new Texture(RES_DIR + "brick.bmp", RECT_WIDTH, RECT_HEIGHT);
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
    Texture *platform_texture = new Texture(RES_DIR + "platform.bmp", RECT_WIDTH, RECT_HEIGHT);
    platform_texture->load_texture();
    _textures.push_back(platform_texture);

    Vector2f platform_pos(0, _left_bottom.get_y() + PLATFORM_HEIGHT / 2);
    Vector2f platform_size(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    Platform *platform = new Platform(platform_pos, platform_size, PLATFORM_SPEED);
    platform->set_texture(platform_texture);
    _game_objects.push_back(platform);

    // Adding ball to the scene
    Texture *ball_texture = new Texture(RES_DIR + "ball.bmp", BALL_WIDTH, BALL_HEIGHT);
    ball_texture->load_texture();
    _textures.push_back(ball_texture);

    Vector2f pos(0, platform_pos.get_y() + PLATFORM_HEIGHT / 2 + RADIUS);
    _ball = new Ball(pos, RADIUS, BALL_SPEED);
    _ball->set_texture(ball_texture);
}

/*
 * Update to be done at each frame.
 */
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
            _total_time += 1;
            break;
        case WON:
            if (_total_time < _best_time) {
                _best_time = _total_time;
                write_best_time();
            }
            break;
        case LOST:
            break;
        default:
            break;
    }
}

/*
 * Draw at each frame
 */
void Game::draw() {
    _bg->draw();

    vector<GameObject *>::iterator it;
    for (it = _game_objects.begin(); it != _game_objects.end(); it++) {
        (*it)->draw();
    }
    _ball->draw();

    draw_scoreboard();
}

/*
    Perform specific actions according to the keys pressed.
*/
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

/*
    Function to determine the state (win or loss) of the game.
*/
void Game::update_state(){
    if(num_active_bricks == 0)   // only platform remains
        state = WON;

    Vector2f ball_pos = _ball->get_pos();
    if(ball_pos.get_y() < _left_bottom.get_y() + PLATFORM_HEIGHT)
        state = LOST;
}

/*
    Function to check collisions of the ball with various objects.
*/
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

/*
    Function to draw the scoreboard and display the appropriate message on the screen.
*/
void Game::draw_scoreboard() {

    char time_text[50];
    sprintf(time_text, "Time %d", (_total_time * REFRESH_MILLI_SEC) / 1000);
    string left_text, right_text, centre_text;
    char centre_text_buffer[50];

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
            if (_best_time < numeric_limits<int>::max()) {
                sprintf(centre_text_buffer, "Best Time %d", (_best_time * REFRESH_MILLI_SEC) / 1000);
                centre_text = centre_text_buffer;
            } else {
                centre_text = "";
            }
            break;
        default:
            break;
    }

    glPushMatrix();

    glColor3f(TEXT_R, TEXT_G, TEXT_B);

    glPushMatrix();

    glTranslatef(_left_bottom.get_x(), 0, 0);
    glScalef(FONT_SCALING_FACTOR, FONT_SCALING_FACTOR, FONT_SCALING_FACTOR);

    for (int i = 0; i < left_text.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, left_text[i]);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(_right_top.get_x() - right_text.size() * FONT_WIDTH * FONT_SCALING_FACTOR, 0, 0);
    glScalef(FONT_SCALING_FACTOR, FONT_SCALING_FACTOR, FONT_SCALING_FACTOR);

    for (int i = 0; i < right_text.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, right_text[i]);

    glPopMatrix();

    glPushMatrix();

    glTranslatef(-0.5f * centre_text.size() * FONT_WIDTH * FONT_SCALING_FACTOR,
                 -0.1f - FONT_HEIGHT * FONT_SCALING_FACTOR, 0);
    glScalef(FONT_SCALING_FACTOR, FONT_SCALING_FACTOR, FONT_SCALING_FACTOR);

    for (int i = 0; i < centre_text.size(); i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, centre_text[i]);

    glPopMatrix();

    glColor3f(1, 1, 1);

    glPopMatrix();
}

/*
    Function to read the best time from the file.
*/
void Game::read_best_time() {
    _best_time = numeric_limits<int>::max();

    string file_name = DATA_DIR + "scores.bin";

    ifstream in_file;
    in_file.open(file_name.c_str(), ios_base::in);

    if (!in_file.is_open()) {
        cout << file_name << " not found!" << endl;
        return;
    }

    try {
        in_file.read(reinterpret_cast<char *>(&_best_time), sizeof(int));
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    in_file.close();
}

/*
    Function to write the best time in a file for future comparisons.
*/
void Game::write_best_time() {
    string file_name = DATA_DIR + "scores.bin";

    struct stat info;

    // Ref : http://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
    if (stat(file_name.c_str(), &info) != 0) {

        //Ref : http://stackoverflow.com/questions/20358455/cross-platform-way-to-make-a-directory
        mode_t n_mode = 0733; // UNIX style permissions
        int n_error = 0;
#if defined(_WIN32)
        n_error = _mkdir(DATA_DIR.c_str()); // can be used on Windows
#else
        n_error = mkdir(DATA_DIR.c_str(), n_mode); // can be used on non-Windows
#endif
        if (n_error != 0) {
            cerr << "Can not create directory!";
        }
    }


    ofstream out_file;
    out_file.open(file_name.c_str(), ios_base::app);

    try {
        out_file.write(reinterpret_cast<char *>(&_best_time), sizeof(int));
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    out_file.close();
}