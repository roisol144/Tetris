#pragma once

#include <iostream>

#include "Tetrimino.h"

class Board 
{
	
public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int FIRST_BOARD_START = 0;
	static constexpr int SECOND_BOARD_START = 20;

private:
	char gameBoard1[GAME_WIDTH][GAME_HEIGHT];
	
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

	/*
	int getGameWidth();
	int getGameHeight();
	*/
	//TODO, maybe not needed
	//char** getBoard();

	void addToBoard(Tetrimino* shape);

	char getChar(int row,int col);


	void drawBoard(int boardsGap);
	//void initBoard();

};