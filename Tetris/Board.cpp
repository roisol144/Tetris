#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H
#include <iostream>
using namespace std;
#include "Board.h"
#include "general.h"
/*
void Board::init() {
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			gameBoard[i][j] = ' '; // Initialize with some default value
		}
	}
}
*/

void Board::drawBoard(int boardsGap)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
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
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdOut, 15);
	this->drawBoard(boardsGap);
	for (int row = 0; row < this->GAME_HEIGHT; row++) {
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (this->gameBoard[row][col] != ' ') {
				gotoxy(boardsGap + col + 1, row);
				SetConsoleTextAttribute(hStdOut, this->gameBoard[row][col]);
				cout << (char)219;
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

void Board::addToBoard(Tetrimino* shape) {
	Point* arr = shape->getTetroPoints();
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->gameBoard[arr[i].getY()][arr[i].getX()] = shape->getColor();

	}

}

char Board::getChar(int row, int col) {
	return this->gameBoard[col][row];
}

int Board::whichRowFull() {
	int counter;
	for (int row = this->GAME_HEIGHT-1; row >= 0; row--) {
		counter = 0;
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (this->getChar(col,row) == ' ') {
				break;
			}
			counter++;
		}
		if (counter == this->GAME_WIDTH)
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
	this->drawBoardInGame(gap);
}


#endif // !__GAMEBOARD_H

