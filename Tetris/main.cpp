#include <iostream>
using namespace std;
#include "general.h"
#include "Controller.h"


void main() 
{
	ShowConsoleCursor(false);
	Controller game;
	game.entryScreen();
	cout << endl;

}

/*
TODOS:
1. VVVVVVVV fix bug of decolorize when return to game. VVVVVVVVV
2. implement cpp concepts: (constractors V), (destractor V), const, (static V), (friend V)
3. add bomb
4. add computer moves
*/

