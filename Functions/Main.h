#include "../Base/Includes.h"



void moveArrow(float angle = 90.0)
{
    glColor4f(1,1,1,1);
    glBegin(GL_LINES);
    glVertex2f(screenLeft, screenTop/2);
    glVertex2f(2, screenTop/2);
    glEnd();
}