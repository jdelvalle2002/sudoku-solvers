#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

// Load a 9x9 Sudoku grid from a CSV/text file.
std::optional<std::array<std::array<int, 9>, 9>>
loadSudokuFromFile(const std::string &filename) {
  std::ifstream file(filename); // This line opens the file for reading

  // We check if the file was successfully opened. If not, we print an error
  // message and return std::nullopt.
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return std::nullopt;
  }

  std::array<std::array<int, 9>, 9>
      sudoku{}; // Initialize a 9x9 grid filled with zeros.
  std::string line;
  std::string header;
  if (!std::getline(file, header))
    return std::nullopt; // consume header line
  bool found = false;
  while (std::getline(file, line)) { // Read the file line by line
    std::istringstream iss(
        line); // Create a string stream from the line to parse the numbers
    std::string id_str;
    std::string sudoku_str;
    std::string metricas_1_str;
    std::string metricas_2_str;

    // We read until we find a comma. The ID is not used in this function, but
    // it could be useful for identification.
    std::getline(iss, id_str, ',');
    std::getline(
        iss, sudoku_str,
        ','); // Read the Sudoku string (e.g., "." for empty, digits 1-9)
    std::getline(iss, metricas_1_str, ','); // Read the first metrics string
    std::getline(iss, metricas_2_str);      // Read the second metrics string

    if (sudoku_str.length() !=
        81) { // Check if the Sudoku string has exactly 81 characters. If not,
              // print an error and return nullopt.
      std::cerr << "Error: Invalid Sudoku string length in file " << filename
                << std::endl;
      return std::nullopt;
    }
    for (int i = 0; i < 9; ++i) { // Loop through each row of the Sudoku grid.
      for (int j = 0; j < 9;
           ++j) { // Loop through each column of the Sudoku grid.
        char c = sudoku_str[i * 9 + j]; // Calculate the index in the string for
                                        // the current cell.
        if (c == '.') {
          sudoku[i][j] = 0; // "." represents an empty cell
        } else if (c >= '1' && c <= '9') {
          sudoku[i][j] = c - '0'; // Convert char to int by subtracting '0'
        } else { // If the character is not valid, print an error and return
                 // nullopt
          std::cerr << "Error: Invalid character '" << c
                    << "' in Sudoku string." << std::endl;
          return std::nullopt;
        }
      }
    }
    found = true; // Set found to true to indicate that we have successfully
                  // read a Sudoku puzzle.
    for (const auto &row :
         sudoku) { // Print the Sudoku grid to the console for verification.
      for (auto x : row)
        std::cout << x << ' ';
      std::cout << '\n';
    }
    if (found) {
      break; // Exit the loop after reading the first Sudoku puzzle.
    }
  }
  return sudoku;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <sudoku_file>" << std::endl;
    return 1;
  }

  std::string filename = argv[1];
  auto sudoku = loadSudokuFromFile(filename);
  if (!sudoku.has_value()) {
    return 1; // Error already printed in loadSudokuFromFile
  }

  return 0;
}