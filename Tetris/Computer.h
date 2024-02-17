#pragma once
#include "Player.h"

class Computer: public Player
{
private:
    //members only for computer!!
    Point dests[12][4];
    int logSize = 0;
    char computerLevel = 'a';
    int movesCounter = 0;

public:
    virtual void createNextTetrimino(const bool isColor) override;
    void setDestsPerRotation();
    void pickComputerMove();
    int bestMoveFromDestsIndex(int* score);
    int sumOfYcoordsByIndex(int index);
    void moveComputer(Point* dest);
    bool isXSumEqual(Point* dest);
    int sumOfXcoords(const Point* p);
    int sumOfYcoords(const Point* p);
    void setComputerLevel(char lvl) { this->computerLevel = lvl; }
    void increaseMovesCounter() { this->movesCounter++; }

};

//int Computer::movesCounter = 0;
