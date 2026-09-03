/* Author: Saadiq Shahsamand
 * Creation Date: Sep 2, 2026
 * Modified Date: Sep 2, 2026
 * Filename: TitleState.h
 * Project Name: HappyHorses
 * Description: header for titlestate
 */

#pragma once

#include "State.h"
#include "../ui/Menu.h"
#include "../data/MenuEntries.h"

class TitleState : public State {
    public:
        TitleState(SpriteManager* spriteMgr, TextLayer* textLayer, GraphicsManager* gfxMgr);

        void onEnter() override;
        void onExit() override;
        void update(u32 keysHeld, u32 keysDown, u32 keysUp) override;
        void renderTop() override;
        void renderBottom() override;
    private:
        Menu menu;
        SpriteManager* spriteMgr;
        TextLayer* textLayer;
        GraphicsManager* gfxMgr;
};