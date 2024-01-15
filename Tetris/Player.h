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
private:
    Board gameBoard;
    //Tetrimino* currentTetrimino;
    char letters[54] = { 'A','B','C','D','E','F','G','H','I','L','M','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int currLettersIdx = 0;
    
};