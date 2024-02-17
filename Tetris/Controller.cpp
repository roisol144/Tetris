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
	if (!this->gameStatus) {
		this->player1->resetScore();
		this->player2->resetScore();
		this->player2->setGap(this->player2->PLAYER2_GAP); // Set gap for Player 2
		this->printScoreBoard(); // Display the initial scoreboard
		this->gameStatus = true; // Set game status to true to start the game
		//this->player1->initBoard(); // Initialize the game board for Player 1
		this->player1->gameBoard.init();
		//this->player2->initBoard(); // Initialize the game board for Player 2
		this->player2->gameBoard.init();
		//this->player1->drawBoard(); // Draw the initial game board for Player 1
		this->player1->gameBoard.drawBoard();
		//this->player2->drawBoard(this->player2->getGap()); // Draw the initial game board for Player 2 with gap
		this->player2->gameBoard.drawBoard(this->player2->gap);

		this->player1->setPlayerName("Player 1"); // Set the name for Player 1
		this->player2->setPlayerName("Player 2"); // Set the name for Player 2

		this->player1->createNextTetrimino(isColor); // Create the first tetromino for player 1
		this->player2->createNextTetrimino(isColor); // Create the first tetromino for player 2
	
	}
	
	while (this->gameStatus)
	{
		/* Checking if tetromino is not moving (landed), then create a new tetromino */
		if (this->player1->currTetro.getIsMoving() == false)
		{
			this->player1->createNextTetrimino(isColor); // Create a new tetromino for Player 1			
		}

		if (this->player2->currTetro.getIsMoving() == false)
		{			
			this->player2->createNextTetrimino(isColor); // Create a new tetromino for Player 2		
		}
		/*this->player1->pickComputerMove();
		this->player2->pickComputerMove();*/
		
		Sleep(300); // Pause for a short duration (milliseconds) for game update
		if (scanKeys())// Handle user input during the game
			return;
		// Erase the current tetrominos for both players before processing user input
		this->player1->currTetro.erase(this->player1->getGap());
		this->player2->currTetro.erase(this->player2->getGap());
		
		this->moveTetriminoDown(*this->player1); // Move the tetromino of Player 1 down
		this->moveTetriminoDown(*this->player2); // Move the tetromino of Player 2 down
		
	}
	// check if both players lost at the same time

	endGame(); // End the game when the game status is false	
}

bool Controller::scanKeys() {
	char keyPressed;
	while (_kbhit()) {
		
		keyPressed = _getch();
		keyPressed = (char)tolower(keyPressed);
		if (keyPressed == 'x' || keyPressed == 'a' || keyPressed == 's' || keyPressed == 'd' || keyPressed == 'w') {
			player1->handleUserInput(keyPressed);
		}
		if (keyPressed == 'i' || keyPressed == 'j' || keyPressed == 'k' || keyPressed == 'l' || keyPressed == 'm') {
			player2->handleUserInput(keyPressed);
		}
		if (keyPressed == 27)
			return true;
	}
	return false;
}



void Controller::moveTetriminoDown(Player& player)
{
	// Iterate through each point of the tetromino and set the next move based on the character below it
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		player.currTetro.setNextMoveByIndex(
			player.gameBoard.getChar(player.currTetro.getTetroPoints()[i].getX(),
				player.currTetro.getTetroPoints()[i].getY() + 1),i);
	}

	// Move the tetromino down and check if it can move further
	if (player.currTetro.moveDown(player.currTetro.getNextMove()))
	{
		// Move the tetromino based on the player's gap
		
		player.currTetro.move(player.gap);

		// If the tetromino is newly born, mark it as not new born after moving
		if (player.currTetro.isNewBorn())
			player.currTetro.setNewBorn(false);
	}
	else
	{
		// If the tetromino cannot move down anymore
		if (player.currTetro.isTopReached())
		{
			// Check who's the winner based on the gap
			player.gap == this->player2->gap ? this->winner = this->PLAYER1 : this->winner = this->PLAYER2;
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
		player.currTetro.setNewBorn(true); // Mark the tetromino as newly born
		player.currTetro.draw(player.gap); // Draw the tetromino on the board
		player.currTetro.finishMoving(); // Finish moving the tetromino
		if (player.currTetro.isBombSet()) {
			player.gameBoard.explosion(player.currTetro.getTetroPoints()[0],player.gap);
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

void Controller::entryScreen()
{
	bool isColor = false;
	bool isUserActive = true;
	char computerLevel;

	// Clear the console screen
	
		gotoxy(50, 13);
		PlaySound(TEXT("bestTetris.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << "Loading: [";

		for (int i = 0; i < 5; ++i) {
			cout << "=";
			(i == 4) ? (cout << "]") : cout;
			cout.flush();
			this_thread::sleep_for(chrono::seconds(20 / 20));
		}

		char choice;
		while (isUserActive)
		{
			resetColor();
			system("cls");
			// Display the Tetris headline
			cout << "*********************" << endl;
			cout << "*    Tetris C++    *" << endl;
			cout << "*********************" << endl << endl;

			// Display the menu options
			cout << "(1) Start a new game - Human vs Human" << endl;
			cout << "(2) Start a new game - Human vs Computer" << endl;
			cout << "(3) Start a new game - Computer vs Computer" << endl;
			if (this->gameStatus) {
				cout << "(4) Continue a paused game" << endl;
			}
			cout << "(8) Present instructions and keys" << endl;
			cout << "(9) EXIT" << endl << endl;

			//Message for the user to pick a choice


			//cin >> choice;
			choice = _getch();
			// Process user choice
			switch (choice)
			{
			case '1':
				this->player1 = new Human();
				this->player2 = new Human();
				this->setGameColor(&isColor);
				break;
			case '2':
				this->player1 = new Human;
				this->player2 = new Computer;
				system("cls");
				cout << "Pick Level Of Computer: (a) BEST (b) GOOD and (c) NOVICE : ";
				cin >> computerLevel;
				while (computerLevel != 'a' && computerLevel != 'b' && computerLevel != 'c')
				{
					cout << "Invalid level, try again." << endl;
					cin >> computerLevel;

				}
				dynamic_cast<Computer*>(this->player2)->setComputerLevel(computerLevel);
				this->setGameColor(&isColor);
				break;
			case '3':
				this->player1 = new Computer;
				this->player2 = new Computer;
				system("cls");
				cout << "Pick Level Of Computer 1: (a) BEST (b) GOOD and (c) NOVICE : ";
				cin >> computerLevel;
				while (computerLevel != 'a' && computerLevel != 'b' && computerLevel != 'c')
				{
					cout << "Invalid level, try again." << endl;
					cin >> computerLevel;
				}

				dynamic_cast<Computer*>(this->player1)->setComputerLevel(computerLevel);
				system("cls");
				cout << "Pick Level Of Computer 2: (a) BEST (b) GOOD and (c) NOVICE : ";
				cin >> computerLevel;
				while (computerLevel != 'a' && computerLevel != 'b' && computerLevel != 'c')
				{
					cout << "Invalid level, try again." << endl;
					cin >> computerLevel;

				}
				dynamic_cast<Computer*>(this->player2)->setComputerLevel(computerLevel);
				this->setGameColor(&isColor);
				break;

			case '4':
				system("cls");
				this->player1->gameBoard.drawBoardInGame();
				this->player2->gameBoard.drawBoardInGame(22);
				this->printScoreBoard();
				playGame(isColor);
				break;
			case '8':
				showInstructions();
				break;

			case '9':
				// Exit the program
				this->gameStatus = false;
				isUserActive = false;
				cout << endl;
				endGame();
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
} 

void Controller::setGameColor(bool* isColor)
{
	system("cls");
	cout << "****************************" << endl;
	cout << "*   Choose Color Option    *" << endl;
	cout << "****************************" << endl;
	cout << "(1) With Color" << endl << "(0) No Color" << endl;
	*isColor = _getch() - '0';
	system("cls");
	this->gameStatus = false;
	playGame(*isColor);
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
	cout << "Score: " << this->player1->score;

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
	cout << "Score: " << this->player2->score;
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
		if (this->player1->getScore() > this->player2->getScore()) {
			//player 1 win
			cout << "\033[1;32m*      The Winner is: " << this->PLAYER1 << "        *\033[0m" << endl;  // Bold green text
		}
		else if (this->player1->getScore() < this->player2->getScore()) {
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
	cout << "Player 1 Score: " << this->player1->getScore() << endl;
	cout << "Player 2 Score: " << this->player2->getScore() << endl;
	//cout << "Press any key to return to main menu. "<< endl;
	delete this->player1;
	delete this->player2;
	//cin.ignore();
	//cin >> x;
	//while (!_kbhit()) {}
	_getch();
}

void Controller::resetColor() {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
}