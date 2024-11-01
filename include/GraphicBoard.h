#ifndef GRAPHIC_BOARD_H
#define GRAPHIC_BOARD_H

#include <SFML/Graphics.hpp>

#include "GameController.h"

using namespace sf;

class GraphicBoard
{
private:
    // Frame
    int width;
    int height;

    Vector2f relative_pos;

    Color backgroundColor;

    // Game controller
    GameController controller;

    // Scale
    float x_scale;
    float y_scale;

    // Elements
    RectangleShape frame;
    std::vector<VertexArray> axes;
    std::vector<std::pair<RectangleShape, Vector2i>> rectangles;

public:
    // Constructor
    GraphicBoard(int width, int height, Vector2f position, Color backgroundColor, GameController gameController);

    // Drawers
    void drawAxes();
    void drawRectangle(Vector2i position, Color color);
    void draw(RenderWindow &window);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Vector2i getSize() const { return Vector2i(width, height); }
    Vector2f getPosition() const { return relative_pos; }
    // Setters
};

#endif // GRAPHIC_BOARD_H