/* Author: Saadiq Shahsamand
 * Creation Date: Aug 19, 2026
 * Modified Date: Aug 20, 2026
 * Filename: Menu.h
 * Project Name: HappyHorses
 * Description: header file for menu
 */

#pragma once

#include <nds.h>
#include <vector>

#include "../ui/Button.h"

using namespace std;

class Menu {
    public:
        Menu(SpriteManager& spriteMgr, TextLayer& textLayer);

        Button& addButton();

        void update(int touchX, int touchY, bool touching, bool justReleased);
        void draw();

        int selectedIndex() const { return lastSelected; }
        Button* selectedButton() const;
        
        void clear();
    private:
        SpriteManager& spriteMgr;
        TextLayer& textLayer;

        vector<unique_ptr<Button>> buttons;
        int lastSelected = -1;
};