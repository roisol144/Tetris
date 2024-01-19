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
	

private:
	char gameBoard[GAME_HEIGHT][GAME_WIDTH];
	
public:
	void init();

	void addToBoard(Tetrimino* shape);

	char getChar(int row,int col);


	void drawBoard(int boardsGap = 0);

	void drawBoardInGame(int boardsGap = 0);

	int whichRowFull();

	void removeFullLine(int lineNum, int gap);

	
};