/* Author: Saadiq Shahsamand
 * Creation Date: Aug 1, 2026
 * Modified Date: Aug 6, 2026
 * Filename: SpriteManager.cpp
 * Project Name: HappyHorses
 * Description: Keep track of allocated sprites
 */

#include "core/SpriteManager.h"
#include <algorithm>

using namespace std;

SpriteManager::SpriteManager(OamState* oam)
    : oam(oam), oamMgr(oam)
{
}

int SpriteManager::loadPalette(const void* paletteData, size_t lengthBytes, SpriteColorFormat format)
{
    if (format == SpriteColorFormat_256Color)
    {
        if (loaded256Shared_ && data256Shared_ == paletteData)
            return 0;

        u16* dest = (oam == &oamMain) ? SPRITE_PALETTE : SPRITE_PALETTE_SUB;
        dmaCopyHalfWords(Sprite::SPRITE_DMA_CHANNEL, paletteData, dest, lengthBytes);

        data256Shared_ = paletteData;
        loaded256Shared_ = true;
        return 0;
    }
    else 
    {
        for (int i = 0; i < MAX_16COLOR_SLOTS; ++i)
            if (slots16_[i].used && slots16_[i].data == paletteData)
                return i;

        for (int i = 0; i < MAX_16COLOR_SLOTS; ++i)
        {
            if (!slots16_[i].used)
            {
                u16* base = (oam == &oamMain) ? SPRITE_PALETTE : SPRITE_PALETTE_SUB;
                u16* dest = base + (i * 16);
                dmaCopyHalfWords(Sprite::SPRITE_DMA_CHANNEL, paletteData, dest, lengthBytes);

                slots16_[i] = { paletteData, true };
                return i;
            }
        }
        return -1;
    }
}

void SpriteManager::freePalette(int slot, SpriteColorFormat format)
{
    if (format == SpriteColorFormat_256Color)
    {
        loaded256Shared_ = false;
        data256Shared_ = nullptr;
    }
    else if (slot >= 0 && slot < MAX_16COLOR_SLOTS)
    {
        slots16_[slot] = {};
    }
}

void SpriteManager::clearPalettes()
{
    for (auto& s : slots16_) s = {};
    loaded256Shared_ = false;
    data256Shared_ = nullptr;
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
        oamMgr.free((*it)->getSpriteId());
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
    clearPalettes();
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