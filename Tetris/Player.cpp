#include "Player.h"



Tetrimino* Player::createNextTetrimino()
{
	Tetrimino* t = new Tetrimino;
	t->createTetromino(letters[currIdx++]);

}