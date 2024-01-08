#include "GameController.h"
#include <windows.h>
using namespace std;

// TODO- sleep 200 while working
// LAROHAV PROGRAMMING. 
// TODO - one shape moving down.
// TODO - Solve when shape can't move anymore. LAROHAV 
// TODO - implement move left (_kbhit).
// TODO - Working on player only. 
// TODO - all members must have m_ before them
// TODO - adding defines - constants.




void GameController::playGame()
{
	while (true)
	{
		char keyPressed;
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == 27) // 27 is the ASCII value of ESC.
			{
				clrscr(); // Clearing the console.

				//Menu
				cout << "MENU\n";
				cout << "***************\n";
				cout << "(1) Start a new game\n";
				cout << "(2) Continue a paused game\n";
				cout << "(8) Present instructions and keys\n";
				cout << "(9) EXIT\n";
				cout << "Choose: ";
				cin >> keyPressed;
				
				//Insert switch or handler function.

			}
		}
	}
}