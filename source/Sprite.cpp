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

void Sprite::draw()
{
    oamSet(&oamMain,
           spriteId, // Sprite ID
           x, y, // X, Y
           0, // Priority
           0, // Palette index
           size, colorFormat, // Size, format
           gfx,  // Graphics offset
           -1, // Affine index (unused in this example)
           false, // Double size for affine sprites
           hidden, // Hide
           flipHor, flipVer, // H flip, V flip
           false); // Mosaic
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

void Sprite::flipH()
{
    flipHor = !flipHor
}

void Sprite::flipV()
{
    flipVer = !flipVer
}

void Sprite::rotate(int angle)
{
    this->angle = angle;
}