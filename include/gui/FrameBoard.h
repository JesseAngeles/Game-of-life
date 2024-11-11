#ifndef GRAME_BOARD_H
#define GRAME_BOARD_H

#include "gui/Frame.h"
#include "GameController.h"

using namespace sf;

class FrameBoard : public Frame
{
private:
    // Game controller
    GameController controller;

    // Scale
    float x_scale;
    float y_scale;

    // Elements
    std::vector<VertexArray> axes;
    std::vector<std::pair<RectangleShape, Vector2i>> rectangles;

public:
    // Constructor
    FrameBoard(int width, int height, Vector2f position, Color background_color, GameController controller);

    // Drawers
    void drawAxes();
    void drawRectangle(Vector2i position, Color color);
    void draw(RenderWindow &window);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    
    // Setters
};

#endif // GRAME_BOARD_H