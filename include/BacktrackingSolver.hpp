#pragma once
#include "SudokuSolver.hpp"
#include <array>
#include <optional>

// Implementation of SudokuSolver using a classic recursive backtracking
// algorithm.
class BacktrackingSolver : public SudokuSolver {
private:
  // Fast lookup tables to check if a digit (1-9) is already used in a row,
  // column, or 3x3 box. Using index 1-9 directly, hence size 10.
  std::array<std::array<bool, 10>, 9> rows{};
  std::array<std::array<bool, 10>, 9> columns{};
  std::array<std::array<bool, 10>, 9> boxes{};

  // Performance metrics
  int backtrackingIterations = 0;

  // Stores the final solved state
  std::optional<std::array<std::array<int, 9>, 9>> solution{};

  // Pointer to the Sudoku being currently solved
  Sudoku *current_sudoku = nullptr;

  // Checks if it is valid to place `num` at coordinates `row`, `col`
  bool isSafe(int row, int col, int num) const;

  // The core recursive backtracking function
  bool solveRecursive();

  // Initializes the lookup tables based on the current state of the board
  void initializeState(const Sudoku &sudoku);

  // Saves the final solution into the `solution` attribute
  void saveSolution();

public:
  // Interface implementation
  bool solve(Sudoku &sudoku) override;

  // Getters for performance metrics
  int getIterations() const { return backtrackingIterations; }
};
