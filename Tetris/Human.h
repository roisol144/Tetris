#pragma once
#include "Player.h"
class Human: public Player
{
private:

public:
	virtual void handleUserInput(char keyPressed) override;
	virtual void createNextTetrimino(const bool isColor) override;
};

