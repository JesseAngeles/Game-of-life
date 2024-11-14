#include "gui/Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor, GameController &controller)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor),
      controller(controller), window(VideoMode(width, height), tittle, Style::Close),
      board(1000, 880, Vector2f(70, 10), Color(0, 255, 100), controller),
      start_button(50, 50, Vector2f(10, 10), Color(0, 0, 0), "./resources/images/start.png"),
      step_button(50, 50, Vector2f(10, 70), Color(0, 0, 0), "./resources/images/step.png"),
      reset_button(50, 50, Vector2f(10, 130), Color(0, 0, 0), "./resources/images/reset.png"),
      save_button(50, 50, Vector2f(10, 190), Color(0, 0, 0), "./resources/images/save.png"),
      load_button(50, 50, Vector2f(10, 250), Color(0, 0, 0), "./resources/images/load.png")
{

    if (!this->font.loadFromFile(font_route))
        std::cout << "Error in Grapher.loadFont. Can´t load font from " << font_route << std::endl;

    // Function assignation
    start_button.setButtonFunction([this]()
                                   { startFunction(); });
    reset_button.setButtonFunction([this]()
                                   { resetFunction(); });
    step_button.setButtonFunction([this]()
                                  { stepFunction(); });
    save_button.setButtonFunction([this]()
                                  { saveFunction(); });
    load_button.setButtonFunction([this]()
                                  { loadFunction(); });
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
                board.clickEvent(mouse_pos);

                // Click in buttons
                start_button.triggerFunction(mouse_pos);
                step_button.triggerFunction(mouse_pos);
                reset_button.triggerFunction(mouse_pos);
                save_button.triggerFunction(mouse_pos);
                load_button.triggerFunction(mouse_pos);
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

        // Buttons
        start_button.draw(window);
        reset_button.draw(window);
        step_button.draw(window);
        save_button.draw(window);
        load_button.draw(window);

        window.display();
    }
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

// Button functions
void Grapher::startFunction()
{
    std::cout << "Button start!" << std::endl;
    for (int i = 0; i < 30; i++)
        stepFunction();
    
}

void Grapher::stepFunction()
{
    std::set<Cell> changes = controller.step();
    for (Cell cell : changes)
        board.changeColor(cell.y, cell.x);
}

void Grapher::resetFunction()
{
    std::cout << "Button reset!" << std::endl;
}

void Grapher::saveFunction()
{

    std::cout << "Button save!" << std::endl;
}

void Grapher::loadFunction()
{
    std::cout << "Button load!" << std::endl;
}