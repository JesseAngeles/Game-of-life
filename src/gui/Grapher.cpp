#include "gui/Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor, GameController &controller)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor), file(),
      controller(controller), window(VideoMode(width, height), tittle, Style::Close),

      board(1000, 880, Vector2f(70, 10), Color(100, 100, 100), controller),
      lineal(500, 300, Vector2f(1080, 170), {255, 255, 255}, controller),
      logarithm(500, 300, Vector2f(1080, 570), {255, 255, 255}, controller),

      start_button(50, 50, Vector2f(10, 10), Color(0, 0, 0), START_ROUTE),
      increase_speed_button(20, 20, Vector2f(10, 70), {0, 0, 0}, INCREASE_ROUTE),
      decrease_speed_button(20, 20, Vector2f(40, 70), {0, 0, 0}, DECREASE_ROUTE),
      step_button(50, 50, Vector2f(10, 100), Color(0, 0, 0), STEP_ROUTE),
      reset_button(50, 50, Vector2f(10, 160), Color(0, 0, 0), RESET_ROUTE),
      random_button(50, 50, Vector2f(10, 220), Color(0, 0, 0), RANDOM_ROUTE),
      save_button(50, 50, Vector2f(10, 280), Color(0, 0, 0), SAVE_ROUTE),
      load_button(50, 50, Vector2f(10, 340), Color(0, 0, 0), LOAD_ROUTE),
      graph_button(50, 50, Vector2f(10, 400), Color(0, 0, 0), GRAPH_ROUTE),
      bull_button(50, 50, Vector2f(10, 460), {0, 0, 0}, NO_BULL_ROUTE),
      zoom_in_button(20, 20, Vector2f(10, 520), {0, 0, 0}, ZOOM_IN_ROUTE),
      zoom_out_button(20, 20, Vector2f(40, 520), {0, 0, 0}, ZOOM_OUT_ROUTE)
{

    if (!this->font.loadFromFile(font_route))
        std::cout << "Error in Grapher.loadFont. Can´t load font from " << font_route << std::endl;

    lineal.setFont(this->font);
    logarithm.setFont(this->font);

    count_text.setFont(font);
    count_text.setString("Population");
    count_text.setCharacterSize(20);
    count_text.setFillColor(Color{0, 0, 0});
    count_text.setPosition(1080, 10);

    time_text.setFont(font);
    time_text.setString("Time");
    time_text.setCharacterSize(20);
    time_text.setFillColor(Color{0, 0, 0});
    time_text.setPosition(1080, 40);

    lineal_text.setFont(font);
    lineal_text.setString("LINEAL");
    lineal_text.setCharacterSize(20);
    lineal_text.setFillColor(Color{0, 0, 0});
    lineal_text.setPosition(1080, 120);

    logarithm_text.setFont(font);
    logarithm_text.setString("LOGARITHM");
    logarithm_text.setCharacterSize(20);
    logarithm_text.setFillColor(Color{0, 0, 0});
    logarithm_text.setPosition(1080, 520);

    // Function assignation
    start_button.setButtonFunction([this]()
                                   { startFunction(); });

    increase_speed_button.setButtonFunction([this]()
                                            { increaseSpeedFunction(); });

    decrease_speed_button.setButtonFunction([this]()
                                            { decreaseSpeedFunction(); });

    step_button.setButtonFunction([this]()
                                  { stepFunction(); });
    reset_button.setButtonFunction([this]()
                                   { resetFunction(); });
    random_button.setButtonFunction([this]()
                                    { randomFunction(); });
    save_button.setButtonFunction([this]()
                                  { saveFunction(); });
    load_button.setButtonFunction([this]()
                                  { loadFunction(); });

    graph_button.setButtonFunction([this]()
                                   { graphFunction(); });
    
    bull_button.setButtonFunction([this]()
                                   { bullFunction(); });
    
    zoom_in_button.setButtonFunction([this]()
                                     { zoomInFunction(); });

    zoom_out_button.setButtonFunction([this]()
                                      { zoomOutFunction(); });

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
                increase_speed_button.triggerFunction(mouse_pos);
                decrease_speed_button.triggerFunction(mouse_pos);
                step_button.triggerFunction(mouse_pos);
                reset_button.triggerFunction(mouse_pos);
                random_button.triggerFunction(mouse_pos);
                save_button.triggerFunction(mouse_pos);
                load_button.triggerFunction(mouse_pos);
                graph_button.triggerFunction(mouse_pos);
                bull_button.triggerFunction(mouse_pos);
                zoom_in_button.triggerFunction(mouse_pos);
                zoom_out_button.triggerFunction(mouse_pos);
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
                board.moveHorizontal(true);

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
                board.moveHorizontal(false);

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
                board.moveVertical(true);

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
                board.moveVertical(false);
        }

        delta_time += clock.restart().asMilliseconds();
        if (is_running && delta_time >= speed)
        {
            stepFunction();
            delta_time = 0;
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
        lineal.draw(window);
        logarithm.draw(window);

        // Text
        window.draw(lineal_text);
        window.draw(logarithm_text);
        window.draw(count_text);
        window.draw(time_text);

        // Buttons
        start_button.draw(window);
        increase_speed_button.draw(window);
        decrease_speed_button.draw(window);
        reset_button.draw(window);
        step_button.draw(window);
        random_button.draw(window);
        save_button.draw(window);
        load_button.draw(window);
        graph_button.draw(window);
        bull_button.draw(window);
        zoom_in_button.draw(window);
        zoom_out_button.draw(window);

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
    is_running = !is_running;
    start_button.setTexture((is_running) ? PAUSE_ROUTE : START_ROUTE);
}

void Grapher::increaseSpeedFunction()
{
    speed /= 1.5;
}

void Grapher::decreaseSpeedFunction()
{
    speed *= 1.5;
}

void Grapher::stepFunction()
{
    std::set<Cell> changes = controller.step();
    for (Cell cell : changes)
        board.changeColor(cell.y, cell.x);

    population.push_back(controller.getLivingCells().size());

    time_text.setString("Time: " + std::to_string(controller.getCount()));
    count_text.setString("Population: " + std::to_string(controller.getLivingCells().size()));
}

void Grapher::resetFunction()
{
    controller.setCount(0);
    population.clear();

    controller.cleanSpace();
    board.resetSpace();

    time_text.setString("Time: 0");
    count_text.setString("Population: 0");

    is_running = false;
    start_button.setTexture(START_ROUTE);
}

void Grapher::randomFunction()
{
    controller.randomizeSpace();

    board.resetSpace();
    for (Cell cell : controller.getLivingCells())
        board.changeColor(cell.y, cell.x);
}

void Grapher::saveFunction()
{
    file.saveFile(controller.getSpace());
}

void Grapher::loadFunction()
{
    controller.setSpace(file.readFile());
    population.clear();
    controller.setCount(0);

    board.resetSpace();
    for (Cell cell : controller.getLivingCells())
        board.changeColor(cell.y, cell.x);
}

void Grapher::graphFunction()
{
    lineal.setMax(Vector2f(population.size(), *max_element(population.begin(), population.end())));
    logarithm.setMax(Vector2f(population.size(), log10(*max_element(population.begin(), population.end()))));

    for (int i = 0; i < population.size(); i++)
    {
        lineal.drawCircleShape(i, (population[i]), 3, {255, 0, 0});
        logarithm.drawCircleShape(i, log10(population[i]), 3, {255, 0, 0});
    }
}

void Grapher::bullFunction()
{
    controller.switchBull();
    bull_button.setTexture((controller.getBull() ? BULL_ROUTE : NO_BULL_ROUTE));
}

void Grapher::zoomInFunction()
{
    board.zoom(true);
}

void Grapher::zoomOutFunction()
{
    board.zoom(false);
}

void Grapher::leftFunction()
{
    board.moveHorizontal(false);
}

void Grapher::rightFunction()
{
    board.moveHorizontal(true);
}

void Grapher::upFunction()
{
    board.moveVertical(false);
}

void Grapher::downFunction()
{
    board.moveVertical(true);
}