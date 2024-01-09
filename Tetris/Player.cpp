#include "Player.h"



Tetrimino* Player::createNextTetrimino()
{
	Tetrimino* t = new Tetrimino;
	t->createTetromino(this->letters[this->currLettersIdx++]);
	return t;
}

void Player::drawBoard(int boardGap) {
	this->gameBoard.drawBoard(boardGap);
}

char Player::getCharFromBoard(int row, int col) {
	return this->gameBoard.getChar(row, col);
}