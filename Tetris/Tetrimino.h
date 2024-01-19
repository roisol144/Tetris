#pragma once
#include "Point.h"
#include "general.h"

class Tetrimino
{
private:
    static const int NUM_OF_POINTS = 4;
    Point m_points[NUM_OF_POINTS];
    char m_char = 219;
    char nextMove[NUM_OF_POINTS];
    bool isMoving = true;
    bool newBorn = true;
    string colorAnsciCode;
public:
    // Methods for manipulating the Tetrimino
    Tetrimino() : m_points{ {0, 0}, {0, 0}, {0, 0}, {0, 0} } {} //Default constructor 

    //CONSTS
    static constexpr int GAME_HEIGHT = 18;
    static constexpr int GAME_WIDTH = 12;
    static constexpr char RESETCOLOR[7] = "\033[0m";

    //functions
    void createTetromino();
    //string getColor() { return colorAnsciCode; }
    //void setColor(string color) { colorAnsciCode = color; }
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
    char* getNextMove() { return this->nextMove; }
    void setNextMoveByIndex(char ch1, int index);
};