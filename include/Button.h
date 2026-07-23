/* Author: Saadiq Shahsamand
 * Creation Date: Jul 22, 2026
 * Modified Date: Jul 22, 2026
 * Filename: Button.h
 * Project Name: HappyHorses
 * Description: Header file for button class
 */

#pragma once

class Button {
    public:
        Button(int x, int y, int width, int height);

        bool contains();

        void setPosition(int x, int y);

        int getX() const;
        int getY() const;
        int getWidth() const;
        int getHeight() const;
    private:
        int x;
        int y;

        int width;
        int height;
};