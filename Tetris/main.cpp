#include <iostream>
#include "Board.h"
using namespace std;
#include "general.h"
#include <cstdlib> // for std::rand and std::srand
#include <ctime> 
#include "Tetrimino.h"


void main() 
{
	//Board board1, board2;
	//board1.drawBoard(Board::FIRST_BOARD_START);
	//board2.drawBoard(Board::SECOND_BOARD_START);
	//gotoxy(10, 15);
	//cout << "x";
	Tetromino t;
	t.createTetromino();
	Point* p = t.getTetromino();

	for (int i = 0; i < 4; i++)
	{
		gotoxy(p[i].getX(), p[i].getY());
		cout << 'Q';
	}
	

	cout << endl;

}

