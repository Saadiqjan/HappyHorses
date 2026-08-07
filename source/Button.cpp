/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 22, 2026
 * Filename: Button.cpp
 * Project Name: HappyHorses
 * Description: Button class
 */

#include "Button.h"
#include "Sprite.h"
#include <nds.h>

Button::Button(int x, int y, int width, int height)
{
    // leftSprite = new Sprite();
    // middleSprite = new Sprite();
    // rightSprite = new Sprite();
}

void Button::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;

    //sprite.setPosition(x, y);
}