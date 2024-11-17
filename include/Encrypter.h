#ifndef ENCRYPTER_H
#define ENCRYPTER_H

#include <vector>
#include <algorithm>
#include <cmath>

// //
#include<iostream>

class Encrypter
{
private:

    std::vector<std::vector<bool>> makeSquare(std::vector<std::vector<bool>> matrix);
    std::vector<std::vector<bool>> rotate(std::vector<std::vector<bool>> matrix);
    std::vector<std::vector<bool>> transpose(std::vector<std::vector<bool>> matrix);
    std::vector<int> getRings(std::vector<std::vector<bool>> matrix);

public:
    // Constructor
    Encrypter() = default;

    // Functions
    std::vector<int> encrypt(std::vector<std::vector<bool>> matrix);

    void printMatrix(std::vector<std::vector<bool>> matrix);
};


#endif // ENCRYPTER_H