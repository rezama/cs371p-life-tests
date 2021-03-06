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
#include <vector>
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

using namespace std;

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------

    // try {
    //     cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    //     Life<ConwayCell> life("RunLifeConway.in");
    //     life.print();
    //     life.simulate(40);
    //     life.print();
    //     life.simulate(283-40);
    //     life.print();
    //     life.simulate(2500-283);
    //     life.print();
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
    //     }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    // try {
    //      cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    //      Life<FredkinCell> life("RunLifeFredkin.in");
    //      life.simulate(2,1);
    // // /*
    // //     read RunLifeFredkin.in // assume all Fredkin cells
    // //     Print grid.
    // //     Simulate 2 moves.
    // //     Print every grid.
    // //     */
    //     }
    // catch (const invalid_argument&) {
    //     assert(false);}
    // catch (const out_of_range&) {
    //     assert(false);}

    // // ----------
    // // Cell 20x20
    // // ----------

    try {
           cout << "*** Life<Cell> 20x20 ***" << endl;
           Life<Cell> life("RunLife.in");
           life.simulate(5,1);
    //     /*
    //     read RunLife.in // assume all Fredkin cells
    //     Print grid.
    //     Simulate 5 moves.
    //     Print every grid.
    //     */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}