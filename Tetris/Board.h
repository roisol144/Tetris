#pragma once
#include <iostream>
#include "Tetrimino.h"

class Board 
{
public:
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int GAME_WIDTH = 12;
	static constexpr int FIRST_BOARD_START = 0;
	static constexpr int SECOND_BOARD_START = 22;
	static const int NUM_OF_POINTS = 4;

	Board()
	{
		for (int i = 0; i < GAME_HEIGHT; i++)
		{
			for (int j = 0; j < GAME_WIDTH; j++)
			{
				gameBoard[i][j] = ' '; // Initialize with some default value
			}
		}
	}

	//void init();
	void addToBoard(const Tetrimino* shape);
	char getChar(int row, int col) const;
	void drawBoard(const int boardsGap = 0) const;
	void drawBoardInGame(const int boardsGap = 0) const;
	int whichRowFull() const;
	void removeFullLine(const int lineNum,const int gap);


private:
	int gameBoard[GAME_HEIGHT][GAME_WIDTH];
	
	
};