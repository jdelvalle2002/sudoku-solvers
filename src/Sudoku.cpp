#include "Sudoku.hpp"

// Constructor that takes a 2D array and sets up the board.
// It also initializes the fixed_values array based on the initial clues provided.
Sudoku::Sudoku(const std::array<std::array<int, 9>, 9>& initial_grid) : grid(initial_grid) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j] != 0) {
                // If there's a number initially, it's a fixed clue
                fixed_values[i][j] = true;
            } else {
                // If it's 0, it's an empty cell
                fixed_values[i][j] = false;
            }
        }
    }
}

// Outputs the Sudoku grid to the console.
// Fixed numbers are printed with a '*' next to them.
void Sudoku::print() const {
    for (int i = 0; i < 9; i++) {
        // Print horizontal separators between 3x3 blocks
        if (i % 3 == 0 && i != 0) {
            std::cout << "-----------------------------\n";
        }
        for (int j = 0; j < 9; j++) {
            // Print vertical separators between 3x3 blocks
            if (j % 3 == 0 && j != 0) {
                std::cout << "|";
            }
            // Display cell content
            if (fixed_values[i][j]) {
                std::cout << "*" << grid[i][j]; // Asterisk denotes a fixed clue
            } else {
                if (grid[i][j] == 0) std::cout << "  "; // Empty spaces for 0
                else std::cout << " " << grid[i][j];
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}
