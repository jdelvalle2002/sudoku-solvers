#pragma once
#include "Sudoku.hpp"

// Abstract base class (Interface) for all Sudoku solving algorithms.
// Defines the Strategy pattern interface so that different solvers 
// (Backtracking, OR-Tools, etc.) can be interchanged easily.
class SudokuSolver {
public:
    virtual ~SudokuSolver() = default;
    
    // Attempt to solve the given sudoku in place.
    // The sudoku object's grid will be modified directly.
    // Returns true if a solution was found, false otherwise.
    virtual bool solve(Sudoku& sudoku) = 0;
};
