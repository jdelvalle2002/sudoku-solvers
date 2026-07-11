#include <array>
#include <iostream>
#include <optional>

using namespace std;

// we must define the data structures that save the already satisfied digits
// among other stuff.
//

class Sudoku {
public:
  array<array<bool, 9>, 9> fixed_values{};
  array<array<int, 9>, 9> sudoku_grid{};
  array<array<bool, 10>, 9>
      rows{}; // for each row we use a boolean array of size 10 where each index
              // represents a digit (1-9)
  array<array<bool, 10>, 9>
      columns{}; // for each column we use a boolean array of size 10 where each
                 // index represents a digit (1-9)
  array<array<bool, 10>, 9>
      boxes{}; // for each box we use a boolean array of size 10 where each
               // index represents a digit (1-9)

  optional<array<array<int, 9>, 9>>
      solutions{}; // we define an atribute to save the solution

  int backtrackingIterations = 0;
  int stepCount = 0;
  // constructors
  Sudoku(const array<array<int, 9>, 9> &grid) {
    this->sudoku_grid = grid;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (grid[i][j] != 0) {
          fixed_values[i][j] = true;     // mark as fixed
          rows[i][grid[i][j]] = true;    // mark the digit as used in the row
          columns[j][grid[i][j]] = true; // mark the digit as used in the column
          boxes[i / 3 * 3 + j / 3][grid[i][j]] =
              true; // mark the digit as used in the box
        }
      }
    }
  }

  // methods
  void printSudoku() {
    for (int i = 0; i < 9; i++) {
      if (i % 3 == 0 && i != 0) {
        for (int j = 0; j < 9; j++) {
          cout << "---";
        }
        cout << "--" << endl;
      }
      for (int j = 0; j < 9; j++) {
        if (j % 3 == 0 && j != 0) {
          cout << "|";
        }
        if (fixed_values[i][j]) {
          cout << "*" << sudoku_grid[i][j];
        } else
          cout << " " << sudoku_grid[i][j];
        cout << " ";
      }
      cout << endl;
    }
  }
  // Helper methods
  void resetSudoku() {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (!fixed_values[i][j]) {
          int digit = sudoku_grid[i][j];
          sudoku_grid[i][j] = 0;
          rows[i][digit] = false;
          columns[j][digit] = false;
          boxes[i / 3 * 3 + j / 3][digit] = false;
        }
      }
    }
    backtrackingIterations = 0;
    stepCount = 0;
    solutions = {};
    cout << "Sudoku reset successfully!\n";
    printSudoku();
  }

  bool isSafe(int row, int col, int num) {
    return !rows[row][num] && !columns[col][num] &&
           !boxes[row / 3 * 3 + col / 3][num];
  }

  void saveSolution() {
    solutions = sudoku_grid;
    cout << "Solution saved successfully!\n";
    printSudoku();
  }

  // Solution Methods
  bool solveSudoku() {
    backtrackingIterations++;       // we increment the number of backtracking
                                    // iterations
    for (int i = 0; i < 9; i++) {   // iterate through each row
      for (int j = 0; j < 9; j++) { // iterate through each column
        if (sudoku_grid[i][j] == 0) {  // if the cell is empty
          for (int num = 1; num <= 9; num++) { // try each digit from 1 to 9
            if (isSafe(i, j, num)) {           // if the digit is safe to place
              stepCount++;
              sudoku_grid[i][j] = num; // place the digit
              rows[i][num] = true;     // mark the digit as used in the row
              columns[j][num] = true;  // mark the digit as used in the column
              boxes[i / 3 * 3 + j / 3][num] =
                  true;            // mark the digit as used in the box
              if (solveSudoku()) { // recursive call to solveSudoku
                return true; // return true if the recursive call returns true
              }
              sudoku_grid[i][j] = 0;   // reset the cell
              rows[i][num] = false;    // unmark the digit as used in the row
              columns[j][num] = false; // unmark the digit as used in the column
              boxes[i / 3 * 3 + j / 3][num] =
                  false; // unmark the digit as used in the box
            }
          }
          return false; // backtracking
        }
      }
    }
    saveSolution();
    return true; // Sudoku solved
  }
};

int main() {
  // Define a 9x9 Sudoku grid using std::array. Each inner array
  // represents a row in the grid, and each integer represents a cell in that
  // row. A value of 0 indicates an empty cell, while values from 1 to 9
  // represent filled cells.
  array<array<int, 9>, 9> sudoku = {{{5, 6, 0, 7, 0, 0, 0, 0, 0},
                                     {2, 0, 0, 8, 4, 0, 5, 0, 0},
                                     {0, 0, 0, 1, 0, 0, 0, 0, 4},

                                     {0, 0, 7, 9, 0, 0, 0, 1, 0},
                                     {6, 0, 3, 0, 0, 0, 2, 0, 7},
                                     {0, 1, 0, 0, 0, 2, 9, 0, 0},

                                     {3, 0, 0, 2, 0, 0, 0, 0, 0},
                                     {0, 0, 8, 6, 1, 0, 0, 0, 2},
                                     {0, 0, 0, 4, 0, 0, 0, 5, 6}}};

  Sudoku mySudoku(sudoku);

  // test printSudoku
  mySudoku.printSudoku();
  bool solved = mySudoku.solveSudoku();
  cout << "Solved: " << (solved ? "YES" : "NO") << endl;
  cout << "\nNumber of backtracking iterations: "
       << mySudoku.backtrackingIterations << endl;
  mySudoku.resetSudoku();
  // The Sudoku grid is now defined and can be used for further processing, such
  // as solving the puzzle or validating the grid.
  return 0; // Return 0 to indicate successful execution of the program.
}