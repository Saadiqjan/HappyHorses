/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Aug 19, 2026
 * Filename: Button.cpp
 * Project Name: HappyHorses
 * Description: Button class
 */

#include "ui/Button.h"

Button::Button(SpriteManager& spriteMgr, TextLayer& textLayer)
    : spriteMgr(&spriteMgr), textLayer(&textLayer)
{
}

Button::~Button()
{
    clear();
}

Button::Button(Button&& other) noexcept
{
    *this = std::move(other);
}

Button& Button::operator=(Button&& other) noexcept
{
    if (this != &other)
    {
        clear(); 

        spriteMgr = other.spriteMgr;
        textLayer = other.textLayer;
        renderable = other.renderable;
        x = other.x; y = other.y;
        width = other.width; height = other.height;
        label = std::move(other.label);

        other.renderable = std::monostate{}; 
    }
    return *this;
}

void Button::clear()
{
    std::visit([this](auto&& r)
    {
        using T = std::decay_t<decltype(r)>;
        if constexpr (std::is_same_v<T, Sprite*>)
        {
            if (r) spriteMgr->destroySprite(r);
        }
        else if constexpr (std::is_same_v<T, MetaSprite*>)
        {
            if (r) spriteMgr->destroyMetaSprite(r);
        }
    }, renderable);

    renderable = std::monostate{};
}

bool Button::createSingle(const SpriteConfig& cfg, int w, int h)
{
    Sprite* s = spriteMgr->createSprite(cfg);
    if (!s) return false;

    renderable = s;
    width = w;
    height = h;
    return true;
}

void Button::createMulti()
{
    renderable = spriteMgr->createMetaSprite();
}

bool Button::addPart(const SpriteConfig& cfg, int offsetX, int offsetY)
{
    if (auto* m = get_if<MetaSprite*>(&renderable))
        return (*m)->addPart(spriteMgr->getOamManager(), cfg, offsetX, offsetY);
    return false;
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
        using T = decay_t<decltype(r)>;
        if constexpr (is_same_v<T, Sprite*> || is_same_v<T, MetaSprite*>)
        {
            if (r) r->setPosition(x, y);
        }
    }, renderable);
}

void Button::setPressed(bool pressed)
{
    int frame = pressed ? 1 : 0;

    visit([frame](auto&& r)
    {
        using T = decay_t<decltype(r)>;
        if constexpr (is_same_v<T, Sprite*> || is_same_v<T, MetaSprite*>)
        {
            if (r) r->setFrame(frame);
        }
    }, renderable);
}

void Button::draw()
{
    if (!label.empty())
        textLayer->drawTextCentered(x, y, width, height, label);
}

bool Button::contains(int touchX, int touchY) const
{
    return touchX >= x && touchX < x + width &&
           touchY >= y && touchY < y + height;
}