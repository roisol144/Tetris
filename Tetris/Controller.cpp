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
	//char keyPressed;
	Tetrimino* tetro1 = this->player1.createNextTetrimino();
	//Tetrimino* tetro2 = this->player2.createNextTetrimino();
	while (this->gameStatus)
	{
		/*
		if (tetro1 == nullptr || tetro1->getIsMoving() == false) {
			tetro1 = this->player1.createNextTetrimino();
		}
		if (tetro2 == nullptr || tetro2->getIsMoving() == false) {
			tetro2 = this->player2.createNextTetrimino();
		}
		*/
		//Point pointsToRotate[4];
		//Point* pointsArrTemp;
		//char rotateArr[4];
		//char rotateCounterArr[4];

		if (tetro1->getIsMoving() == false) {
			tetro1 = this->player1.createNextTetrimino();
		}
		//if (tetro2->getIsMoving() == false) {
		//	tetro2 = this->player2.createNextTetrimino();
		//}

		//----- PLAYER 1 -----

		char downArr1[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX(),tetro1->getTetromino()[0].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX(),tetro1->getTetromino()[1].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX(),tetro1->getTetromino()[2].getY() + 1),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX(),tetro1->getTetromino()[3].getY() + 1) };

		

		char rightArr1[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX() + 1,tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX() + 1,tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX() + 1,tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX() + 1,tetro1->getTetromino()[3].getY()) };

		

		char leftArr1[4] = { this->player1.getCharFromBoard(tetro1->getTetromino()[0].getX() - 1,tetro1->getTetromino()[0].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[1].getX() - 1,tetro1->getTetromino()[1].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[2].getX() - 1,tetro1->getTetromino()[2].getY()),
							this->player1.getCharFromBoard(tetro1->getTetromino()[3].getX() - 1,tetro1->getTetromino()[3].getY()) };

		
	
		handleUserInput(tetro1, player1, leftArr1, rightArr1, downArr1);
		
		moveTetriminoDown(tetro1,player1);

		//----- END PLAYER 1 -----

		//----- PLAYER 2 -----
		
		/*
		char downArr2[4] = { this->player2.getCharFromBoard(tetro2->getTetromino()[0].getX(),tetro2->getTetromino()[0].getY() + 1),
							this->player2.getCharFromBoard(tetro2->getTetromino()[1].getX(),tetro2->getTetromino()[1].getY() + 1),
							this->player2.getCharFromBoard(tetro2->getTetromino()[2].getX(),tetro2->getTetromino()[2].getY() + 1),
							this->player2.getCharFromBoard(tetro2->getTetromino()[3].getX(),tetro2->getTetromino()[3].getY() + 1) };

		char rightArr2[4] = { this->player2.getCharFromBoard(tetro2->getTetromino()[0].getX() + 1,tetro2->getTetromino()[0].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[1].getX() + 1,tetro2->getTetromino()[1].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[2].getX() + 1,tetro2->getTetromino()[2].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[3].getX() + 1,tetro2->getTetromino()[3].getY()) };

		char leftArr2[4] = { this->player2.getCharFromBoard(tetro2->getTetromino()[0].getX() - 1,tetro2->getTetromino()[0].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[1].getX() - 1,tetro2->getTetromino()[1].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[2].getX() - 1,tetro2->getTetromino()[2].getY()),
							this->player2.getCharFromBoard(tetro2->getTetromino()[3].getX() - 1,tetro2->getTetromino()[3].getY()) };

		handleUserInput(tetro2, player2, leftArr2, rightArr2, downArr2, 22);
		moveTetriminoDown(tetro2, player2, 22);
		*/
		

		// ----- END PLAYER 2 -----
	

	}




}

void Controller::moveTetriminoDown(Tetrimino* tetro, Player& player, int gap)
{
	char downArr[4] = {
	player.getCharFromBoard(tetro->getTetromino()[0].getX(), tetro->getTetromino()[0].getY() + 1),
	player.getCharFromBoard(tetro->getTetromino()[1].getX(), tetro->getTetromino()[1].getY() + 1),
	player.getCharFromBoard(tetro->getTetromino()[2].getX(), tetro->getTetromino()[2].getY() + 1),
	player.getCharFromBoard(tetro->getTetromino()[3].getX(), tetro->getTetromino()[3].getY() + 1)
	};

	if (tetro->moveDown(downArr))
	{
		tetro->move(gap);
	}
	else
	{
		int num;
		tetro->draw(gap);
		tetro->finishMoving();
		player.addToBoard(tetro);
		while((num=player.whichRowFull()) != -1)
			player.removeFullLine(num);
	}
}




void Controller::handleUserInput(Tetrimino* tetro, Player& player, char* leftArr, char* rightArr, char* downArr, int gap)
{
	Point pointsToRotate[4];
	Point* pointsArrTemp;
	char keyPressed;

	if (_kbhit())
	{
		keyPressed = _getch();
		if (gap == 22) // if it's the second player
		{
			switch (keyPressed)
			{
			case 'l':
			case 'L':
			{
				tetro->moveRight(rightArr);
				break;
			}
			case 'k':
			case 'K':
			{
				pointsArrTemp = tetro->rotateClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}

				char rotateArr[4] = { player.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
									 player.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
									 player.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
									 player.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro->isRotateLegal(pointsToRotate, rotateArr);
				break;
			}
			case 'i':
			case 'I':
			{
				pointsArrTemp = tetro->rotateCounterClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				char rotateCounterArr[4] = { player.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
											player.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
											player.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
											player.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro->isRotateLegal(pointsToRotate, rotateCounterArr);
				break;
			}		
			case 'j':
			case 'J':
			{
				tetro->moveLeft(leftArr);
				break;
			}
			case 'm':
			case 'M':
			{
				while (tetro->moveDown(downArr)) {
					tetro->draw(gap);
					Sleep(20);
					tetro->erase(gap);
					for (int i = 0; i < 4; i++) {
						downArr[i] = player.getCharFromBoard(tetro->getTetromino()[i].getX(), tetro->getTetromino()[i].getY() + 1);
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
		else // Player 1
		{
			switch (keyPressed)
			{
			case 'a':
			case 'A':
			{
				tetro->moveLeft(leftArr);
				break;
			}

			case 'd':
			case 'D':
			{
				tetro->moveRight(rightArr);
				break;
			}
			case 's':
			case 'S':
			{
				pointsArrTemp = tetro->rotateClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}

				char rotateArr[4] = { player.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
									 player.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
									 player.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
									 player.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro->isRotateLegal(pointsToRotate, rotateArr);
				break;
			}
			case 'w':
			case 'W':
			{
				pointsArrTemp = tetro->rotateCounterClockwise();
				for (int i = 0; i < 4; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				char rotateCounterArr[4] = { player.getCharFromBoard(pointsToRotate[0].getX(),pointsToRotate[0].getY()),
											player.getCharFromBoard(pointsToRotate[1].getX(),pointsToRotate[1].getY()),
											player.getCharFromBoard(pointsToRotate[2].getX(),pointsToRotate[2].getY()),
											player.getCharFromBoard(pointsToRotate[3].getX(),pointsToRotate[3].getY()) };
				tetro->isRotateLegal(pointsToRotate, rotateCounterArr);
				break;
			}
			case 'x':
			case 'X':
			{
				while (tetro->moveDown(downArr)) {
					tetro->draw();
					Sleep(20);
					tetro->erase();
					for (int i = 0; i < 4; i++) {
						downArr[i] = player.getCharFromBoard(tetro->getTetromino()[i].getX(), tetro->getTetromino()[i].getY() + 1);
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