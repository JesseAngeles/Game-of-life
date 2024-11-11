#include "GraphicBoard.h"

// Constructor
GraphicBoard::GraphicBoard(int width, int height, Vector2f relative_pos, Color background_color, GameController controller)
    : GraphicFrame(width, height, relative_pos, background_color), controller(controller)
{
    drawAxes();
}

// Drawers
void GraphicBoard::drawAxes()
{
    int width_size = controller.getWidth();
    int height_size = controller.getHeight();

    x_scale = width / static_cast<float>(width_size);
    y_scale = height / static_cast<float>(height_size);

    for (int x = 0; x < width_size; x++)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f((x * x_scale) + relative_pos.x, relative_pos.y);
        line[1].position = Vector2f((x * x_scale) + relative_pos.x, height + relative_pos.y);
        line[0].color = line[1].color = Color(250, 250, 250);

        axes.push_back(line);
    }

    for (int y = 0; y < height_size; y++)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(relative_pos.x, (y * y_scale) + relative_pos.y);
        line[1].position = Vector2f(width + relative_pos.x, (y * y_scale) + relative_pos.y);
        line[0].color = line[1].color = Color(250, 250, 250);

        axes.push_back(line);
    }
}

void GraphicBoard::drawRectangle(Vector2i pos, Color color)
{
    RectangleShape rectangle(Vector2f(x_scale, y_scale));
    rectangle.setPosition({pos.x * x_scale + relative_pos.x, pos.y * y_scale + relative_pos.y});
    rectangle.setOutlineThickness(0);
    rectangle.setFillColor(color);

    this->rectangles.push_back(std::make_pair(rectangle, pos));
}

void GraphicBoard::draw(RenderWindow &window)
{
    GraphicFrame::draw(window);

    if (!rectangles.empty())
        for (const std::pair<RectangleShape, Vector2i> &rectangle : rectangles)
            window.draw(rectangle.first);

    for (const VertexArray &axis : axes)
        window.draw(axis);
}

// Clicker function
void GraphicBoard::clickEvent(Vector2i pos)
{
    int x_pos = (pos.x - relative_pos.x) / x_scale;
    int y_pos = (pos.y - relative_pos.y) / y_scale;

    Vector2i clicked_cell(x_pos, y_pos);

    bool cell = controller.switchCell(Cell(x_pos, y_pos));
    if (cell)
    {
        drawRectangle(clicked_cell, {250, 100, 100});
    }
    else
    {
        for (auto it = rectangles.begin(); it != rectangles.end(); ++it)
            if (it->second == clicked_cell)
            {
                rectangles.erase(it);
                break;
            }
    }
}