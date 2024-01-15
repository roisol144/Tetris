#include "Player.h"
#include "general.h"
#include "Board.h"


class Controller 
{
public:
    // Methods for managing the game loop, updating players, etc.
    void playGame();
    void entryScreen();
    void handleUserInput(Tetrimino* tetro, Player& player, char* leftArr, char* rightArr, char* downArr, int gap = 0);
    void moveTetriminoDown(Tetrimino* tetro, Player& player, int gap = 0);
    void printScoreBoard();
    void showInstructions();
    void updateScore(Player& p);
    void endGame(); // TODO

private:
    Player player1;
    Player player2;
    int winner; 
    bool gameStatus = false; // true for there's active game, false if not.
};