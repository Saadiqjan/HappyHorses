/* Author: Saadiq Shahsamand
 * Creation Date: Aug 7, 2026
 * Modified Date: Aug 8, 2026
 * Filename: TextLayer.h
 * Project Name: HappyHorses
 * Description: Header file for text layer
 */

#pragma once
#include <nds.h>
#include <string>

class TextLayer
{
public:
    TextLayer(u16* mapBuffer, int mapWidthTiles, char firstChar = ' ');

    void drawText(int tileX, int tileY, const std::string& text);
    void drawTextCentered(int pixelBoxX, int pixelBoxY, int pixelBoxW, int pixelBoxH, const std::string& text);
    void clearRow(int tileY, int startTileX, int lengthTiles);
    void clear();

private:
    u16* mapBuffer;
    int mapWidthTiles;
    char firstChar;
    static constexpr int TILE_PX = 8;
};