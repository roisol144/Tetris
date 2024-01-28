#pragma once
#include "Point.h"
#include "general.h"

class Tetrimino
{
private:
    static constexpr int NUM_OF_POINTS = 4;
    enum Colors {
        WHITE=15, BLUE=1, GREEN=2, CYAN=3, RED=4, MAGENTA=5, BROWN=6,YELLOW=14
    };
    Point m_points[NUM_OF_POINTS];
    //char m_char = 219;
    char nextMove[NUM_OF_POINTS];
    bool isMoving = true;
    bool newBorn = true;
    int color = Colors::WHITE;
public:
    // Methods for manipulating the Tetrimino
    //Tetrimino() : m_points{ {0, 0}, {0, 0}, {0, 0}, {0, 0} } {} //Default constructor 
    
    Tetrimino() : m_points{}{}

    //CONSTS
    static constexpr int GAME_HEIGHT = 18;
    static constexpr int GAME_WIDTH = 12;
    //static constexpr char RESETCOLOR[7] = "\033[0m";

    //functions
    void createTetromino(bool isColor);
    //string getColor() { return colorAnsciCode; }
    //void setColor(string color) { colorAnsciCode = color; }
    Point* getTetroPoints() { return m_points; }
    bool getIsMoving() { return isMoving; }
    void finishMoving() { isMoving = false; }
    void move(int gap = 0);
    bool moveRight(char* right);
    bool moveLeft(char* left);
    Point calculatePivot();
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
    int getColor() { return this->color; }
};