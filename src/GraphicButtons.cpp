#include "GraphicButtons.h"

// Constructor
GraphicButtons::GraphicButtons(int width, int height, Vector2f relative_pos, Color background_color, GameController controller)
    : GraphicFrame(width, height, relative_pos, background_color), controller(controller)
{}

// Drawers
void GraphicButtons::draw(RenderWindow &window)
{
    GraphicFrame::draw(window);
}
