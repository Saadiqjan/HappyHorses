/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Aug 17, 2026
 * Filename: Game.cpp
 * Project Name: HappyHorses
 * Description: Game loop will be handled here
 */

#include "Game.h"

#include <nds.h>

Game::Game()
{
	
}

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
	u32 keys_Held = keysHeld();
	u32 keys_Down = keysDown();
	u32 keys_Up = keysUp();

	if (currentState)
	{
		if (auto next = currentState->update(keys_Held, keys_Down, keys_Up))
		{
    		transitionTo(*next);
		}
	}
}

void Game::draw()
{
	if (currentState) 
	{
		spriteMgrMain.updateAndDraw();
		spriteMgrSub.updateAndDraw();
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
			return make_unique<TitleState>(&spriteMgrMain, &textLayer, &graphics);
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

void Game::enterState(State& state)
{
    state.onEnter();
}

void Game::exitState(State& state)
{
    state.onExit();
}