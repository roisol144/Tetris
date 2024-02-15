﻿#pragma once
#include "Board.h"
#include <vector>


class Player 
{
public:
   
    //CONSTS
    static constexpr int PLAYER2_GAP = 22;
    static constexpr int FULLROW_NOTFOUND = -1;
 // Methods for handling user input, updating the game state, etc.
    /* createNextTetrimino() - creating a new tetrimino*/
    virtual void createNextTetrimino(const bool isColor) {}
    /* drawBoard() - drawing the board */
    //void drawBoard(int boardGap = 0);
    /* getting cooridantes to retrieve char from thr board 2D array. */
    //char getCharFromBoard(int row, int col);
    /* addToBoard() - adding chars to the board */
    //void addToBoard(Tetrimino* t);
    /* this function will draw the board while the game is running  */
    //void drawBoardInGame(int boardsGap = 0);
    /*  this function will initilize each cell inside the 2D array that represent the board */
    //void initBoard();
    /* function will check which row is full and will return its index */
    //int whichRowFull();
    /* function will remove a full line based on the index that was given by whichRowFull() returned value */
    //void removeFullLine(int lineNum, int gap);
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