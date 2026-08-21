/* Author: Saadiq Shahsamand
 * Creation Date: Aug 1, 2026
 * Modified Date: Aug 6, 2026
 * Filename: SpriteManager.h
 * Project Name: HappyHorses
 * Description: Header file for sprite manager
 */

#pragma once
#include <nds.h>
#include "Sprite.h"
#include "MetaSprite.h"
#include "OamManager.h"
#include <vector>
#include <memory>

using namespace std;

class SpriteManager {
    public:
        explicit SpriteManager(OamState* oam);

        int loadPalette(const void* paletteData, size_t length);

        Sprite* createSprite(const SpriteConfig& cfg);
        MetaSprite* createMetaSprite();

        void destroySprite(Sprite* sprite);
        void destroyMetaSprite(MetaSprite* meta);

        void updateAndDraw();
        void clear();

        OamManager& getOamManager();
        OamState* getOamState();
    private:
        OamState* oam;
        OamManager oamMgr;

        vector<unique_ptr<Sprite>> sprites;
        vector<unique_ptr<MetaSprite>> metaSprites;

        int nextPaletteSlot = 0;
};