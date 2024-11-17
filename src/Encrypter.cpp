#include "Encrypter.h"

std::vector<int> Encrypter::encrypt(std::vector<std::vector<bool>> matrix)
{
    matrix = makeSquare(matrix);

    std::vector<std::vector<std::vector<bool>>> matrices;
    std::vector<std::vector<bool>> tmp_matrix = matrix;

    // Obtener las cuatro rotaciones
    for (int i = 0; i < 4; i++)
    {
        tmp_matrix = rotate(tmp_matrix);

        matrices.push_back(tmp_matrix);
        matrices.push_back(transpose(tmp_matrix));
    }

    
    std::vector<int> encrypter_string;

    for (std::vector<std::vector<bool>> matrix : matrices)
    {
        std::vector<int> chain = getRings(matrix);
        if (encrypter_string.size() != chain.size())
            encrypter_string.resize(chain.size());

        for (int i = 0; i < chain.size(); i++)
            encrypter_string[i] += chain[i];
    }

    return encrypter_string;
}

std::vector<int> Encrypter::getRings(std::vector<std::vector<bool>> matrix)
{
    int i = 0;
    int j = 0;

    int ring = 1;
    int total_rings = std::ceil(static_cast<float>(matrix.size()) / 2.0);
    
    int half_ring = matrix.size() * 2 - 2;
    int count = 0;

    std::vector<int> chain;

    do
    {
        count = 0;
        half_ring = (matrix.size() - 2 * ring + 1) * 2;
        do
        {
            chain.push_back(matrix[i][j]);

            if (i == ring - 1 && j < matrix[i].size() - ring)
                j++;
            else if (j == matrix[i].size() - ring && i < matrix.size() - ring)
                i++;
            else if (i == matrix.size() - ring && j > ring - 1)
                j--;
            else if (j == ring - 1 && i > ring - 1)
                i--;

            count++;
        } while ((i != ring - 1 || j != ring - 1) && count < half_ring);
        i = ring;
        j = ring;
        ring++;

        chain.push_back(-1);

    } while (ring <= total_rings);

    return chain;
}


std::vector<std::vector<bool>> Encrypter::makeSquare(std::vector<std::vector<bool>> matrix)
{
    int max_size = std::max(matrix.size(), matrix[0].size());

    std::vector<std::vector<bool>> square_matrix(max_size, std::vector<bool>(max_size, false));
    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < matrix[i].size(); ++j)
            square_matrix[i][j] = matrix[i][j];

    return square_matrix;
}

std::vector<std::vector<bool>> Encrypter::rotate(std::vector<std::vector<bool>> matrix)
{
    // Si la matriz está vacía, devolver una matriz vacía
    if (matrix.empty())
    {
        return {};
    }

    // Dimensiones de la matriz original
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    // Crear una nueva matriz con dimensiones invertidas (cols x rows)
    std::vector<std::vector<bool>> rotated(cols, std::vector<bool>(rows));

    // Llenar la nueva matriz con los valores rotados
    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            rotated[c][rows - 1 - r] = matrix[r][c];
    return rotated;
}

std::vector<std::vector<bool>> Encrypter::transpose(std::vector<std::vector<bool>> matrix)
{
    // Si la matriz está vacía, devolver una matriz vacía
    if (matrix.empty())
    {
        return {};
    }

    // Dimensiones de la matriz original
    size_t rows = matrix.size();
    size_t cols = matrix[0].size();

    // Crear una nueva matriz transpuesta de dimensiones (cols x rows)
    std::vector<std::vector<bool>> transposed(cols, std::vector<bool>(rows));

    // Llenar la matriz transpuesta
    for (size_t r = 0; r < rows; ++r)
    {
        for (size_t c = 0; c < cols; ++c)
        {
            transposed[c][r] = matrix[r][c];
        }
    }

    return transposed;
}

void Encrypter::printMatrix(std::vector<std::vector<bool>> matrix)
{
    std::cout << "\n";
    for (auto i : matrix)
    {
        for (auto a : i)
            std::cout << a << " ";
        std::cout << "\n";
    }
}

