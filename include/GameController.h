#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

// // Erase
#include <iostream>

#include <vector>
#include <set>
#include <functional>

#include "Functions.h"
#include "Randomizer.h"

struct Cell
{
    int y;
    int x;

    Cell(int y, int x) : y(y), x(x) {};
    bool operator<(const Cell &other) const
    {
        return (x < other.x) || (x == other.x && y < other.y);
    }
};

class GameController
{
private:
    // Classes
    Randomizer randomizer;

    // Evolution rules
    int b_min = 3;
    int b_max = 3;
    int s_min = 2;
    int s_max = 3;

    // Regular space
    int y;
    int x;
    std::vector<std::vector<bool>> space;

    // Cellular positions
    std::set<Cell> living_cells; // alive
    std::set<Cell> death_cells;  // death (near to alive)

    // Functions
    void updateSpace();

    // Neighbour functions
    void forEachNeighbour(Cell cell, std::function<void(int, int)> callback);
    int countNeighbourhood(Cell cell);
    void updateNear(Cell cell);
    bool transition(Cell cell);
    void setDeathCells(Cell living_cell);

public:
    // Constructor
    GameController(int y, int x);

    // Functions
    std::set<Cell> step();
    bool switchCell(Cell cell);

    void resizeSpace();
    void cleanSpace();

    void randomizeSpace();

    // Getters
    int getBMin() const { return b_min; }
    int getBMax() const { return b_max; }
    int getSMin() const { return s_min; }
    int getSMax() const { return s_max; }

    int getY() const { return y; }
    int getX() const { return x; }
    std::vector<std::vector<bool>> getSpace() const { return space; }

    std::set<Cell> getLivingCells() const { return living_cells; }
    std::set<Cell> getDeathCells() const { return death_cells; }

    // Setters
    void setBMin(int b_min) { this->b_min = b_min; }
    void setBMax(int b_max) { this->b_max = b_max; }
    void setSMin(int s_min) { this->s_min = s_min; }
    void setSMax(int s_max) { this->s_max = s_max; }

    void setY(int y);
    void setX(int x);
    void setSpace(std::vector<std::vector<bool>> space);

    void setLivingCells(std::set<Cell> living_cells);

    // // Erase
    void draw()
    {
        std::cout << std::endl;
        for (const auto &line : space)
        {
            for (bool cell : line)
                std::cout << (cell ? "*" : ".") << " ";
            std::cout << std::endl;
        }
    }
};

#endif // GAME_CONTROLLER_H
