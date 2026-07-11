/*
 * How to compile and run this project:
 *
 * 1. Create a build directory and configure CMake:
 *    mkdir -p build && cd build && cmake ..
 *
 * 2. Compile the project:
 *    make
 *
 * 3. Run the executable (from the build directory):
 *    ./sudoku_solver ../data/20240415.csv
 */

#include "BacktrackingSolver.hpp"
#include "Sudoku.hpp"
#include "SudokuLoader.hpp"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[]) {
  // Default file to load if no arguments are provided
  std::string filename = "../data/20240415.csv";

  // Read filename from command line arguments
  if (argc > 1) {
    filename = argv[1];
  }

  std::cout << "Loading Sudoku from " << filename << "...\n";
  auto loaded_grid = loadSudokuFromFile(filename);
  if (!loaded_grid) {
    std::cerr << "Failed to load Sudoku.\n";
    return 1;
  }

  // Initialize the Sudoku board with the loaded grid
  Sudoku board(*loaded_grid);
  std::cout << "Initial board:\n";
  board.print();

  // Use polymorphism to instantiate the solver.
  // If you add OrToolsSolver later, you can swap it right here.
  std::unique_ptr<SudokuSolver> solver = std::make_unique<BacktrackingSolver>();

  std::cout << "\nSolving...\n";
  // The solver mutates the board in place
  if (solver->solve(board)) {
    std::cout << "Sudoku solved successfully!\n";
    board.print();

    // Print specific statistics if the solver is BacktrackingSolver
    auto *backtracking = dynamic_cast<BacktrackingSolver *>(solver.get());
    if (backtracking) {
      std::cout << "\nNumber of backtracking iterations: "
                << backtracking->getIterations() << "\n";
    }
  } else {
    std::cout << "Failed to solve Sudoku.\n";
  }

  return 0;
}
