#include "Player.h"
#include "general.h"


class Controller 
{
private:
    Player player1;
    Player player2;
    int winner;
    bool gameStatus = true; // true for there's active game, false if not.
    static const int NUM_OF_POINTS = 4;

   
public:
    // Methods for managing the game loop, updating players, etc.
    
    //CONSTS
    static constexpr int PLAYER1 = 1;
    static constexpr int PLAYER2 = 2;
    static constexpr int TIE = 0;
    static constexpr int HARDDROP_SLEEPTIME = 20;
    static constexpr int ESC_KEYCODE = 27;
    void playGame();
    void entryScreen();
    void handleUserInput();
    void moveTetriminoDown(Player& player);
    void printScoreBoard();
    void showInstructions();
    void updateScore(Player& p, int gap);
    void endGame(); 
 
};