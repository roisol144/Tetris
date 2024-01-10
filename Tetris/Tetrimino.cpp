#include "Tetrimino.h"

void Tetrimino::createTetromino(char ch) {
	//reset the first point 
	this->m_char = ch;
	this->m_points[0].setX(4);
	this->m_points[0].setY(0);
	std::srand(std::time(nullptr));
	int randNum = 1 + std::rand() % 7;

	switch (randNum) {
	case 1: { // STRAIGHT
		for (int i = 1; i < 4; i++) {
			this->m_points[i].setX(this->m_points[i-1].getX() + 1);
			this->m_points[i].setY(0);
		}
		break;
	}
	case 2: { // SQUARE
		for (int i = 1; i < 2; i++) {
			this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
			this->m_points[i].setY(0);
		}
		for (int i = 2; i < 4; i++) {
			this->m_points[i].setX(this->m_points[i - 2].getX());
			this->m_points[i].setY(1);
		}
		break;
	}
	case 3: { // T
		for (int i = 1; i < 3; i++) {
			this->m_points[i].setX(this->m_points[i - 1].getX() + 1);
			this->m_points[i].setY(0);
		}
		this->m_points[3].setX(5);
		this->m_points[3].setY(1);
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
		break;
	}
	case 7: { // Z
		this->m_points[1].setX(5);
		this->m_points[1].setY(0);
		this->m_points[2].setX(5);
		this->m_points[2].setY(1);
		this->m_points[3].setX(6);
		this->m_points[3].setY(1);
		break;
	}
	}	
}

bool Tetrimino::moveDown(char* down) {
	for (int i = 0; i < 4; i++) {
		if (this->m_points[i].getY() + 1 == 18)
			return false;
	}

	for (int i = 0; i < 4; i++) {
		if (down[i] != ' ')
			return false;
	}

	for (int i = 0; i < 4; i++) {
		this->m_points[i].setY(this->m_points[i].getY() + 1);	
	}

	return true;

}

void Tetrimino::draw() {
	for (int i = 0; i < 4; i++) {
		gotoxy(this->m_points[i].getX(), this->m_points[i].getY());
		cout << this->m_char;
	}
}

void Tetrimino::erase() {
	for (int i = 0; i < 4; i++) {
		gotoxy(this->m_points[i].getX(), this->m_points[i].getY());
		cout << ' ';
	}
}

void Tetrimino::move() {
	this->draw();
	Sleep(600);
	this->erase();
	//this->moveDown();
}



void Tetrimino::moveRight()
{
	for (int i = 0; i < 4; i++)
	{
		this->m_points[i].setX(this->m_points[i].getX() + 1);
	}
}


void Tetrimino::moveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		this->m_points[i].setX(this->m_points[i].getX() - 1);
	}
}
 


// C

Point Tetrimino::calculatePivot() 
{
	int sumX = 0;
	int sumY = 0;

	for (Point& point : m_points)
	{
		sumX += point.getX();
		sumY += point.getY();
	}

	int averageX = std::round(static_cast<double>(sumX) / 4); // TODO - Change 4 to constant
	int averageY = std::round(static_cast<double>(sumY) / 4);

	return Point(averageX, averageY);
}

void Tetrimino::rotateClockwise()
{
	Point pivot = calculatePivot();
	for (int i = 0; i < 4; i++)
	{
		pivot.setX(pivot.getX() + m_points[i].getX());
		pivot.setY(pivot.getY() + m_points[i].getY());
	}
	pivot.setX(pivot.getX() / 4);
	pivot.setY(pivot.getY() / 4);

	// Rotate clockwise around the pivot
	for (int i = 0; i < 4; i++)
	{
		m_points[i].rotateClockwise(pivot);
	}
}

void Tetrimino::rotateCounterClockwise()
{
	// Choose a pivot point (e.g., the center of the Tetrimino)
	Point pivot = calculatePivot();
	for (int i = 0; i < 4; ++i)
	{
		pivot.setX(pivot.getX() + m_points[i].getX());
		pivot.setY(pivot.getY() + m_points[i].getY());
	}
	pivot.setX(pivot.getX() / 4);
	pivot.setY(pivot.getY() / 4);

	// Rotate counterclockwise around the pivot
	for (int i = 0; i < 4; i++)
	{
		m_points[i].rotateCounterClockwise(pivot);
	}
}




