#include "GameController.h"

// Controlador
GameController::GameController(int width, int height)
    : width(width), height(height)
{
    resizeSpace();
    cleanSpace();
}

// Functions
void GameController::resizeSpace()
{
    space.resize(width);

    for (int i = 0; i < width; ++i)
        space[i].resize(height);
}

void GameController::cleanSpace()
{
    for (std::vector<bool> row : space)
        std::fill(row.begin(), row.end(), false);
}

int GameController::countNeighbourhood(Cell cell)
{
    int count = 0;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            // Ignorar [x][y]
            if (i == 0 && j == 0)
                continue;

            // Validacion de bordes
            int nx = cell.x + i;
            int ny = cell.y + j;
            if (fun_in(nx, 0, width - 1) && fun_in(ny, 0, height - 1))
                if (space[nx][ny])
                    count++;
        }

    return count;
}

bool GameController::transition(Cell cell)
{
    int neightbourhood = countNeighbourhood(cell);

    if (space[cell.x][cell.y])
        return fun_in(neightbourhood, s_min, s_max);
    else
        return fun_in(neightbourhood, b_min, b_max);
}

void GameController::updateSpace()
{
    for (Cell cell : living_cells)
        space[cell.x][cell.y] = true;
}

void GameController::updateCells()
{
    std::set<Cell> test_cells;
    std::set<Cell> new_living_cells;

    // test_cells.insert(living_cells.begin(), living_cells.end());
    living_cells.insert(death_cells.begin(), death_cells.end());

    for (Cell cell : living_cells)
        if (transition(cell))
            new_living_cells.insert(Cell(cell.x, cell.y));

    // Se limpian unicamente las celdas que fueron consultadas
    for (Cell cell : living_cells)
        space[cell.x][cell.y] = false;

    // Reasignacion de celulas vivas y muertas
    living_cells = new_living_cells;
    setDeathCells();
    updateSpace();
}

// Setters
void GameController::setWidth(int width)
{
    this->width = width;
    resizeSpace();
    cleanSpace();
}

void GameController::setHeight(int height)
{
    this->height = height;
    resizeSpace();
    cleanSpace();
}

void GameController::setLivingCells(std::set<Cell> living_cells)
{
    this->living_cells = living_cells;
    updateSpace();
    setDeathCells();
}

void GameController::setDeathCells()
{
    for (Cell living_cell : living_cells)
    {
        int x = living_cell.x;
        int y = living_cell.y;

        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {
                int nx = x + i;
                int ny = y + j;

                if (fun_in(nx, 0, width - 1) && fun_in(ny, 0, height - 1))
                    if (!space[nx][ny])
                        death_cells.insert(Cell(nx, ny));
            }
    }
}