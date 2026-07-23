/* Author: Saadiq Shahsamand
 * Creation Date: Jul 21, 2026
 * Modified Date: Jul 21, 2026
 * Filename: GraphicsManager.h
 * Project Name: HappyHorses
 * Description: Header file for graphics manager
 */

#pragma once

class GraphicsManager {
    public:
        void init();
        void update();

        void loadTitleScreen();
    private:
        void initVideo();
        void initBackgrounds();
        void initSprites(OAMTable *oam);

        static const int DMA_CHANNEL = 3;
};