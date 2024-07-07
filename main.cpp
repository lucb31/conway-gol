#include <iostream>

const int n_rows = 5;
const int n_cols = 5;

// Todo: Unit tests for tick calculation: Confirm oscillators
// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
// clang-format off
// Blinker (period 2)
int blinkerState[5][5] = {
  0, 0, 0, 0, 0, 
  0, 0, 1, 0, 0, 
  0, 0, 1, 0, 0, 
  0, 0, 1, 0, 0, 
  0, 0, 0, 0, 0
};
// Toad (period 2)
int toadState[5][5] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
                                 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0};
// clang-format on

void initState(int (&state)[n_rows][n_rows]) {
  std::copy(&blinkerState[0][0], &blinkerState[0][0] + 5 * 5, &state[0][0]);
  return;
  for (int row = 0; row < n_rows; row++) {
    for (int col = 0; col < n_cols; col++) {
      // Initialize every field with 1
      state[row][col] = 1;
    }
  }
}

void printState(int (&state)[n_rows][n_rows]) {
  for (int row = 0; row < n_rows; row++) {
    for (int col = 0; col < n_cols; col++) {
      std::cout << state[row][col] << " ";
    }
    std::cout << "\n";
  }
}
int main() {
  std::cout << "Welcome to Conways Game of Life\n";

  int state[n_rows][n_cols];

  // Initialize state
  initState(state);
  std::cout << "--- Initial state ---\n";
  printState(state);

  int maxTicks = 10;
  for (int tick = 0; tick < maxTicks; tick++) {
    // Store copy of current state before starting to modify it
    int prevState[n_rows][n_cols];
    std::copy(&state[0][0], &state[0][0] + n_rows * n_cols, &prevState[0][0]);
    for (int row = 0; row < n_rows; row++) {
      for (int col = 0; col < n_cols; col++) {
        // Calculate state in next tick based on neighbors

        // Calculate nr of alive neighbors
        int neighbors = 0;
        int cells_checked = 0;
        int start_row = row > 0 ? row - 1 : row;
        int end_row = (row < n_rows - 1 ? row + 1 : row);
        int start_col = col > 0 ? col - 1 : col;
        int end_col = (col < n_cols - 1 ? col + 1 : col);

        for (int inner_row = start_row; inner_row <= end_row; inner_row++) {
          for (int inner_col = start_col; inner_col <= end_col; inner_col++) {
            // Ignore current cell
            if (inner_row == row && inner_col == col) {
              continue;
            }
            if (prevState[inner_row][inner_col] == 1) {
              neighbors++;
            }
            cells_checked++;
          }
        }

        // std::cout << "[" << row << "][" << col << "]: " << neighbors << "("
        //           << cells_checked << ", " << start_row << "-" << end_row <<
        //           ","
        //           << start_col << "- " << end_col << ") \n";

        // Check if alive cell dies
        if (state[row][col] == 1) {
          if (
              // Cell dies by underpopulation
              neighbors < 2
              // Overpopulation
              || neighbors > 3) {
            state[row][col] = 0;
          }
        }
        // Check if dead cell becomes alive
        else if (neighbors == 3) {
          state[row][col] = 1;
        }
      }
    }
    std::cout << "--- Tick " << tick << " ---\n";
    printState(state);
  }
}
