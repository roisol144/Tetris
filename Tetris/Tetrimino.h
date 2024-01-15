#pragma once
#include "Point.h"
#include "general.h"

class Tetrimino
{ 
private:
    static const int NUM_OF_POINTS = 4;
    Point m_points[NUM_OF_POINTS];
    char m_char;
    bool isMoving = true;

public:
    // Methods for manipulating the Tetrimino
    // (e.g., rotate, moveLeft, moveRight, moveDown, etc.) 

    Tetrimino() : m_points{ {0, 0}, {0, 0}, {0, 0}, {0, 0} }, m_char('A') {} //Default constructor 


    void createTetromino(char ch);
    Point* getTetromino() { return m_points; }
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
    //void drop();


};