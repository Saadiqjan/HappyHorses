/* Author: Saadiq Shahsamand
 * Creation Date: Aug 1, 2026
 * Modified Date: Aug 5, 2026
 * Filename: SpriteManager.cpp
 * Project Name: HappyHorses
 * Description: Keep track of allocated sprites
 */

#include "SpriteManager.h"
#include <algorithm>

using std;

SpriteManager::SpriteManager(OamState* oam)
    : oam(oam), oamMgr(oam)
{
}

int SpriteManager::loadPalette(const void* paletteData, size_t lengthBytes)
{
    int slot = nextPaletteSlot++;

    u16* dest = (oam == &oamMain)
        ? SPRITE_PALETTE
        : SPRITE_PALETTE_SUB;

    dmaCopyHalfWords(SPRITE_DMA_CHANNEL, paletteData, dest, lengthBytes);

    return slot;
}

Sprite* SpriteManager::createSprite(const SpriteConfig& cfgIn)
{
    SpriteConfig cfg = cfgIn;
    cfg.oam = oam;
    cfg.spriteId = oamMgr.allocate();
    if (cfg.spriteId == -1) return nullptr;

    auto sprite = std::make_unique<Sprite>();
    sprite->init(cfg);

    sprites.push_back(std::move(sprite));
    return sprites.back().get();
}

MetaSprite* SpriteManager::createMetaSprite()
{
    auto meta = std::make_unique<MetaSprite>();
    metaSprites.push_back(std::move(meta));
    return metaSprites.back().get();
}

void SpriteManager::destroySprite(Sprite* target)
{
    auto it = find_if(sprites.begin(), sprites.end(), [target](const unique_ptr<Sprite>& s) { return s.get() == target; });

    if (it != sprites.end())
    {
        oamMgr.free((*it)->spriteId());
        sprites.erase(it);
    }
}

void SpriteManager::destroyMetaSprite(MetaSprite* target)
{
    auto it = std::find_if(metaSprites.begin(), metaSprites.end(),
        [target](const std::unique_ptr<MetaSprite>& m) { return m.get() == target; });

    if (it != metaSprites.end())
    {
        metaSprites.erase(it);
    }
}

void SpriteManager::updateAndDraw()
{
    for (auto& s : sprites) 
    {
        s->draw();
    }

    for (auto& m : metaSprites) 
    {
        m->draw();
    }

    oamUpdate(oam);
}

void SpriteManager::clear()
{
    sprites.clear();
    metaSprites.clear();
    oamMgr = OamManager(oam);
}

OamManager& SpriteManager::getOamManager()
{
    return oamMgr;
}

OamState* SpriteManager::getOamState()
{
    return oam;
}