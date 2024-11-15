#include "gui/FrameGraphic.h"

FrameGraphic::FrameGraphic(int width, int height, Vector2f relative_pos, Color backtground_color, GameController &controller)
    : Frame(width, height, relative_pos, background_color), controller(controller)
{
    drawAxes();
}

// Drawers
void FrameGraphic::drawAxes()
{
    axes.clear();
    
    float margin_x = std::min(10.0f, width / 10.0f);
    float margin_y = std::min(10.0f, height / 10.0f);

    VertexArray x_axis(Lines, 2);
    x_axis[0].position = Vector2f(relative_pos.x + margin_x, height + relative_pos.y - margin_y);
    x_axis[1].position = Vector2f(width + relative_pos.x - margin_x, height + relative_pos.y - margin_y);
    x_axis[0].color = x_axis[1].color = Color(0, 0, 0);

    VertexArray y_axis(Lines, 2);
    y_axis[0].position = Vector2f(relative_pos.x + margin_x, relative_pos.y + margin_y);
    y_axis[1].position = Vector2f(relative_pos.x + margin_x, height + relative_pos.y - margin_y);
    y_axis[0].color = y_axis[1].color = Color(0, 0, 0);

    axes.push_back(x_axis);
    axes.push_back(y_axis);
}

void FrameGraphic::drawCircleShape(float x, float y, float radius, Color color)
{
    CircleShape circle(radius);

    float margin_x = std::min(10.0f, width / 10.0f);
    float margin_y = std::min(10.0f, height / 10.0f);

    float posX = relative_pos.x + margin_x + x * x_scale;
    float posY = relative_pos.y + height - margin_y - max.y; //y * y_scale;

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
}

// Setters
void FrameGraphic::setMax(Vector2i max)
{
    this->max = max;

    // Ajustar el margen proporcional al tamaño máximo en cada eje
    float margin_x = std::min(10.0f, width / 10.0f);
    float margin_y = std::min(10.0f, height / 10.0f);

    // Calcular escalas
    this->x_scale = (width - margin_x * 2) / static_cast<float>(max.x + 1);
    this->y_scale = (height - margin_y * 2) / static_cast<float>(max.y + 1);

    points.clear();
}
