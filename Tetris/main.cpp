#include <iostream>
#include "GameBoard.h"
using namespace std;
#include "general.h"



void main() 
{
	GameBoard board1, board2;
	board1.drawBoard(GameBoard::FIRST_BOARD_START);
	board2.drawBoard(GameBoard::SECOND_BOARD_START);

}

