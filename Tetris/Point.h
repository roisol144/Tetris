#pragma once

class Point
{

private:
	int x;
	int y;

public:
	// Constructors
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	int getX() { return x; }
	int getY() { return y; }
	void setX(int xParam) { x = xParam; }
	void setY(int yParam) { y = yParam; }

	void rotateClockwise(Point& pivot);
	void rotateCounterClockwise(Point& pivot);
};

