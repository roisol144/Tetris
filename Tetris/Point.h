#pragma once

class Point
{

private:
	int x;
	int y;

public:
	
	// Constructors
	Point(int _x=0, int _y=0)
	{
		x = _x;
		y = _y;
	}
	

	int getX() { return x; }
	int getY() { return y; }
	void setX(int xParam) { x = xParam; }
	void setY(int yParam) { y = yParam; }

	Point rotateClockwise(Point& pivot);
	Point rotateCounterClockwise(Point& pivot);
};

