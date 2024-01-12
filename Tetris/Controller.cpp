#include "Controller.h"
#include "Board.h"
#include <windows.h>
using namespace std;

void Controller::playGame()
{
	this->gameStatus = true;
	this->player1.initBoard();
	this->player1.drawBoard(0);
	char keyPressed;
	Tetrimino *tetro1 = nullptr, *tetro2 = nullptr;
	while (this->gameStatus)
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
				if (tetro1->moveLeft(leftArr))
					tetro1->move();
				break;
			case 'A':
				if (tetro1->moveLeft(leftArr))
					tetro1->move();
				break;
			case 'd':
				if (tetro1->moveRight(rightArr))
					tetro1->move();
				break;
			case 'D':
				if (tetro1->moveRight(rightArr))
					tetro1->move();				
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
			case 27:
				entryScreen();
				break;
			default:
				break;
			}
		}

		if (tetro1->moveDown(downArr))
			tetro1->move();
		else 
		{
			tetro1->draw();
			tetro1->finishMoving();
			this->player1.addToBoard(tetro1);
		}
	}
}



void Controller::entryScreen()
{
	// Clear the console screen
	system("cls");
	if (this->gameStatus)
	{
		// Display the Tetris headline
		cout << "*********************" << endl;
		cout << "*    Tetris C++    *" << endl;
		cout << "*********************" << endl << endl;

		// Display the menu options
		cout << "(1) Start a new game" << endl;
		cout << "(2) Continue a paused game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl << endl;

		//Message for the user to pick a choice
		cout << "Please enter your choice: ";
	}

	else 
	{
		// Display the Tetris headline
		cout << "*********************" << endl;
		cout << "*    Tetris C++    *" << endl;
		cout << "*********************" << endl << endl;

		// Display the menu options
		cout << "(1) Start a new game" << endl;
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl << endl;

		//Message for the user to pick a choice
		cout << "Please enter your choice: ";
	}


	char choice;
	cin >> choice;

	// Process user choice
	switch (choice) 
	{
		case '1':
			cout << "Starting a new game..." << endl;
			system("cls");
			playGame();
			break;

		case '8':
			showInstructions();
			break;

		case '9':
			// Exit the program
			this->gameStatus = false;
			cout << endl;
			cout << "Exiting the Tetris game. Goodbye!" << endl;
			break;

		default:
			// Invalid choice
			cout << "Invalid choice. Please try again." << endl;
			cin.ignore();
			cin.get();
			break;
	}
} 



void Controller::showInstructions()
{
	system("cls");  // Clear console screen
	cout << "*********************" << endl;
	cout << "*    Instructions   *" << endl;
	cout << "*********************" << endl << endl;
	cout << "Player 1 - Use 'A' to move the Tetromino left and 'D' for right." << endl;
	cout << "Player 1 - Use 'X' to drop the Tetromino" << endl;
	cout << "Player 1 - Use 'S' to rotate the Tetromino clockwise and 'W' for counter clockwise." << endl << endl;

	cout << "Player 2 - Use 'J' to move the Tetromino left and 'L' for right." << endl;
	cout << "Player 2 - Use 'M' to drop the Tetromino" << endl;
	cout << "Player 2 - Use 'K' to rotate the Tetromino clockwise and 'I' for counter clockwise." << endl << endl;
	cout << "Press 'ESC' to pause the game." << endl;
	cout << "Press 'Enter' key to go back to the menu...";
	cin.ignore();
	cin.ignore();
	if (_kbhit)
		entryScreen();
}