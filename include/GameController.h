#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

// // borrar
#include <iostream>

#include <vector>
#include <set>

#include "Functions.h"

struct Cell
{
    int x;
    int y;

    Cell(int x, int y) : x(x), y(y) {};
    bool operator<(const Cell &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

class GameController
{
private:
    // Evolution rules
    int b_min = 3;
    int b_max = 3;
    int s_min = 2;
    int s_max = 3;

    // Regular space
    int width;
    int height;
    std::vector<std::vector<bool>> space;

    // Cellular positions
    std::set<Cell> living_cells; // alive
    std::set<Cell> death_cells;  // death (near to alive)

    // Functions
    void resizeSpace();
    void cleanSpace();
    int countNeighbourhood(Cell cell);
    bool transition(Cell cell);
    void updateSpace();

    // Setters
    void setDeathCells();

public:
    // Constructor
    GameController(int width, int height);

    // Functions
    void updateCells();

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::vector<std::vector<bool>> getSpace() const { return space; }

    std::set<Cell> getLivingCells() const { return living_cells; }

    // Setters
    void setWidth(int width);
    void setHeight(int height);
    void setSpace(std::vector<std::vector<bool>> space) { this->space = space; }

    void setLivingCells(std::set<Cell> living_cells);

    // // borrar
    void draw()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
                std::cout << space[i][j] << " ";
            std::cout << std::endl;
        }
    }

    // // borrar
    void print(Cell cell)
    {
        std::cout << "(x, y) ->" << cell.x << ", " << cell.y << std::endl;
    }
};

#endif // GAME_CONTROLLER_H
