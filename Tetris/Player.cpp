#include "Player.h"



Tetrimino* Player::createNextTetrimino(const bool isColor)
{
	Tetrimino* t = new Tetrimino;
	t->createTetromino(isColor);
	this->currTetro = t;
	return t;
}
/*
void Player::drawBoard(int boardGap) {
	this->gameBoard.drawBoard(boardGap);
}

char Player::getCharFromBoard(int row, int col) {
	return this->gameBoard.getChar(col,row);
}

void Player::addToBoard(Tetrimino* t) {
	this->gameBoard.addToBoard(t);
}
/*
void Player::initBoard() {
	this->gameBoard.init();
}

void Player::drawBoardInGame(int boardsGap) {
	this->gameBoard.drawBoardInGame(boardsGap);
}

int Player::whichRowFull() {
	return this->gameBoard.whichRowFull();
}

void Player::removeFullLine(int lineNum, int gap) {
	if(lineNum != this->FULLROW_NOTFOUND)
		this->gameBoard.removeFullLine(lineNum,gap);
}
*/
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



