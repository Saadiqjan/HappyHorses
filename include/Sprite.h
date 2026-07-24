/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 22, 2026
 * Filename: Sprite.h
 * Project Name: HappyHorses
 * Description: Header file for graphics manager
 */

#pragma once

class Sprite {
    public:
        Sprite();

        void init(OamState* oam, SpriteSize size, SpriteColorFormat colorFormat);

        void setGraphics(const void* tiles, int tilesLen);
        void setPosition(int x, int y);
        void setVisible(bool visible);
        void rotate(int angle);

        void update();
    private:
        OamState* oam;

        int spriteId;

        int x;
        int y;

        SpriteSize size;
        SpriteColorFormat colorFormat;

        u16* gfx;
};