/* Author: Saadiq Shahsamand
 * Creation Date: Jul 31, 2026
 * Modified Date: Aug 6, 2026
 * Filename: MetaSprite.cpp
 * Project Name: HappyHorses
 * Description: store a larger sprite made up of smaller sprites
 */

#include "graphics/MetaSprite.h"
#include <nds.h>

using namespace std;

bool MetaSprite::addPart(OamManager& mgr, const SpriteConfig& cfgIn, int offsetX, int offsetY)
{
    SpritePart part;
    part.offsetX = offsetX;
    part.offsetY = offsetY;

    SpriteConfig cfg = cfgIn;
    cfg.oam = mgr.getOam();

    cfg.spriteId = mgr.allocate();
    if (cfg.spriteId == -1) return false;

    part.sprite.init(cfg);
    parts.push_back(std::move(part));
    return true;
}

void MetaSprite::setPosition(int x, int y)
{
    posX = x; posY = y;
    for (auto& part : parts)
    {
        part.sprite.setPosition(posX + part.offsetX, posY + part.offsetY);
    }
}

void MetaSprite::setFrame(int frame)
{
    for (auto& part : parts) 
    {
        part.sprite.setFrame(frame);
    }
}

void MetaSprite::setVisible(bool visible)
{
    for (auto& part : parts) 
    {
        part.sprite.setVisible(visible);
    }
}

void MetaSprite::draw()
{
    for (auto& part : parts) 
    {
        part.sprite.draw();
    }
}