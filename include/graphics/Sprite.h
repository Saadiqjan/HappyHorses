/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Aug 6, 2026
 * Filename: Sprite.h
 * Project Name: HappyHorses
 * Description: Header file for sprites
 */

#pragma once
#include <nds.h>

struct SpriteConfig
{
    OamState* oam         = nullptr;
    int spriteId          = -1;
    int affineId          = -1;
    bool affine           = false;
    int paletteIdx        = 0;
    ObjPriority priority = OBJPRIORITY_0;
    bool hidden           = false;
    bool doubleSize       = false;
    bool flipHor          = false;
    bool flipVer          = false;
    bool mosaic           = false;
    SpriteSize size               = SpriteSize_32x32;
    SpriteColorFormat colorFormat = SpriteColorFormat_256Color;

    const void* paletteData = nullptr;
    int paletteLength       = 0;

    const void* tiles       = nullptr;
    int tileLength          = 0;
    int frameCount          = 1;
};

inline void spriteSizePixels(SpriteSize size, int& outW, int& outH)
{
    switch (size)
    {
        case SpriteSize_8x8:   outW = 8;  outH = 8;  break;
        case SpriteSize_16x16: outW = 16; outH = 16; break;
        case SpriteSize_32x32: outW = 32; outH = 32; break;
        case SpriteSize_64x64: outW = 64; outH = 64; break;
        case SpriteSize_16x8:  outW = 16; outH = 8;  break;
        case SpriteSize_32x8:  outW = 32; outH = 8;  break;
        case SpriteSize_32x16: outW = 32; outH = 16; break;
        case SpriteSize_64x32: outW = 64; outH = 32; break;
        case SpriteSize_8x16:  outW = 8;  outH = 16; break;
        case SpriteSize_8x32:  outW = 8;  outH = 32; break;
        case SpriteSize_16x32: outW = 16; outH = 32; break;
        case SpriteSize_32x64: outW = 32; outH = 64; break;
        default: outW = 0; outH = 0; break;
    }
}

class Sprite
{
public:
    static const int SPRITE_DMA_CHANNEL = 3;

    Sprite();
    ~Sprite();

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;

    Sprite(Sprite&& other) noexcept;
    Sprite& operator=(Sprite&& other) noexcept;

    void init(const SpriteConfig& cfg);
    void unload();

    void draw();

    void setPosition(int x, int y);
    void move(int dx, int dy);

    void setVisible(bool visible);
    void setFlip(bool h, bool v);
    void toggleFlipH();
    void toggleFlipV();

    void setFrame(int frame);
    int  frame() const { return currentFrame; }
    int  frameCount() const { return numFrames; }

    void rotate(int angle);
    void setScale(int scaleX, int scaleY);

    int x() const { return posX; }
    int y() const { return posY; }
    bool isLoaded() const { return gfx != nullptr; }

    int getSpriteId() const { return spriteId; }
private:
    OamState* oam   = nullptr;
    int spriteId    = -1;
    int affineId    = -1;
    int paletteIdx  = 0;
    ObjPriority priority = OBJPRIORITY_0;

    int posX = 0, posY = 0;

    SpriteSize size               = SpriteSize_32x32;
    SpriteColorFormat colorFormat = SpriteColorFormat_256Color;

    bool affine     = false;
    bool hidden     = false;
    bool doubleSize = false;
    bool flipHor    = false;
    bool flipVer    = false;
    bool mosaic     = false;

    int angle   = 0;
    int scaleX  = 1 << 8; // identity scale, 20.12-ish fixed point (verify against oamRotateScale)
    int scaleY  = 1 << 8;

    void* gfx              = nullptr;
    int   frameSizeBytes   = 0;
    int   numFrames         = 1;
    int   currentFrame      = 0;
};