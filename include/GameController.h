#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

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
    int getBMin() const { return b_min; }
    int getBMax() const { return b_max; }
    int getSMin() const { return s_min; }
    int getSMax() const { return s_max; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
    std::vector<std::vector<bool>> getSpace() const { return space; }

    std::set<Cell> getLivingCells() const { return living_cells; }

    // Setters
    void setBMin(int b_min) { this->b_min = b_min; }
    void setBMax(int b_max) { this->b_max = b_max; }
    void setSMin(int s_min) { this->s_min = s_min; }
    void setSMax(int s_max) { this->s_max = s_max; }

    void setWidth(int width);
    void setHeight(int height);
    void setSpace(std::vector<std::vector<bool>> space) { this->space = space; }

    void setLivingCells(std::set<Cell> living_cells);
};

#endif // GAME_CONTROLLER_H
