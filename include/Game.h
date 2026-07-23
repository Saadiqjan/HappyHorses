/* Author: Saadiq Shahsamand
 * Creation Date: Jul 19, 2026
 * Modified Date: Jul 21, 2026
 * Filename: Game.h
 * Project Name: HappyHorses
 * Description: Header file for game object
 */

#pragma once

#include "GraphicsManager.h"

class Game {
	public:
		void init();
		void run();
	private:
		void update();
		void draw();

		GraphicsManager graphics;
};