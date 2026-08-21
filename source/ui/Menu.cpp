/* Author: Saadiq Shahsamand
 * Creation Date: Aug 19, 2026
 * Modified Date: Aug 20, 2026
 * Filename: Menu.cpp
 * Project Name: HappyHorses
 * Description: Menu to keep track of menu objects
 */

#include "Menu.h"

Menu::Menu(SpriteManager& mgr, TextLayer& layer)
    : spriteMgr(mgr), textLayer(layer)
{
}

Button& Menu::addButton()
{
    buttons.push_back(std::make_unique<Button>(spriteMgr, textLayer));
    return *buttons.back();
}

void Menu::update(int touchX, int touchY, bool touching, bool justReleased)
{
    lastSelected = -1;

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (!buttons[i]->isLoaded()) continue;

        bool over = buttons[i]->contains(touchX, touchY);
        buttons[i]->setPressed(over && touching);

        if (over && justReleased)
            lastSelected = static_cast<int>(i);
    }
}

void Menu::draw()
{
    for (auto& b : buttons)
        if (b->isLoaded()) b->draw();
}

Button* Menu::selectedButton() const
{
    if (lastSelected < 0 || lastSelected >= (int)buttons.size()) 
    {
        return nullptr;
    }
    
    return buttons[lastSelected].get();
}

void Menu::clear()
{
    buttons.clear();
}