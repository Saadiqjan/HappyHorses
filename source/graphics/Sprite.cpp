/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 31, 2026
 * Filename: Sprite.cpp
 * Project Name: HappyHorses
 * Description: Sprite wrapper class
 */

#include "graphics/Sprite.h"
#include <utility>

Sprite::Sprite() = default;

Sprite::~Sprite()
{
    unload();
}

Sprite::Sprite(Sprite&& other) noexcept
{
    *this = std::move(other);
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
    if (this != &other)
    {
        unload();

        oam         = other.oam;
        spriteId    = other.spriteId;
        affineId    = other.affineId;
        paletteIdx  = other.paletteIdx;
        priority    = other.priority;
        posX = other.posX; 
        posY = other.posY;
        size        = other.size;
        colorFormat = other.colorFormat;
        affine      = other.affine;
        hidden      = other.hidden;
        doubleSize  = other.doubleSize;
        flipHor     = other.flipHor;
        flipVer     = other.flipVer;
        mosaic      = other.mosaic;
        angle       = other.angle;
        scaleX      = other.scaleX;
        scaleY      = other.scaleY;
        frameGfx    = other.frameGfx;
        frameSizeBytes  = other.frameSizeBytes;
        numFrames       = other.numFrames;
        currentFrame    = other.currentFrame;

        other.frameGfx.clear();
        other.oam = nullptr;
    }
    return *this;
}

void Sprite::init(const SpriteConfig& cfg)
{
    unload();

    oam         = cfg.oam;
    spriteId    = cfg.spriteId;
    affineId    = cfg.affineId;
    affine      = cfg.affine;
    paletteIdx  = cfg.paletteIdx;
    priority    = cfg.priority;
    hidden      = cfg.hidden;
    doubleSize  = cfg.doubleSize;
    flipHor     = cfg.flipHor;
    flipVer     = cfg.flipVer;
    mosaic      = cfg.mosaic;
    size        = cfg.size;
    colorFormat = cfg.colorFormat;

    numFrames      = cfg.frameCount > 0 ? cfg.frameCount : 1;
    frameSizeBytes = cfg.tileLength / numFrames;
    currentFrame   = 0;

    frameGfx.resize(numFrames);
    for (int i = 0; i < numFrames; ++i)
    {
        frameGfx[i] = oamAllocateGfx(oam, size, colorFormat);   // one full-size block per frame
        const u8* src = static_cast<const u8*>(cfg.tiles) + (i * frameSizeBytes);
        dmaCopyHalfWords(SPRITE_DMA_CHANNEL, src, frameGfx[i], frameSizeBytes);
    }
}

void Sprite::unload()
{
    for (void* g : frameGfx)
    {
        if (g) 
        {
            oamFreeGfx(oam, g);
        }
    }

    frameGfx.clear();
}

void Sprite::draw()
{
    if (!oam || frameGfx.empty()) return; 

    if (affine)
    {
        oamRotateScale(oam, affineId, scaleX, scaleY, angle);
    }

    oamSet(oam,
           spriteId,
           posX, posY,
           priority,
           paletteIdx,
           size, colorFormat,
           frameGfx[currentFrame],
           affineId,
           doubleSize,
           hidden,
           flipHor, flipVer,
           mosaic);
}

void Sprite::setPosition(int x, int y)
{
    posX = x;
    posY = y;
}

void Sprite::move(int dx, int dy)
{
    posX += dx;
    posY += dy;
}

void Sprite::setVisible(bool visible)
{
    hidden = !visible;
}

void Sprite::setFlip(bool h, bool v)
{
    flipHor = h;
    flipVer = v;
}

void Sprite::toggleFlipH()
{
    flipHor = !flipHor;
}

void Sprite::toggleFlipV()
{
    flipVer = !flipVer;
}

void Sprite::setFrame(int frame)
{
    if (frame < 0 || frame >= numFrames) return;
    currentFrame = frame;
}

void Sprite::rotate(int newAngle)
{
    angle = newAngle;
}

void Sprite::setScale(int newScaleX, int newScaleY)
{
    scaleX = newScaleX;
    scaleY = newScaleY;
}