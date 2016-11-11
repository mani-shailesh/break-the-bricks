//
// Created by shailesh on 11/10/16.
//

#ifndef BREAK_THE_BRICKS_CONSTANTS_H
#define BREAK_THE_BRICKS_CONSTANTS_H


// constants for game window
int const REFRESH_MILLI_SEC = 20;

// constants for game
enum{
    ACTIVE, PAUSED, LOST, WON
};

// constants for bricks
const float BRICK_WIDTH = 0.3, BRICK_HEIGHT = 0.1;
const float ROWS = 5, COLUMNS = 7;
const float GAP = 0.006;

// constants for ball
const float RADIUS = 0.04;
const float BALL_SPEED = 0.025;
const float BALL_DELTA_SPEED = 0.01f / 40;

// constants for platform
const float PLATFORM_WIDTH = 0.5, PLATFORM_HEIGHT = 0.05;
const float PLATFORM_SPEED = 0.1;

// constants for keys
const int NUM_KEYS = 3;
enum {
    LEFT_KEY, RIGHT_KEY, RESET_KEY
};

// constants for font
const float FONT_SCALING_FACTOR = 1.0f/1000;
const float FONT_WIDTH = 104.76f;
const float TEXT_R = 1.0f, TEXT_G = 1.0f, TEXT_B = 1.0f;

// constants for resources dir
const std::string RES_DIR = "assets/textures/";

// constants for image sizes
const int BG_WIDTH = 500, BG_HEIGHT = 300;
const int BALL_WIDTH = 300, BALL_HEIGHT = 300;
const int RECT_WIDTH = 300, RECT_HEIGHT = 100;

#endif //BREAK_THE_BRICKS_CONSTANTS_H
