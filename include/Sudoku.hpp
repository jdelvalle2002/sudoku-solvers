#pragma once
#include <array>
#include <iostream>

// Represents a 9x9 Sudoku board.
// Stores both the current values in the grid and a map of which values are fixed clues.
class Sudoku {
public:
    // The 9x9 grid holding numbers from 1-9 (0 represents an empty cell)
    std::array<std::array<int, 9>, 9> grid{};
    
    // A boolean grid where true means the cell was an initial clue (cannot be modified by solvers)
    std::array<std::array<bool, 9>, 9> fixed_values{};

    Sudoku() = default;
    
    // Initializes the board and marks non-zero values as fixed clues
    explicit Sudoku(const std::array<std::array<int, 9>, 9>& initial_grid);

    // Prints the Sudoku grid to standard output with borders
    void print() const;
};
