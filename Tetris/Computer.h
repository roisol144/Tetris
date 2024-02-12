#pragma once
#include "Point.h"
#include "Player.h"
class Computer: public Player
{
	Point dests[12][4];
	int logSize = 0;

};

