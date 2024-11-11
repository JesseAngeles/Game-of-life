#include "Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor, GameController controller)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor),
      controller(controller), window(VideoMode(width, height), tittle, Style::Close),
      board(400, 400, Vector2f(10, 10), Color(100, 255, 100), controller),
      buttons(400, 400, Vector2f(420, 10), Color(100, 255, 255), controller)
{
    loadFont();
    setScale();
    // drawAxis();
}

void Grapher::setScale()
{
    x_scale = width / static_cast<float>(controller.getWidth());
    y_scale = height / static_cast<float>(controller.getHeight());
}

void Grapher::drawAxis()
{
    for (int x = 0; x < controller.getWidth(); x++)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(x * x_scale, 0);
        line[1].position = Vector2f(x * x_scale, height);
        line[0].color = line[1].color = Color(250, 250, 250);

        axes.push_back(line);
    }

    for (int y = 0; y < controller.getHeight(); y++)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(0, y * y_scale);
        line[1].position = Vector2f(width, y * y_scale);
        line[0].color = line[1].color = Color(250, 250, 250);

        axes.push_back(line);
    }
}

// Main Loop
void Grapher::mainLoop()
{
    Clock clock;

    // Board
    Vector2f board_position = board.getRelativePosition();
    Vector2i board_size = board.getSize();


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Manejar el clic del botón
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos(event.mouseButton.x, event.mouseButton.y);
                
                // Click en cuadricula
                if (fun_in(mouse_pos.x, board.getRelativePosition().x, board.getRelativePosition().x + board.getWidth()) &&
                    fun_in(mouse_pos.y, board.getRelativePosition().y, board.getRelativePosition().y + board.getHeight()))
                        board.clickEvent(mouse_pos);
                    

                Vector2i clicked_cell = clickedCell(mouse_pos);
                bool cell = controller.switchCell(Cell(clicked_cell.x, clicked_cell.y));



                // if (cell)
                //     drawRectangle(clicked_cell, {255, 100, 100});
                // else
                // {
                //     for (auto it = rectangles.begin(); it != rectangles.end(); ++it)
                //         if (it->second == clicked_cell)
                //         {
                //             rectangles.erase(it);
                //             break;
                //         }
                // }
            }
        }

        window.clear(backgroundColor);

        // Dibujar elementos estaticos
        if (!axes.empty())
            for (const VertexArray &axis : axes)
                window.draw(axis);

        if (!lines.empty())
            for (const VertexArray &line : lines)
                window.draw(line);

        // Frames
        board.draw(window);
        buttons.draw(window);

        // if (!rectangles.empty())
        //     for (const std::pair<RectangleShape, Vector2i> &rectangle : rectangles)
        //         window.draw(rectangle.first);
        window.display();
    }
}

// Functions
void Grapher::loadFont()
{
    if (!this->font.loadFromFile(font_route))
        std::cout << "Error in Grapher.loadFont. Can´t load font from " << font_route << std::endl;
}

Vector2i Grapher::clickedCell(Vector2i position)
{
    int x_pos = position.x / static_cast<float>(x_scale);
    int y_pos = position.y / static_cast<float>(y_scale);

    return Vector2i(x_pos, y_pos);
}

// Drawers
void Grapher::drawLine(Vector2f pos_1, Vector2f pos_2, Color color)
{
    VertexArray line(Lines, 2);
    line[0].position = pos_1;
    line[1].position = pos_2;

    line[0].color = line[1].color = color;

    this->lines.push_back(line);
}
