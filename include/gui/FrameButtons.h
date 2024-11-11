#ifndef FRAME_BUTTONS_H
#define FRAME_BUTTONS_H

#include <iostream>

#include "GameController.h"

#include "gui/Frame.h"
#include "gui/Button.h"

using namespace sf;

class FrameButtons : public Frame
{
private:
    // Game Controller
    GameController controller;

    // Elements
    Button start_button;
    Button reset_button;
    Button step_button;
    Button save_button;
    Button load_button;

    // Button Functions
    void startFunction();
    void resetFunction();
    void stepFunction();
    void saveFunction();
    void loadFunction();


public:
    // Constructor
    FrameButtons(int width, int height, Vector2f relative_pos, Color background_color, GameController &controller);
    
    // Drawers
    void draw(RenderWindow &window);

    

    // Clicker functions
    void clickEvent(Vector2i position, GameController &controller);

    // Getters

    // Setters
};

#endif // FRAME_BUTTONS_H