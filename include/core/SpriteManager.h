/* Author: Saadiq Shahsamand
 * Creation Date: Aug 1, 2026
 * Modified Date: Aug 6, 2026
 * Filename: SpriteManager.h
 * Project Name: HappyHorses
 * Description: Header file for sprite manager
 */

#pragma once
#include <nds.h>
#include "../graphics/Sprite.h"
#include "../graphics/MetaSprite.h"
#include "OamManager.h"
#include <vector>
#include <memory>

using namespace std;

class SpriteManager {
    public:
        explicit SpriteManager(OamState* oam);

        int loadPalette(const void* paletteData, size_t length, SpriteColorFormat format);
        void freePalette(int slot, SpriteColorFormat format);
        void clearPalettes();

        Sprite* createSprite(const SpriteConfig& cfg);
        MetaSprite* createMetaSprite();

        void destroySprite(Sprite* sprite);
        void destroyMetaSprite(MetaSprite* meta);

        void updateAndDraw();
        void clear();

        OamManager& getOamManager();
        OamState* getOamState();
    private:
        static const int MAX_16COLOR_SLOTS = 16;
        static const int MAX_256COLOR_SLOTS = 16; 

        struct PaletteSlot { const void* data = nullptr; bool used = false; };

        PaletteSlot slots16_[MAX_16COLOR_SLOTS];
        PaletteSlot slots256Ext_[MAX_256COLOR_SLOTS];
        bool loaded256Shared_ = false;
        const void* data256Shared_ = nullptr;

        OamState* oam;
        OamManager oamMgr;

        vector<unique_ptr<Sprite>> sprites;
        vector<unique_ptr<MetaSprite>> metaSprites;

        int nextPaletteSlot = 0;
};