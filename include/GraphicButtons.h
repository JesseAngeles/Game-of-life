#ifndef GRAPHIC_BUTTONS_H
#define GRAPHIC_BUTTONS_H

#include "GraphicFrame.h"
#include "GameController.h"

using namespace sf;

class GraphicButtons : public GraphicFrame
{
private:
    // Game Controller
    GameController controller;

    // Elements


public:
    // Constructor
    GraphicButtons(int width, int height, Vector2f relative_pos, Color background_color, GameController controller);
    
    // Drawers
    void draw(RenderWindow &window);

    // Button Functions
    

    // Getters

    // Setters
};

#endif // GRAPHIC_BUTTONS_H