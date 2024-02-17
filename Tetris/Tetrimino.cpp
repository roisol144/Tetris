#include "Tetrimino.h"
using namespace std;

void Tetrimino::createTetromino(bool isColor) {
	//reset the first point 
	this->m_points[0].setX(4);
	this->m_points[0].setY(0);
	
	int randShape = 1 + rand() % 7;
	int randBomb = 1 + rand() % 20;
	
	if (randBomb == 1) {
		this->isBomb = true;
		for (int i = 1; i < NUM_OF_POINTS; i++) {
			this->m_points[i].setX(4);
			this->m_points[i].setY(0);
		}
		if (isColor)
			this->color = Colors::RED;
	}
	else {
		this->isBomb = false;
		switch (randShape) {
		case STRAIGHT: { // STRAIGHT
			for (int i = 1; i < NUM_OF_POINTS; i++) {
				this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
				this->m_points[i].setY(0);
			}
			
			if (isColor)
				this->color = Colors::CYAN;
			break;
		}
		case SQUARE: { // SQUARE
			for (int i = 1; i < 2; i++) {
				this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
				this->m_points[i].setY(0);
			}
			for (int i = 2; i < NUM_OF_POINTS; i++) {
				this->m_points[i].setX(this->m_points[i - 2].getX());
				this->m_points[i].setY(1);
			}
			
			if (isColor)
				this->color = Colors::YELLOW;

			break;
		}
		case T: { // T
			for (int i = 1; i < 3; i++) {
				this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
				this->m_points[i].setY(0);
			}
			this->m_points[3].setX(5);
			this->m_points[3].setY(1);
			
			if (isColor)
				this->color = Colors::MAGENTA;

			break;
		}
		case J: { // J
			this->m_points[0].setX(5);
			for (int i = 1; i < 3; i++) {
				this->m_points[i].setX(5);
				this->m_points[i].setY(this->m_points[i - 1].getY() + 1);
			}
			this->m_points[3].setX(4);
			this->m_points[3].setY(2);
			
			if (isColor)
				this->color = Colors::BLUE;

			break;
		}
		case L: { // L
			for (int i = 1; i < 3; i++)
			{
				this->m_points[i].setX(4);
				this->m_points[i].setY(this->m_points[i - 1].getY() + 1);
			}
			this->m_points[3].setX(5);
			this->m_points[3].setY(2);
			
			if (isColor)
				this->color = Colors::BROWN;

			break;
		}

		case S: { // S
			this->m_points[0].setX(4);
			this->m_points[0].setY(1);
			this->m_points[1].setX(5);
			this->m_points[1].setY(1);
			this->m_points[2].setX(5);
			this->m_points[2].setY(0);
			this->m_points[3].setX(6);
			this->m_points[3].setY(0);
			
			if (isColor)
				this->color = Colors::GREEN;

			break;
		}
		case Z: { // Z
			this->m_points[1].setX(5);
			this->m_points[1].setY(0);
			this->m_points[2].setX(5);
			this->m_points[2].setY(1);
			this->m_points[3].setX(6);
			this->m_points[3].setY(1);
			
			if (isColor)
				this->color = Colors::LIGHTRED;

			break;
		}
		}
	}
}

bool Tetrimino::moveDown(const char* down) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (this->m_points[i].getY() + 1 == this->GAME_HEIGHT)
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (down[i] != ' ')
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->m_points[i].setY(this->m_points[i].getY() + 1);	
	}

	return true;

}

void Tetrimino::draw(int gap) const {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		gotoxy(this->m_points[i].getX() + gap + 1, this->m_points[i].getY()+1);
		SetConsoleTextAttribute(hStdOut, this->color);
		if (this->isBomb)
			cout << 'X';
		else
			cout << (char)219;
	}
}

void Tetrimino::erase(int gap) const {
	for (int i = 0; i < NUM_OF_POINTS && !newBorn; i++) {
		gotoxy(this->m_points[i].getX() + gap + 1, this->m_points[i].getY()+1);
		cout << ' ';
	}
}

void Tetrimino::move(int gap) const
{
	this->draw(gap);
}



bool Tetrimino::moveRight(const char* right) {
	
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (this->m_points[i].getX() + 1 == this->GAME_WIDTH)
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (right[i] != ' ')
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		this->m_points[i].setX(this->m_points[i].getX() + 1);
	}
	return true;
}


bool Tetrimino::moveLeft(const char* left)
{
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (this->m_points[i].getX() == 0)
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (left[i] != ' ')
			return false;
	}


	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		this->m_points[i].setX(this->m_points[i].getX() - 1);
	}
	return true;
}


Point Tetrimino::calculatePivot()
{
	int sumX = 0;
	int sumY = 0;

	for (Point& point : m_points)
	{
		sumX += point.getX();
		sumY += point.getY();
	}

	int averageX = round(static_cast<double>(sumX) / NUM_OF_POINTS); 
	int averageY = round(static_cast<double>(sumY) / NUM_OF_POINTS);

	return Point(averageX, averageY);
}


void Tetrimino::rotateClockwise(Point* pointsToRotate)
{
	Point pivot = calculatePivot();
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		pivot.setX(pivot.getX() + m_points[i].getX());
		pivot.setY(pivot.getY() + m_points[i].getY());
	}
	pivot.setX(pivot.getX() / NUM_OF_POINTS);
	pivot.setY(pivot.getY() / NUM_OF_POINTS);

	

	// Rotate clockwise around the pivot
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		pointsToRotate[i].setX(m_points[i].rotateClockwise(pivot).getX());
		pointsToRotate[i].setY(m_points[i].rotateClockwise(pivot).getY());

	}
}


bool Tetrimino::isRotateLegal(const Point* pointsArr, const char* rotated)
{
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (pointsArr[i].getX() < 0 || pointsArr[i].getX() >= GAME_WIDTH)
			return false;
		if (pointsArr[i].getY() < 0 || pointsArr[i].getY() >= GAME_HEIGHT)
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (rotated[i] != ' ')
			return false;
	}

	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->m_points[i].setX(pointsArr[i].getX());
		this->m_points[i].setY(pointsArr[i].getY());
	}

	return true;
}


void Tetrimino::rotateCounterClockwise(Point* pointToRotate)
{
	Point pivot = calculatePivot();
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		pivot.setX(pivot.getX() + m_points[i].getX());
		pivot.setY(pivot.getY() + m_points[i].getY());
	}
	pivot.setX(pivot.getX() / NUM_OF_POINTS);
	pivot.setY(pivot.getY() / NUM_OF_POINTS);

	// Rotate counterclockwise around the pivot
	

	// Rotate clockwise around the pivot
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		pointToRotate[i].setX(m_points[i].rotateCounterClockwise(pivot).getX());
		pointToRotate[i].setY(m_points[i].rotateCounterClockwise(pivot).getY());
	}
}

bool Tetrimino::isTopReached()
{
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		if (this->m_points[i].getY() == 0)
		{
			for (int j = i; j < NUM_OF_POINTS; j++)
				this->m_points[j].setY(this->m_points[j].getY() + 1);
			return true;
		}
	}
	return false;
}


void Tetrimino::setNextMoveByIndex(char ch1, int index) {
	this->nextMove[index] = ch1;
	
}

void Tetrimino::setYcoords(int* y) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->m_points[i].setY(y[i]);
	}
}
void Tetrimino::setYcoordsByIndex(int y,int index) {
	
		this->m_points[index].setY(y);
	
}

void Tetrimino::setXcoordsByIndex(int x, int index) {
	
		this->m_points[index].setX(x);
	
}

void Tetrimino::setXcoords(int* x) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->m_points[i].setX(x[i]);
	}
}