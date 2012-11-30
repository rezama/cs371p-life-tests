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
#include <fstream>
#include "Life.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell
    // ------------------

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLifeConway.in");
        outFile.open("RunLifeConway.out");
        outFile << "*** Life<ConwayCell> 109x69 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<ConwayCell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '.') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(283);
        outFile << grid.print_grid() << "\n";
        grid.evolve(40);
        outFile << grid.print_grid() << "\n";
        grid.evolve(2500);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLifeConway2.in");
        outFile.open("RunLifeConway2.out");
        outFile << "*** Life<ConwayCell> 2x2 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<ConwayCell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '.') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(2);
        outFile << grid.print_grid() << "\n";
        grid.evolve(3);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLifeConway3.in");
        outFile.open("RunLifeConway3.out");
        outFile << "*** Life<ConwayCell> 2x3 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<ConwayCell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '.') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(2);
        outFile << grid.print_grid() << "\n";
        grid.evolve(3);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell
    // ------------------

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLifeFredkin.in");
        outFile.open("RunLifeFredkin.out");
        outFile << "*** Life<FredkinCell> 20x20 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<FredkinCell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLifeFredkin2.in");
        outFile.open("RunLifeFredkin2.out");
        outFile << "*** Life<FredkinCell> 2x2 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<FredkinCell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLifeFredkin3.in");
        outFile.open("RunLifeFredkin3.out");
        outFile << "*** Life<FredkinCell> 2x2 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<FredkinCell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell
    // ----------

    try {
        cout << "*** Life<Cell> 20x20 ***\n" << endl;
        ifstream inFile;
        inFile.open("RunLife.in");
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<Cell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        cout << grid.print_grid() << endl;
        grid.evolve(1);
        cout << grid.print_grid() << endl;
        grid.evolve(1);
        cout << grid.print_grid() << endl;
        grid.evolve(1);
        cout << grid.print_grid() << endl;
        grid.evolve(1);
        cout << grid.print_grid() << endl;
        grid.evolve(1);
        cout << grid.print_grid() << endl;
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLife2.in");
        outFile.open("RunLife2.out");
        outFile << "*** Life<Cell> 2x2 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<Cell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLife3.in");
        outFile.open("RunLife3.out");
        outFile << "*** Life<Cell> 2x3 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<Cell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        ifstream inFile;
        ofstream outFile;
        inFile.open("RunLife4.in");
        outFile.open("RunLife4.out");
        outFile << "*** Life<Cell> 1x1 ***\n\n";
        int r;
        inFile >> r;
        int c;
        inFile >> c;
        Life<Cell> grid(r, c);
        char value;
        for (int a = 0; a < r; ++a) {
          for (int b = 0; b < c; ++b) {
            inFile >> value;
            if (value != '-') {
              grid.make_alive(a, b);
            }
          }
        }
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid() << "\n";
        grid.evolve(1);
        outFile << grid.print_grid();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
