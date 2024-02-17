#pragma once
#include "Board.h"
#include <vector>


class Player 
{
public:
   
    //CONSTS
    static constexpr int PLAYER2_GAP = 22;
    static constexpr int FULLROW_NOTFOUND = -1;
    static const int NUM_OF_POINTS = 4;
 // Methods for handling user input, updating the game state, etc.
    /* creating a new tetrimino*/
    virtual void createNextTetrimino(const bool isColor) {}
    /* function that will handle score increament. */
    void increaseScore();
    /* function will reset the score of the player at the beginning of the game.  */
    void resetScore();
    /*  function will return the score of the player */
    int getScore() const { return this->score; }
    /* function will set the gap of the player (printed gap of the console board)*/
    void setGap(const int gapParam) { this->gap = gapParam; }
    /* function will return the gap of the player */
    int getGap() const { return this->gap; }
    /* function will initilize the player name  */
    void setPlayerName(string name);
    void setNextMove(int x, int y);
    virtual void handleUserInput(char keyPressed) {}
    virtual ~Player() {}
    

protected:
    Board gameBoard;
    Tetrimino currTetro;
    

private:
    int score = 0;
    int gap = 0;
    string name;
    friend class Controller;
};