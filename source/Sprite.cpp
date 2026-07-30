/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 29, 2026
 * Filename: Sprite.cpp
 * Project Name: HappyHorses
 * Description: Sprite wrapper class
 */

#include "Sprite.h"

#include <nds.h>

Sprite::Sprite()
    : oam(nullptr),
      spriteId(-1),
      affineId(-1),
      paletteIdx(0),
      priority(OBJPRIORITY_0),
      x(0),
      y(0),
      size(SpriteSize_32x32),
      colorFormat(SpriteColorFormat_256Color),
      affine(false),
      hidden(false),
      doubleSize(false),
      flipHor(false),
      flipVer(false),
      gfx(nullptr)
{
}

void Sprite::init(OamState* oam,
                  int spriteId,
                  int affineId,
                  bool affine,
                  int paletteIdx,
                  int priority,
                  bool hidden,
                  bool doubleSize,
                  bool flipHor,
                  bool flipVer,
                  bool mosaic,
                  SpriteSize size,
                  SpriteColorFormat colorFormat,
                  const void* tiles,
                  int tileLength)
{
    this->oam = oam;
    this->spriteId = spriteId;
    this->affineId = affineId;
    this->affine = affine;
    this->paletteIdx = paletteIdx;
    this->priority = priority;
    this->hidden = hidden;
    this->doubleSize = doubleSize;
    this->flipHor = flipHor;
    this->flipVer = flipVer;
    this->mosaic = mosaic;
    this->size = size;
    this->colorFormat = colorFormat;

    gfx = oamAllocateGfx(oam, size, colorFormat);

    dmaCopyHalfWords(SPRITE_DMA_CHANNEL, 
                   tiles,
                   gfx,
                   tileLength);
}

void Sprite::draw()
{
    if (affine)
    {
        oamRotateScale(
            &oamMain,
            affineId,
            scaleX,
            scaleY,
            angle
        );
    }

    oamSet(&oamMain,
           spriteId, // Sprite ID
           x, y, // X, Y
           priority, // Priority
           paletteIdx, // Palette index
           size, colorFormat, // Size, format
           gfx,  // Graphics offset
           affineId, // Affine index
           doubleSize, // Double size for affine sprites
           hidden, // Hide
           flipHor, flipVer, // H flip, V flip
           mosaic); // Mosaic
}

void Sprite::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Sprite::setVisible(bool hidden)
{
    this->hidden = hidden;
}

void Sprite::rotate(int angle)
{
    this->angle = angle;
}

void Sprite::setScale(int scaleX, int scaleY)
{
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

void Sprite::flipH()
{
    flipHor = !flipHor;
}

void Sprite::flipV()
{
    flipVer = !flipVer;
}