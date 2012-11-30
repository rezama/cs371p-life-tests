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
#include <fstream>   // ifstream
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"

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

        ifstream in("RunLifeConway.in");
        ofstream out("RunLifeConway.out");
        out << "*** Life<ConwayCell> 109x69 ***" << endl << endl;

        Life<ConwayCell> life(in);
        life.print(out);
        life.simulate(283);
        life.print(out);
        life.simulate(40);
        life.print(out);
        life.simulate(2500);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Conway Cell 5x5
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 5x5 ***" << endl;

        ifstream in("josephw-RunLifeConwaySml.in");
        ofstream out("josephw-RunLifeConwaySml.out");
        out << "*** Life<ConwayCell> 5x5 ***" << endl << endl;

        Life<ConwayCell> life(in);
        life.print(out);
        for (int i=0; i<3; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(10);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Conway Cell 20x25
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 20x25 ***" << endl;

        ifstream in("josephw-RunLifeConwayLrg.in");
        ofstream out("josephw-RunLifeConwayLrg.out");
        out << "*** Life<ConwayCell> 20x25 ***" << endl << endl;

        Life<ConwayCell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(20);
        life.print(out);
        life.simulate(100);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Conway Cell Random (10x20)
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 10x20 ***" << endl;

        ifstream in("josephw-RunLifeConwayRand.in");
        ofstream out("josephw-RunLifeConwayRand.out");
        out << "*** Life<ConwayCell> 10x20 ***" << endl << endl;

        Life<ConwayCell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(5);
        life.print(out);
        life.simulate(20);
        life.print(out);
        cout.flush();
        out.close();
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
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */

        ifstream in("RunLifeFredkin.in");
        ofstream out("RunLifeFredkin.out");
        out << "*** Life<FredkinCell> 20x20 ***" << endl << endl;

        Life<FredkinCell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 5x5
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 5x5 ***" << endl;

        ifstream in("josephw-RunLifeFredkinSml.in");
        ofstream out("josephw-RunLifeFredkinSml.out");
        out << "*** Life<FredkinCell> 5x5 ***" << endl << endl;

        Life<FredkinCell> life(in);
        life.print(out);
        for (int i=0; i<3; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(10);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x25
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 20x25 ***" << endl;

        ifstream in("josephw-RunLifeFredkinLrg.in");
        ofstream out("josephw-RunLifeFredkinLrg.out");
        out << "*** Life<FredkinCell> 20x25 ***" << endl << endl;

        Life<FredkinCell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(20);
        life.print(out);
        life.simulate(100);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell Random (10x20)
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 10x20 ***" << endl;

        ifstream in("josephw-RunLifeFredkinRand.in");
        ofstream out("josephw-RunLifeFredkinRand.out");
        out << "*** Life<FredkinCell> 10x20 ***" << endl << endl;

        Life<FredkinCell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(5);
        life.print(out);
        life.simulate(20);
        life.print(out);
        cout.flush();
        out.close();
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
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */

        ifstream in("RunLife.in");
        ofstream out("RunLife.out");
        out << "*** Life<Cell> 20x20 ***" << endl << endl;
        Life<Cell> life(in);
        life.print(out);
        for (int i=0; i<5; ++i) {
            life.simulate(1, true);
            life.print(out);
        }
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Cell 5x5
    // ------------------

    try {
        cout << "*** Life<Cell> 5x5 ***" << endl;

        ifstream in("josephw-RunLifeCellSml.in");
        ofstream out("josephw-RunLifeCellSml.out");
        out << "*** Life<Cell> 5x5 ***" << endl << endl;

        Life<Cell> life(in);
        life.print(out);
        for (int i=0; i<3; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(10);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Cell 20x25
    // ------------------

    try {
        cout << "*** Life<Cell> 20x25 ***" << endl;

        ifstream in("josephw-RunLifeCellLrg.in");
        ofstream out("josephw-RunLifeCellLrg.out");
        out << "*** Life<Cell> 20x25 ***" << endl << endl;

        Life<Cell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(20);
        life.print(out);
        life.simulate(100);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Cell Random (10x20)
    // ------------------

    try {
        cout << "*** Life<Cell> 10x20 ***" << endl;

        ifstream in("josephw-RunLifeCellRand.in");
        ofstream out("josephw-RunLifeCellRand.out");
        out << "*** Life<Cell> 10x20 ***" << endl << endl;

        Life<Cell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(5);
        life.print(out);
        life.simulate(20);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Cell Random Large (20x20)
    // ------------------

    try {
        cout << "*** Life<Cell> 20x20 ***" << endl;

        ifstream in("josephw-RunLifeCellRandLrg.in");
        ofstream out("josephw-RunLifeCellRandLrg.out");
        out << "*** Life<Cell> 20x20 ***" << endl << endl;

        Life<Cell> life(in);
        life.print(out);
        for (int i=0; i<2; ++i) {
            life.simulate(1);
            life.print(out);
        }
        life.simulate(20);
        life.print(out);
        life.simulate(100);
        life.print(out);
        cout.flush();
        out.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}

