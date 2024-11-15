#ifndef FRAME_GRAPHIC_H
#define FRAME_GRAPHIC_H

#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "gui/Frame.h"
#include "GameController.h"

class FrameGraphic : public Frame
{
private:
    // Scale
    float x_scale;
    float y_scale;

    Vector2f max;

    // Elements
    std::vector<VertexArray> axes;
    std::vector<CircleShape> points;
    GameController &controller;
    Text y_text, x_text;
    Font font;

public:
    // Constructor
    FrameGraphic(int width, int height, Vector2f position, Color background_color, GameController &controller);

    // Drawers
    void drawAxes();
    void drawLabels();
    // void drawTexts();
    void drawCircleShape(float x, float y, float radius, Color color);
    void draw(RenderWindow &window);

    // Getters
    Vector2f getMax() const { return max; }

    // Setters
    void setFont(Font font) { this->font = font; }
    void setMax(Vector2f max);
};

#endif // FRAME_GRAPHIC_H