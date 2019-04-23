#include "Point.h"


struct Line{
    Point *from, *to;
    Line(Point *_from, Point *_to){
        from = _from;
        to = _to;
    }
    Line(){
        from = to = new Point();
    };
}