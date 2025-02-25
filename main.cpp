#include <iostream>
#include <sstream>
using namespace std;

bool is_valid(int grid [9][9], int row, int column, int number);
bool solve(int grid [9][9], int row, int column);
void get_input(int grid[9][9]);

int main() {

    int grid [9][9];
    get_input(grid);

    if (solve(grid, 0, 0)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (j == 3 || j == 6) {
                    cout << "|  ";
                }
                cout << grid[i][j] << "  ";
            }
            cout << endl;
            if (i == 2 || i == 5) {
                cout << "---------+-----------+---------" << endl;
            }
        }

    } else {
        cout << "Solution does not exist." << endl;
    }

    return 0;
}

bool is_valid(int grid [9][9], int row, int column, int number) {

    for(int i = 0; i < 9; i++) {
        if (grid[row][i] == number) {
            return false;
        }
    }

    for(int i = 0; i < 9; i++) {
        if (grid[i][column] == number) {
            return false;
        }
    }

    int corner_row = row - row % 3;
    int corner_column = column - column % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[corner_row + i][corner_column + j] == number) {
                return false;
            }
        }
    }

    return true;
}

bool solve(int grid [9][9], int row, int column) {

    if (column == 9) {
        if (row == 8) {
          return true;
        }
        row += 1;
        column = 0;
    }

    if (grid[row][column] > 0) {
        return solve(grid,row,column + 1);
    }

    for (int i = 0; i < 10; i++) {
        if (is_valid(grid,row,column,i)) {
            grid[row][column] = i;
            if (solve(grid,row,column + 1)) {
              return true;
            }
        }
        grid[row][column] = 0;
    }

    return false;
}

void get_input(int grid[9][9]) {

    cout << "Enter the Sudoku puzzle row by row (use 0 for empty cells):" << endl;
    for (int i = 0; i < 9; i++) {
        bool valid_row = false;
        while (!valid_row) {
            cout << "Row " << i + 1 << " (9 numbers, space-separated): ";
            string line;
            getline(cin, line);
            istringstream iss(line);
            int count = 0;
            bool valid = true;

            for (int j = 0; j < 9; j++) {
                if (!(iss >> grid[i][j]) || grid[i][j] < 0 || grid[i][j] > 9) {
                    valid = false;
                    break;
                }
                count++;
            }

            if (count == 9 && valid) {
                valid_row = true;
            } else {
                cout << "Invalid input! Enter exactly 9 numbers between 0 and 9." << endl;;
                cin.clear();
            }
        }
    }
}

