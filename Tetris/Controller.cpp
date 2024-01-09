#include "Controller.h"
#include "Board.h"
#include <windows.h>
using namespace std;


// LAROHAV PROGRAMMING. 
// TODO - Solve when shape can't move anymore. LAROHAV
//		TODO - check for border reached or shapes collision.
// TODO - implement move left (_kbhit).
// TODO - Working on player only. 
// TODO - all members must have m_ before them
// TODO - adding defines - constants.


void Controller::playGame()
{
	this->player1.drawBoard(0);
	char keyPressed;
	Tetrimino *tetro1 = nullptr, *tetro2 = nullptr;
	while (true)
	{
		if (tetro1 == nullptr || tetro1->getIsMoving() == false) {
			tetro1 = this->player1.createNextTetrimino();
		}

		char downArr[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX(),tetro1->getTetromino()[0].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX(),tetro1->getTetromino()[1].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX(),tetro1->getTetromino()[2].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX(),tetro1->getTetromino()[3].getY() + 1) };

		if(tetro1->moveDown(downArr))
			tetro1->move();

		if(_kbhit())
		{
			keyPressed = _getch();
			switch (keyPressed)
			{
			case 'a':
				tetro1->moveLeft();
				break;
			case 'd':
				tetro1->moveRight();
				break;
			default:
				break;
			}
		}

		/*
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == 27) // 27 is the ASCII value of ESC.
			{
				clrscr(); // Clearing the console.

				//Menu
				cout << "MENU\n";
				cout << "***************\n";
				cout << "(1) Start a new game\n";
				cout << "(2) Continue a paused game\n";
				cout << "(8) Present instructions and keys\n";
				cout << "(9) EXIT\n";
				cout << "Choose: ";
				cin >> keyPressed;
				
				//Insert switch or handler function.

			}
		}
		*/
	}
}