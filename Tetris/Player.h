#include "Board.h"
#include "Tetrimino.h"


class Player 
{
public:
    // Methods for handling user input, updating the game state, etc.
    //TODO intialize with all letter in constructor
    /*
    Player(int _gap, string _name) {
        this->initBoard();
        //this->drawBoard();
        this->createNextTetrimino();
        this->score = 0;
        this->currLettersIdx = 0;
        this->gap = _gap;
        this->name = _name;
    }
    */
    //Player() {};

    Tetrimino* createNextTetrimino();
    void drawBoard(int boardGap = 0);
    char getCharFromBoard(int row, int col);
    void addToBoard(Tetrimino* t);
    void drawBoardInGame(int boardsGap = 0);
    void initBoard();
    int whichRowFull();
    void removeFullLine(int lineNum, int gap);
    void increaseScore();
    void resetScore();
    int getScore() { return this->score; }
    void setGap(int gapParam) { this->gap = gapParam; }
    int getGap() { return this->gap; }
    void setPlayerName(string name);
    Tetrimino* getCurrTetro() { return this->currTetro; }

private:
    Board gameBoard;
    Tetrimino* currTetro;
    char letters[54] = { 'A','B','C','D','E','F','G','H','I','L','M','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int currLettersIdx = 0;
    int score = 0;
    int gap = 0;
    string name;
    
};