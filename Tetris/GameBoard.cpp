#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H
#include <iostream>
using namespace std;
#include "GameBoard.h"
#include "general.h"

int GameBoard::getGameHeight() 
{
	return this->GAME_HEIGHT;
}

int GameBoard::getGameWidth() 
{
	return this->GAME_WIDTH;
}


void GameBoard::drawBoard()
{
	for (int col = 0; col <= this->GAME_WIDTH + 1; col++)
	{
		
		gotoxy(col, 0);
		cout << "- ";

		gotoxy(col, this->GAME_HEIGHT + 1);
		cout << "- ";
	}

	for (int row = 0; row <= this->GAME_HEIGHT + 1; row++)
	{

		gotoxy(0, row);
		cout << "| ";

		gotoxy(this->GAME_WIDTH + 1,row);
		cout << " |";
	}

}


#endif // !__GAMEBOARD_H

