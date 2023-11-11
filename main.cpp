// ConsolTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"

void main(int argc, char** argv[]) {

	// Initialize	random seed

	srand(static_cast<unsigned>(time(0)));


	//Init game object
	Game game;


	// Game loop
	while (game.running()) {
		game.update();
		game.render();
	}



	//End of application
}
