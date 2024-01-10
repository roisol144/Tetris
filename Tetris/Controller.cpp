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
	this->player1.initBoard();
	this->player1.drawBoard(0);
	char keyPressed;
	Tetrimino *tetro1 = nullptr, *tetro2 = nullptr;
	while (true)
	{
		if (tetro1 == nullptr || tetro1->getIsMoving() == false) {
			tetro1 = this->player1.createNextTetrimino();
		}

		char downArr[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX(),tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX(),tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX(),tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX(),tetro1->getTetromino()[3].getY()) };

		char rightArr[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX() + 1,tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX() + 1,tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX() + 1,tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX() + 1,tetro1->getTetromino()[3].getY()) };

		char leftArr[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX() - 1,tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX() - 1,tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX() - 1,tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX() - 1,tetro1->getTetromino()[3].getY()) };


		if (_kbhit())
		{
			keyPressed = _getch();
			switch (keyPressed)
			{
			case 'a':
				tetro1->moveLeft(leftArr);
				break;
			case 'A':
				tetro1->moveLeft(leftArr);
				break;
			case 'd':
				tetro1->moveRight(rightArr);
				break;
			case 'D':
				tetro1->moveRight(rightArr);
				break;
			case 's':
				tetro1->rotateClockwise();
				break;
			case 'S':
				tetro1->rotateClockwise();
				break;
			case 'w':
				tetro1->rotateCounterClockwise();
				break;
			case 'W':
				tetro1->rotateCounterClockwise();
				break;
			default:
				break;
			}
		}
		else
		{
			if (tetro1->moveDown(downArr))
				tetro1->move();
			else {
				tetro1->draw();
				tetro1->finishMoving();
				this->player1.addToBoard(tetro1);
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