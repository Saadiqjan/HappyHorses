/* Author: Saadiq Shahsamand
 * Creation Date: Aug 26, 2026
 * Modified Date: Aug 26, 2026
 * Filename: ButtonConfigs.h
 * Project Name: HappyHorses
 * Description: Store preset button configurations
 */

#pragma once

#include <nds.h>
#include "../graphics/Sprite.h"

#include "menuButtonSheet.h"

// Main menu buttons
inline const SpriteConfig btnCfgNewGame = {
    .paletteIdx  = 0,
    .priority    = OBJPRIORITY_0,
    .size        = SpriteSize_64x32,
    .colorFormat = SpriteColorFormat_16Color,
    .tiles       = menuButtonSheetTiles,
    .tileLength  = menuButtonSheetTilesLen,
    .frameCount  = 2,
};

inline const SpriteConfig btnCfgContinue = {
    .paletteIdx  = 0,
    .priority    = OBJPRIORITY_0,
    .size        = SpriteSize_64x32,
    .colorFormat = SpriteColorFormat_16Color,
    .tiles       = menuButtonSheetTiles,
    .tileLength  = menuButtonSheetTilesLen,
    .frameCount  = 2,
};

inline const SpriteConfig btnCfgSettings = {
    .paletteIdx  = 0,
    .priority    = OBJPRIORITY_0,
    .size        = SpriteSize_64x32,
    .colorFormat = SpriteColorFormat_16Color,
    .tiles       = menuButtonSheetTiles,
    .tileLength  = menuButtonSheetTilesLen,
    .frameCount  = 2,
};

// Save select buttons
inline const SpriteConfig btnCfgSave1 = {
    .paletteIdx  = 0,
    .priority    = OBJPRIORITY_0,
    .size        = SpriteSize_64x32,
    .colorFormat = SpriteColorFormat_16Color,
    .tiles       = menuButtonSheetTiles,
    .tileLength  = menuButtonSheetTilesLen,
    .frameCount  = 2,
};

inline const SpriteConfig btnCfgSave2 = {
    .paletteIdx  = 0,
    .priority    = OBJPRIORITY_0,
    .size        = SpriteSize_64x32,
    .colorFormat = SpriteColorFormat_16Color,
    .tiles       = menuButtonSheetTiles,
    .tileLength  = menuButtonSheetTilesLen,
    .frameCount  = 2,
};

inline const SpriteConfig btnCfgSave3 = {
    .paletteIdx  = 0,
    .priority    = OBJPRIORITY_0,
    .size        = SpriteSize_64x32,
    .colorFormat = SpriteColorFormat_16Color,
    .tiles       = menuButtonSheetTiles,
    .tileLength  = menuButtonSheetTilesLen,
    .frameCount  = 2,
};