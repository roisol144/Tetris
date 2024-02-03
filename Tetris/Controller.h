#include "Player.h"
#include "general.h"


class Controller 
{
private:
    Player player1;
    Player player2;
    int winner;
    bool gameStatus = false; // true for there's active game, false if not.
   

   
public:
    // Methods for managing the game loop, updating players, etc.
    
    //CONSTS
    static const int NUM_OF_POINTS = 4;
    static constexpr int PLAYER1 = 1;
    static constexpr int PLAYER2 = 2;
    static constexpr int TIE = 0;
    static constexpr int SCREEN_START_COL = 0;
    static constexpr int SCORE_FRAME_COL_END = 0;
    static constexpr int HARDDROP_SLEEPTIME = 20;
    static constexpr int ESC_KEYCODE = 27;
    static constexpr int SCORE_FRAME_ROW_START = 20;
    static constexpr int SCORE_FRAME_ROW_END = 23;
    static constexpr int SCORE_FRAME_START_COL = 1;
    static constexpr int SCORE_FRAME_END_COL = 12;
    void playGame(const bool isColor);
    void entryScreen();
    void handleUserInput();
    void moveTetriminoDown(Player& player);
    void printScoreBoard();
    void showInstructions();
    void updateScore(Player& p, int gap);
    void endGame(); 
    void resetColor();
    
 
};