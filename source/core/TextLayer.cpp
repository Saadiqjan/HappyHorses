/* Author: Saadiq Shahsamand
 * Creation Date: Aug 7, 2026
 * Modified Date: Aug 8, 2026
 * Filename: TextLayer.cpp
 * Project Name: HappyHorses
 * Description: create a tilemap background to display text anywhere on the screen
 */

#include "core/TextLayer.h"

TextLayer::TextLayer()
    : mapBuffer(nullptr), mapWidthTiles(0), firstChar(' ')
{
}

TextLayer::TextLayer(u16* mapBuffer, int mapWidthTiles, char firstChar)
    : mapBuffer(mapBuffer), mapWidthTiles(mapWidthTiles), firstChar(firstChar)
{
}

void TextLayer::drawText(int tileX, int tileY, const std::string& text)
{
    for (size_t i = 0; i < text.size(); ++i)
    {
        int tileIndex = text[i] - firstChar;
        mapBuffer[tileY * mapWidthTiles + (tileX + i)] = tileIndex;
    }
}

void TextLayer::drawTextCentered(int pixelBoxX, int pixelBoxY, int pixelBoxW, int pixelBoxH, const std::string& text)
{
    int textPxWidth = (int)text.size() * TILE_PX;

    int px = pixelBoxX + (pixelBoxW - textPxWidth) / 2;
    int py = pixelBoxY + (pixelBoxH - TILE_PX) / 2;

    int tileX = px / TILE_PX;
    int tileY = py / TILE_PX;

    drawText(tileX, tileY, text);
}

void TextLayer::clearRow(int tileY, int startTileX, int lengthTiles)
{
    for (int i = 0; i < lengthTiles; ++i)
        mapBuffer[tileY * mapWidthTiles + (startTileX + i)] = 0;
}

void TextLayer::setMapBuffer(u16* mapBuffer)
{
    this->mapBuffer = mapBuffer;
}

void TextLayer::setMapWidthTiles(int mapWidthTiles)
{
    this->mapWidthTiles = mapWidthTiles;
}

void TextLayer::setFirstChar(char firstChar)
{
    this->firstChar = firstChar;
}