/*

    State.cpp

    Implementation file for state class

*/

#include "State.hpp"
#include <string>
#include <iostream>

// Assignment from a temp object
State State::operator=(State&& rval) {
    this->n = rval.n;
    this->queensPlaced = rval.queensPlaced;
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            this->queens[i][j] = rval.queens[i][j];
        }
    }
    return *this;
}

// Copy Constructor
State::State(const State& board) {
    this->n = board.n;
    this->queensPlaced = board.queensPlaced;
    this->queens = new bool*[n];
    for (int i = 0; i < n; i++) {
        this->queens[i] = new bool[n];
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (board.queens[i][j] == 0) {
                this->queens[i][j] = false;
            } else if (board.queens[i][j] == 1) {
                this->queens[i][j] = true;
            }
        }
    }
}

// Costruct from input file
State::State(std::ifstream& input){
    std::string row;
    std::getline(input, row);
    n = (row.length() + 1) / 2;
    queensPlaced = 0;
    queens = new bool*[n];
    for (int i = 0; i < n; i++) {
        queens[i] = new bool[n];
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < row.length(); i += 2) {
            if (row[i] == '0') {
                queens[i / 2][j] = false;
            } else if (row[i] == '1') {
                queens[i / 2][j] = true;
                queensPlaced++;
            } else {
                std::cerr << "Improper input file format\n";
                exit(1); 
            }
        }
        if (input.eof()) {
            std::cerr << "Improper input file format\n";
            exit(1);
        }
        std::getline(input, row);
    }
    if (!input.eof()) {
        std::cerr << "Improper input file format\n";
        exit(1);
    }
}

// Successor function (Constructor with a State arg and a Move portrayed as indexed coordinates)
State::State(State& board, int col, int row) {
    this->n = board.n;
    this->queens = new bool*[n];
    for (int i = 0; i < n; i++) {
        this->queens[i] = new bool[n];
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (board.queens[i][j] == 0) {
                this->queens[i][j] = false;
            } else {
                this->queens[i][j] = true;
            }
        }
    }
    if (!this->queens[col][row]) {
        this->queens[col][row] = true;
        this->queensPlaced = board.queensPlaced + 1;
    } else {
        this->queensPlaced = board.queensPlaced;
    }
}

// Construct a blank nxn board 
State::State(int size) {
    n = size;
    queensPlaced = 0;
    queens = new bool*[n];
    for (int i = 0; i < n; i++) {
        queens[i] = new bool[n];
    }
}

// Class Destructor
State::~State() {
    for (int i = 0; i < n; i++) {
        delete[] queens[i];
    }
    delete[] queens;
}

// Output the solution to an output.csv file.
void State::output2CSV(std::ofstream& output) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output << queens[j][i];
            if (j != n - 1) {
                output << ",";
            }
        }
        output << "\n";
    }
}

// Predicate function for checking for a goal state
bool State::isGoal() {
    return queensPlaced == n;
}

// get function for board size
int State::size() {
    return n;
}

// Check for a blank board (no solution state)
bool State::isBlank() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j ++) {
            if (queens[i][j] == true) {
                return false;
            }
        }
    }
    return true;
}

// Clear a board. Used as return value for a no solution
void State::makeBlank() {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            queens[i][j] = false;
        }
    }
}

// Show the board in cout
void State::display() {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            std::cout << queens[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// check if the current board follows the no attacking queens rules
bool State::valid(int x, int y) {
    if (this->diagonals(x, y) && this->checkRowCol(x, y)) {
        return true;
    }
    return false;
}

// Check if the rows and columns are clear
bool State::checkRowCol(int x, int y) {
    for (int i = 0; i < y; i++) {       // Left of coordinate 
        if (queens[x][i])
            return false;
    }
    for (int i = 0; i < x; i++) {       // Below coordinate
        if (queens[i][y])
            return false;
    }
    for (int i = y + 1; i < n; i++) {   // Right of coordinate
        if (queens[x][i])
            return false;
    }
    for (int i = x + 1; i < n; i++) {   // Above coordinate
        if (queens[i][y])
            return false;
    }
    return true;
}

// check if the diagonals are clear
bool State::diagonals(int x, int y) {
    int i = 1;
    while (x - i >= 0 && y - i >= 0) {          // SW
        if (queens[x - i][y - i] == true) {
            return false;
        }
        i++;
    }
    i = 1;
    while (x + i < n && y - i >= 0) {           // SE
        if (queens[x + i][y - i] == true) {
            return false;
        }
        i++;
    }
    i = 1;
    while (x - i >= 0 && y + i < n) {           // NW
        if (queens[x - i][y + i] == true) {
            return false;
        }
        i++;
    }
    i = 1;
    while (x + i < n && y + i < n) {            // NE
        if (queens[x + i][y + i] == true) {
            return false;
        }
        i++;
    }
    return true;
}
