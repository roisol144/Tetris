#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H
#include <iostream>
using namespace std;
#include "Board.h"
#include "general.h"

/*
int GameBoard::getGameHeight() 
{
	return this->GAME_HEIGHT;
}

int GameBoard::getGameWidth() 
{
	return this->GAME_WIDTH;
}
*/


void Board::init() {
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			gameBoard[i][j] = ' '; // Initialize with some default value
		}
	}
}

void Board::drawBoard(int boardsGap)
{
	
	for (int col = 0 + boardsGap; col <= this->GAME_WIDTH + 1 + boardsGap; col++)
	{
		
		gotoxy(col, 0);
		cout << "# ";

		gotoxy(col, this->GAME_HEIGHT);
		cout << "# ";
	}
	

	for (int row = 1; row <= this->GAME_HEIGHT; row++)
	{
		gotoxy(0 + boardsGap, row);
		cout << "# ";

		gotoxy(this->GAME_WIDTH + boardsGap,row);
		cout << " #";
	}
	cout << endl;

}

void Board::drawBoardInGame(int boardsGap) {
	this->drawBoard(boardsGap);
	for (int row = 0; row < this->GAME_HEIGHT; row++) {
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (this->gameBoard[row][col] != ' ') {
				gotoxy(boardsGap + col + 1, row);
				cout << this->gameBoard[row][col];
			}
			else {
				if (row == 0)
					continue;
				gotoxy(boardsGap + col + 1, row);
				cout << ' ';
			}
		}
	}
}

/*
char** Board::getBoard()
{
	return gameBoard1;
}
*/

void Board::addToBoard(Tetrimino* shape) {
	Point* arr = shape->getTetroPoints();
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->gameBoard[arr[i].getY()][arr[i].getX()] = shape->getChar();
	}

}


char Board::getChar(int row, int col) {
	return this->gameBoard[row][col];
}

/*
bool Board::isRowFull(char* row) {
	for (int col = 0; col < this->GAME_WIDTH; col++) {
		if (row[col] == ' ')
			return false;
	}
	return true;
}
*/

int Board::whichRowFull() {
	int counter;
	for (int row = 17; row >= 0; row--) {
		counter = 0;
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (this->getChar(row,col) == ' ') {
				break;
			}
			counter++;
		}
		if (counter == 12)
			return row;
	}
	return -1;
	
}

void Board::removeFullLine(int lineNum, int gap) {
	for (int row = lineNum; row > 0; row--) {
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (row == 1)
				this->gameBoard[row][col] = ' ';
			else
				this->gameBoard[row][col] = this->gameBoard[row - 1][col];
		}
	}
	this->drawBoardInGame(gap); //TODO add gap
	
}


#endif // !__GAMEBOARD_H

