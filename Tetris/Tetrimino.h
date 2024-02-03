#pragma once
#include "Point.h"
#include "general.h"

class Tetrimino
{
private:
    static constexpr int NUM_OF_POINTS = 4;
    enum Colors {
        WHITE=15, BLUE=1, GREEN=2, CYAN=3, LIGHTRED=12, MAGENTA=5, BROWN=6,YELLOW=14, RED=4
    };
    Point m_points[NUM_OF_POINTS];
    //char m_char = 219;
    char nextMove[NUM_OF_POINTS];
    bool isMoving = true;
    bool isBomb = false;
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
    const Point* getTetroPoints() const { return m_points; }
    bool getIsMoving() const { return isMoving; }
    void finishMoving() { isMoving = false; }
    void move(int gap = 0) const;
    bool moveRight(const char* right);
    bool moveLeft(const char* left);
    Point calculatePivot();
    bool moveDown(const char* down);
    void draw(int gap = 0) const;
    void erase(int gap = 0) const;
    bool isRotateLegal(const Point* pointsArr,const char* rotated);
    //Point* rotateClockwise();
    void rotateClockwise(Point* pointsToRotate);
    //Point* rotateCounterClockwise();
    void rotateCounterClockwise(Point* pointToRotate);
    void setNewBorn(bool newborn) { newBorn = newborn; }
    bool isNewBorn() const { return newBorn; }
    bool isTopReached();
    const char* getNextMove() const { return this->nextMove; }
    void setNextMoveByIndex(char ch1, int index);
    int getColor() const { return this->color; }
    bool isBombSet() { return isBomb; }
};