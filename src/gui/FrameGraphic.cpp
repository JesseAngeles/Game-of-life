#include "gui/FrameGraphic.h"

FrameGraphic::FrameGraphic(int width, int height, Vector2f relative_pos, Color backtground_color, GameController &controller)
    : Frame(width, height, relative_pos, background_color), controller(controller)
{
    drawAxes();
    drawLabels();
}

// Drawers
void FrameGraphic::drawAxes()
{
    axes.clear();

    VertexArray x_axis(Lines, 2);
    x_axis[0].position = Vector2f(relative_pos.x, height + relative_pos.y);
    x_axis[1].position = Vector2f(relative_pos.x + width, height + relative_pos.y);
    x_axis[0].color = x_axis[1].color = Color(0, 0, 0);

    VertexArray y_axis(Lines, 2);
    y_axis[0].position = Vector2f(relative_pos.x, relative_pos.y);
    y_axis[1].position = Vector2f(relative_pos.x, height + relative_pos.y);
    y_axis[0].color = y_axis[1].color = Color(0, 0, 0);

    axes.push_back(x_axis);
    axes.push_back(y_axis);
}

void FrameGraphic::drawLabels()
{
    y_text.setFont(font);
    y_text.setString("Y: ");
    y_text.setCharacterSize(20);
    y_text.setFillColor(Color{0, 0, 0}); 
    y_text.setPosition(relative_pos.x, relative_pos.y - 20);

    x_text.setFont(font); 
    x_text.setString("X: ");
    x_text.setCharacterSize(20);
    x_text.setFillColor(Color{0, 0, 0});
    x_text.setPosition(relative_pos.x + width - 50, relative_pos.y + height);
}

void FrameGraphic::drawCircleShape(float x, float y, float radius, Color color)
{
    CircleShape circle(radius);

    float posX = relative_pos.x + x * x_scale;
    float posY = relative_pos.y + height - y * y_scale; 

    circle.setPosition(posX, posY);
    circle.setFillColor(color);
    
    points.push_back(circle);
}


void FrameGraphic::draw(RenderWindow &window)
{
    Frame::draw(window);

    for (VertexArray &axis : axes)
        window.draw(axis);

    for (CircleShape point : points)
        window.draw(point);

    window.draw(y_text);
    window.draw(x_text);
}

// Setters
void FrameGraphic::setMax(Vector2f max)
{
    this->max = max;

    y_text.setString("Y:" + std::to_string(max.y));
    x_text.setString("X:" + std::to_string(max.x));

    // Calcular escalas
    this->x_scale = (width) / (max.x);
    this->y_scale = (height) / (max.y);

    points.clear();
}
