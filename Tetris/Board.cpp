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
			gameBoard1[j][i] = ' '; // Initialize with some default value
		}
	}
}

void Board::drawBoard(int boardsGap)
{
	
	for (int col = 1 + boardsGap; col <= this->GAME_WIDTH + 1 + boardsGap; col++)
	{
		
		gotoxy(col, 0);
		cout << "- ";

		gotoxy(col, this->GAME_HEIGHT);
		cout << "- ";
	}
	

	for (int row = 1; row <= this->GAME_HEIGHT; row++)
	{

		gotoxy(0 + boardsGap, row);
		cout << "| ";

		gotoxy(this->GAME_WIDTH + boardsGap,row);
		cout << " |";
	}
	cout << endl;

}

/*
char** Board::getBoard()
{
	return gameBoard1;
}
*/

void Board::addToBoard(Tetrimino* shape) {
	Point* arr = shape->getTetromino();
	for (int i = 0; i < 4; i++) {
		this->gameBoard1[arr[i].getX()][arr[i].getY()] = shape->getChar();
	}

}

char Board::getChar(int row, int col) {
	return this->gameBoard1[row][col];
}


#endif // !__GAMEBOARD_H

