#pragma once

#include "../Entity/Point.h"
#include <iostream>

using namespace std;

struct Arrow
{
    float angle;
    Line * base, *left, *right;


    Arrow(float _angle, Line  *_base, Line *_left, Line *_right) {
        angle = _angle;
        base = _base;
        left = _left;
        right = _right;
    }

    void changeAngleFromPoint(Point point) {

        //calc here:

        cout<<"start calc:\n";


        cout<<"end calc:\n";


        angle = 0.0;
    }

    Arrow(){
        base = left = right = new Line();
    };
};
