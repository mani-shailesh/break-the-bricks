//
// Main controller.
//

#include "game.h"

#include <GL/glut.h>

#define WINDOW_TITLE "Break the Bricks"

Game game;

void init() {
    game.setup();
}

void display() {
    game.draw();
}

void idle() {
    game.update();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(WINDOW_TITLE);

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}