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

// #include <cassert>   // assert
// #include <iostream>  // cout, endl
// #include <stdexcept> // invalid_argument, out_of_range
#include <fstream>

#include "Life.h"
#include "AbstractCell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"
#include "Cell.h"

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
        fstream f("RunLifeConway.in");
        // fstream out("RunLifeConway.out");
        ostream& out = std::cout;

        out << "*** Life<ConwayCell> 109x69 ***" << endl;
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
        unsigned int row,col;
        f >> row;
        f >> col;
        Life<ConwayCell> life(row,col,ConwayCell(),out);

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '*') {
                    life.set(r,c,ConwayCell(true));
                }
            }
        }

        life.print();
        life.run(283);
        life.print();
        life.run(40);
        life.print();
        life.run(2500);
        life.print();

        // out.close();
        f.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        fstream f("RunLifeFredkin.in");
        // fstream out("RunLifeFredkin.out");
        ostream& out = std::cout;

        out << "*** Life<FredkinCell> 20x20 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        unsigned int row,col;
        f >> row;
        f >> col;
        Life<FredkinCell> life(row,col,FredkinCell(),out);

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '0') {
                    life.set(r,c,FredkinCell(true,0));
                }
            }
        }

        life.run(2,1);

        // out.close();
        f.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        fstream f("RunLifeCell.in");
        // fstream out("RunLifeCell.out");
        ostream& out = std::cout;

        out << "*** Life<Cell> 20x20 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        unsigned int row,col;
        f >> row;
        f >> col;
        Life<Cell> life(row,col,new FredkinCell(),out);

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '0') {
                    life.set(r,c,new FredkinCell(true,0));
                }
            }
        }

        life.run(5,1);

        // out.close();
        f.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -----------------
    // Conway Cell 40x60
    // -----------------

    try {
        fstream f("RunLifeConway40x60.in");
        // fstream out("RunLifeConway40x60.out");
        ostream& out = std::cout;

        out << "*** Life<ConwayCell> 40x60 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Simulate 500 moves.
        Print every 25 grids.
        */
        unsigned int row,col;
        f >> row;
        f >> col;
        Life<ConwayCell> life(row,col,ConwayCell(),out);

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '*') {
                    life.set(r,c,ConwayCell(true));
                }
            }
        }

        life.run(500,25);

        // out.close();
        f.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 40x40
    // ------------------

    try {
        fstream f("RunLifeFredkin40x40.in");
        // fstream out("RunLifeFredkin40x40.out");
        ostream& out = std::cout;

        out << "*** Life<FredkinCell> 40x40 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 15 moves.
        Print every grid.
        */
        unsigned int row,col;
        f >> row;
        f >> col;
        Life<FredkinCell> life(row,col,FredkinCell(),out);

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '0') {
                    life.set(r,c,FredkinCell(true,0));
                }
            }
        }

        life.run(15,1);

        // out.close();
        f.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 50x50
    // ----------

    try {
        fstream f("RunLifeCell50x50.in");
        // fstream out("RunLifeCell50x50.out");
        ostream& out = std::cout;

        out << "*** Life<Cell> 50x50 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 15 moves.
        Print every grid.
        */
        unsigned int row,col;
        f >> row;
        f >> col;
        Life<Cell> life(row,col,new FredkinCell(),out);

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '0') {
                    life.set(r,c,new FredkinCell(true,0));
                }
            }
        }

        life.run(15,1);

        // out.close();
        f.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
