#pragma once

#include "../Base/Includes.h"


void writeText(string text, float x, float y)
{	
	glColor3f(1.0, 1.0, 0.0); //yellow
    glRasterPos2i(x,y);
    int len = text.length();
    for(int i = 0; i < len; i++)
    { 
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18 , text[i]);
        glutPostRedisplay();
    }

    glFlush();
}

void displyInitArrow(float angle = 90.0)
{
    initArrow = Arrow(
        0.0,
        Line(),
        Line(),
        Line()
    );
    
    glColor4f(1,1,1,1);
    glBegin(GL_LINES);
    glVertex2f(screenLeft, screenTop / 2); // center |
    glVertex2f((screenRight/5), screenTop / 2); // (1/5) ---
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((screenRight/5), screenTop / 2); // (1/5) ---
    glVertex2f((screenRight/5) - 25, screenTop / 2 - 15);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f((screenRight/5), screenTop / 2); // (1/5) ---
    glVertex2f((screenRight/5) - 25, screenTop / 2 + 15);
    glEnd();
}

void drawPoint(float x, float y)
{
    glColor4f(1, 1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
    glFlush();    
}


