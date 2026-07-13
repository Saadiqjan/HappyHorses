#include <nds.h>
#include <maxmod9.h>
#include <assert.h>

void initVideo();
void initBackgrounds();

int main(void)
{
	powerOn(POWER_ALL_2D);

	for (;;)
		;

	return 0;
}

void initVideo()
{
	vramSetPrimaryBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_MAIN_BG_0x06020000,
                      VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD);

  /*  Set the video mode on the main screen. */
  videoSetMode(MODE_5_2D |           // Set the graphics mode to Mode 5
               DISPLAY_BG2_ACTIVE |  // Enable BG2 for display
               DISPLAY_BG3_ACTIVE);  // Enable BG3 for display

  /*  Set the video mode on the sub screen. */
  videoSetModeSub(MODE_5_2D |           // Set the graphics mode to Mode 5
                  DISPLAY_BG3_ACTIVE);  // Enable BG3 for display
}

void initBackgrounds()
{

}
