//
// Created by shailesh on 11/10/16.
//

#ifndef BREAK_THE_BRICKS_CONSTANTS_H
#define BREAK_THE_BRICKS_CONSTANTS_H

// constants for bricks
const float BRICK_WIDTH = 0.3, BRICK_HEIGHT = 0.1;
const float ROWS = 5, COLUMNS = 7;
const float GAP = 0.006;

// constants for ball
const float RADIUS = 0.05;
const float BALL_SPEED = 0.04;

// constants for platform
const float PLATFORM_WIDTH = 0.5, PLATFORM_HEIGHT = 0.05;
const float PLATFORM_SPEED = 0.08;
const float VEL_DELTA_X = 0.03;

// constants for keys
const int NUM_KEYS = 3;
enum {
    LEFT_KEY, RIGHT_KEY, RESET_KEY
};

#endif //BREAK_THE_BRICKS_CONSTANTS_H
