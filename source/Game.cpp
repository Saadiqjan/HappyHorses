/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Aug 17, 2026
 * Filename: Game.cpp
 * Project Name: HappyHorses
 * Description: Game loop will be handled here
 */

#include "Game.h"

#include <nds.h>

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

		update();
		draw();
	}
}

void Game::update()
{
	// Retrieve input 
	scanKeys();
	unsigned int keys_held = keysHeld();

	switch (currentState)
	{
		case GameState::TitleScreen:
			if (keys_held & KEY_A)
			{
				graphics.clearBitmapLayer(false, 3, 256, 256, 1);
				graphics.clearBitmapLayer(true, 3, 256, 256, 1);
            	transitionTo(GameState::Gameplay);
			}
			break;
		case GameState::SelectSave:
			break;
		case GameState::Gameplay:
			break;
		case GameState::PauseScreen:
			break;
		default:
			break;
	}
}

void Game::draw()
{
	switch (currentState)
	{
		case GameState::TitleScreen:
			break;
		case GameState::SelectSave:
			break;
		case GameState::Gameplay:
			break;
		case GameState::PauseScreen:
			break;
		default:
			break;
	}
}

void Game::transitionTo(GameState newState)
{
    pendingState = newState;
    transitionRequested = true;
}

void Game::applyPendingTransition()
{
    if (!transitionRequested) return;
    transitionRequested = false;

    exitState(currentState);

    currentState = pendingState;

    enterState(currentState);
}

void Game::exitState(GameState state)
{
    // spriteManagerMain.clear();
    // spriteManagerSub.clear();
    // textLayer.clearAll();

    switch (state)
	{
		case GameState::TitleScreen:
			break;
		case GameState::SelectSave:
			break;
		case GameState::Gameplay:
			break;
		case GameState::PauseScreen:
			break;
		default:
			break;
	}
}

void Game::enterState(GameState state)
{
    switch (state)
	{
		case GameState::TitleScreen:
			break;
		case GameState::SelectSave:
			break;
		case GameState::Gameplay:
			break;
		case GameState::PauseScreen:
			break;
		default:
			break;
	}
}