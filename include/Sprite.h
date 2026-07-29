/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 23, 2026
 * Filename: Sprite.h
 * Project Name: HappyHorses
 * Description: Header file for sprites
 */

#pragma once

class Sprite {
    public:
        static const int SPRITE_DMA_CHANNEL = 3;

        Sprite();

        init(OamState* oam, int id, SpriteSize size, SpriteColorFormat format, const void* tiles, int tileLength);

        void setPosition(int x, int y);
        void setVisible(bool hidden);
        void rotate(int angle);
        void setScale(int scaleX, int scaleY);
        void flipH();
        void flipV();

        void draw();
    private:
        OamState* oam;

        int spriteId;
        int affineId;
        int paletteIdx;
        int priority;

        int x;
        int y;
        int scaleX = 1 << 8;
        int scaleY = 1 << 8;

        SpriteSize size;
        SpriteColorFormat colorFormat;

        bool affine;
        bool hidden;
        bool doubleSize;
        bool flipHor;
        bool flipVer;
        bool mosaic;
        int angle = 0;

        u16* gfx;
};