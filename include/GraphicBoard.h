#ifndef GRAPHIC_BOARD_H
#define GRAPHIC_BOARD_H

#include "GraphicFrame.h"
#include "GameController.h"

using namespace sf;

class GraphicBoard : public GraphicFrame
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
    GraphicBoard(int width, int height, Vector2f position, Color background_color, GameController controller);

    // Drawers
    void drawAxes();
    void drawRectangle(Vector2i position, Color color);
    void draw(RenderWindow &window);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    
    // Setters
};

#endif // GRAPHIC_BOARD_H