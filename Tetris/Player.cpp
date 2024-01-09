#include "Player.h"



Tetrimino* Player::createNextTetrimino()
{
	//TODO - remove (only debug).
	Tetrimino* t = new Tetrimino;
	int idx = this->currLettersIdx++;
	char letter = this->letters[idx];
	t->createTetromino(letter);

	//t->createTetromino(this->letters[this->currLettersIdx++]);
	return t;
}

void Player::drawBoard(int boardGap) {
	this->gameBoard.drawBoard(boardGap);
}

char Player::getCharFromBoard(int row, int col) {
	return this->gameBoard.getChar(row, col);
}

void Player::addToBoard(Tetrimino* t) {
	this->gameBoard.addToBoard(t);
}

void Player::initBoard() {
	this->gameBoard.init();
}