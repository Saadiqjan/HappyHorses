/* Author: Saadiq Shahsamand
 * Creation Date: Sep 2, 2026
 * Modified Date: Sep 2, 2026
 * Filename: TitleState.cpp
 * Project Name: HappyHorses
 * Description: title state
 */

#include "state/TitleState.h"

#include "../data/MenuEntries.h"

TitleState::TitleState(SpriteManager* spriteMgr, TextLayer* textLayer, GraphicsManager* gfxMgr)
    : spriteMgr(spriteMgr), textLayer(textLayer), gfxMgr(gfxMgr), menu(spriteMgr, textLayer)
{
}

void TitleState::onEnter() 
{
    gfxMgr->loadTitleScreen();

    for (const auto& entry : mainMenuEntries) 
    {
        menu.addButton(entry.label, entry.buttonConfig, spriteMgr, textLayer);
    }    
}

void TitleState::onExit() {
    menu.clear();
    spriteMgr->clear();
    textLayer->clear();
    gfxMgr->unloadTitleScreen();
}

void TitleState::update(u32 keysHeld, u32 keysDown, u32 keysUp) 
{
    touchPosition touch;
    touchRead(&touch);

    menu.update(touch.px, touch.py, keysHeld & KEY_TOUCH, keysUp & KEY_TOUCH);

    if (menu.selectedIndex() >= 0) 
    {
        const MenuEntry& entry = mainMenuEntries[menu.selectedIndex()];
        game->transitionTo(entry.target);
    }
}