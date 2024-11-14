#include "gui/FrameBoard.h"

// Constructor
FrameBoard::FrameBoard(int width, int height, Vector2f relative_pos, Color background_color, GameController &controller)
    : Frame(width, height, relative_pos, background_color), controller(controller)
{
    drawAxes();
}

// Drawers
void FrameBoard::drawAxes()
{
    int width_size = controller.getX();
    int height_size = controller.getY();

    x_scale = width / static_cast<float>(width_size);
    y_scale = height / static_cast<float>(height_size);

    for (int y = 0; y < height_size; y++)
    {
        std::vector<std::pair<RectangleShape, bool>> line;
        for (int x = 0; x < width_size; x++)
            line.push_back(std::make_pair(drawRectangle(y, x, {0, 0, 0}), false));

        space.push_back(line);
    }
}

RectangleShape FrameBoard::drawRectangle(int y, int x, Color color)
{
    RectangleShape rectangle(Vector2f(x_scale, y_scale));
    rectangle.setPosition({x * x_scale + relative_pos.x, y * y_scale + relative_pos.y});
    rectangle.setOutlineColor({100, 100, 100});
    rectangle.setOutlineThickness(2);
    rectangle.setFillColor(color);

    return rectangle;
}

void FrameBoard::changeColor(int y, int x)
{
    space[y][x].second = !space[y][x].second;

    if (space[y][x].second)
    {
        space[y][x].first.setFillColor({255, 255, 255});
    }
    else
        space[y][x].first.setFillColor({0, 0, 0});
}

void FrameBoard::draw(RenderWindow &window)
{
    Frame::draw(window);

    for (std::vector<std::pair<RectangleShape, bool>> line : space)
        for (std::pair<RectangleShape, bool> square : line)
            window.draw(square.first);

    for (const VertexArray &axis : axes)
        window.draw(axis);
}

// Clicker function
void FrameBoard::clickEvent(Vector2i pos)
{
    if (!fun_in(pos.x, relative_pos.x, relative_pos.x + width) ||
        !fun_in(pos.y, relative_pos.y, relative_pos.y + height))
        return;

    int x_pos = (pos.x - relative_pos.x) / x_scale;
    int y_pos = (pos.y - relative_pos.y) / y_scale;

    changeColor(y_pos, x_pos);

    controller.switchCell({y_pos, x_pos});
}