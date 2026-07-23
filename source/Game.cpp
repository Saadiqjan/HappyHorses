/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Jul 21, 2026
 * Filename: Game.cpp
 * Project Name: HappyHorses
 * Description: Game loop will be handled here
 */

#include "Game.h"

#include <nds.h>

#include "GraphicsManager.h"

void Game::init()
{
	powerOn(POWER_ALL_2D);
	
	lcdMainOnBottom();
	
	graphics.init();

	graphics.loadTitleScreen();
}

void Game::run()
{
	while (true)
	{
		swiWaitForVBlank();
	}
}

void Game::update()
{
	
}

void Game::draw()
{
	
}