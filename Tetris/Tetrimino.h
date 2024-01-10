#pragma once
#include "Point.h"
#include "general.h"

class Tetrimino
{ 
private:
    // Data members to store information about the Tetrimino
    // (e.g., shape, rotation, position)
    Point m_points[4];
    char m_char;
    bool isMoving = true;

public:
    // Methods for manipulating the Tetrimino
    // (e.g., rotate, moveLeft, moveRight, moveDown, etc.) 

    Tetrimino() : m_points{ {0, 0}, {0, 0}, {0, 0}, {0, 0} } {} //Default constructor 

    void createTetromino(char ch);
    Point* getTetromino() { return m_points; }
    bool getIsMoving() { return isMoving; }
    void finishMoving() { isMoving = false; }
    void move();
    void moveRight();
    void moveLeft();
    Point calculatePivot();
    char getChar() { return m_char; }
    bool moveDown(char* down);
    void draw();
    void erase();



    void rotateClockwise();
    void rotateCounterClockwise();


};