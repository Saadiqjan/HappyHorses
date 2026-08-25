/* Author: Saadiq Shahsamand
 * Creation Date: Aug 25, 2026
 * Modified Date: Aug 25, 2026
 * Filename: MenuState.cpp
 * Project Name: HappyHorses
 * Description: blueprint for menu states
 */

#include "MenuState.h"

MenuState::MenuState(std::vector<MenuEntry> entries, SpriteManager* spriteMgr, TextLayer* textLayer, GraphicsManager* gfxMgr)
    : entries(entries), spriteMgr(spriteMgr), textLayer(textLayer), gfxMgr(gfxMgr)
{

}

void Menu::onEnter()
{
    gfxMgr->loadTitleScreen();

    for (const auto& entry : entries) 
    {
        Button* btn = menu.addButton(entry.label, entry.buttonConfig, spriteMgr, textLayer);
    }
}

void Menu::onExit()
{
    menu.clear();
    spriteMgr->clear();
    textLayer->clear();
    gfxMgr->unloadMenuScreen();
}

void MenuState::update(u32 keysHeld, u32 keysDown, u32 keysUp) 
{
    touchPosition touch;
    touchRead(&touch);
    bool touching = keysHeld & KEY_TOUCH;
    bool justReleased = keysUp & KEY_TOUCH;

    menu.update(touch.px, touch.py, touching, justReleased);

    if (menu.selectedIndex() >= 0) 
    {
        GameStateType target = entries[menu.selectedIndex()].target;
        game->transitionTo(target);
    }
}