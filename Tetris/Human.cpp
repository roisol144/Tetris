#include "Human.h"
void Human::createNextTetrimino(const bool isColor)
{
	Tetrimino t;
	t.createTetromino(isColor);
	for (int i = 0; i < 4; i++) {
		t.setYcoordsByIndex(t.getTetroPoints()[i].getY() - 1, i);
	}
	this->currTetro = t;
	
}
void Human::handleUserInput(char keyPressed) {
	
		// Arrays and variables for handling rotation
		Point pointsToRotate[4];
		Point pointsArrTemp[4];
		

		

	// Process user input while keys are pressed
	this->currTetro.erase(this->getGap());
		// Switch statement to handle different key inputs for Player 2
		switch (keyPressed)
		{
		case 'l':
		case 'L':
		{// Move Player 2's tetromino to the right

			// Update the next move based on the character on the board to the right

			this->setNextMove(1, 0);
			// Move the tetromino to the right
				
			this->currTetro.moveRight(this->currTetro.getNextMove());
			break;
		}
		case 'k':
		case 'K':
		{
			// Rotate Player 2's tetromino clockwise
			// Get the rotated points and check if the rotation is legal
			this->currTetro.rotateClockwise(pointsArrTemp);
			for (int i = 0; i < 4; i++) {
				pointsToRotate[i].setX(pointsArrTemp[i].getX());
				pointsToRotate[i].setY(pointsArrTemp[i].getY());
			}
			// Copy rotated points to a temporary array
			for (int i = 0; i < 4; i++)
			{
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(pointsToRotate[i].getX(),
					pointsToRotate[i].getY()), i);
			}
			// Update the next move based on the character on the board after rotation
			this->currTetro.isRotateLegal(pointsToRotate, this->currTetro.getNextMove());
			break;
		}
		case 'i':
		case 'I':
		{
			// Rotate Player 2's tetromino counter-clockwise
			// Get the rotated points and check if the rotation is legal
			this->currTetro.rotateCounterClockwise(pointsArrTemp);
			// Copy rotated points to a temporary array
			for (int i = 0; i < 4; i++) {
				pointsToRotate[i].setX(pointsArrTemp[i].getX());
				pointsToRotate[i].setY(pointsArrTemp[i].getY());
			}
			for (int i = 0; i < 4; i++)
			{
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(pointsToRotate[i].getX(),
					pointsToRotate[i].getY()), i);
			}
			
			// Update the next move based on the character on the board after rotation
			this->currTetro.isRotateLegal(pointsToRotate, this->currTetro.getNextMove());
			break;
		}
		case 'j':
		case 'J':
		{
			// Move Player 2's tetromino to the left
			// Update the next move based on the character on the board to the left		

			this->setNextMove(-1, 0);
			// Move the tetromino to the left
			this->currTetro.moveLeft(this->currTetro.getNextMove());
			break;
		}
		case 'm':
		case 'M':
		{
			// Move Player 2's tetromino down quickly (hard drop)
			// Update the next move based on the character below, move down until landing
			// Draw and erase the tetromino for each step to create the falling effect
			for (int i = 0; i < 4; i++) {
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(this->currTetro.getTetroPoints()[i].getX(),
					this->currTetro.getTetroPoints()[i].getY() + 1), i);
			}
			this->setNextMove(0, 1);
			this->currTetro.setNewBorn(false);
			while (this->currTetro.moveDown(this->currTetro.getNextMove())) {
				this->currTetro.draw(this->getGap());
				Sleep(20);
				this->currTetro.erase(this->getGap());
				this->setNextMove(0, 1);
			}
			break;
		}
		default:
			break;
		}

		// Switch statement for Player 1 Controls
		// Same logic and functions as player 2
		switch (keyPressed)
		{
		case 'a':
		case 'A':
		{
			for (int i = 0; i < 4; i++) {
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(this->currTetro.getTetroPoints()[i].getX() - 1,
					this->currTetro.getTetroPoints()[i].getY()), i);
			}

			this->currTetro.moveLeft(this->currTetro.getNextMove());
			break;
		}

		case 'd':
		case 'D':
		{
			for (int i = 0; i < 4; i++) {
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(this->currTetro.getTetroPoints()[i].getX() + 1,
					this->currTetro.getTetroPoints()[i].getY()), i);
			}

			this->currTetro.moveRight(this->currTetro.getNextMove());
			break;
		}
		case 's':
		case 'S':
		{
			this->currTetro.rotateClockwise(pointsArrTemp);
			for (int i = 0; i < 4; i++) {
				pointsToRotate[i].setX(pointsArrTemp[i].getX());
				pointsToRotate[i].setY(pointsArrTemp[i].getY());
			}

			for (int i = 0; i < 4; i++)
			{
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(pointsToRotate[i].getX(),
					pointsToRotate[i].getY()), i);
			}
			this->currTetro.isRotateLegal(pointsToRotate, this->currTetro.getNextMove());
			break;
		}
		case 'w':
		case 'W':
		{
			this->currTetro.rotateCounterClockwise(pointsArrTemp);
			for (int i = 0; i < 4; i++) {
				pointsToRotate[i].setX(pointsArrTemp[i].getX());
				pointsToRotate[i].setY(pointsArrTemp[i].getY());
			}

			for (int i = 0; i < 4; i++)
			{
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(pointsToRotate[i].getX(),
					pointsToRotate[i].getY()), i);
			}

			this->currTetro.isRotateLegal(pointsToRotate, this->currTetro.getNextMove());
			break;
		}
		case 'x':
		case 'X':
		{
			for (int i = 0; i < 4; i++) {
				this->currTetro.setNextMoveByIndex
				(this->gameBoard.getChar(this->currTetro.getTetroPoints()[i].getX(),
					this->currTetro.getTetroPoints()[i].getY() + 1), i);
			}

			while (this->currTetro.moveDown(this->currTetro.getNextMove())) {
				this->currTetro.setNewBorn(false);
				this->currTetro.draw(this->getGap());
				Sleep(20);
				this->currTetro.erase(this->getGap());
				for (int i = 0; i < 4; i++) {
					this->currTetro.setNextMoveByIndex
					(this->gameBoard.getChar(this->currTetro.getTetroPoints()[i].getX(),
						this->currTetro.getTetroPoints()[i].getY() + 1), i);
				}
			}
			break;
		}
		default:
			break;
		}
}