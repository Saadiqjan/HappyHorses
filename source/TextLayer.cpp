/* Author: Saadiq Shahsamand
 * Creation Date: Aug 7, 2026
 * Modified Date: Aug 8, 2026
 * Filename: TextLayer.cpp
 * Project Name: HappyHorses
 * Description: create a tilemap background to display text anywhere on the screen
 */

#include "TextLayer.h"

// TextLayer.cpp
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

void TextLayer::clearRow(int tileY, int startTileX, int lengthTiles)
{
    for (int i = 0; i < lengthTiles; ++i)
        mapBuffer[tileY * mapWidthTiles + (startTileX + i)] = 0;
}