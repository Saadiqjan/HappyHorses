/* Author: Saadiq Shahsamand
 * Creation Date: Jul 21, 2026
 * Modified Date: Aug 17, 2026
 * Filename: GraphicsManager.cpp
 * Project Name: HappyHorses
 * Description: Manages setting up and loading graphics
 */

#include "core/GraphicsManager.h"

#include <nds.h>

#include "titleScreen.h"
#include "titleScreenSub.h"

void GraphicsManager::init()
{
    initVideo();
    initBackgrounds();
    initSprites();
}

void GraphicsManager::initVideo()
{
    // Allocate VRAM
    vramSetPrimaryBanks(
    	VRAM_A_MAIN_BG_0x06000000,
    	VRAM_B_MAIN_BG_0x06020000,
    	VRAM_C_SUB_BG_0x06200000,
    	VRAM_D_LCD
	);

	// Allocate VRAM bank E for sprites
	vramSetBankE(VRAM_E_MAIN_SPRITE);

    // Main screen (top)
    videoSetMode(
        MODE_5_2D |
        DISPLAY_BG3_ACTIVE |
        DISPLAY_SPR_ACTIVE |
        DISPLAY_SPR_1D
    );

    // Sub screen (bottom)
    videoSetModeSub(
        MODE_5_2D |
        DISPLAY_BG3_ACTIVE |
        DISPLAY_SPR_ACTIVE |
        DISPLAY_SPR_1D
    );
}

void GraphicsManager::initBackgrounds()
{
    bgIdsMain[3] = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
    bgSetPriority(bgIdsMain[3], 3);

    bgIdsSub[3] = bgInitSub(3, BgType_Bmp8, BgSize_B8_256x256, 0, 0);
    bgSetPriority(bgIdsSub[3], 3);
}

void GraphicsManager::initSprites()
{
    oamInit(&oamMain, SpriteMapping_1D_64, false);
    
    update();
}

void GraphicsManager::update()
{
   oamUpdate(&oamMain);
}

void GraphicsManager::loadTitleScreen()
{
    // Copy palette for main BG
    dmaCopy(
        titleScreenPal,
        BG_PALETTE,
        titleScreenPalLen
    );

    // Top screen
    dmaCopyHalfWords(
        DMA_CHANNEL,
        titleScreenBitmap,
        BG_BMP_RAM(0),
        titleScreenBitmapLen
    );


    // Copy palette for sub BG
    dmaCopy(
        titleScreenSubPal,
        BG_PALETTE_SUB,
        titleScreenSubPalLen
    );

    // Bottom screen
    dmaCopyHalfWords(
        DMA_CHANNEL,
        titleScreenSubBitmap,
        BG_BMP_RAM_SUB(0),
        titleScreenSubBitmapLen
    );
}

void GraphicsManager::unloadTitleScreen()
{
    clearBitmapLayer(false, 3, 256, 192, 1);
    clearBitmapLayer(true, 3, 256, 192, 1);
}

int GraphicsManager::bgId(bool sub, int layer) const
{
    return sub ? bgIdsSub[layer] : bgIdsMain[layer];
}

void GraphicsManager::clearBitmapLayer(bool sub, int layer, int widthPx, int heightPx, int bytesPerPixel)
{
    int id = bgId(sub, layer);
    if (id == -1) return;

    dmaFillWords(0, bgGetGfxPtr(id), widthPx * heightPx * bytesPerPixel);
}

void GraphicsManager::clearTiledLayer(bool sub, int layer, int mapWidthTiles, int mapHeightTiles)
{
    int id = bgId(sub, layer);
    if (id == -1) return;

    u16* map = (u16*)bgGetMapPtr(id);
    dmaFillWords(0, map, mapWidthTiles * mapHeightTiles * sizeof(u16));
}