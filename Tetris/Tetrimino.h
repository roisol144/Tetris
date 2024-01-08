#pragma once
#include "Point.h"
#include <random>
#include <cstdlib> // for std::rand and std::srand
#include <ctime> 

class Tetrimino
{ 
private:
    // Data members to store information about the Tetrimino
    // (e.g., shape, rotation, position)
    Point m_points[4];
    char m_char;

public:
    // Methods for manipulating the Tetrimino
    // (e.g., rotate, moveLeft, moveRight, moveDown, etc.)
    void createTetromino(char ch);
    Point* getTetromino() { return m_points; }
    void moveRight();
    void moveLeft();
    void rotateLeft();
    void rotateRight();
    char getChar() { return m_char; }



};