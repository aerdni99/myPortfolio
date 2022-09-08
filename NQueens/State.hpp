/*

    State.hpp

    Header file for state class

*/

#include <fstream>

class State {
  public:

    // Assignment from a temp object
    State operator=(State&&);

    // Copy Constructor
    State(const State&);

    // Costruct from input file
    State(std::ifstream&);

    // Successor function (Constructor with a State arg and a Move portrayed as indexed coordinates)
    State(State&, int, int);

    // Construct a blank nxn board 
    State(int);

    // Class Destructor
    ~State();

    // Output the solution to an output.csv file.
    void output2CSV(std::ofstream&);

    // Predicate function for checking for a goal state
    bool isGoal();

    // get function for board size
    int size();

    // Check for a blank board
    bool isBlank();

    // Clear a board. Used as return value for a no solution
    void makeBlank();

    // Show the board in cout (FOR TESTING)
    void display();

    // check if the current board follows the no attacking queens rules
    bool valid(int, int);

  private:
    // Size of board and total queens
    int n;

    // To hold the location of each queen on the board
    bool** queens;

    // check if the rows and columns are clear
    bool checkRowCol(int x, int y);

    // check if the diagonals are clear
    bool diagonals(int x, int y);

};
