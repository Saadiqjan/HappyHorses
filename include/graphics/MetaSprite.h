/* Author: Saadiq Shahsamand
 * Creation Date: Jul 31, 2026
 * Modified Date: Aug 6, 2026
 * Filename: MetaSprite.h
 * Project Name: HappyHorses
 * Description: Header file for meta sprite
 */

#pragma once
#include "Sprite.h"
#include "OamManager.h"
#include <vector>

using namespace std;

struct SpritePart
{
    Sprite sprite;
    int offsetX, offsetY;
};

class MetaSprite {
    public:
        bool addPart(OamManager& mgr, const SpriteConfig& cfg, int offsetX, int offsetY);

        void setPosition(int x, int y);
        void setFrame(int frame);
        void setVisible(bool visible);
        void setFlip(bool h, bool v);
        void draw();
    private:
        vector<SpritePart> parts;
        int posX = 0, posY = 0;
};
