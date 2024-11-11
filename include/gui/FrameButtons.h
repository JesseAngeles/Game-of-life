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
    static void startFunction();
    static void resetFunction();
    static void stepFunction();
    static void saveFunction();
    static void loadFunction();


public:
    // Constructor
    FrameButtons(int width, int height, Vector2f relative_pos, Color background_color, GameController controller);
    
    // Drawers
    void draw(RenderWindow &window);

    

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters

    // Setters
};

#endif // FRAME_BUTTONS_H