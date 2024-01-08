#pragma once

#include <iostream>
#include <vector>

class Board 
{
private:
	char gameBoard1[18][12];
	
public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int FIRST_BOARD_START = 0;
	static constexpr int SECOND_BOARD_START = 20;
	

	Board() // Constructor to initialize the array
	{
		for (int i = 0; i < GAME_HEIGHT; ++i)
		{
			for (int j = 0; j < GAME_WIDTH; ++j)
			{
				gameBoard1[i][j] = ' '; // Initialize with some default value
			}
		}
	}

	/*
	int getGameWidth();
	int getGameHeight();
	*/

	char** getBoard();


	void drawBoard(int boardsGap);
	void initBoard();

};