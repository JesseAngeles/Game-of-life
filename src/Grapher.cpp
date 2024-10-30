#include "Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor, GameController controller)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor),
      controller(controller), window(VideoMode(width, height), tittle)
{
    loadFont();
    drawAxis();
}

void Grapher::drawAxis()
{
    int width_size = controller.getWidth();
    int height_size = controller.getHeight();

    x_scale = width / static_cast<float>(width_size);
    y_scale = height / static_cast<float>(height_size);

    for (int x = 0; x < width_size; x++)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(x * x_scale, 0);
        line[1].position = Vector2f(x * x_scale, height);
        line[0].color = line[1].color = Color(250, 250, 250);

        axes.push_back(line);
    }

    for (int y = 0; y < height_size; y++)
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
                Vector2i clicked_cell = clickedCell(mouse_pos);
                // Probar clic del boton
                std::cout << "mouse pos: " << clicked_cell.x << ", " << clicked_cell.y << std::endl;
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

        if (!rectangles.empty())
            for (const RectangleShape &rectangle : rectangles)
                window.draw(rectangle);
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
    int x_pos = position.x / static_cast<float>(controller.getWidth());
    int y_pos = position.y / static_cast<float>(controller.getHeight());

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

void Grapher::drawRectangle(Vector2f position, int widht, int height, Color color)
{
    RectangleShape rectangle(Vector2f(width, height));
    rectangle.setPosition(position);
    rectangle.setOutlineThickness(0);
    rectangle.setFillColor(color);

    this->rectangles.push_back(rectangle);
}
