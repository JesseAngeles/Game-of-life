#ifndef GRAPHIC_FRAME_H
#define GRAPHIC_FRAME_H

#include <SFML/Graphics.hpp>

using namespace sf;

class GraphicFrame
{
protected:
    // Frame
    int width;
    int height;

    Vector2f relative_pos;

    Color background_color;

    // Elements
    RectangleShape frame;

public:
    // Constructor
    GraphicFrame(int width, int height, Vector2f relative_pos, Color background_color);

    // Drawers
    void draw(RenderWindow &window);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Vector2i getSize() const { return Vector2i(width, height); }
    Vector2f getRelativePosition() const { return relative_pos; }
};

#endif // GRAPHIC_FRAME_H