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
	return this->gameBoard.getChar(col,row);
}

void Player::addToBoard(Tetrimino* t) {
	this->gameBoard.addToBoard(t);
}

void Player::initBoard() {
	this->gameBoard.init();
}

void Player::drawBoardInGame(int boardsGap) {
	this->gameBoard.drawBoardInGame(boardsGap);
}

int Player::whichRowFull() {
	return this->gameBoard.whichRowFull();
}

void Player::removeFullLine(int lineNum) {
	if(lineNum!=-1)
		this->gameBoard.removeFullLine(lineNum);
}
