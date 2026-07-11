#include "BacktrackingSolver.hpp"
#include <iostream>

// Prepares the solver by reading the initial clues of the Sudoku
// and marking the corresponding rows, columns, and boxes as used.
void BacktrackingSolver::initializeState(const Sudoku &sudoku) {
  // Reset all states
  rows = {};
  columns = {};
  boxes = {};
  backtrackingIterations = 0;
  solution = std::nullopt;

  // Populate lookup tables with initial fixed values
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      int val = sudoku.grid[i][j];
      if (val != 0) {
        rows[i][val] = true;
        columns[j][val] = true;
        boxes[i / 3 * 3 + j / 3][val] = true; // Maps (i, j) to box index 0-8
      }
    }
  }
}

// Verifies if a number can be placed at a specific cell without violating
// Sudoku rules.
bool BacktrackingSolver::isSafe(int row, int col, int num) const {
  return !rows[row][num] && !columns[col][num] &&
         !boxes[row / 3 * 3 + col / 3][num];
}

// Copies the grid into the solution attribute.
void BacktrackingSolver::saveSolution() {
  if (current_sudoku) {
    solution = current_sudoku->grid;
  }
}

// The core algorithm: searches for the first empty cell, tries all valid
// numbers, and calls itself recursively until the board is completely filled.
bool BacktrackingSolver::solveRecursive() {
  backtrackingIterations++;

  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      // Find an empty cell
      if (current_sudoku->grid[i][j] == 0) {
        // Try digits 1 to 9
        for (int num = 1; num <= 9; ++num) {
          if (isSafe(i, j, num)) {
            // Place the digit
            current_sudoku->grid[i][j] = num;
            rows[i][num] = true;
            columns[j][num] = true;
            boxes[i / 3 * 3 + j / 3][num] = true;

            // Recurse to fill the rest of the board
            if (solveRecursive()) {
              return true;
            }

            // Backtrack: if the recursive call failed, undo the placement
            current_sudoku->grid[i][j] = 0;
            rows[i][num] = false;
            columns[j][num] = false;
            boxes[i / 3 * 3 + j / 3][num] = false;
          }
        }
        return false; // Trigger backtrack because no digit was valid in this
                      // cell
      }
    }
  }

  // If we reach this point, all cells are filled.
  saveSolution();
  return true; // Solved
}

// Entry point for the solver.
bool BacktrackingSolver::solve(Sudoku &sudoku) {
  current_sudoku = &sudoku;
  initializeState(sudoku);
  return solveRecursive();
}
