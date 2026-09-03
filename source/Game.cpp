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

	currentState = createState(GameStateType::TitleScreen);

	if (currentState) 
	{
		currentState->onEnter();
	}
}

void Game::run()
{
	while (true)
	{
		swiWaitForVBlank();

		update();
		applyPendingTransition();
		draw();
	}
}

void Game::update()
{
	// Retrieve input 
	scanKeys();
	u32 keysHeld = keysHeld();
	u32 keysDown = keysDown();
	u32 keysUp = keysUp();

	if (currentState)
	{
		currentState->update(keysHeld, keysDown, keysUp);
	}
}

void Game::draw()
{
	if (currentState) 
	{
        currentState->renderMain();
        currentState->renderSub();
    }
}

void Game::transitionTo(GameStateType newState)
{
    pendingState = newState;
    transitionRequested = true;
}

void Game::applyPendingTransition()
{
    if (!transitionRequested) 
	{
		return;
	}
    
	transitionRequested = false;

    if (currentState)
	{
		exitState(*currentState);
	}

    currentState = createState(pendingState);

    if (currentState)
	{
		enterState(*currentState);
	}
}

unique_ptr<State> Game::createState(GameStateType state)
{
	switch (state)
	{
		case GameStateType::TitleScreen:
			break;
		case GameStateType::SelectSave:
			break;
		case GameStateType::Gameplay:
			break;
		case GameStateType::PauseScreen:
			break;
		default:
			return nullptr;
			break;
	}
}

void Game::exitState(State& state)
{
    state.onExit();
}

void Game::enterState(State& state)
{
    state.onEnter();
}