#include <iostream>
#include <vector>
#include <set>

#include "gui/Grapher.h"
#include "GameController.h"

using namespace std;

void draw(vector<vector<bool>> board);

int main(int argc, char *argv[])
{
    GameController controller(100, 100);
    Grapher grapher(1600, 900, "Game of life", Color(200, 200, 200), controller);

    grapher.mainLoop();

    return 0;
}

int main1(int argc, char *argv[])
{

    GameController controller(7, 7);

    controller.switchCell({1, 2});

    controller.switchCell({3, 2});

    controller.switchCell({2,2});

    // controller.switchCell({1, 1});

    cout << "Alive: \n";
    for (auto i : controller.getLivingCells())
        std::cout << i.y << ", " << i.x << "\n";

    cout << "Death: \n";
    for (auto i : controller.getDeathCells())
        std::cout << i.y << ", " << i.x << "\n";

    controller.draw();
    std::set<Cell> a = controller.step();

    cout << "Cambios:  \n";
    for (auto i : a)
        std::cout << i.y << ", " << i.x << "\n";


    cout << "Alive: \n";
    for (auto i : controller.getLivingCells())
        std::cout << i.y << ", " << i.x << "\n";

    cout << "Death: \n";
    for (auto i : controller.getDeathCells())
        std::cout << i.y << ", " << i.x << "\n";

    controller.draw();

    // set<Cell> living_cells = {
    //     Cell(3, 4),
    //     Cell(3, 3),
    //     Cell(3, 2)};

    // controller.setLivingCells(living_cells);

    // for (int i = 0; i < 4; i++)
    // {
    //     controller.updateCells();
    //     draw(controller.getSpace());
    //     cout << endl;
    // }

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