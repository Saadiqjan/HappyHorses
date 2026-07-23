/* Author: Saadiq Shahsamand
 * Creation Date: Jul 21, 2026
 * Modified Date: Jul 21, 2026
 * Filename: GraphicsManager.cpp
 * Project Name: HappyHorses
 * Description: Manages setting up and loading graphics
 */

#include "GraphicsManager.h"

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
    // Top screen background (BG3)
    REG_BG3CNT = BG_BMP8_256x256 |
                 BG_BMP_BASE(0) |
                 BG_PRIORITY(3);

    // Identity transformation matrix
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

    // Position at top-left
    REG_BG3X = 0;
    REG_BG3Y = 0;


    // Bottom screen background (BG3)
    REG_BG3CNT_SUB = BG_BMP8_256x256 |
                     BG_BMP_BASE(0) |
                     BG_PRIORITY(3);

    // Identity transformation matrix
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;

    // Position at top-left
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
}

void GraphicsManager::initSprites()
{
    for (int i = 0; i < SPRITE_COUNT; i++) {
        oamMain->oamBuffer[i].attribute[0] = ATTR0_DISABLED;
        oamMain->oamBuffer[i].attribute[1] = 0;
        oamMain->oamBuffer[i].attribute[2] = 0;
    }
    for (int i = 0; i < MATRIX_COUNT; i++) {
        oamMain->matrixBuffer[i].hdx = 1 << 8;
        oamMain->matrixBuffer[i].hdy = 0;
        oamMain->matrixBuffer[i].vdx = 0;
        oamMain->matrixBuffer[i].vdy = 1 << 8;
    }
    
    update(oam);
}

void GraphicsManager::update()
{
    DC_FlushRange(oamMain->oamBuffer, SPRITE_COUNT * sizeof(SpriteEntry));
    dmaCopyHalfWords(SPRITE_DMA_CHANNEL, oamMain->oamBuffer, OAM,
                     SPRITE_COUNT * sizeof(SpriteEntry));
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
        (uint16*)BG_BMP_RAM(0),
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
        (uint16*)BG_BMP_RAM_SUB(0),
        titleScreenSubBitmapLen
    );
}