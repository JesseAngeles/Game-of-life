#include "gui/FrameBoard.h"

// Constructor
FrameBoard::FrameBoard(int width, int height, Vector2f relative_pos, Color background_color, GameController &controller)
    : Frame(width, height, relative_pos, background_color), controller(controller)
{
    drawSpace();
    init_pos.y = init_pos.x = 0;
}

// Drawers
void FrameBoard::drawSpace()
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
    rectangle.setOutlineThickness(1);
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
        for (std::pair<RectangleShape, bool> cell : line)
            window.draw(cell.first);
}

void FrameBoard::resetSpace()
{
    for (int i = 0; i < space.size(); i++)
        for (int j = 0; j < space[i].size(); j++)
            if (space[i][j].second)
                changeColor(i, j);
}

// Redraws
void FrameBoard::zoom(bool in)
{
    if (in)
    {
        x_scale *= 2;
        y_scale *= 2;
    }
    else
    {
        x_scale /= 2;
        y_scale /= 2;
    }

    for (int i = 0; i < space.size(); i++)
        for (int j = 0; j < space[i].size(); j++)
        {
            space[i][j].first.setPosition({j * x_scale + relative_pos.x, i * y_scale + relative_pos.y});
            space[i][j].first.setSize({x_scale, y_scale});
        }
}

void FrameBoard::moveHorizontal(bool right)
{
    float move = (right) ? x_scale : -x_scale;

    for (std::vector<std::pair<RectangleShape, bool>> &line : space)
        for (std::pair<RectangleShape, bool> &cell : line)
            cell.first.move({move, 0});

    init_pos.x += move;
}

void FrameBoard::moveVertical(bool down)
{
    float move = (down) ? y_scale : -y_scale;
    for (std::vector<std::pair<RectangleShape, bool>> &line : space)
        for (std::pair<RectangleShape, bool> &cell : line)
            cell.first.move({0, move});

    init_pos.y += move;
}

// Clicker function
void FrameBoard::clickEvent(Vector2i pos)
{
    if (!fun_in(pos.x, relative_pos.x, relative_pos.x + width) ||
        !fun_in(pos.y, relative_pos.y, relative_pos.y + height))
        return;

    int x_pos = (pos.x - init_pos.x - relative_pos.x) / x_scale;
    int y_pos = (pos.y - init_pos.y - relative_pos.y) / y_scale;

    // std::cout << x_pos << ", " << y_pos << std::endl;

    if (fun_in(x_pos, 0, controller.getX() - 1) &&
        fun_in(y_pos, 0, controller.getY() - 1))
    {
        changeColor(y_pos, x_pos);
        controller.switchCell({y_pos, x_pos});
    }
}

// Setters
void FrameBoard::setInitPos(Vector2f init_pos)
{
    // Reallocate elements
    moveVertical(false);
}
