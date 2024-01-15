#include "Controller.h"
#include "Board.h"
#include <windows.h>
using namespace std;

void Controller::playGame()
{
	this->gameStatus = true;
	this->player1.initBoard();
	this->player2.initBoard();
	this->player1.drawBoard();
	this->player2.drawBoard(22);
	char keyPressed;
	Tetrimino *tetro1 = nullptr, *tetro2 = nullptr;
	while (this->gameStatus)
	{
		if (tetro1 == nullptr || tetro1->getIsMoving() == false) {
			tetro1 = this->player1.createNextTetrimino();
		}
		if (tetro2 == nullptr || tetro2->getIsMoving() == false) {
			tetro2 = this->player2.createNextTetrimino();
		}

		char downArr1[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX(),tetro1->getTetromino()[0].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX(),tetro1->getTetromino()[1].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX(),tetro1->getTetromino()[2].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX(),tetro1->getTetromino()[3].getY() + 1) };

		char downArr2[4] = { this->player2.getCharFromBoard(tetro2->getTetromino()[0].getX(),tetro2->getTetromino()[0].getY() + 1),
							this->player2.getCharFromBoard(tetro2->getTetromino()[1].getX(),tetro2->getTetromino()[1].getY() + 1),
							this->player2.getCharFromBoard(tetro2->getTetromino()[2].getX(),tetro2->getTetromino()[2].getY() + 1),
							this->player2.getCharFromBoard(tetro2->getTetromino()[3].getX(),tetro2->getTetromino()[3].getY() + 1) };

		char rightArr1[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX() + 1,tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX() + 1,tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX() + 1,tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX() + 1,tetro1->getTetromino()[3].getY()) };

		char rightArr2[4] = { this->player2.getCharFromBoard(tetro2->getTetromino()[0].getX() + 1,tetro2->getTetromino()[0].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[1].getX() + 1,tetro2->getTetromino()[1].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[2].getX() + 1,tetro2->getTetromino()[2].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[3].getX() + 1,tetro2->getTetromino()[3].getY()) };

		char leftArr1[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX() - 1,tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX() - 1,tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX() - 1,tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX() - 1,tetro1->getTetromino()[3].getY()) };

		char leftArr2[4] = { this->player2.getCharFromBoard(tetro2->getTetromino()[0].getX() - 1,tetro2->getTetromino()[0].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[1].getX() - 1,tetro2->getTetromino()[1].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[2].getX() - 1,tetro2->getTetromino()[2].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[3].getX() - 1,tetro2->getTetromino()[3].getY()) };

		Point pointsToRotate[4];
		Point* pointsArrTemp;
		//char rotateArr[4];
		//char rotateCounterArr[4];

		if (_kbhit())
		{
			keyPressed = _getch();
			switch (keyPressed)
			{
			case 'a':
			case 'A':
			{
				tetro1->moveLeft(leftArr1);
				break;
			}
			case 'j':
			case 'J':
			{
				tetro2->moveLeft(leftArr2);
				break;
			}
			case 'd':
			case 'D':
			{
				tetro1->moveRight(rightArr1);
				break;
			}
			case 'l':
			case 'L':
			{
				tetro2->moveRight(rightArr2);
				break;
			}
			case 's':
			case 'S':
			{
				pointsArrTemp = tetro1->rotateClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				
				char rotateArr[4] = { this->player1.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
									 this->player1.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
									 this->player1.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
									 this->player1.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro1->isRotateLegal(pointsToRotate, rotateArr);
				break;
			}
			case 'k':
			case 'K':
			{
				pointsArrTemp = tetro2->rotateClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}

				char rotateArr[4] = { this->player2.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
									 this->player2.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
									 this->player2.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
									 this->player2.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro2->isRotateLegal(pointsToRotate, rotateArr);
				break;
			}
			case 'w':
			case 'W':
			{
				pointsArrTemp = tetro1->rotateCounterClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				char rotateCounterArr[4] = { this->player1.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
											this->player1.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
											this->player1.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
											this->player1.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro1->isRotateLegal(pointsToRotate, rotateCounterArr);
				break;
			}
			case 'i':
			case 'I':
			{
				pointsArrTemp = tetro2->rotateCounterClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				char rotateCounterArr[4] = { this->player2.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
											this->player2.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
											this->player2.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
											this->player2.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro2->isRotateLegal(pointsToRotate, rotateCounterArr);
				break;
			}
			case 'x':
			case 'X':
			{
				while (tetro1->moveDown(downArr1)) {
					tetro1->draw();
					Sleep(20);
					tetro1->erase();
					for (int i = 0; i < 4; i++) {
						downArr1[i] = this->player1.getCharFromBoard(tetro1->getTetromino()[i].getX(), tetro1->getTetromino()[i].getY() + 1);
					}
				}
				break;
			}
			case 'm':
			case 'M':
			{
				while (tetro2->moveDown(downArr2)) {
					tetro2->draw(22);
					Sleep(20);
					tetro2->erase(22);
					for (int i = 0; i < 4; i++) {
						downArr2[i] = this->player2.getCharFromBoard(tetro2->getTetromino()[i].getX(), tetro2->getTetromino()[i].getY() + 1);
					}
				}
				break;
			}
			case 27:
				entryScreen();
				break;
			default:
				break;
			}
		}
		
		
		if (tetro1->moveDown(downArr1))
			tetro1->move();
		else 
		{
			tetro1->draw();
			tetro1->finishMoving();
			this->player1.addToBoard(tetro1);
		}
		
		
		
		if (tetro2->moveDown(downArr2))
			tetro2->move(22);
		else
		{
			tetro2->draw(22);
			tetro2->finishMoving();
			this->player2.addToBoard(tetro2);
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
		case '2':
			system("cls");
			this->player1.drawBoardInGame();
			this->player2.drawBoardInGame(20);
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