#ifndef __GAMEBOARD_H
#define __GAMEBOARD_H
#include <iostream>
using namespace std;
#include "Board.h"
#include "general.h"


void Board::init() {
	for (int i = 0; i < GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
		{
			
				gameBoard[i][j] = ' '; // Initialize with some default value
		}
	}
}



void Board::drawBoard(const int boardsGap) const
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 15);
	for (int col = 0 + boardsGap; col <= this->GAME_WIDTH + 1 + boardsGap; col++)
	{
		
		gotoxy(col, 0);
		cout << "# ";

		gotoxy(col, this->GAME_HEIGHT+1);
		cout << "# ";
	}
	

	for (int row = 0; row <= this->GAME_HEIGHT; row++)
	{
		gotoxy(0 + boardsGap, row);
		cout << "# ";

		gotoxy(this->GAME_WIDTH + boardsGap,row);
		cout << " #";
	}
	cout << endl;

}

void Board::drawBoardInGame(int boardsGap) const {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleTextAttribute(hStdOut, 15);
	this->drawBoard(boardsGap);
	for (int row = 0; row < this->GAME_HEIGHT; row++) {
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (this->gameBoard[row][col] != ' ') {
				gotoxy(boardsGap + col + 1, row+1);
				SetConsoleTextAttribute(hStdOut, this->gameBoard[row][col]);
				cout << (char)219;
			}
			else {
				if (row == 0)
					continue;
				gotoxy(boardsGap + col + 1, row+1);
				cout << ' ';
			}
		}
	}
}

void Board::addToBoard(const Tetrimino shape) {
	const Point* arr = shape.getTetroPoints();
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->gameBoard[arr[i].getY()][arr[i].getX()] = shape.getColor();
	}

}

char Board::getChar(int row, int col) const {
	return this->gameBoard[col][row];
}

int Board::whichRowFull() const {
	int counter;
	for (int row = this->GAME_HEIGHT-1; row >= 0; row--) {
		counter = 0;
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (this->getChar(col,row) == ' ') {
				break;
			}
			counter++;
		}
		if (counter == this->GAME_WIDTH)
			return row;
	}
	return -1;
	
}

void Board::removeFullLine(const int lineNum,const int gap) {
	for (int row = lineNum; row > 0; row--) {
		for (int col = 0; col < this->GAME_WIDTH; col++) {
			if (row == 1)
				this->gameBoard[row][col] = ' ';
			else
				this->gameBoard[row][col] = this->gameBoard[row - 1][col];
		}
	}
	this->drawBoardInGame(gap);
}

void Board::explosion(const Point& pnt, const int gap) {
	int startX = pnt.getX() - 4;
	int startY = pnt.getY() - 4;
	while (startX < 0) { startX++; }
	while (startY < 0) { startY++; }

	for (int row = startY; row < GAME_HEIGHT && row <= (startY + 8); row++) {
		for (int col = startX; col < GAME_WIDTH && col <= (startX + 8); col++) {
			for (int i = row; i > 0; i--) {
				this->gameBoard[i][col] = this->gameBoard[i - 1][col];
				this->gameBoard[i - 1][col] = ' ';
			}
			this->gameBoard[0][col] = ' ';		
		}
	}

	this->drawBoardInGame(gap);
}

int Board::countFullRows(Point* dest) {
	int countColumns = 0;
	int res = 0;
	

	//counting how many rows are full:
	for (int i = 0; i < 4; i++) {	
		countColumns = 0;
		for (int col = 0; col < GAME_WIDTH; col++) {
			if (this->gameBoard[dest[i].getY()][col] != ' ') {
				countColumns++;
			}
			if (countColumns == GAME_WIDTH) {
				res++;
			}		
		}
		
	}


	return res;
}

int Board::countHoles() {
	int counter = 0;
	for (int row = 1; row < GAME_HEIGHT; row++) {
		for (int col = 0; col < GAME_WIDTH; col++) {
			if (this->gameBoard[row][col] == ' ' && this->gameBoard[row-1][col] != ' ') {
				counter++;
			}
		}
	}
	return counter;
}

int Board::calcBumpiness() {
	int res = 0;
	int prevBump=calcHeight(0);
	int currBump;
	for (int col = 1; col < GAME_WIDTH; col++) {
		currBump = calcHeight(col);
		res += abs(prevBump - currBump);
		prevBump = currBump;
	}
	return res;
}
int Board::calcHeight(int col) {
	int row = 0;
	while (this->gameBoard[row][col] == ' ') {
		row++;
	}
	return (18 - row);
}

void Board::addTempPoint(Point p) {
	this->gameBoard[p.getY()][p.getX()] = 1;
}

void Board::removeTempPoint(Point p) {
	this->gameBoard[p.getY()][p.getX()] = ' ';
}

int Board::aggregateHeight()
{


	int res = 0;
	int row;
	for (int col = 0; col < 12; col++) {
		row = 0;
		while (this->gameBoard[row][col] == ' ') {
			row++;
		}
		/*if ((18 - row) >= 16)
			res += row*1000;*/
		res += (18 - row);
	}


	return res;
}


/*
void Board::explosion(const Point& pnt,const int gap)
{
	double squaredX;
	double squaredY;
	Point erasedPnts[GAME_HEIGHT * GAME_WIDTH];
	int howManyToErase = 0;
	for (int row = 0; row < GAME_HEIGHT; row++)
	{
		for (int col = 0; col < GAME_WIDTH; col++)
		{
			squaredX = pow((col - pnt.getX()), 2);
			squaredY = pow((row - pnt.getY()), 2);
			if (sqrt(squaredX + squaredY) <= 4)
			{
				
				this->gameBoard[row][col] = ' ';
				erasedPnts[howManyToErase] = { col,row };
				howManyToErase++;
			}
		}
	}

	/* CHAT GPT SOLUTION FOR MINIMIZING GAPS AFTER BOMB
	for (int col = 0; col < GAME_WIDTH; col++) {
		int emptyCells = 0;
		for (int row = GAME_HEIGHT - 1; row >= 0; row--) {
			if (this->gameBoard[row][col] == ' ') {
				emptyCells++;
			}
			else if (emptyCells > 0) {
				// Shift non-empty cell downwards by emptyCells
				this->gameBoard[row + emptyCells][col] = this->gameBoard[row][col];
				this->gameBoard[row][col] = ' '; // Clear original cell
			}
		}
	}
	

	int currRow;
	for (int i = 0; i < howManyToErase; i++) { //iterate over the points that got erased
		currRow = erasedPnts[i].getY();
		for (int rowUp = currRow - 1; rowUp >= 0; rowUp--) {
			if (this->gameBoard[rowUp][erasedPnts[i].getX()] != ' ') 
			{
				this->gameBoard[currRow][erasedPnts[i].getX()] = this->gameBoard[rowUp][erasedPnts[i].getX()];
				this->gameBoard[rowUp][erasedPnts[i].getX()] = ' ';
				currRow--;
			}
		}
	}

	
	this->drawBoardInGame(gap);
}
*/


#endif // !__GAMEBOARD_H

