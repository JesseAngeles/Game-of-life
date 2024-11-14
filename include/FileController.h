#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "tinyfiledialogs.h"

class FileController
{
private:

public:
    FileController() = default;

    std::vector<std::vector<bool>> readFile();
    void saveFile(std::vector<std::vector<bool>>);

};

#endif // FILE_CONTROLLER_H