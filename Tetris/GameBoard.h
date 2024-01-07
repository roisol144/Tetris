#pragma once

class GameBoard 
{
public:
	static constexpr int GAME_WIDTH = 25;
	static constexpr int GAME_HEIGHT = 80;
	int getGameWidth();
	int getGameHeight();
	void drawBoard();

};