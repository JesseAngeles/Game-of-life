#ifndef GRAPHER_H
#define GRAPHER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>

#include "GameController.h"
#include "FrameBoard.h"
#include "Button.h"

using namespace sf;

class Grapher
{
private:
    // Window
    int width;
    int height;
    std::string tittle;
    Color backgroundColor;
    Font font;

    std::string font_route = "./resources/fonts/Roboto-Medium.ttf";
    // Frames
    FrameBoard board;

    // Game Controller
    GameController &controller;

    // Lines
    std::vector<VertexArray> axes;
    std::vector<VertexArray> lines;

    // Buttons
    Button start_button;
    Button step_button;
    Button reset_button;
    Button save_button;
    Button load_button;

    // Button Functions
    void startFunction();
    void stepFunction();
    void resetFunction();
    void saveFunction();
    void loadFunction();

    // Rectangles (alive cells)
    std::vector<std::pair<RectangleShape, Vector2i>> rectangles;

    // Functions
    void loadFont();

public:
    // Constructor
    Grapher(int width, int height, std::string tittle, Color background, GameController &controller);
    void drawAxis();

    RenderWindow window;

    // Functions
    void mainLoop();

    // Drawers
    void drawLine(Vector2f pos_1, Vector2f pos_2, Color color);
    void drawRectangle(Vector2i position, Color color);

    // Getters

    // Settters
};

#endif // GRAPHER_H