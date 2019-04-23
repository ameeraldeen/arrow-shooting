#pragma once

#include "../Base/Includes.h"

using namespace std;


void onKeyboardEvent(unsigned char key, int x, int y)
{
    cout<<key<<endl;
    switch (key)
    {
    case 27: // Escape key
        exit(0);
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
        
        cout<<xPos<<" "<<yPos<<endl;

        initArrow.changeAngleFromPoint(Point(x,y));

        glutPostRedisplay();
    }
}


void onIdleEvent(){
    
    cout<<"test"<<endl;
    delay(700);
}


void onPassiveMotionEvent(int x, int y){
    
    cout<<x<<" "<<y<<endl;

    initArrow.changeAngleFromPoint(Point(x,y));

    glutPostRedisplay();
    // delay(200);
}


void onMotionEvent(int x, int y){
     
    
    glutPostRedisplay();
    // delay(200);
}