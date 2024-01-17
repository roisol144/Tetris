#include "Player.h"
#include "general.h"
#include "Board.h"


class Controller 
{
private:
    Player player1;
    Player player2;
    int winner;
    bool gameStatus = true; // true for there's active game, false if not.

   
public:
    // Methods for managing the game loop, updating players, etc.

    //Controller(Player _player1, Player _player2) : player1(_player1), player2(_player2) {}   
    void playGame();
    void entryScreen();
    void handleUserInput();
    void moveTetriminoDown(Player& player);
    void printScoreBoard();
    void showInstructions();
    void updateScore(Player& p, int gap);
    void endGame(); // TODO
 
};