#include "Point.h"

// Figure out how to change it to const.
Point Point::rotateClockwise(Point& pivot)
{
    int newX = pivot.getX() + (pivot.getY() - y);
    int newY = pivot.getY() - (pivot.getX() - x);
    Point p = { newX, newY };
    //this->x = newX;
    //this->y = newY;
    return p;
}

Point Point::rotateCounterClockwise(Point& pivot)
{
    int newX = pivot.getX() - (pivot.getY() - y);
    int newY = pivot.getY() + (pivot.getX() - x);
    Point p = { newX, newY };
    //this->x = newX;
    //this->y = newY;
    return p;
}



