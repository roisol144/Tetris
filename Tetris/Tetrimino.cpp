#include "Tetrimino.h"
using namespace std;

void Tetrimino::createTetromino() {
	//reset the first point 
	this->m_points[0].setX(4);
	this->m_points[0].setY(0);
	srand(time(nullptr));
	int randNum = 1 + rand() % 7;

	//int randNum = 1; // FOR TESTS

	switch (randNum) {
	case 1: { // STRAIGHT
		for (int i = 1; i < NUM_OF_POINTS; i++) {
			this->m_points[i].setX(this->m_points[i-1].getX() + 1);
			this->m_points[i].setY(0);
		}
		this->colorAnsciCode = "\033[36m";
		break;
	}
	case 2: { // SQUARE
		for (int i = 1; i < 2; i++) {
			this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
			this->m_points[i].setY(0);
		}
		for (int i = 2; i < NUM_OF_POINTS; i++) {
			this->m_points[i].setX(this->m_points[i - 2].getX());
			this->m_points[i].setY(1);
		}
		this->colorAnsciCode = "\033[33m";
		break;
	}
	case 3: { // T
		for (int i = 1; i < 3; i++) {
			this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
			this->m_points[i].setY(0);
		}
		this->m_points[3].setX(5);
		this->m_points[3].setY(1);
		this->colorAnsciCode = "\033[35m";
		break;
	}
	case 4: { // J
		this->m_points[0].setX(5);
		for (int i = 1; i < 3; i++) {
			this->m_points[i].setX(5);
			this->m_points[i].setY(this->m_points[i-1].getY() + 1);
		}
		this->m_points[3].setX(4);
		this->m_points[3].setY(2);
		this->colorAnsciCode = "\033[34m";
		break;
	}
	case 5: { // L
		for (int i = 1; i < 3; i++)
		{
			this->m_points[i].setX(4);
			this->m_points[i].setY(this->m_points[i - 1].getY() + 1);
		}
		this->m_points[3].setX(5);
		this->m_points[3].setY(2);
		this->colorAnsciCode = "\033[37m";
		break;
	}
		
	case 6: { // S
		this->m_points[0].setX(4);
		this->m_points[0].setY(1);
		this->m_points[1].setX(5);
		this->m_points[1].setY(1);
		this->m_points[2].setX(5);
		this->m_points[2].setY(0);
		this->m_points[3].setX(6);
		this->m_points[3].setY(0);
		this->colorAnsciCode = "\033[32m";
		break;
	}
	case 7: { // Z
		this->m_points[1].setX(5);
		this->m_points[1].setY(0);
		this->m_points[2].setX(5);
		this->m_points[2].setY(1);
		this->m_points[3].setX(6);
		this->m_points[3].setY(1);
		this->colorAnsciCode = "\033[31m";
		break;
	}
	}	
}

bool Tetrimino::moveDown(char* down) {
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

void Tetrimino::draw(int gap) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		gotoxy(this->m_points[i].getX() + gap + 1, this->m_points[i].getY());
		cout << this->colorAnsciCode << this->m_char << this->RESETCOLOR;
	}
}

void Tetrimino::erase(int gap) {
	for (int i = 0; i < NUM_OF_POINTS && !newBorn; i++) {
		gotoxy(this->m_points[i].getX() + gap + 1, this->m_points[i].getY());
		cout << ' ';
	}
}

void Tetrimino::move(int gap) 
{
	this->draw(gap);
}



bool Tetrimino::moveRight(char* right) {
	
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


bool Tetrimino::moveLeft(char* left)
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

	int averageX = round(static_cast<double>(sumX) / NUM_OF_POINTS); // TODO - Change 4 to constant
	int averageY = round(static_cast<double>(sumY) / NUM_OF_POINTS);

	return Point(averageX, averageY);
}

Point* Tetrimino::rotateClockwise()
{
	Point pivot = calculatePivot();
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		pivot.setX(pivot.getX() + m_points[i].getX());
		pivot.setY(pivot.getY() + m_points[i].getY());
	}
	pivot.setX(pivot.getX() / NUM_OF_POINTS);
	pivot.setY(pivot.getY() / NUM_OF_POINTS);

	Point points_to_rotate[NUM_OF_POINTS];
	
	// Rotate clockwise around the pivot
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		points_to_rotate[i].setX(m_points[i].rotateClockwise(pivot).getX());
		points_to_rotate[i].setY(m_points[i].rotateClockwise(pivot).getY());
		
	}
	return points_to_rotate;
}

bool Tetrimino::isRotateLegal(Point* pointsArr,char* rotated)
{
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		if (pointsArr[i].getX() <= 0 || pointsArr[i].getX() >= GAME_WIDTH)
			return false;
		if (pointsArr[i].getY() <= 0 || pointsArr[i].getY() >= GAME_HEIGHT)
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

Point* Tetrimino::rotateCounterClockwise()
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
	Point points_to_rotate[NUM_OF_POINTS];

	// Rotate clockwise around the pivot
	for (int i = 0; i < NUM_OF_POINTS; i++)
	{
		points_to_rotate[i].setX(m_points[i].rotateCounterClockwise(pivot).getX());
		points_to_rotate[i].setY(m_points[i].rotateCounterClockwise(pivot).getY());
	}
	return points_to_rotate;
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




