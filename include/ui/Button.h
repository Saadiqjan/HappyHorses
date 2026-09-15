/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Aug 19, 2026
 * Filename: Button.h
 * Project Name: HappyHorses
 * Description: Header file for button class
 */

#pragma once

#include <nds.h>
#include <string>
#include <variant>
#include <type_traits>

#include "../core/TextLayer.h"
#include "../core/SpriteManager.h"
#include "../graphics/Sprite.h"
#include "../graphics/MetaSprite.h"

using namespace std;

class Button {
    public:
        Button(SpriteManager& spriteMgr, TextLayer& textLayer);
        ~Button();

        Button(const Button&) = delete;
        Button& operator=(const Button&) = delete;

        Button(Button&& other) noexcept;
        Button& operator=(Button&& other) noexcept;
    
        bool createSingle(const SpriteConfig& cfg, int width, int height);

        void createMulti();
        bool addPart(const SpriteConfig& cfg, int offsetX, int offsetY);
        void finalizeMulti(int width, int height);

        void setPosition(int x, int y);
        void setLabel(const std::string& text) { label = text; };
        void setPressed(bool pressed);

        void clear();

        void draw();

        int getX() { return x;};
        int getY() { return y; };
        int getWidth() { return width; };
        int getHeight() { return height; };

        bool contains(int touchX, int touchY) const;
        bool isLoaded() const { return !holds_alternative<monostate>(renderable); }
    private:
        SpriteManager* spriteMgr;
        TextLayer* textLayer;

        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        using Renderable = variant<monostate, Sprite*, MetaSprite*>;
        Renderable renderable;
        string label;
};