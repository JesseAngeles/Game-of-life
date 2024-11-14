#ifndef GRAME_BOARD_H
#define GRAME_BOARD_H

#include "gui/Frame.h"
#include "GameController.h"

using namespace sf;

class FrameBoard : public Frame
{
private:

    // Scale
    float x_scale;
    float y_scale;

    // Elements
    std::vector<VertexArray> axes;
    std::vector<std::vector<std::pair<RectangleShape, bool>>> space;

    GameController &controller;

public:
    // Constructor
    FrameBoard(int width, int height, Vector2f position, Color background_color, GameController &controller);

    // Drawers
    void drawAxes();
    RectangleShape drawRectangle(int y, int x, Color color);
    void changeColor(int y, int x);
    void draw(RenderWindow &window);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    
    // Setters
};

#endif // GRAME_BOARD_H