//
// Main controller.
//

#include "game.h"

#include <GL/glut.h>

#define WINDOW_TITLE "Break the Bricks"

int const REFRESH_MILI_SEC = 30;

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
    GLfloat aspect = (GLfloat) width / (GLfloat) height;

    GLfloat clip_x_left, clip_x_right, clip_y_bottom, clip_y_top;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (width >= height) {
        clip_x_left = -1.0f * aspect;
        clip_x_right = 1.0f * aspect;
        clip_y_bottom = -1.0f;
        clip_y_top = 1.0f;
    } else {
        clip_x_left = -1.0f;
        clip_x_right = 1.0f;
        clip_y_bottom = -1.0f / aspect;
        clip_y_top = 1.0f / aspect;
    }
    gluOrtho2D(clip_x_left, clip_x_right, clip_y_bottom, clip_y_top);
    game.reshape(Vector2f(clip_x_left, clip_y_bottom), Vector2f(clip_x_right, clip_y_top));
}

/* Called back when the timer expired */
void Timer(int value) {
    game.update();
    glutPostRedisplay();    // Post a paint request to activate display()
    glutTimerFunc(REFRESH_MILI_SEC, Timer, 0); // subsequent timer call at milliseconds
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, Timer, 0);

    init();

    game.toggle_pause();
    glutMainLoop();

    return 0;
}