#pragma once

#include <iostream>

#include "Tetrimino.h"

class Board 
{
	
public:
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int GAME_WIDTH = 12;
	static constexpr int FIRST_BOARD_START = 0;
	static constexpr int SECOND_BOARD_START = 20;
	static const int NUM_OF_POINTS = 4;

private:
	char gameBoard[GAME_HEIGHT][GAME_WIDTH];
	
public:
	/*
	Board() // Constructor to initialize the array
	{
		for (int i = 0; i < GAME_HEIGHT; i++)
		{
			for (int j = 0; j < GAME_WIDTH; j++)
			{
				gameBoard1[j][i] = ' '; // Initialize with some default value
			}
		}
	}*/

	void init();

	void addToBoard(Tetrimino* shape);

	char getChar(int row,int col);


	void drawBoard(int boardsGap = 0);

	void drawBoardInGame(int boardsGap = 0);

	int whichRowFull();

	void removeFullLine(int lineNum);

	
};