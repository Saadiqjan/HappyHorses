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

#include "TextLayer.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "MetaSprite.h"

using namespace std;

class Button {
    public:
        Button(SpriteManager& spriteMgr, TextLayer& textLayer);
    
        bool createSingle(const SpriteConfig& cfg, int width, int height);

        void createMulti();
        bool addPart(const SpriteConfig& cfg, int offsetX, int offsetY);
        void finalizeMulti(int width, int height);

        void setPosition(int x, int y);
        void setLabel(const std::string& text);
        void setPressed(bool pressed);

        void draw();

        bool contains(int touchX, int touchY) const;
        bool isLoaded() const { return !std::holds_alternative<std::monostate>(renderable); }
    private:
        SpriteManager& spriteMgr;
        TextLayer& textLayer;

        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;

        using Renderable = variant<std::monostate, Sprite*, MetaSprite*>;
        Renderable renderable;
        string label;
};