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
	/*Tetrimino t;
	t.createTetromino(0);
	t.setNewBorn(false);
	t.draw();
	Sleep(500);
	t.erase();
	int x[4] = { -t.getTetroPoints()[0].getY() + t.getTetroPoints()[2].getY()+ t.getTetroPoints()[2].getX()
		,-t.getTetroPoints()[1].getY() + t.getTetroPoints()[2].getY() + t.getTetroPoints()[2].getX()
		,-t.getTetroPoints()[2].getY() + t.getTetroPoints()[2].getY() + t.getTetroPoints()[2].getX(),
		-t.getTetroPoints()[3].getY() + t.getTetroPoints()[2].getY() + t.getTetroPoints()[2].getX() };
	t.setXcoords(x);
	int y[4] = { t.getTetroPoints()[0].getX() - t.getTetroPoints()[2].getX() + t.getTetroPoints()[2].getY(),
		t.getTetroPoints()[1].getX() - t.getTetroPoints()[2].getX() + t.getTetroPoints()[2].getY(),
		t.getTetroPoints()[2].getX() - t.getTetroPoints()[2].getX() + t.getTetroPoints()[2].getY(),
		t.getTetroPoints()[3].getX() - t.getTetroPoints()[2].getX() + t.getTetroPoints()[2].getY() };
	t.setYcoords(y);
	t.draw();
	cout << endl << endl << endl << endl << endl << endl;*/

}

/*
TODOS:
1. VVVVVVVV fix bug of decolorize when return to game. VVVVVVVVV
2. VVVVVVVVV implement cpp concepts: (constractors V), (destractor V), (const V), (static V), (friend V) VVVVVVV
3. VVVVVVV add bomb
4. add computer moves
*/

/* notes on ex1
* 
* (-2) handling board aspects such as checking whether block reached bottom / collides with another block, whether a full row occurred etc. 
	 should be done by encompassing board / game class (Tetrimino::moveDown, ::moveLeft etc.);

(-6) avoid recursive call structure (Controller::entryScreen -> ::playGame -> ::endGame -> ::entryScreen);
(0) menu code might be better arranged


//DONE!!!

(-1) V srand should be called only once, at beginning of program (Tetrimino::createTetromino); //DONE
(-3) V dynamic memory deallocation for class data  members should occur inside class-  
	memory should be managed by class (Player - currTetro - Player class should have a dtor, copy ctor and operator= implementation to handle dynamic memory allocation); // DONE
For next assignment: V (0) methods which do not change object data members (such as getters) should be marked as const (Player::getScore, Tetrimino::isNewBorn) // DONE


(-5) V should not return local array, as it is deleted upon function return (Tetrimino::rotateClockwise - points_to_rotate); //DONE
(-2) handling board aspects such as checking whether block reached bottom / collides with another block, whether a full row occurred etc. 
	 should be done by encompassing board / game class (Tetrimino::moveDown, ::moveLeft etc.);

(-6) avoid recursive call structure (Controller::entryScreen -> ::playGame -> ::endGame -> ::entryScreen);
(0) menu code might be better arranged

G64

(-2) V use named constants / enum instead of literals (Controller::entryScreen, ::printScoreBoard, VTetrimino::createTetromino);
(0) avoid "using namespace" directive in header file (general.h)
*/

