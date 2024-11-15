#ifndef GRAME_BOARD_H
#define GRAME_BOARD_H

#include "gui/Frame.h"
#include "GameController.h"

#define MOVE_SCALE 10;

using namespace sf;

class FrameBoard : public Frame
{
private:

    // Scale
    float x_scale;
    float y_scale;

    Vector2f init_pos;

    // Elements
    std::vector<VertexArray> axes;
    std::vector<std::vector<std::pair<RectangleShape, bool>>> space;

    GameController &controller;

public:
    // Constructor
    FrameBoard(int width, int height, Vector2f position, Color background_color, GameController &controller);

    // Drawers
    void drawSpace();
    RectangleShape drawRectangle(int y, int x, Color color);
    void changeColor(int y, int x);
    void draw(RenderWindow &window);
    void resetSpace();

    // Redraws
    void zoom(bool in);
    void moveHorizontal(bool right);
    void moveVertical(bool down);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    Vector2f getInitPos() const { return init_pos; }
    
    // Setters
    void setInitPos(Vector2f init_pos);
};

#endif // GRAME_BOARD_H