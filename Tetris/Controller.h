#include "Player.h"
#include "general.h"
#include "Board.h"




class Controller 
{
public:
    // Methods for managing the game loop, updating players, etc.
    void playGame();
    

private:
    Player player1;
    Player player2;
};