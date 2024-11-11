#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>

#include "Functions.h"

using namespace sf;

class Button
{
protected:
    // Button
    int width;
    int height;

    // Figure
    Vector2f relative_pos;
    Color background_color;
    RectangleShape button;
    Texture texture;

    // Text
    Font font;
    Text text;
    std::string font_route = "./resources/fonts/Roboto-Medium.ttf";

    // Function
    std::function<void()> buttonFunction;

public:
    // Constructor
    Button(int width, int height, Vector2f relative_pos, Color background_color, String content);

    // Drawers
    void draw(RenderWindow &window);

    // Trigger
    void triggerFunction(Vector2i position);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Vector2i getSize() const { return Vector2i(width, height); }
    Vector2f getRelativePosition() const { return relative_pos; }

    // Setters
    void setButtonFunction(std::function<void()> buttonFunction) { this->buttonFunction = buttonFunction; }
};

#endif // BUTTON_H