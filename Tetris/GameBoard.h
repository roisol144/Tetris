#pragma once

class GameBoard 
{
public:
	static constexpr int GAME_WIDTH = 80;
	static constexpr int GAME_HEIGHT = 25;
	int getGameWidth();
	int getGameHeight();
	void drawBoard();

};