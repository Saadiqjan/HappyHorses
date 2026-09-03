/* Author: Saadiq Shahsamand
 * Creation Date: Aug 25, 2026
 * Modified Date: Aug 25, 2026
 * Filename: MenuState.h
 * Project Name: HappyHorses
 * Description: header for menustate
 */

#pragma once

#include "State.h"

class MenuState : public State {
    public:
        MenuState(std::vector<MenuEntry> entries,
                  SpriteManager* spriteMgr,
                  TextLayer* textLayer,
                  GraphicsManager* gfxMgr);

        void onEnter() override;
        void onExit() override;
        void update(u32 keysHeld, u32 keysDown, u32 keysUp) override;
    private:
        std::vector<MenuEntry> entries;
        Menu menu;
        SpriteManager* spriteMgr;
        TextLayer* textLayer;
        GraphicsManager* gfxMgr;
};