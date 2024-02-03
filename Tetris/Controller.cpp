#include "Controller.h"
#include <windows.h>
#include <chrono>
#include <thread>
#pragma comment(lib, "winmm.lib")
using namespace std;


void Controller::playGame(const bool isColor)
{
	/* Define and reset new players */
	PlaySound(TEXT("mainMenu.wav"), NULL, SND_FILENAME | SND_ASYNC);
	this->player1.resetScore();
	this->player2.resetScore();
	this->player2.setGap(this->player2.PLAYER2_GAP); // Set gap for Player 2
	this->printScoreBoard(); // Display the initial scoreboard
	this->gameStatus = true; // Set game status to true to start the game
	//this->player1.initBoard(); // Initialize the game board for Player 1
	this->player1.gameBoard.init();
	//this->player2.initBoard(); // Initialize the game board for Player 2
	this->player2.gameBoard.init();
	//this->player1.drawBoard(); // Draw the initial game board for Player 1
	this->player1.gameBoard.drawBoard();
	//this->player2.drawBoard(this->player2.getGap()); // Draw the initial game board for Player 2 with gap
	this->player2.gameBoard.drawBoard(this->player2.gap);

	this->player1.setPlayerName("Player 1"); // Set the name for Player 1
	this->player2.setPlayerName("Player 2"); // Set the name for Player 2

	this->player1.createNextTetrimino(isColor); // Create the first tetromino for player 1
	this->player2.createNextTetrimino(isColor); // Create the first tetromino for player 2

	while (this->gameStatus)
	{
		/* Checking if tetromino is not moving (landed), then create a new tetromino */
		if (this->player1.currTetro->getIsMoving() == false)
		{
			delete (this->player1.currTetro); // Delete the previous tetromino for Player 1		
			this->player1.createNextTetrimino(isColor); // Create a new tetromino for Player 1			
		}

		if (this->player2.currTetro->getIsMoving() == false)
		{
			
			delete (this->player2.currTetro); // Delete the previous tetromino for Player 2
			this->player2.createNextTetrimino(isColor); // Create a new tetromino for Player 2		
		}


		Sleep(300); // Pause for a short duration (milliseconds) for game update
		this->handleUserInput(); // Handle user input during the game
		this->moveTetriminoDown(this->player1); // Move the tetromino of Player 1 down
		this->moveTetriminoDown(this->player2); // Move the tetromino of Player 2 down
	}
	// check if both players lost at the same time



	endGame(); // End the game when the game status is false
	delete (player1.currTetro); // Delete the final tetromino for Player 1
	delete (player2.currTetro); // Delete the final tetromino for Player 2
}



void Controller::moveTetriminoDown(Player& player)
{
	// Iterate through each point of the tetromino and set the next move based on the character below it
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		player.currTetro->setNextMoveByIndex(
			player.gameBoard.getChar(player.currTetro->getTetroPoints()[i].getX(),
				player.currTetro->getTetroPoints()[i].getY() + 1),i);
	}

	// Move the tetromino down and check if it can move further
	if (player.currTetro->moveDown(player.currTetro->getNextMove()))
	{
		// Move the tetromino based on the player's gap
		player.currTetro->move(player.gap);

		// If the tetromino is newly born, mark it as not new born after moving
		if (player.currTetro->isNewBorn())
			player.currTetro->setNewBorn(false);
	}
	else
	{
		// If the tetromino cannot move down anymore
		if (player.currTetro->isTopReached())
		{
			// Check who's the winner based on the gap
			player.gap == this->player2.gap ? this->winner = this->PLAYER1 : this->winner = this->PLAYER2;
			if (this->gameStatus == false)
			{
				this->winner = this->TIE;
			}
			else
			{
				this->gameStatus = false; // Set game status to false as the game is over
			}
			
		}

		int fullRowIndex;
		player.currTetro->setNewBorn(true); // Mark the tetromino as newly born
		player.currTetro->draw(player.gap); // Draw the tetromino on the board
		player.currTetro->finishMoving(); // Finish moving the tetromino
		if (player.currTetro->isBombSet()) {
			player.gameBoard.explosion(player.currTetro->getTetroPoints()[0],player.gap);
			PlaySound(TEXT("explosion.wav"), NULL, SND_FILENAME| SND_ASYNC);
		}
		else {
			// Add the tetromino to the player's board
			player.gameBoard.addToBoard(player.currTetro);
			PlaySound(TEXT("tetroFall.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		

		// Check for and remove full lines, increase score, and update the score display
		while ((fullRowIndex = player.gameBoard.whichRowFull()) != player.FULLROW_NOTFOUND) {
			player.gameBoard.removeFullLine(fullRowIndex, player.gap);
			PlaySound(TEXT("fullLine.wav"), NULL, SND_FILENAME | SND_ASYNC);
			player.increaseScore();
			this->updateScore(player, player.gap);
		}
	}
}


void Controller::handleUserInput()
{
	// Arrays and variables for handling rotation
	Point pointsToRotate[NUM_OF_POINTS];
	Point* pointsArrTemp;
	char keyPressed;

	// Erase the current tetrominos for both players before processing user input
	this->player1.currTetro->erase(player1.gap);
	this->player2.currTetro->erase(player2.gap);

	// Process user input while keys are pressed
	while(_kbhit())
	{
		keyPressed = _getch();
		// Switch statement to handle different key inputs for Player 2
			switch (keyPressed)
			{
			case 'l':
			case 'L':
			{// Move Player 2's tetromino to the right
				
				// Update the next move based on the character on the board to the right
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					this->player2.currTetro->setNextMoveByIndex
					(this->player2.gameBoard.getChar(this->player2.currTetro->getTetroPoints()[i].getX() + 1, 
													this->player2.currTetro->getTetroPoints()[i].getY()), i);
				}
				// Move the tetromino to the right
				this->player2.currTetro->moveRight(this->player2.currTetro->getNextMove());
				break;
			}
			case 'k':
			case 'K':
			{
				// Rotate Player 2's tetromino clockwise
				// Get the rotated points and check if the rotation is legal
				pointsArrTemp = this->player2.currTetro->rotateClockwise();	
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				// Copy rotated points to a temporary array
				for (int i = 0; i < NUM_OF_POINTS; i++)
				{
					this->player2.currTetro->setNextMoveByIndex
					(this->player2.gameBoard.getChar(this->player2.currTetro->getTetroPoints()[i].getX(),
													this->player2.currTetro->getTetroPoints()[i].getY()), i);
				}
				// Update the next move based on the character on the board after rotation
				this->player2.currTetro->isRotateLegal(pointsToRotate, this->player2.currTetro->getNextMove());
				break;
			}
			case 'i':
			case 'I':
			{
				// Rotate Player 2's tetromino counter-clockwise
				// Get the rotated points and check if the rotation is legal
				pointsArrTemp = this->player2.currTetro->rotateCounterClockwise();
				// Copy rotated points to a temporary array
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}
				for (int i = 0; i < NUM_OF_POINTS; i++)
				{
					this->player2.currTetro->setNextMoveByIndex
					(this->player2.gameBoard.getChar(this->player2.currTetro->getTetroPoints()[i].getX(),
													this->player2.currTetro->getTetroPoints()[i].getY()), i);
				}
				// Update the next move based on the character on the board after rotation
				this->player2.currTetro->isRotateLegal(pointsToRotate, this->player2.currTetro->getNextMove());
				break;
			}		
			case 'j':
			case 'J':
			{
				// Move Player 2's tetromino to the left
				// Update the next move based on the character on the board to the left		
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					this->player2.currTetro->setNextMoveByIndex
					(this->player2.gameBoard.getChar(this->player2.currTetro->getTetroPoints()[i].getX() - 1,
													this->player2.currTetro->getTetroPoints()[i].getY()), i);
				}
				// Move the tetromino to the left
				this->player2.currTetro->moveLeft(this->player2.currTetro->getNextMove());
				break;
			}
			case 'm':
			case 'M':
			{
				// Move Player 2's tetromino down quickly (hard drop)
				// Update the next move based on the character below, move down until landing
				// Draw and erase the tetromino for each step to create the falling effect
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					this->player2.currTetro->setNextMoveByIndex
					(this->player2.gameBoard.getChar(this->player2.currTetro->getTetroPoints()[i].getX(),
													this->player2.currTetro->getTetroPoints()[i].getY() + 1), i);
				}

				while (this->player2.currTetro->moveDown(this->player2.currTetro->getNextMove())) {
					this->player2.currTetro->setNewBorn(false);
					this->player2.currTetro->draw(this->player2.gap);
					Sleep(this->HARDDROP_SLEEPTIME);
					this->player2.currTetro->erase(this->player2.gap);
					for (int i = 0; i < NUM_OF_POINTS; i++) {
						this->player2.currTetro->setNextMoveByIndex(this->player2.gameBoard.getChar(this->player2.currTetro->getTetroPoints()[i].getX(), this->player2.currTetro->getTetroPoints()[i].getY() + 1), i);
					}
				}
				break;
			}
			case this->ESC_KEYCODE:
				// Escape key pressed, go back to the entry screen
				entryScreen();
				keyPressed = 0;
				break;
			default:
				break;
			}

			// Switch statement for Player 1 Controls
			// Same logic and functions as player 2
			switch (keyPressed)
			{
			case 'a':
			case 'A':
			{
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					this->player1.currTetro->setNextMoveByIndex
					(this->player1.gameBoard.getChar(this->player1.currTetro->getTetroPoints()[i].getX() - 1,
													this->player1.currTetro->getTetroPoints()[i].getY()), i);
				}

				this->player1.currTetro->moveLeft(this->player1.currTetro->getNextMove());
				break;
			}

			case 'd':
			case 'D':
			{
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					this->player1.currTetro->setNextMoveByIndex
					(this->player1.gameBoard.getChar(this->player1.currTetro->getTetroPoints()[i].getX() + 1,
													this->player1.currTetro->getTetroPoints()[i].getY()), i);
				}

				this->player1.currTetro->moveRight(this->player1.currTetro->getNextMove());
				break;
			}
			case 's':
			case 'S':
			{
				pointsArrTemp = this->player1.currTetro->rotateClockwise();
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}

				for (int i = 0; i < NUM_OF_POINTS; i++)
				{
					this->player1.currTetro->setNextMoveByIndex
					(this->player1.gameBoard.getChar(this->player1.currTetro->getTetroPoints()[i].getX(),
													this->player1.currTetro->getTetroPoints()[i].getY()), i);
				}
				this->player1.currTetro->isRotateLegal(pointsToRotate, this->player1.currTetro->getNextMove());
				break;
			}
			case 'w':
			case 'W':
			{
				pointsArrTemp = this->player1.currTetro->rotateCounterClockwise();
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					pointsToRotate[i].setX(pointsArrTemp[i].getX());
					pointsToRotate[i].setY(pointsArrTemp[i].getY());
				}

				for (int i = 0; i < NUM_OF_POINTS; i++)
				{
					this->player1.currTetro->setNextMoveByIndex
					(this->player1.gameBoard.getChar(this->player1.currTetro->getTetroPoints()[i].getX(),
													this->player1.currTetro->getTetroPoints()[i].getY()), i);
				}

				this->player1.currTetro->isRotateLegal(pointsToRotate, this->player1.currTetro->getNextMove());
				break;
			}
			case 'x':
			case 'X':
			{
				for (int i = 0; i < NUM_OF_POINTS; i++) {
					this->player1.currTetro->setNextMoveByIndex
					(this->player1.gameBoard.getChar(this->player1.currTetro->getTetroPoints()[i].getX(),
													this->player1.currTetro->getTetroPoints()[i].getY() + 1), i);
				}
				
				while (this->player1.currTetro->moveDown(this->player1.currTetro->getNextMove())) {
					this->player1.currTetro->setNewBorn(false);
					this->player1.currTetro->draw(this->player1.gap);
					Sleep(this->HARDDROP_SLEEPTIME);
					this->player1.currTetro->erase(this->player1.gap);
					for (int i = 0; i < NUM_OF_POINTS; i++) {
						this->player1.currTetro->setNextMoveByIndex
						(this->player1.gameBoard.getChar(this->player1.currTetro->getTetroPoints()[i].getX(),
														this->player1.currTetro->getTetroPoints()[i].getY() + 1), i);
					}			
				}
				break;
			}
			case this->ESC_KEYCODE:
				entryScreen();
				break;
			default:
				break;
			}		
	}

}



void Controller::entryScreen()
{
	resetColor();
	//PlaySound(TEXT("bestTetris.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//cout << "]";

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
		gotoxy(50, 13);
		PlaySound(TEXT("bestTetris.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << "Loading: [";

		for (int i = 0; i < 5; ++i) {
			cout << "=";
			(i == 4) ? (cout << "]") : cout;
			cout.flush();
			this_thread::sleep_for(chrono::seconds(20 / 20));
		}
		system("cls");
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
			system("cls");
			cout << "****************************" << endl;
			cout << "*   Choose Color Option    *" << endl;
			cout << "****************************" << endl;
			cout << "With Color: 1" << endl << "No Color: 0" << endl;	
			cout << "Your Choice: ";
			bool isColor;
			//cin >> isColor;
			isColor = _getch();
			system("cls");
			playGame(isColor);
			break;
		case '2':
			system("cls");
			this->player1.gameBoard.drawBoardInGame();
			this->player2.gameBoard.drawBoardInGame(22);
			this->printScoreBoard();
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
	resetColor();

	system("cls");  // Clear console screen
	cout << "*********************" << endl;
	cout << "*    Instructions   *" << endl;
	cout << "*********************" << endl << endl;
	cout << "Player 1 - Use 'A' to move the Tetromino left and 'D' for right." << endl;
	cout << "Player 1 - Use 'X' to drop the Tetromino." << endl;
	cout << "Player 1 - Use 'S' to rotate the Tetromino clockwise and 'W' for counter clockwise." << endl << endl;

	cout << "Player 2 - Use 'J' to move the Tetromino left and 'L' for right." << endl;
	cout << "Player 2 - Use 'M' to drop the Tetromino." << endl;
	cout << "Player 2 - Use 'K' to rotate the Tetromino clockwise and 'I' for counter clockwise." << endl << endl;
	cout << "Press 'Enter' key to go back to the menu...";
	cin.ignore();
	cin.ignore();
	if (_kbhit())
		entryScreen();
}

// Print the ScoreBoard
void Controller::printScoreBoard() {
	resetColor();

	for (int row = 20; row <= 23; row++) {
		gotoxy(0, row);
		cout << '*';
		gotoxy(13, row);
		cout << '*';
	}

	for (int col = 1; col <= 12; col++) {
		gotoxy(col, 20);
		cout << '*';
		gotoxy(col, 23);
		cout << '*';
	}
	gotoxy(3, 21);
	cout << "Player #1";
	gotoxy(3, 22);
	cout << "Score: " << this->player1.score;

	for (int row = 20; row <= 23; row++) {
		gotoxy(22, row);
		cout << '*';
		gotoxy(35, row);
		cout << '*';
	}

	for (int col = 23; col <= 35; col++) {
		gotoxy(col, 20);
		cout << '*';
		gotoxy(col, 23);
		cout << '*';
	}
	gotoxy(25, 21);
	cout << "Player #2";
	gotoxy(25, 22);
	cout << "Score: " << this->player2.score;
}

// Update the scoareBoard
void Controller::updateScore(Player& p,int gap) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
	gotoxy(3 + gap, 22);
	cout << "Score: " << p.score;
}

//Print endgame window
void Controller::endGame()
{
	int x;
	resetColor();
	system("cls");
	cout << "\033[1;32m********************************\033[0m" << endl;  // Bold green text
	if (this->winner == 0) {
		//its a tie
		if (this->player1.getScore() > this->player2.getScore()) {
			//player 1 win
			cout << "\033[1;32m*      The Winner is: " << this->PLAYER1 << "        *\033[0m" << endl;  // Bold green text
		}
		else if (this->player1.getScore() < this->player2.getScore()) {
			//player 2 win
			this->winner = this->PLAYER2;
			cout << "\033[1;32m*      The Winner is: " << this->PLAYER2 << "        *\033[0m" << endl;  // Bold green text
		}
		else
			cout << "\033[1;32m*          Its a Tie!          *\033[0m" << endl;  // Bold green text

	}
	else {
		cout << "\033[1;32m*      The Winner is: " << this->winner << "        *\033[0m" << endl;  // Bold green text

	}
	cout << "\033[1;32m********************************\033[0m" << endl << endl;  // Bold green text
	cout << "Player 1 Score: " << this->player1.getScore() << endl;
	cout << "Player 2 Score: " << this->player2.getScore() << endl;
	cout << "Press any key to return to main menu. "<< endl;

	//TODO ************** BUGGGGG ************ 
	cin.ignore();
	cin >> x;
	//while (!_kbhit()) {}
	_getch();
	this->entryScreen();

}

void Controller::resetColor() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
}