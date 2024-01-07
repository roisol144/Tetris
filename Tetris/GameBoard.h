#pragma once

class GameBoard 
{
public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;
	static constexpr int FIRST_BOARD_START = 0;
	static constexpr int SECOND_BOARD_START = 20;
	int getGameWidth();
	int getGameHeight();
	void drawBoard(int boardsGap);

};