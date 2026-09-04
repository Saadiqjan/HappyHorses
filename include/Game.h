/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Aug 17, 2026
 * Filename: Game.h
 * Project Name: HappyHorses
 * Description: Header file for game object
 */

#pragma once

#include "core/GraphicsManager.h"
#include "core/TextLayer.h"
#include "core/SpriteManager.h"
#include "state/GameStateType.h"
#include "state/State.h"

using namespace std;

class Game {
	public:
		Game();

		void init();
		void run();

		void transitionTo(GameStateType newState);
	private:
		void update();
		void draw();

		void applyPendingTransition();
		unique_ptr<State> createState(GameStateType state);
		void enterState(State& state);
		void exitState(State& state);

		unique_ptr<State> currentState;
    	GameStateType pendingState;
    	bool transitionRequested = false;

		GraphicsManager graphics;
		SpriteManager spriteMgrMain{&oamMain};
		SpriteManager spriteMgrSub{&oamSub};
		TextLayer textLayer;
};