// Author: Khaled Alam
// Email: khaledalam.net@gmail.com

// Description:
// Arrow Shooting 2D Game using C++ and OpenGL

#include <bits/stdc++.h>

#include <GL/glut.h>

using namespace std;

int cnt = 1;
float gx2 = 20;
float gy2 = 20;
float theta = 0;
int windowHeight = 500;
int windowWidth = 500;
const float screenLeft = 0.0f;
const float screenRight = 500.0f;
const float screenBottom = 0.0f;
const float screenTop = 500.0f;
const float minLimit = 70.0f;

const float R = 3.5;

const float PI = 3.14285714286;

const int UP = -1;
const int DOWN = 1;

int recentAction = UP;
bool run = true;

#define MaxNumPts 16

// START Prototypes
void myKeyboardFunc(unsigned char key, int x, int y);
void myMouseFunc(int button, int state, int x, int y);
void displayPoints(void);
void addNewPoint(float x, float y);
void initRendering();
void resizeWindow(int w, int h);
void fire();
void goUp();
void goDown();
// END Prototypes

// START Structs
struct Point
{
    float x, y;
    Point(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    Point(){};
};

struct Line
{
    Point from, to;
    Line(Point _from, Point _to)
    {
        from = _from;
        to = _to;
    }
    Line(){};
};
// END Structs

Line arrow = Line(
    Point(screenLeft, screenTop / 2),
    Point(screenRight / 5, screenTop / 2));

const Line defaultArrow = arrow;

// START Events
void onKeyboardEvent(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Escape key
        exit(0);
        break;
    case 32:
    case 13:
        fire();
        break;
    }
}

void SpecialInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        goDown();
        break;
    case GLUT_KEY_UP:
        goUp();
        break;
    case GLUT_KEY_RIGHT:
    case GLUT_KEY_LEFT:
        arrow = defaultArrow;
        break;
    }
}

void onMouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //scale correction:
        float xPos = ((float)x) / ((float)(windowWidth * (1 / screenRight)));
        float yPos = ((float)y) / ((float)(windowHeight * (1 / screenTop)));
        yPos = screenTop - yPos; // Flip  (y is from top)
        cout << xPos << " " << yPos << endl;
        glutPostRedisplay();
    }
}

void onIdleEvent()
{
    cout << "test" << endl;
    // delay(700);
}

void onPassiveMotionEvent(int x, int y)
{
    cout << x << " " << y << endl;
    glutPostRedisplay();
    // delay(200);
}

void onMotionEvent(int x, int y)
{
    glutPostRedisplay();
    // delay(200);
}

// END Events

void delay(int seconds)
{
    int miSeconds = 1000 * seconds;
    clock_t startTime = clock();
    while (clock() < startTime + miSeconds)
        ;
}

// void writeText(string text, float x, float y)
// {
//     glColor3f(1.0, 1.0, 0.0); //yellow
//     glRasterPos2i(x, y);
//     int len = text.length();
//     for (int i = 0; i < len; i++)
//     {
//         glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
//         glutPostRedisplay();
//     }

//     glFlush();
// }

void drawArrow(Line x)
{
    glColor4f(1, 1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(x.from.x, x.from.y);
    glVertex2f(x.to.x, x.to.y);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((screenRight / 5), screenTop / 2); // (1/5) ---
    glVertex2f((screenRight / 5) - 25, screenTop / 2 - 15);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((screenRight / 5), screenTop / 2); // (1/5) ---
    glVertex2f((screenRight / 5) - 25, screenTop / 2 + 15);
    glEnd();

    if (run)
    {
        fire();
    }
}

void displyInitArrow(float angle = 90.0)
{
}

void fire()
{
    cout << "fired" << endl;

    cout << arrow.to.x << endl;
    if (arrow.to.x >= 500)
    {
        run = false;
        arrow.to.x = 499;
        return;
    }
    arrow.from.x += 0.1, arrow.to.x += 0.1;
}

void goUp()
{
    if (arrow.to.x <= minLimit && recentAction == UP)
    {
        arrow.to.x = minLimit;
        return;
    }

    // theta += 0.05;            //get the current angle
    // float x = R * sin(theta); //calculate the x component
    // float y = R * cos(theta); //calculate the y component

    cout << "up! " << arrow.to.x << " " << arrow.to.y << endl;
    arrow.to.x -= sin(0.7);
    arrow.to.y += cos(0.7);
}

void goDown()
{
    if (arrow.to.x <= minLimit && recentAction == DOWN)
    {
        arrow.to.x = minLimit;
        return;
    }

    cout << "down! " << arrow.to.x << " " << arrow.to.y << endl;

    // if (arrow.to.x >= 100)
    // {
    //     cout << "Y" << endl;
    //     arrow.to.x -= sin(0.7);
    //     arrow.to.y += cos(0.7);
    // }
    // else
    // {
    //     arrow.to.x += sin(0.7);
    //     arrow.to.y -= cos(0.7);
    // }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(1, 1, 1, 1);

    drawArrow(arrow);

    glutPostRedisplay();

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
    glutCreateWindow("Arrow Shooting 2D Game");
    //----------

    initRendering();
    glutDisplayFunc(display);
    glutReshapeFunc(resizeWindow);
    glutKeyboardFunc(onKeyboardEvent);
    glutSpecialFunc(SpecialInput);
    glutMouseFunc(onMouseEvent);
    // glutPassiveMotionFunc(onPassiveMotionEvent);
    // glutMotionFunc(onMotionEvent);
    // glutIdleFunc(onIdleEvent);

    glutMainLoop();

    return 0;
}
