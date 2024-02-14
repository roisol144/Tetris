#pragma once
#include "Player.h"

class Computer: public Player
{
private:
    //members only for computer!!
    Point dests[12][4];
    int logSize = 0;

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
};

