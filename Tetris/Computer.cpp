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
	for (int i = 0; i < 4; i++) {
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
	for (int i = 0; i < 4; i++) {
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
			Sleep(150);
		}
	}
	else { // go left!
		while (this->sumOfXcoords(this->currTetro.getTetroPoints()) > this->sumOfXcoords(dest)) {
			this->currTetro.erase(this->getGap());
			this->setNextMove(-1, 0);
			if (!this->currTetro.moveLeft(this->currTetro.getNextMove()))
				return;
			this->currTetro.draw(this->getGap());
			Sleep(150);

		}
	}
	
}

void Computer::pickComputerMove() {
	Point movesToPickFrom[4][4];
	int counter = 0;
	Point pointsToRotate[4];
	Point pointsArrTemp[4];
	//bool isRotateLegal = true;
	int score;
	int max = -100000;
	int bestMoveIndex;
	for (int i = 0; i < 4; i++) {
		this->setDestsPerRotation();

		memcpy(movesToPickFrom[counter], dests[bestMoveFromDestsIndex(&score)], 4 * sizeof(Point));
		if (max < score) {
			max = score;
			bestMoveIndex = counter;
		}
		counter++;
		this->currTetro.rotateClockwise(pointsArrTemp);

		for (int j = 0; j < 4; j++) {
			pointsToRotate[j].setX(pointsArrTemp[j].getX());
			pointsToRotate[j].setY(pointsArrTemp[j].getY());
		}
		for (int k = 0; k < 4; k++) {

			this->currTetro.setYcoordsByIndex(pointsToRotate[k].getY() + 3, k);
			this->currTetro.setXcoordsByIndex(pointsToRotate[k].getX(), k);
		}
		
	}



	//rotating the shape to the best move rotation:
	for (int i = 0; i < bestMoveIndex; i++) {
		this->currTetro.rotateClockwise(pointsArrTemp);
		for (int j = 0; j < 4; j++) {
			pointsToRotate[j].setX(pointsArrTemp[j].getX());
			pointsToRotate[j].setY(pointsArrTemp[j].getY() + 3);

		}

		for (int k = 0; k < 4; k++) {

			this->currTetro.setYcoordsByIndex(pointsToRotate[k].getY(), k);

			this->currTetro.setXcoordsByIndex(pointsToRotate[k].getX(), k);
		}

	}
	//this->currTetro.move();
	while (this->currTetro.getTetroPoints()[0].getY() != 0 &&
		this->currTetro.getTetroPoints()[1].getY() != 0 &&
		this->currTetro.getTetroPoints()[2].getY() != 0 &&
		this->currTetro.getTetroPoints()[3].getY() != 0) {
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[0].getY() - 1, 0);
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[1].getY() - 1, 1);
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[2].getY() - 1, 2);
		this->currTetro.setYcoordsByIndex(this->currTetro.getTetroPoints()[3].getY() - 1, 3);
	}
	while (this->currTetro.getTetroPoints()[0].getX() != 4 &&
		this->currTetro.getTetroPoints()[1].getX() != 4 &&
		this->currTetro.getTetroPoints()[2].getX() != 4 &&
		this->currTetro.getTetroPoints()[3].getX() != 4) {
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[0].getX() - 1, 0);
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[1].getX() - 1, 1);
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[2].getX() - 1, 2);
		this->currTetro.setXcoordsByIndex(this->currTetro.getTetroPoints()[3].getX() - 1, 3);
	}
	this->moveComputer(movesToPickFrom[bestMoveIndex]);

}

int Computer::bestMoveFromDestsIndex(int* score) {
	int bestMoveIndex = 0;
	vector<int> movesScores(logSize);
	int max = -1000000;
	int counter = 0;
	for (int i = 0; i < logSize; i++) {
		for (int k = 0; k < 4; k++) {
			this->gameBoard.addTempPoint(dests[i][k]);
		}
		movesScores[i] = -2.5 * this->gameBoard.aggregateHeight() +
			0.760666 * this->gameBoard.countFullRows(dests[i]) +
			-0.35663 * this->gameBoard.countHoles() +
			-0.184483 * this->gameBoard.calcBumpiness();

		if (max < movesScores[i]) {
			max = movesScores[i];
			bestMoveIndex = i;
		}
		for (int k = 0; k < 4; k++) {
			this->gameBoard.removeTempPoint(dests[i][k]);
		}

	}
	*score = max;
	return bestMoveIndex;
}



int Computer::sumOfYcoordsByIndex(int index) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += dests[index][i].getY();
	}
	return sum;
}

int Computer::sumOfYcoords(const Point* p) {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		sum += p[i].getY();
	}
	return sum;
}




void Computer::setDestsPerRotation() {
	logSize = 0;
	bool canMoveRight = true;
	int originalY[4];
	int originalX[4];
	for (int i = 0; i < 4; i++) {
		originalX[i] = this->currTetro.getTetroPoints()[i].getX();
	}
	//loop to move the shape all the way to the left
	this->setNextMove(-1, 0);
	while (this->currTetro.moveLeft(this->currTetro.getNextMove()))
	{
		this->setNextMove(-1, 0);
	}

	while (canMoveRight) {
		for (int i = 0; i < 4; i++) {
			originalY[i] = this->currTetro.getTetroPoints()[i].getY();
		}
		//drop the shape till it collapse
		this->setNextMove(0, 1);
		while (this->currTetro.moveDown(this->currTetro.getNextMove())) {
			this->setNextMove(0, 1);
		}

		memcpy(dests[logSize], this->currTetro.getTetroPoints(), sizeof(Point) * 4);
		logSize++;

		this->currTetro.setYcoords(originalY);

		this->setNextMove(1, 0);
		canMoveRight = this->currTetro.moveRight(this->currTetro.getNextMove());
	}


	this->currTetro.setXcoords(originalX);
}
