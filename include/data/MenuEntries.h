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
#include "../state/GameStateType.h"
#include <vector>

using namespace std;

inline const vector<MenuEntry> mainMenuEntries = {
    { "New game", btnCfgNewGame, 96, 24, GameStateType::Gameplay },
    { "Continue", btnCfgContinue, 96, 80, GameStateType::Gameplay },
    { "Settings", btnCfgSettings, 96, 136, GameStateType::Settings }
};

inline const vector<MenuEntry> saveMenuEntries = {
    { "Save 1", btnCfgSave1, 96, 24, GameStateType::Gameplay },
    { "Save 2", btnCfgSave2, 96, 80, GameStateType::Gameplay },
    { "Save 3", btnCfgSave3, 96, 136, GameStateType::Gameplay }
};