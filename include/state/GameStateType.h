/* Author: Saadiq Shahsamand
 * Creation Date: Aug 12, 2026
 * Modified Date: Aug 12, 2026
 * Filename: GameState.h
 * Project Name: HappyHorses
 * Description: for keeping track of game state
 */

#pragma once
#include <cstdint>

enum class GameState : uint8_t
{
    TitleScreen,
    SelectSave,
    Gameplay,
    PauseScreen,
    Settings
};