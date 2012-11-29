// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
    % valgrind RunLife.c++.app > RunLife.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include <string>
#include <fstream>
#include "Life.h"

/**
 * This method reads info in from an ifstream and builds the 0th instance of
 * Life.
 *
 * @param in an ifstream object
 * @return Life<T>* a pointer to a Life instance of type T.
 */
template <typename T>
void readFile(std::ifstream& in, Life<T>& life, int rows) {
  string line;
  if (in.is_open()) {
    in.ignore();
    for (int i = 0 ; i < rows; ++i) {
      line.clear();
      getline(in, line);
      for (size_t j = 0; j < line.size(); ++j) {
        if (line[j] == '*' || line[j] == '0') {
          life.cellGrid[i][j].comeAlive();
          life.population++;
        }
      }
    }
  }
  else cout << "Input file not open." << endl;
}

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 109x69 ***" << endl << endl;

        ifstream input("RunLifeConway.in");
        int rows;
        int cols;
        input >> rows;
        input >> cols;
        Life<ConwayCell> life(rows, cols, ConwayCell());
        readFile(input, life, rows);
        input.close();
        life.display(cout, 0);
        life.run(283, 283);
        life.display(cout, 283);
        life.run(40, 40);
        life.display(cout, 283+40);
        life.run(2500, 2500);
        life.display(cout, 283+40+2500);
        */

        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 283 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        Simulate 2500 moves.
        Print grid.
        */
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 20x20 ***" << endl << endl;

        ifstream input("RunLifeFredkin.in");
        int rows;
        int cols;
        input >> rows;
        input >> cols;
        Life<FredkinCell> life(rows, cols, FredkinCell());
        readFile(input, life, rows);
        input.close();
        life.display(cout, 0);
        life.run(1, 1);
        life.display(cout, 1);
        life.run(1, 1);
        life.display(cout, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<Cell> 20x20 ***" << endl << endl;

        int rows;
        int cols;
        ifstream input("RunLife.in");
        input >> rows;
        input >> cols;
        Life<Cell> life(rows, cols, new FredkinCell());
        readFile(input, life, rows);
        life.run(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    //
    //------------ begin my acceptance tests ----------------
    //

    // ------------------
    // Conway Glider 20x20
    // ------------------

    try {
        cout << "*** zach ConwayGlider - Life<ConwayCell> 20x20 ***" << endl << endl;

        int rows;
        int cols;
        ifstream input("zach-ConwayGlider.in");
        input >> rows;
        input >> cols;
        Life<ConwayCell> life(rows, cols, ConwayCell());
        readFile(input, life, rows);
        life.run(16,1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Conway Blinker 10x10
    // ------------------
    try {
        cout << "*** zach ConwayBlinker - Life<ConwayCell> 10x10 ***" << endl;

        cout << endl;

        int rows;
        int cols;
        ifstream input("zach-ConwayBlinker.in");
        input >> rows;
        input >> cols;
        Life<ConwayCell> life(rows, cols, ConwayCell());
        readFile(input, life, rows);
        life.run(4,1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Conway Tumbler 20x20
    // ------------------


    try {
        cout << "*** zach ConwayTumbler - Life<ConwayCell> 20x20 ***" << endl;

        cout << endl;

        int rows;
        int cols;
        ifstream input("zach-ConwayTumbler.in");
        input >> rows;
        input >> cols;
        Life<ConwayCell> life(rows, cols, ConwayCell());
        readFile(input, life, rows);
        life.run(14,2);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Fireworks 20x20
    // ------------------

    try {
        cout << "*** zach FredkinFireworks - Life<FredkinCell> 20x20 ***" << endl << endl;

        int rows;
        int cols;
        ifstream input("zach-FredkinFireworks.in");
        input >> rows;
        input >> cols;
        Life<FredkinCell> life(rows, cols, FredkinCell());
        readFile(input, life, rows);
        life.run(14,2);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Fireworks(Cell)
    // ------------------

    try {
        cout << "*** zach FredkinFireworksCell - Life<Cell> 20x20 ***" << endl << endl;

        int rows;
        int cols;
        ifstream input("zach-FredkinFireworks.in");
        input >> rows;
        input >> cols;
        Life<Cell> life(rows, cols, new FredkinCell());
        readFile(input, life, rows);
        life.run(14,2);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------------
    // Fredkin Pentomino Replicator 50x50
    // ------------------

    try {
        cout << "*** zach FredkinPentominoReplicator - Life<FredkinCell> 50x50 ***" << endl;
        cout << endl;

        int rows;
        int cols;
        ifstream input("zach-FredkinPentominoReplicator.in");
        input >> rows;
        input >> cols;
        Life<FredkinCell> life(rows, cols, FredkinCell());
        readFile(input, life, rows);
        life.run(20,2);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    
    // ------------------
    // Cell Pentomino Replicator 50x50
    // ------------------

    try {
        cout << "*** zach FredkinPentominoReplicatorCell - Life<Cell> 50x50 ***" << endl;

        int rows;
        int cols;
        ifstream input("zach-FredkinPentominoReplicator.in");
        input >> rows;
        input >> cols;
        Life<Cell> life(rows, cols, new FredkinCell());
        readFile(input, life, rows);
        life.run(40,2);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Conway Ants 6x50
    // ------------------

    try {
        cout << "*** zach ConwayPentomino - Life<ConwayCell> 20x20 ***" << endl << endl;

        int rows;
        int cols;
        ifstream input("zach-ConwayPentomino.in");
        input >> rows;
        input >> cols;
        Life<ConwayCell> life(rows, cols, ConwayCell());
        readFile(input, life, rows);
        life.run(1103,50);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
