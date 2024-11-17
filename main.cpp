#include <iostream>
#include <vector>
#include <set>
#include <cstdlib>

#include "gui/Grapher.h"
#include "GameController.h"

#define DEFAULT_SIZE 100

using namespace std;

pair<int, int> getSize(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    pair<int, int> size = getSize(argc, argv);
    GameController controller(size.first, size.second);
    // controller.setBMin(2);
    // controller.setBMax(2);
    // controller.setSMin(7);
    // controller.setSMax(7);
    Grapher grapher(1600, 900, "Game of life", Color(200, 200, 200), controller);

    grapher.mainLoop();

    return 0;
}

std::pair<int, int> getSize(int argc, char *argv[])
{
    // Valores predeterminados para el tamaño
    if (argc >= 3)
    {
        int width = std::atoi(argv[1]);
        int height = std::atoi(argv[2]);
        if (width > 0 && height > 0)
            return {width, height};
    }

    return {int(DEFAULT_SIZE), int(DEFAULT_SIZE)};
}