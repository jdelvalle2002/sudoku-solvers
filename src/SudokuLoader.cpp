#include "SudokuLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Parses a CSV file to extract the n first 9x9 Sudoku puzzles.
std::vector<std::array<std::array<int, 9>, 9>>
loadSudokusFromFile(const std::string &filename, int n) {

  const int MAX_SUDOKUS = 200000;
  if (n > MAX_SUDOKUS)
    n = MAX_SUDOKUS; // we could use algorithm lib

  std::vector<std::array<std::array<int, 9>, 9>>
      sudokus; // vector of sudokus to be filled

  sudokus.reserve(n); // reserve space for the n sudokus

  int loaded_count = 0;

  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return sudokus;
  }

  std::string line;
  std::string header;

  // Consume and ignore the CSV header
  if (!std::getline(file, header))
    return sudokus;

  while (loaded_count < n && std::getline(file, line)) {
    std::istringstream iss(line);
    std::string id_str, sudoku_str, metricas_1_str, metricas_2_str;
    std::array<std::array<int, 9>, 9> sudoku{};

    // Split by comma. We care mostly about the sudoku_str.
    std::getline(iss, id_str, ',');
    std::getline(iss, sudoku_str, ',');
    std::getline(iss, metricas_1_str, ',');
    std::getline(iss, metricas_2_str);

    if (sudoku_str.length() != 81) {
      std::cerr << "Error: Invalid Sudoku string length in file " << filename
                << std::endl;
      continue;
    }

    // Map the 81-character string into the 9x9 array
    for (int i = 0; i < 9; ++i) {
      for (int j = 0; j < 9; ++j) {
        char c = sudoku_str[i * 9 + j];
        if (c == '.') {
          sudoku[i][j] = 0; // '.' denotes an empty cell
        } else if (c >= '1' && c <= '9') {
          sudoku[i][j] = c - '0'; // Convert char to integer
        } else {
          std::cerr << "Error: Invalid character '" << c
                    << "' in Sudoku string." << std::endl;
          continue;
        }
      }
    }
    sudokus.push_back(sudoku);
    loaded_count++;
  }

  return sudokus;
}
