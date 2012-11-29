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
#include "Life.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

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
        cout << "*** Life<ConwayCell> 109x69 ***" << endl;

		Life<ConwayCell> l("RunLifeConway.in", ConwayCell());
        l.printBoard(std::cout, 0);
        l.beginLife(283);
        l.printBoard(std::cout, 283);
        l.beginLife(40);
        l.printBoard(std::cout, 323);
        l.beginLife(2500);
        l.printBoard(std::cout, 2823);
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
        
        Life<FredkinCell> l("RunLifeFredkin.in", FredkinCell());
        l.printBoard(std::cout, 0);
        l.beginLife(1);
        l.printBoard(std::cout, 1);
        l.beginLife(1);
        l.printBoard(std::cout, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<Cell> 20x20 ***" << endl;
        Life<Cell> l("RunLife.in", new FredkinCell());
        l.printBoard(std::cout, 0);
        l.beginLife(1);
        l.printBoard(std::cout, 1);
        l.beginLife(1);
        l.printBoard(std::cout, 2);
        l.beginLife(1);
        l.printBoard(std::cout, 3);
        l.beginLife(1);
        l.printBoard(std::cout, 4);
        l.beginLife(1);
        l.printBoard(std::cout, 5);
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<Cell> MyRunLifeCell.in ***" << endl;
        Life<Cell> l("MyRunLifeCell.in", new FredkinCell());
        l.printBoard(std::cout, 0);
        l.beginLife(1);
        l.printBoard(std::cout, 1);
        l.beginLife(1);
        l.printBoard(std::cout, 2);
        l.beginLife(1);
        l.printBoard(std::cout, 3);
        l.beginLife(1);
        l.printBoard(std::cout, 4);
        l.beginLife(1);
        l.printBoard(std::cout, 5);
        l.beginLife(1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        try {
        cout << "*** Life<ConwayCell> MyRunLifeConwayCell.in ***" << endl;
        Life<ConwayCell> l("MyRunLifeConwayCell.in", ConwayCell());
        l.printBoard(std::cout, 0);
        l.beginLife(2);
        l.printBoard(std::cout, 1);
        l.beginLife(4);
        l.printBoard(std::cout, 2);
        l.beginLife(6);
        l.printBoard(std::cout, 3);
        l.beginLife(8);
        l.printBoard(std::cout, 4);
        l.beginLife(10);
        l.printBoard(std::cout, 5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

        try {
        cout << "*** Life<Cell> MyRunLifeFredkinCell.in ***" << endl;
        Life<FredkinCell> l("MyRunLifeFredkinCell.in", FredkinCell());
        l.printBoard(std::cout, 0);
        l.beginLife(1);
        l.printBoard(std::cout, 1);
        l.beginLife(1);
        l.printBoard(std::cout, 2);
        l.beginLife(1);
        l.printBoard(std::cout, 3);
        l.beginLife(1);
        l.printBoard(std::cout, 4);
        l.beginLife(1);
        l.printBoard(std::cout, 5);
        l.beginLife(1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}