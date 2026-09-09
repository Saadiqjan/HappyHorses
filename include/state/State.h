/* Author: Saadiq Shahsamand
 * Creation Date: Aug 25, 2026
 * Modified Date: Aug 25, 2026
 * Filename: State.h
 * Project Name: HappyHorses
 * Description: for keeping parent class of state objects
 */

#pragma once

#include <nds.h>

#include "../core/SpriteManager.h"
#include "../core/TextLayer.h"
#include "../core/GraphicsManager.h"
#include "../state/GameStateType.h"
#include <optional>

using namespace std;

class State {
    public:
        virtual ~State() = default;

        virtual void onEnter() {}
        virtual void onExit() {}
        virtual void onPause() {}
        virtual void onResume() {}

        virtual std::optional<GameStateType> update(u32 keysHeld, u32 keysDown, u32 keysUp) = 0;
        virtual void renderMain() {}
        virtual void renderSub() {}
};