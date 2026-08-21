/* Author: Saadiq Shahsamand
 * Creation Date: Aug 17, 2026
 * Modified Date: Aug 17, 2026
 * Filename: Player.h
 * Project Name: HappyHorses
 * Description: header file for the player
 */

#pragma once

#include <nds.h>
#include "../graphics/Sprite.h"

class Player {
    public:
        Player();

        void SetPosition(int posX, int posY);
        void SetVelocity(int velX, int velY);
        void Move();
    private:
        Sprite sprite;

        int posX, posY;
        int velX, velY;
};