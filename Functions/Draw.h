#pragma once
#include <string>
#include "../Base/Includes.h"

int cnt = 1;

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
}

void displyInitArrow(float angle = 90.0)
{
    Line base = Line(
        Point(screenLeft, screenTop / 2),
        Point(screenRight / 5, screenTop / 2));

    drawArrow(base);

    // delay(5);
    glutPostRedisplay();
}

void drawPoint(float x, float y)
{
    glColor4f(1, 1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}
