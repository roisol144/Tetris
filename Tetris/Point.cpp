#include "Point.h"


Point Point::rotateClockwise(Point& pivot)
{
    int newX = pivot.getX() + (pivot.getY() - y);
    int newY = pivot.getY() - (pivot.getX() - x);
    Point p = { newX, newY };
    return p;
}

Point Point::rotateCounterClockwise(Point& pivot)
{
    int newX = pivot.getX() - (pivot.getY() - y);
    int newY = pivot.getY() + (pivot.getX() - x);
    Point p = { newX, newY };
    return p;
}



