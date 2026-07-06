#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> loadSudokuFromFile(const std::string &filename)
{
    std::ifstream file(filename); // This line opens the file for reading

    // We check if the file was successfully opened. If not, we print an error message and return an empty vector.
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return {}; // Empty vector.
    }

    std::vector<std::vector<int>> sudoku(9, std::vector<int>(9, 0)); // Initialize a 9x9 grid filled with zeros. A vector of vectors is used to represent the Sudoku grid, where each inner vector represents a row in the grid.
    std::string line;
    std::string header;
    if (!std::getline(file, header)) return {}; // consume primera línea (cabecera)
    bool found = false;
    while (std::getline(file, line))
    {                                 // Read the file line by line.12
        std::istringstream iss(line); // Create a string stream from the line to parse the numbers.
        std::string id_str;
        std::string sudoku_str;
        std::string metricas_1_str;
        std::string metricas_2_str;

        // we read until we find a comma, which separates the ID from the Sudoku string. The ID is not used in this function, but it could be useful for identifying different Sudoku puzzles in the file.
        std::getline(iss, id_str, ',');         // Read the ID (not used in this function)
        std::getline(iss, sudoku_str, ',');     // Read the Sudoku string, the "." characters denote empty cells, and the digits 1-9 denote filled cells.
        std::getline(iss, metricas_1_str, ','); // Read the first metrics string
        std::getline(iss, metricas_2_str);      // Read the second metrics string

        // we print the sudoku string to test the function
        // std::cout << "Sudoku string: " << sudoku_str << std::endl;
        if (sudoku_str.length() != 81)
        { // Check if the Sudoku string has exactly 81 characters (9 rows * 9 columns). If not, we print an error message and return an empty vector.
            std::cerr << "Error: Invalid Sudoku string length in file " << filename << std::endl;
            return {}; // Return an empty vector to indicate an error.
        }
        for (int i = 0; i < 9; ++i)
        { // Loop through each row of the Sudoku grid.
            for (int j = 0; j < 9; ++j)
            {                                   // Loop through each column of the Sudoku grid.
                char c = sudoku_str[i * 9 + j]; // Calculate the index in the string for the current cell.
                if (c == '.')
                {                     // If the character is a ".", it represents an empty cell, so we set the corresponding cell in the grid to 0.
                    sudoku[i][j] = 0; // the array is already filled with zeros, but we set it explicitly for clarity.
                }
                else if (c >= '1' && c <= '9')
                {                           // If the character is a digit between '1' and '9', we convert it to an integer and store it in the grid.
                    sudoku[i][j] = c - '0'; // Convert char to int by subtracting '0'
                }
                else
                { // If the character is not valid, we print an error message and return an empty vector.
                    std::cerr << "Error: Invalid character '" << c << "' in Sudoku string." << std::endl;
                    return {}; // Return an empty vector to indicate an error.
                }
            }

            
        }
        found = true; // Set found to true to indicate that we have successfully read a Sudoku puzzle.
        for (const auto &row : sudoku)
            { // Print the Sudoku grid to the console for verification. This loop iterates through each row of the grid.
                for (auto x : row)
                    std::cout << x << ' ';
                std::cout << '\n';
            }
        if (found)
        {
            break; // Exit the loop after reading the first Sudoku puzzle.
        }
    }
    return sudoku;
    
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <sudoku_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    auto sudoku = loadSudokuFromFile(filename);
    if (sudoku.empty())
    {
        return 1; // Error already printed in loadSudokuFromFile
    }

    return 0;
}