/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Aug 17, 2026
 * Filename: Game.h
 * Project Name: HappyHorses
 * Description: Header file for game object
 */

#pragma once

#include "GraphicsManager.h"
#include "GameState.h"

class Game {
	public:
		void init();
		void run();

		void transitionTo(GameState newState);
	private:
		void update();
		void draw();

		void applyPendingTransition();

		void enterState(GameState state);
		void exitState(GameState state);

		GameState currentState = GameState::TitleScreen;
    	GameState pendingState = GameState::TitleScreen;
    	bool transitionRequested = false;

		GraphicsManager graphics;
};