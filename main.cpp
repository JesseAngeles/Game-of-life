#include <iostream>
#include <vector>
#include <set>

#include "include/GameController.h"

using namespace std;

void draw(vector<vector<bool>> board);

int main(int argc, char *argv[])
{

    GameController controller(10, 10);

    set<Cell> living_cells = {
        Cell(3, 4),
        Cell(3, 3),
        Cell(3, 2)};

    controller.setLivingCells(living_cells);

    string stop;
    for (int i = 0; i < 10; i++)
    {
        controller.updateCells();

        cin >> stop;
    }
    return 0;
}
