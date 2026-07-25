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
        void setVisible(bool visible);
        void rotate(int angle);

        void draw();
    private:
        OamState* oam;

        int spriteId;

        int x;
        int y;

        SpriteSize size;
        SpriteColorFormat colorFormat;

        u16* gfx;
};