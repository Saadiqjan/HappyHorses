/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Aug 19, 2026
 * Filename: Button.cpp
 * Project Name: HappyHorses
 * Description: Button class
 */

#include "Button.h"

Button::Button(SpriteManager& spriteMgr, TextLayer& textLayer)
    : spriteMgr(spriteMgr), textLayer(textLayer)
{
}

bool Button::createSingle(const SpriteConfig& cfg, int w, int h)
{
    Sprite* s = spriteMgr.createSprite(cfg);
    if (!s) return false;

    renderable = s;
    width = w;
    height = h;
    return true;
}

void Button::createMulti()
{
    renderable = spriteMgr.createMetaSprite();
}

bool Button::addPart(const SpriteConfig& cfg, int offsetX, int offsetY)
{
    if (auto* m = std::get_if<MetaSprite*>(&renderable))
        return (*m)->addPart(spriteMgr.getOamManager(), cfg, offsetX, offsetY);
    return false; // createMulti() wasn't called first
}

void Button::finalizeMulti(int w, int h)
{
    width = w;
    height = h;
}

void Button::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;

    std::visit([x, y](auto&& r)
    {
        using T = std::decay_t<decltype(r)>;
        if constexpr (std::is_same_v<T, Sprite*> || std::is_same_v<T, MetaSprite*>)
        {
            if (r) r->setPosition(x, y);
        }
    }, renderable);
}

void Button::setPressed(bool pressed)
{
    int frame = pressed ? 1 : 0;

    std::visit([frame](auto&& r)
    {
        using T = std::decay_t<decltype(r)>;
        if constexpr (std::is_same_v<T, Sprite*> || std::is_same_v<T, MetaSprite*>)
        {
            if (r) r->setFrame(frame);
        }
    }, renderable);
}

void Button::draw()
{
    if (!label.empty())
        textLayer.drawTextCentered(x, y, width, height, label);
}

bool Button::contains(int touchX, int touchY) const
{
    return touchX >= x && touchX < x + width &&
           touchY >= y && touchY < y + height;
}