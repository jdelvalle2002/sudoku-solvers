#pragma once
#include <array>
#include <string>
#include <vector>

// Reads a Sudoku grid from a CSV file.
// Expects a specific CSV format containing a string representation of the puzzle.
// Returns an std::vector containing the 9x9 grids.
std::vector<std::array<std::array<int, 9>, 9>> loadSudokusFromFile(const std::string& filename, int n);
