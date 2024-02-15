#pragma once

class Point
{

private:
	int x;
	int y;

public:
	
	// Constructors
	Point() {}

	Point(int x, int y) :x(0),y(0) {
		this->x = x;
		this->y = y;
	}

	

	
	

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(const int xParam) { x = xParam; }
	void setY(const int yParam) { y = yParam; }

	Point rotateClockwise(const Point& pivot) const;
	Point rotateCounterClockwise(const Point& pivot) const;
};

