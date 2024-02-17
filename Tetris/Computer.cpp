#include "Computer.h"

void Computer::createNextTetrimino(const bool isColor) {
	Tetrimino t;
	t.createTetromino(isColor);
	this->currTetro = t;
	this->pickComputerMove();

}

//computer
bool Computer::isXSumEqual(Point* dest) {
	int sumCurr = 0;
	int sumDest = 0;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		sumCurr += this->currTetro.getTetroPoints()[i].getX();
		sumDest += dest[i].getX();
	}

	if (sumCurr == sumDest)
		return true;
	return false;
}
//computer
int Computer::sumOfXcoords(const Point* p) {
	int sum = 0;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		sum += p[i].getX();
	}
	return sum;
}

//computer
void Computer::moveComputer(Point* dest) {
	this->currTetro.setNewBorn(false);

	//go right!
	if (this->sumOfXcoords(this->currTetro.getTetroPoints()) < this->sumOfXcoords(dest)) {

		while (this->sumOfXcoords(this->currTetro.getTetroPoints()) < this->sumOfXcoords(dest)) {
			this->currTetro.erase(this->getGap());
			this->setNextMove(1, 0);
			if (!this->currTetro.moveRight(this->currTetro.getNextMove()))
				return;
			this->currTetro.draw(this->getGap());
			Sleep(100);
		}
	}
	else { // go left!
		while (this->sumOfXcoords(this->currTetro.getTetroPoints()) > this->sumOfXcoords(dest)) {
			this->currTetro.erase(this->getGap());
			this->setNextMove(-1, 0);
			if (!this->currTetro.moveLeft(this->currTetro.getNextMove()))
				return;
			this->currTetro.draw(this->getGap());
			Sleep(100);

		}
	}
	
}

void Computer::pickComputerMove() {
	Point movesToPickFrom[NUM_OF_POINTS][NUM_OF_POINTS];
	int counter = 0;
	Point pointsToRotate[NUM_OF_POINTS];
	Point pointsArrTemp[NUM_OF_POINTS];

	int score;
	int max = -100000;
	int bestMoveIndex;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		this->setDestsPerRotation();

		memcpy(movesToPickFrom[counter], dests[bestMoveFromDestsIndex(&score)], NUM_OF_POINTS * sizeof(Point));
		if (max < score) {
			max = score;
			bestMoveIndex = counter;
		}
		counter++;
		this->currTetro.rotateClockwise(pointsArrTemp);

		for (int j = 0; j < NUM_OF_POINTS; j++) {
			pointsToRotate[j].setX(pointsArrTemp[j].getX());
			pointsToRotate[j].setY(pointsArrTemp[j].getY());
		}
		for (int k = 0; k < NUM_OF_POINTS; k++) {

			this->currTetro.setYcoordsByIndex(pointsToRotate[k].getY() + 3, k);
			this->currTetro.setXcoordsByIndex(pointsToRotate[k].getX(), k);
		}

	}



	//rotating the shape to the best move rotation:
	for (int i = 0; i < bestMoveIndex; i++) {
		this->currTetro.rotateClockwise(pointsArrTemp);
		for (int j = 0; j < NUM_OF_POINTS; j++) {
			pointsToRotate[j].setX(pointsArrTemp[j].getX());
			pointsToRotate[j].setY(pointsArrTemp[j].getY() + 3);

		}

		for (int k = 0; k < NUM_OF_POINTS; k++) {

			this->currTetro.setYcoordsByIndex(pointsToRotate[k].getY(), k);

			this->currTetro.setXcoordsByIndex(pointsToRotate[k].getX(), k);
		}

	}
	while (this->currTetro.getTetroPoints()[0].getY() != 0 &&
		this->currTetro.getTetroPoints()[1].getY() != 0 &&
		this->currTetro.getTetroPoints()[2].getY() != 0 &&
		this->currTetro.getTetroPoints()[3].getY() != 0) {
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[0].getY() - 1, 0);
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[1].getY() - 1, 1);
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[2].getY() - 1, 2);
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[3].getY() - 1, 3);
	}
	while (this->currTetro.getTetroPoints()[0].getX() != NUM_OF_POINTS &&
		this->currTetro.getTetroPoints()[1].getX() != NUM_OF_POINTS &&
		this->currTetro.getTetroPoints()[2].getX() != NUM_OF_POINTS &&
		this->currTetro.getTetroPoints()[3].getX() != NUM_OF_POINTS) {
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[0].getX() - 1, 0);
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[1].getX() - 1, 1);
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[2].getX() - 1, 2);
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[3].getX() - 1, 3);
	}
	if (this->computerLevel == 'a') // Best Computer - should calculate the exact best step for each move
		this->moveComputer(movesToPickFrom[bestMoveIndex]);

	else if (this->computerLevel == 'b') // Good Computershould miss occasionally (e.g. randomly once in ~NUM_OF_POINTS0 moves)
	{
		if (movesCounter % 40 == 0) // every other NUM_OF_POINTS0 moves
			this->moveComputer(movesToPickFrom[rand() % 3]);

		else
			this->moveComputer(movesToPickFrom[bestMoveIndex]);
	}
	else if (this->computerLevel == 'c') // every other 10 moves
	{
		if (movesCounter % 10 == 0)
			this->moveComputer(movesToPickFrom[rand() % 3]);
		else
			this->moveComputer(movesToPickFrom[bestMoveIndex]);
	}
	this->increaseMovesCounter();
}

int Computer::bestMoveFromDestsIndex(int* score) {
	int bestMoveIndex = 0;
	vector<int> movesScores(logSize);
	int max = -1000000;
	int counter = 0;
	for (int i = 0; i < logSize; i++) {
		for (int k = 0; k < NUM_OF_POINTS; k++) {
			this->gameBoard.addTempPoint(dests[i][k]);
		}
		//parameters to calculate and pick the best move
		movesScores[i] = -2.5 * this->gameBoard.aggregateHeight() +
			0.760666 * this->gameBoard.countFullRows(dests[i]) +
			-0.35663 * this->gameBoard.countHoles() +
			-0.184483 * this->gameBoard.calcBumpiness();

		if (max < movesScores[i]) {
			max = movesScores[i];
			bestMoveIndex = i;
		}
		for (int k = 0; k < NUM_OF_POINTS; k++) {
			this->gameBoard.removeTempPoint(dests[i][k]);
		}

	}
	*score = max;
	return bestMoveIndex;
}



int Computer::sumOfYcoordsByIndex(int index) {
	int sum = 0;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		sum += dests[index][i].getY();
	}
	return sum;
}

int Computer::sumOfYcoords(const Point* p) {
	int sum = 0;
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		sum += p[i].getY();
	}
	return sum;
}




void Computer::setDestsPerRotation() {
	logSize = 0;
	bool canMoveRight = true;
	int originalY[NUM_OF_POINTS];
	int originalX[NUM_OF_POINTS];
	for (int i = 0; i < NUM_OF_POINTS; i++) {
		originalX[i] = this->currTetro.getTetroPoints()[i].getX();
	}
	//loop to move the shape all the way to the left
	this->setNextMove(-1, 0);
	while (this->currTetro.moveLeft(this->currTetro.getNextMove()))
	{
		this->setNextMove(-1, 0);
	}

	while (canMoveRight) {
		for (int i = 0; i < NUM_OF_POINTS; i++) {
			originalY[i] = this->currTetro.getTetroPoints()[i].getY();
		}
		//drop the shape till it collapse
		this->setNextMove(0, 1);
		while (this->currTetro.moveDown(this->currTetro.getNextMove())) {
			this->setNextMove(0, 1);
		}

		memcpy(dests[logSize], this->currTetro.getTetroPoints(), sizeof(Point) * NUM_OF_POINTS);
		logSize++;

		this->currTetro.setYcoords(originalY);

		this->setNextMove(1, 0);
		canMoveRight = this->currTetro.moveRight(this->currTetro.getNextMove());
	}


	this->currTetro.setXcoords(originalX);
}
