#include <nds.h>
#include <maxmod9.h>
#include <assert.h>

#include "titleScreen.h"

static const int DMA_CHANNEL = 3;

void initVideo();
void initBackgrounds();
void displayMenuBackgrounds();

int main(void)
{
	powerOn(POWER_ALL_2D);

	initVideo();
	initBackgrounds();

	displayMenuBackgrounds();

	for (;;)
		;

	return 0;
}

void initVideo()
{
	// Allocate VRAM
    vramSetPrimaryBanks(
    	VRAM_A_MAIN_BG_0x06000000,
    	VRAM_B_MAIN_BG_0x06020000,
    	VRAM_C_SUB_BG_0x06200000,
    	VRAM_D_LCD
	);

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

void initBackgrounds()
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

void displayMenuBackgrounds()
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
        titleScreenPal,
        BG_PALETTE_SUB,
        titleScreenPalLen
    );

    // Bottom screen
    dmaCopyHalfWords(
        DMA_CHANNEL,
        titleScreenBitmap,
        (uint16*)BG_BMP_RAM_SUB(0),
        titleScreenBitmapLen
    );
}
