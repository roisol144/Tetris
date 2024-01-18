#pragma once
#include "Point.h"
#include "general.h"

class Tetrimino
{ 
private:
    static const int NUM_OF_POINTS = 4;
    Point m_points[NUM_OF_POINTS];
    char m_char;
    char nextMove[NUM_OF_POINTS];
    bool isMoving = true;
    bool newBorn = true;
    static constexpr int GAME_HEIGHT = 18;
    static constexpr int GAME_WIDTH = 12;
public:
    // Methods for manipulating the Tetrimino
    Tetrimino() : m_points{ {0, 0}, {0, 0}, {0, 0}, {0, 0} }, m_char('A') {} //Default constructor 


    void createTetromino(char ch);
    Point* getTetroPoints() { return m_points; }
    bool getIsMoving() { return isMoving; }
    void finishMoving() { isMoving = false; }
    void move(int gap = 0);
    bool moveRight(char* right);
    bool moveLeft(char* left);
    Point calculatePivot();
    char getChar() { return m_char; }
    bool moveDown(char* down);
    void draw(int gap = 0);
    void erase(int gap = 0);
    bool isRotateLegal(Point* pointsArr,char* rotated);
    Point* rotateClockwise();
    Point* rotateCounterClockwise();
    void setNewBorn(bool newborn) { newBorn = newborn; }
    bool isNewBorn() { return newBorn; }
    bool isTopReached();
    void setNextMove(char ch1, char ch2, char ch3, char ch4);
    char* getNextMove() { return this->nextMove; }
    void setNextMoveByIndex(char ch1, int index);
};