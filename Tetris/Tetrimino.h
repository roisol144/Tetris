#pragma once
#include "Point.h"
#include <random>
#include <cstdlib> // for std::rand and std::srand
#include <ctime> 

class Tetromino
{ 
private:
    // Data members to store information about the Tetrimino
    // (e.g., shape, rotation, position)
    Point tetromino[4];
   

public:
    // Methods for manipulating the Tetrimino
    // (e.g., rotate, moveLeft, moveRight, moveDown, etc.)
    void createTetromino();
    Point* getTetromino() { return tetromino; }
    void moveRight();
    void moveLeft();
    void rotateLeft();
    void rotateRight();



};