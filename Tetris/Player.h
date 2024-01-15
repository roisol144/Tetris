#include "Board.h"
#include "Tetrimino.h"


class Player 
{
public:
    // Methods for handling user input, updating the game state, etc.
    //TODO intialize with all letter in constructor
    Tetrimino* createNextTetrimino();
    void drawBoard(int boardGap = 0);
    char getCharFromBoard(int row, int col);
    void addToBoard(Tetrimino* t);
    void drawBoardInGame(int boardsGap = 0);
    void initBoard();
    int whichRowFull();
    void removeFullLine(int lineNum);
    void increaseScore();
    void resetScore();
    int getScore() { return this->score; }
    void setGap(int gapParam) { this->gap = gapParam; }
    int getGap() { return this->gap; }
private:
    Board gameBoard;
    //Tetrimino* currentTetrimino;
    char letters[54] = { 'A','B','C','D','E','F','G','H','I','L','M','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int currLettersIdx = 0;
    int score = 0;
    int gap = 0;
    
};