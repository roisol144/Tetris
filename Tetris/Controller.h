#include "Player.h"
#include "general.h"
#include "Board.h"


class Controller 
{
public:
    // Methods for managing the game loop, updating players, etc.
    void playGame();
    void entryScreen();
    void showInstructions();
    void endGame(); // TODO

private:
    Player player1;
    Player player2;
    int winner; 
    bool gameStatus = false; // true for there's active game, false if not.
};