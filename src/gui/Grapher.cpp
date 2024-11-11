#include "gui/Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor, GameController controller)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor),
      controller(controller), window(VideoMode(width, height), tittle, Style::Close),
      board(400, 400, Vector2f(10, 10), Color(0, 255, 100), controller),
      buttons(310, 70, Vector2f(420, 10), Color(100, 255, 255), controller)
{
    loadFont();
    setScale();

}

void Grapher::setScale()
{
    x_scale = width / static_cast<float>(controller.getWidth());
    y_scale = height / static_cast<float>(controller.getHeight());
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
                {
                    board.clickEvent(mouse_pos, controller);
                }
                // Click en botones
                else if (fun_in(mouse_pos.x, buttons.getRelativePosition().x, buttons.getRelativePosition().x + buttons.getWidth()) &&
                         fun_in(mouse_pos.y, buttons.getRelativePosition().y, buttons.getRelativePosition().y + buttons.getHeight()))
                    buttons.clickEvent(mouse_pos, controller);

                else
                    controller.draw();
                // Click en graficas
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

        window.display();
    }
}

// Functions
void Grapher::loadFont()
{
    if (!this->font.loadFromFile(font_route))
        std::cout << "Error in Grapher.loadFont. Can´t load font from " << font_route << std::endl;
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
