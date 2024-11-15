#include "GameController.h"

// Controlador
GameController::GameController(int y, int x)
    : y(y), x(x), randomizer()
{
    count = 0;
    resizeSpace();
    cleanSpace();
}

// Private functions
bool GameController::transition(Cell cell)
{
    int neightbourhood = countNeighbourhood(cell);

    if (space[cell.y][cell.x])
        return fun_in(neightbourhood, s_min, s_max);
    else
        return fun_in(neightbourhood, b_min, b_max);
}

// Neighbour functions

void GameController::forEachNeighbour(Cell cell, std::function<void(int, int)> callback)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            int ny = cell.y + i;
            int nx = cell.x + j;

            if (bull)
            {
                if (ny < 0)
                    ny = y - 1;
                if (ny >= y)
                    ny = 0;
                if (nx < 0)
                    nx = x - 1;
                if (nx >= x)
                    nx = 0;
            }

            if (fun_in(ny, 0, y - 1) && fun_in(nx, 0, x - 1))
                callback(ny, nx);
        }
}

int GameController::countNeighbourhood(Cell cell)
{
    int count = 0;
    forEachNeighbour(cell, [&](int ny, int nx)
                         {
        if (space[ny][nx])
            count++; });

    return count;
}

void GameController::updateNear(Cell cell)
{
    forEachNeighbour(cell, [&](int ny, int nx)
                         {
        if(!countNeighbourhood({ny, nx}))
            death_cells.erase({ny, nx}); });
}

void GameController::setDeathCells(Cell cell)
{
    forEachNeighbour(cell, [&](int ny, int nx)
                         {
        if (!space[ny][nx])
            death_cells.insert({ny, nx}); });
}

// Public functions
std::set<Cell> GameController::step()
{
    std::set<Cell> switch_cells;

    std::set<Cell> test_cells = living_cells;
    test_cells.insert(death_cells.begin(), death_cells.end());

    for (Cell cell : test_cells)
        if (space[cell.y][cell.x] != transition(cell))
            switch_cells.insert(cell);

    for (Cell cell : switch_cells)
        switchCell(cell);

    count++;

    return switch_cells;
}

bool GameController::switchCell(Cell cell)
{
    space[cell.y][cell.x] = !space[cell.y][cell.x];

    // Switch to alive (1)
    if (living_cells.find(cell) == living_cells.end())
    {
        living_cells.insert(cell);
        death_cells.erase(cell);
        setDeathCells(cell);
    }
    else // Switch to death(0)
    {
        living_cells.erase(cell);
        if (countNeighbourhood(cell))
            death_cells.insert(cell);

        updateNear(cell);
    }

    return space[cell.y][cell.x];
}

void GameController::resizeSpace()
{
    space.resize(y);

    for (int i = 0; i < y; ++i)
        space[i].resize(x);
}

void GameController::cleanSpace()
{
    for (std::vector<bool> &row : space)
        std::fill(row.begin(), row.end(), false);
    living_cells.clear();
    death_cells.clear();
}

void GameController::randomizeSpace()
{
    for (int i = 0; i < space.size(); i++)
        for (int j = 0; j < space[i].size(); j++)
            if (round(randomizer.generate(0, 1)))
                switchCell({i, j});
}

// Setters
void GameController::setY(int y)
{
    this->y = y;
    resizeSpace();
    cleanSpace();
}

void GameController::setX(int x)
{
    this->x = x;
    resizeSpace();
    cleanSpace();
}

void GameController::setSpace(std::vector<std::vector<bool>> new_space)
{
    cleanSpace();

    for (int i = 0; i < new_space.size(); i++)
        for (int j = 0; j < new_space[i].size(); j++)
            if (new_space[i][j])
                switchCell({i, j});
}

void GameController::setLivingCells(std::set<Cell> living_cells)
{
    this->living_cells = living_cells;
    for (Cell cell : living_cells)
        setDeathCells(cell);
}
