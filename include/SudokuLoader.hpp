#pragma once
#include <array>
#include <string>
#include <optional>

// Reads a Sudoku grid from a CSV file.
// Expects a specific CSV format containing a string representation of the puzzle.
// Returns an std::optional containing the 9x9 grid, or std::nullopt on error.
std::optional<std::array<std::array<int, 9>, 9>> loadSudokuFromFile(const std::string& filename);
