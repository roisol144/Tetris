#include "Tetrimino.h"

void Tetromino::createTetromino() {
	//reset the first point 
	this->tetromino[0].setX(4);
	this->tetromino[0].setY(0);
	std::srand(std::time(nullptr));
	int randNum = 1 + std::rand() % 7;

	switch (randNum) {
	case 1: { // STRAIGHT
		for (int i = 1; i < 4; i++) {
			this->tetromino[i].setX(this->tetromino[i-1].getX() + 1);
			this->tetromino[i].setY(0);
		}
		break;
	}
	case 2: { // SQUARE
		for (int i = 1; i < 2; i++) {
			this->tetromino[i].setX(this->tetromino[i - 1].getX() + 1);
			this->tetromino[i].setY(0);
		}
		for (int i = 2; i < 4; i++) {
			this->tetromino[i].setX(this->tetromino[i - 2].getX());
			this->tetromino[i].setY(1);
		}
		break;
	}
	case 3: { // T
		for (int i = 1; i < 3; i++) {
			this->tetromino[i].setX(this->tetromino[i - 1].getX() + 1);
			this->tetromino[i].setY(0);
		}
		this->tetromino[3].setX(5);
		this->tetromino[3].setY(1);
		break;
	}
	case 4: { // J
		this->tetromino[0].setX(5);
		for (int i = 1; i < 3; i++) {
			this->tetromino[i].setX(5);
			this->tetromino[i].setY(this->tetromino[i-1].getY() + 1);
		}
		this->tetromino[3].setX(4);
		this->tetromino[3].setY(2);
		break;
	}
	case 5: { // L
		for (int i = 1; i < 3; i++)
		{
			this->tetromino[i].setX(4);
			this->tetromino[i].setY(this->tetromino[i - 1].getY() + 1);
		}
		this->tetromino[3].setX(5);
		this->tetromino[3].setY(2);
		break;
	}
	case 6: { // S
		this->tetromino[0].setY(1);
		this->tetromino[1].setX(5);
		this->tetromino[1].setY(1);
		this->tetromino[2].setX(5);
		this->tetromino[2].setY(0);
		this->tetromino[3].setY(0);
		this->tetromino[3].setY(6);
		break;
	}
	case 7: { // Z
		this->tetromino[1].setX(5);
		this->tetromino[1].setY(0);
		this->tetromino[2].setX(5);
		this->tetromino[2].setY(1);
		this->tetromino[3].setX(6);
		this->tetromino[3].setY(1);
		break;
	}
	}	
}

void Tetromino::moveRight()
{
	for (int i = 0; i < 4; i++)
	{
		this->tetromino[i].setX(this->tetromino[i].getX() + 1);
	}
}


void Tetromino::moveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		this->tetromino[i].setX(this->tetromino[i].getX() - 1);
	}
}


