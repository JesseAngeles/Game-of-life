#ifndef FRAME_GRAPHIC_H
#define FRAME_GRAPHIC_H

#include <vector>

#include "gui/Frame.h"
#include "GameController.h"

class FrameGraphic : public Frame
{
private:
    // Scale
    float x_scale;
    float y_scale;

    Vector2i max;

    // Elements
    std::vector<VertexArray> axes;
    std::vector<CircleShape> points;

    GameController &controller;

public:
    // Constructor
    FrameGraphic(int width, int height, Vector2f position, Color background_color, GameController &controller);

    // Drawers
    void drawAxes();
    void drawCircleShape(float x, float y, float radius, Color color);
    void draw(RenderWindow &window);

    // Getters
    Vector2i getMax() const { return max; }

    // Setters
    void setMax(Vector2i max);
};

#endif // FRAME_GRAPHIC_H