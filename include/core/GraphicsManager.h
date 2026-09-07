/* Author: Saadiq Shahsamand
 * Creation Date: Jul 21, 2026
 * Modified Date: Aug 17, 2026
 * Filename: GraphicsManager.h
 * Project Name: HappyHorses
 * Description: Header file for graphics manager
 */

#pragma once

#include <nds.h>
#include <array>

using namespace std;

class GraphicsManager {
    public:
        void init();
        void update();

        void loadTitleScreen();
        void unloadTitleScreen();

        int bgId(bool sub, int layer) const;

        void clearBitmapLayer(bool sub, int layer, int widthPx, int heightPx, int bytesPerPixel);
        void clearTiledLayer(bool sub, int layer, int mapWidthTiles, int mapHeightTiles);
    private:
        void initVideo();
        void initBackgrounds();
        void initSprites();
        
        array<int, 4> bgIdsMain{ -1, -1, -1, -1 };
        array<int, 4> bgIdsSub{ -1, -1, -1, -1 };

        static const int DMA_CHANNEL = 3;
};