/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 25, 2026
 * Filename: Sprite.cpp
 * Project Name: HappyHorses
 * Description: Sprite wrapper class
 */

Sprite::Sprite()
    : oam(nullptr),
      id(0),
      x(0),
      y(0),
      size(SpriteSize_32x32),
      format(SpriteColorFormat_256Color),
      gfx(nullptr)
{
}

void Sprite::init(OamState* oam,
                  int id,
                  SpriteSize size,
                  SpriteColorFormat format,
                  const void* tiles,
                  int tileLength)
{
    this->oam = oam;
    this->id = id;
    this->size = size;
    this->format = format;

    gfx = oamAllocateGfx(oam, size, format);

    dmaCopyHalfWords(SPRITE_DMA_CHANNEL, 
                   tiles,
                   gfx,
                   tilesLength);
}

void Sprite::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}