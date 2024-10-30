#include <iostream>
#include <vector>
#include <set>

#include "include/GameController.h"

using namespace std;

void draw(vector<vector<bool>> board);

int main(int argc, char *argv[])
{

    GameController controller(7, 7);

    set<Cell> living_cells = {
        Cell(3, 4),
        Cell(3, 3),
        Cell(3, 2)};

    controller.setLivingCells(living_cells);

    for (int i = 0; i < 4; i++)
    {
        controller.updateCells();
        draw(controller.getSpace());
        cout << endl;
    }

    return 0;
}

// // borrar
void draw(vector<vector<bool>> space)
{
    for (int i = 0; i < space.size(); i++)
    {
        for (int j = 0; j < space[i].size(); j++)
            std::cout << space[i][j] << " ";
        std::cout << std::endl;
    }
}