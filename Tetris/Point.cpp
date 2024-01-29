#include "Point.h"


Point Point::rotateClockwise(const Point& pivot) const
{
    int newX = pivot.getX() + (pivot.getY() - y);
    int newY = pivot.getY() - (pivot.getX() - x);
    Point p = { newX, newY };
    return p;
}

Point Point::rotateCounterClockwise(const Point& pivot) const
{
    int newX = pivot.getX() - (pivot.getY() - y);
    int newY = pivot.getY() + (pivot.getX() - x);
    Point p = { newX, newY };
    return p;
}



