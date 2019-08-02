// Author: Khaled Alam
// Email: khaledalam.net@gmail.com

// Description:
// Arrow Shooting 2D Game using C++ and OpenGL

#include "Base/Includes.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor4f(1, 1, 1, 1);

    displyInitArrow();

    glFlush();
}

void initRendering()
{
    glClearColor(0, 0, 0, 0);
    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void resizeWindow(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // [left, right] x [bottom, top]
    gluOrtho2D(screenLeft, screenRight, screenBottom, screenTop);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Arrows Attak Shooter");
    //----------

    initRendering();
    glutDisplayFunc(display);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(onKeyboardEvent);
    glutMouseFunc(onMouseEvent);
    // glutPassiveMotionFunc(onPassiveMotionEvent);
    // glutMotionFunc(onMotionEvent);
    // glutIdleFunc(onIdleEvent);

    glutMainLoop();

    return 0;
}
