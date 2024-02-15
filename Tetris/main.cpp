#include <iostream>
using namespace std;
#include "general.h"
#include "Controller.h"


void main()
{
	srand(time(nullptr));
	ShowConsoleCursor(false);
	Controller game;
	game.entryScreen();
	cout << endl;
}