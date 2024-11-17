#include "FileController.h"

std::vector<std::vector<bool>> FileController::readFile()
{
    std::vector<std::vector<bool>> space;

    const char *filterPatterns[] = {"*.txt", "*.csv"};
    const char *filePath = tinyfd_openFileDialog(
        "Select a file",                // Título del diálogo
        "./resources/files/glider.csv", // Ruta inicial (vacío para la ruta actual)
        2,                              // Número de filtros de extensión
        filterPatterns,                 // Array de filtros de extensión
        nullptr,                        // Descripción de filtros (puede ser nullptr)
        0                               // Permitir selección múltiple (0 = no)
    );

    if (!filePath)
        return space;

    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error open file: " << filePath << std::endl;
        return space;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<bool> row;
        for (char &ch : line)
        {
            if (ch == 'O')
                row.push_back(true);
            else if (ch == '.')
                row.push_back(false);
        }
        space.push_back(row);
    }
    file.close();

    return space;
}

void FileController::saveFile(std::vector<std::vector<bool>> space)
{
    const char *filename = tinyfd_saveFileDialog(
        "Guardar archivo",                     // Título del diálogo
        "./resources/files/nuevo_archivo.txt", // Nombre y ruta inicial
        1,                                     // Número de filtros de extensión
        (const char *[]){"*.txt"},             // Extensiones permitidas
        "Archivo TXT (*.txt)"                  // Descripción de los filtros
    );

    if (!filename)
    {
        std::cerr << "No se seleccionó ningún archivo para guardar." << std::endl;
        return;
    }

    // Abre el archivo para guardar datos
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo para guardar: " << filename << std::endl;
        return;
    }

    // Itera sobre cada fila del vector y escribe los datos
    for (const auto &row : space)
    {
        for (bool cell : row)
            file << (cell ? 'O' : '.');
        file << "\n";
    }

    file.close(); // Cierra el archivo
    std::cout << "Archivo guardado correctamente en: " << filename << std::endl;
}