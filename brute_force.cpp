#include <array>
#include <iostream>

using namespace std;

// we must define the data structures that save the already satisfied digits
// among other stuff.

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

  // The Sudoku grid is now defined and can be used for further processing, such
  // as solving the puzzle or validating the grid.
  return 0; // Return 0 to indicate successful execution of the program.
}