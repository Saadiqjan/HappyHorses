/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Jul 21, 2026
 * Filename: Main.cpp
 * Project Name: HappyHorses
 * Description: Entry point of program and responsible for initializing and running the game loop
 */

#include "Game.h"

Game game;

int main(void)
{
	game.init();
    game.run();

	return 0;
}
