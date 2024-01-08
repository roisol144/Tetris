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


void Board::drawBoard(int boardsGap)
{
	
	for (int col = 1 + boardsGap; col <= this->GAME_WIDTH + 1 + boardsGap; col++)
	{
		
		gotoxy(col, 0);
		cout << "- ";

		gotoxy(col, this->GAME_HEIGHT + 2);
		cout << "- ";
	}
	

	for (int row = 1; row <= this->GAME_HEIGHT +1; row++)
	{

		gotoxy(0 + boardsGap, row);
		cout << "| ";

		gotoxy(this->GAME_WIDTH + 1 + boardsGap,row);
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


#endif // !__GAMEBOARD_H

