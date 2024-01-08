#include "Board.h"
#include "Tetrimino.h"


class Player 
{
public:
    // Methods for handling user input, updating the game state, etc.
    //TODO inisialize with all letter in constractor
    Tetrimino* createNextTetrimino();
private:
    Board gameBoard;
    //Tetrimino currentTetrimino;
    char letters[54] = { 'A','B','C' };
    int currIdx = 0;
};