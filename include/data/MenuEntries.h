/* Author: Saadiq Shahsamand
 * Creation Date: Aug 27, 2026
 * Modified Date: Aug 27, 2026
 * Filename: MenuEntries.h
 * Project Name: HappyHorses
 * Description: Store preset menu entries for different menus
 */

#pragma once

#include "ButtonConfigs.h"
#include "MenuEntry.h"
#include "../state/GameState.h"
#include <vector>

using namespace std;

inline const vector<MenuEntry> mainMenuEntries = {
    { "New game", btnCfgNewGame, GameState::Gameplay },
    { "Continue", btnCfgContinue, GameState::Gameplay },
    { "Settings", btnCfgSettings, GameState::settingsS }
};

inline const vector<MenuEntry> saveMenuEntries = {
    { "Save 1", btnCfgSave1, GameState::Gameplay },
    { "Save 2", btnCfgSave2, GameState::Gameplay },
    { "Save 3", btnCfgSave3, GameState::Gameplay }
};