/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 31, 2026
 * Filename: Sprite.cpp
 * Project Name: HappyHorses
 * Description: Sprite wrapper class
 */

#include "Sprite.h"
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
        gfx             = other.gfx;
        frameSizeBytes  = other.frameSizeBytes;
        numFrames        = other.numFrames;
        currentFrame     = other.currentFrame;

        // Prevent the moved-from object from freeing gfx we now own
        other.gfx = nullptr;
        other.oam = nullptr;
    }
    return *this;
}

void Sprite::init(const SpriteConfig& cfg)
{
    unload(); // safety: if re-init'ing an already-loaded sprite, free old gfx first

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

    numFrames       = cfg.frameCount > 0 ? cfg.frameCount : 1;
    frameSizeBytes  = cfg.tileLength / numFrames;
    currentFrame    = 0;

    gfx = oamAllocateGfx(oam, size, colorFormat);

    dmaCopyHalfWords(SPRITE_DMA_CHANNEL,
                      cfg.tiles,
                      gfx,
                      cfg.tileLength);
}

void Sprite::unload()
{
    if (gfx && oam)
    {
        oamFreeGfx(oam, gfx);
    }
    gfx = nullptr;
}

void Sprite::draw()
{
    if (!oam || !gfx) return; // not loaded, nothing to draw

    if (affine)
    {
        oamRotateScale(oam, affineId, scaleX, scaleY, angle);
    }

    u8* frameGfx = static_cast<u8*>(gfx) + (currentFrame * frameSizeBytes);

    oamSet(oam,
           spriteId,
           posX, posY,
           priority,
           paletteIdx,
           size, colorFormat,
           frameGfx,
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