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
#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <ratio>
#include <string>

int main(int argc, char *argv[]) {
  std::vector<Sudoku> all_sudokus;

  if (argc <= 1) {
    std::string filename = argv[1];
    std::cout << "Loading Sudokus from " << filename << "...\n";
    auto loaded_grids = loadSudokusFromFile(filename, 100000);
    if (!loaded_grid) {
      std::cerr << "Failed to load Sudoku.\n";
      return 1;
    }
    board = Sudoku(*loaded_grid);
  } else {
    std::cout << "No file provided. Using default Sudoku grid from image...\n";
    std::array<std::array<int, 9>, 9> default_grid = {
        {{0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 3, 0, 8, 5},
         {0, 0, 1, 0, 2, 0, 0, 0, 0},

         {0, 0, 0, 5, 0, 7, 0, 0, 0},
         {0, 0, 4, 0, 0, 0, 1, 0, 0},
         {0, 9, 0, 0, 0, 0, 0, 0, 2},

         {5, 0, 0, 0, 0, 0, 0, 7, 3},
         {0, 0, 2, 0, 1, 0, 0, 0, 0},
         {0, 0, 0, 0, 4, 0, 0, 0, 9}}};
    board = Sudoku(default_grid);
  }

  std::cout << "Initial board:\n";
  board.print();

  // Use polymorphism to instantiate the solver.
  // If you add OrToolsSolver later, you can swap it right here.
  std::unique_ptr<SudokuSolver> solver = std::make_unique<BacktrackingSolver>();

  std::cout << "\nSolving...\n";

  auto start = std::chrono::high_resolution_clock::now();
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
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

  if (duration.count() < 1000)
    std::cout << "Time taken to solve Sudoku: " << duration.count()
              << " microseconds\n";
  else if (duration.count() < 1000000)
    std::cout << "Time taken to solve Sudoku: " << duration.count() / 1000.0
              << " milliseconds\n";
  else
    std::cout << "Time taken to solve Sudoku: " << duration.count() / 1000000.0
              << " seconds\n";
  return 0;
}
