//
// Main controller.
//

#include "game.h"

#include <GL/glut.h>

#define WINDOW_TITLE "Break the Bricks"



// variables for game window
int WINDOW_WIDTH = 500, WINDOW_HEIGHT = 500;
int WINDOW_POS_X = 100, WINDOW_POS_Y = 100;

bool fullscreen = false;

Game game;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    game.setup();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
    glLoadIdentity();

    game.draw();

    glutSwapBuffers();
}

// Ref : https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0

    GLsizei viewport_size = width < height ? width : height;

    GLfloat clip_x_left, clip_x_right, clip_y_bottom, clip_y_top;

    // Set the viewport to cover the new window
    glViewport((width - viewport_size) / 2, (height - viewport_size) / 2, viewport_size, viewport_size);

    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix

    clip_x_left = -1.0f;
    clip_x_right = 1.0f;
    clip_y_bottom = -1.0f;
    clip_y_top = 1.0f;

    gluOrtho2D(clip_x_left, clip_x_right, clip_y_bottom, clip_y_top);
    game.reshape(Vector2f(clip_x_left, clip_y_bottom), Vector2f(clip_x_right, clip_y_top));
}

/* Called back when the timer expired */
void Timer(int value) {
    game.update();
    glutPostRedisplay();    // Post a paint request to activate display()
    glutTimerFunc(REFRESH_MILLI_SEC, Timer, 0); // subsequent timer call at milliseconds
}

void keyboard(unsigned char key, int x, int y) {
    game.key_pressed(key);
    switch (key) {
        case 'f':
        case 'F':
            // Ref : https://www3.ntu.edu.sg/home/ehchua/programming/opengl/CG_Introduction.html
            fullscreen = !fullscreen;         // Toggle state
            if (fullscreen) {                     // Full-screen mode
                WINDOW_POS_X   = glutGet(GLUT_WINDOW_X); // Save parameters for restoring later
                WINDOW_POS_Y   = glutGet(GLUT_WINDOW_Y);
                WINDOW_WIDTH  = glutGet(GLUT_WINDOW_WIDTH);
                WINDOW_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);
                glutFullScreen();                      // Switch into full screen
            } else {                                         // Windowed mode
                glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT); // Switch into windowed mode
                glutPositionWindow(WINDOW_POS_X, WINDOW_POS_Y);   // Position top-left corner
            }
            break;
        default:
            break;
    }
}


void keyboard_special(int key, int x, int y) {
    game.key_pressed(key);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow(WINDOW_TITLE);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(REFRESH_MILLI_SEC, Timer, 0);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboard_special);
//    glutFullScreen();

    init();

    glutMainLoop();

    return 0;
}