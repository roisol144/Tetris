#include "Player.h"



void Player::increaseScore() {
	this->score++;
}


void Player::resetScore() {
	this->score = 0;
}

void Player::setPlayerName(string name)
{
	this->name = name;
}


void Player::setNextMove(int x, int y) {
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->currTetro.setNextMoveByIndex
		(this->gameBoard.getChar(this->currTetro.getTetroPoints()[i].getX() + x,
			this->currTetro.getTetroPoints()[i].getY() + y), i);
	}
}





