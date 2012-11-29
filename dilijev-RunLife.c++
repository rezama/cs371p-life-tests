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

#include <cassert>    // assert
#include <stdexcept>  // invalid_argument, out_of_range
#include <iostream>   // cout, endl
#include <fstream>    // ifstream

#include "./AbstractCell.h"
#include "./ConwayCell.h"
#include "./FredkinCell.h"
#include "./Cell.h"
#include "./Life.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
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

        ifstream in("RunLifeConway.in", ifstream::in);
        ofstream out("RunLifeConway.out", ofstream::out);

        out << "*** Life<ConwayCell> 109x69 ***" << endl;

        Life<ConwayCell> life(in);
        life.display(out);
        life.evolve(283);  // generation 283
        life.display(out);
        life.evolve(40);  // generation 323
        life.display(out);
        life.evolve(2500);  // generation 2823
        life.display(out);
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */

        ifstream in("RunLifeFredkin.in", ifstream::in);
        ofstream out("RunLifeFredkin.out", ofstream::out);

        out << "*** Life<FredkinCell> 20x20 ***" << endl;

        Life<FredkinCell> life(in);
        life.display(out);
        life.evolve(1);  // generation 1
        life.display(out);
        life.evolve(1);  // generation 2
        life.display(out);
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ----------
    // Cell 20x20
    // ----------

    try {
        /*
        read RunLifeCell.in // assume all Fredkin cells (when starting)
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */

        ifstream in("RunLife.in", ifstream::in);
        ofstream out("RunLife.out", ofstream::out);

        out << "*** Life<Cell> 20x20 ***" << endl;

        Life<Cell> life(in);
        life.display(out);
        for (int i = 0; i < 5; ++i) {
            life.evolve();
            life.display(out);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    return 0;
}
