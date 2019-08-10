// Author: Khaled Alam
// Email: khaledalam.net@gmail.com

// Description:
// Arrow Shooting 2D Game using C++ and OpenGL

#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;

const float gx2 = 20;
const float gy2 = 20;
const int windowHeight = 500;
const int windowWidth = 500;
const float screenLeft = 0.0f;
const float screenRight = 500.0f;
const float screenBottom = 0.0f;
const float screenTop = 500.0f;

const float rateChangeAngle = 0.025; // rate used to change angle when click (Up & Down)
const float rateFireSpeed = 0.8;     // rate used for increasing radius wile firing
const float rateHitDistance = 10.0;  // rate used for considering line hit dot

const int rateGameoverSeconds = 20; // rate used to set when game is over

// const float PI = 3.14285714286;

bool firing = false;
int score = 0;

time_t start, tillNow;

// START Prototypes
struct Point;
struct Line;
void myKeyboardFunc(unsigned char key, int x, int y);
void myMouseFunc(int button, int state, int x, int y);
void displayPoints(void);
void addNewPoint(float x, float y);
void initRendering();
void resizeWindow(int w, int h);
void goUp();
void goDown();
void generateDot();
void writeText(string text, float x, float y);
double distanceBetweenTwoPoints(Point A, Point B);

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

    void draw()
    {
        glColor3f(rand() % 2, rand() % 2, rand() % 2);

        glBegin(GL_POINTS);
        glPointSize(10.0f); // wat
        glVertex2f(x, y);
        glEnd();
    }
};

struct Line
{
    float angle;
    float R_from; // radius from point(0, 0) to point(x_from, y_from)
    float R_to;   // radius from point(0, 0) to point(x_to, y_to)
    Point from, to;
    int lifeSteps = 1000;

    Line(Point _from, Point _to, float _angle = 45.0, float _R_from = 0, float _R_to = 100.0)
    {
        angle = _angle;
        R_from = _R_from;
        R_to = _R_to;
        from = _from;
        to = _to;
    }
    Line(){};

    void draw()
    {
        glColor3f(1.0, 1.0, 0.0); //yellow
        glBegin(GL_LINES);
        glVertex2f(from.x, from.y);
        glVertex2f(to.x, to.y);
        glEnd();

        /*
            Coordinates of a point on a circle 

            (0,0) ------------ (x,y)

            x = R * cos(angle)
            y = R * sin(angle)
        */

        from.x = (R_from * cos(angle));
        from.y = (R_from * sin(angle));

        to.x = (R_to * cos(angle));
        to.y = (R_to * sin(angle));

        // cout << angle << " (" << to.x << ", " << to.y << ")" << endl;
    }

    void fire()
    {
        R_to += rateFireSpeed;
        R_from += rateFireSpeed;
        this->changeAngle(angle);
        this->draw();
    }

    void changeAngle(float newAngle)
    {
        if (firing)
            return;

        if (angle > 45.5)
        {
            angle = 45.5;
            return;
        }
        if (angle < 44.02)
        {
            angle = 44.02;
            return;
        }

        angle = newAngle;
    }

    bool insideBorder()
    {
        return to.x < screenRight && to.y < screenTop;
    }

    bool hitPoint(Point point)
    {
        return distanceBetweenTwoPoints(to, point) <= rateHitDistance;
    }

    void reset()
    {
        R_from = 0.0;
        R_to = 100.0;
        angle = 45.0;
        this->changeAngle(angle);
        this->draw();
    }
};
// END Structs

Point dot = Point(screenRight / 2, screenTop / 2);

Line arrow = Line(
    Point(0, 0),
    Point(100 * cos(45.0), 100 * sin(45.0)),
    45.0,
    0.0,
    100.0);

const Line defaultArrow = arrow;

double distanceBetweenTwoPoints(Point A, Point B)
{
    return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

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
        firing = true;
        break;
    case 'r': // r key
        time(&start);
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
    case GLUT_KEY_LEFT:
        arrow.reset();
        break;
    case GLUT_KEY_RIGHT:
        firing = true;
        break;
    }
}

// END Events

void writeText(string text, float x, float y)
{
    glColor3f(1.0, 1.0, 0.0); //yellow
    glRasterPos2i(x, y);
    int len = text.length();
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
    glutPostRedisplay();

    glFlush();
}

void goUp()
{
    arrow.changeAngle(arrow.angle + rateChangeAngle);
}

void goDown()
{
    arrow.changeAngle(arrow.angle - rateChangeAngle);
}

void generateDot()
{
    dot = Point((rand() % (int)screenRight), (rand() % (int)screenTop));
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);

    time(&tillNow);
    int dif = difftime(tillNow, start);

    bool gameover = (dif >= rateGameoverSeconds);
    if (gameover)
    {
        firing = false;
        arrow.reset();
        writeText("Score: " + to_string(score) + "  in " + to_string(rateGameoverSeconds) +
                      " second" + (rateGameoverSeconds > 1 ? "s" : "") + "!  press [r] key",
                  screenRight / 6, screenTop / 2);
    }
    else
    {
        arrow.draw();
        dot.draw();

        writeText(to_string(dif) + " second" + (dif > 1 ? "s" : "") + "   |   score: " + to_string(score),
                  screenRight / 4, screenTop - 20);
    }

    if (firing)
    {
        if (arrow.insideBorder())
        {
            arrow.fire();
            double x = distanceBetweenTwoPoints(arrow.to, dot);

            if (arrow.hitPoint(dot))
            {
                score += (50 / distanceBetweenTwoPoints(arrow.to, dot));
                generateDot();
            }
        }
        else
        {
            firing = false;
            arrow.reset();
        }
    }

    if (!gameover)
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
    time(&start);
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

    glutMainLoop();

    return 0;
}
