#include "gui/FrameButtons.h"

// Declaración de la función antes de usarla en el constructor
void startFunction();

// Constructor
FrameButtons::FrameButtons(int width, int height, Vector2f relative_pos, Color background_color, GameController controller)
    : Frame(width, height, relative_pos, background_color), controller(controller),
      load_button(50, 50, Vector2f(relative_pos.x + 10, relative_pos.y + 10), Color(0, 0, 0), "./resources/images/load.png"),
      save_button(50, 50, Vector2f(relative_pos.x + 70, relative_pos.y + 10), Color(0, 0, 0), "./resources/images/save.png"),
      start_button(50, 50, Vector2f(relative_pos.x + 130, relative_pos.y + 10), Color(0, 0, 0), "./resources/images/start.png"),
      step_button(50, 50, Vector2f(relative_pos.x + 190, relative_pos.y + 10), Color(0, 0, 0), "./resources/images/step.png"),
      reset_button(50, 50, Vector2f(relative_pos.x + 250, relative_pos.y + 10), Color(0, 0, 0), "./resources/images/reset.png")
{
    // Button functions assignation
    start_button.setButtonFunction(startFunction);
    reset_button.setButtonFunction(resetFunction);
    step_button.setButtonFunction(stepFunction);
    save_button.setButtonFunction(saveFunction);
    load_button.setButtonFunction(loadFunction);
}

// Drawers
void FrameButtons::draw(RenderWindow &window)
{
    Frame::draw(window);

    start_button.draw(window);
    reset_button.draw(window);
    step_button.draw(window);
    save_button.draw(window);
    load_button.draw(window);
}

// Funciones de boton
void FrameButtons::startFunction()
{
    std::cout << "Button start!" << std::endl;
}

void FrameButtons::resetFunction()
{
    std::cout << "Button reset!" << std::endl;
}

void FrameButtons::stepFunction()
{

    std::cout << "Button step!" << std::endl;
}

void FrameButtons::saveFunction()
{

    std::cout << "Button save!" << std::endl;
}

void FrameButtons::loadFunction()
{
    std::cout << "Button load!" << std::endl;
}

// Clicker function
void FrameButtons::clickEvent(Vector2i pos)
{
    // Buttons
    start_button.triggerFunction(pos);
    reset_button.triggerFunction(pos);
    step_button.triggerFunction(pos);
    save_button.triggerFunction(pos);
    load_button.triggerFunction(pos);
}