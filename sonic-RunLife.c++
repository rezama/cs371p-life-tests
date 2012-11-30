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
#include "AbstractCell.h"
#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

void readCell(fstream& f, size_t row, size_t col, Life<Cell>& l) {
    char ch;
    for(size_t r = 0; r < row; r++) {
        for(size_t c = 0; c < col; c++) {
            f >> ch;
            switch(ch) {
                case '.' :
                    l.setCell(r, c, new ConwayCell(false));
                    break;
                case '-' :
                    l.setCell(r, c, new FredkinCell(false, 0));
                    break;
                case '*' :
                    l.setCell(r, c, new ConwayCell(true));
                    break;
                case '0' :
                    l.setCell(r, c, new FredkinCell(true, 0));
                    break;
                case '1' :
                    l.setCell(r, c, new FredkinCell(true, 1));
                    break;
                case '2' :
                    l.setCell(r, c, new FredkinCell(true, 2));
                    break;
                case '3' :
                    l.setCell(r, c, new FredkinCell(true, 3));
                    break;
                case '4' :
                    l.setCell(r, c, new FredkinCell(true, 4));
                    break;
                case '5' :
                    l.setCell(r, c, new FredkinCell(true, 5));
                    break;
                case '6' :
                    l.setCell(r, c, new FredkinCell(true, 6));
                    break;
                case '7' :
                    l.setCell(r, c, new FredkinCell(true, 7));
                    break;
                case '8' :
                    l.setCell(r, c, new FredkinCell(true, 8));
                    break;
                case '9' :
                    l.setCell(r, c, new FredkinCell(true, 9));
                    break;
                case '+' :
                    l.setCell(r, c, new FredkinCell(true, 10));
                    break;
            }
        }
    }
}

void readConway(fstream& f, size_t row, size_t col, Life<ConwayCell>& l) {
    char ch;
    for(size_t r = 0; r < row; r++) {
        for(size_t c = 0; c < col; c++) {
            f >> ch;
            switch(ch) {
                case '.' :
                    l.setCell(r, c, ConwayCell(false));
                    break;
                case '*' :
                    l.setCell(r, c, ConwayCell(true));
                    break;
            }
        }
    }
}

void readFredkin(fstream& f, size_t row, size_t col, Life<FredkinCell>& l) {
    char ch;
    for(size_t r = 0; r < row; r++) {
        for(size_t c = 0; c < col; c++) {
            f >> ch;
            switch(ch) {
                case '-' :
                    l.setCell(r, c, FredkinCell(false, 0));
                    break;
                case '0' :
                    l.setCell(r, c, FredkinCell(true, 0));
                    break;
                case '1' :
                    l.setCell(r, c, FredkinCell(true, 1));
                    break;
                case '2' :
                    l.setCell(r, c, FredkinCell(true, 2));
                    break;
                case '3' :
                    l.setCell(r, c, FredkinCell(true, 3));
                    break;
                case '4' :
                    l.setCell(r, c, FredkinCell(true, 4));
                    break;
                case '5' :
                    l.setCell(r, c, FredkinCell(true, 5));
                    break;
                case '6' :
                    l.setCell(r, c, FredkinCell(true, 6));
                    break;
                case '7' :
                    l.setCell(r, c, FredkinCell(true, 7));
                    break;
                case '8' :
                    l.setCell(r, c, FredkinCell(true, 8));
                    break;
                case '9' :
                    l.setCell(r, c, FredkinCell(true, 9));
                    break;
                case '+' :
                    l.setCell(r, c, FredkinCell(true, 10));
                    break;
            }
        }
    }
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
        cout << "*** Life<ConwayCell> 109x69 ***" << endl << endl;;
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
        fstream f("RunLifeConway.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<ConwayCell> life(row, col, ConwayCell());

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '*') {
                    life.setCell(r, c, ConwayCell(true));
                }
            }
        }
        f.close();

        life.print();
        life.simulate(283);
        life.print();
        life.simulate(40);
        life.print();
        life.simulate(2500);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 20x20 ***" << endl << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        fstream f("RunLifeFredkin.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<FredkinCell> life(row, col, FredkinCell());

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '0') {
                    life.setCell(r, c, FredkinCell(true, 0));
                }
            }
        }
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
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
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        fstream f("RunLife.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<Cell> life(row, col, new FredkinCell());

        char ch;
        for (size_t r = 0; r < row; ++r) {
            for (size_t c = 0; c < col; ++c) {
                f >> ch;
                if (ch == '0') {
                    life.setCell(r, c, new FredkinCell(true, 0));
                }
            }
        }
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // --------
    // My Tests
    // --------

    try {
        cout << "*** Life<Cell> 20x20 ***" << endl << endl;
        fstream f("RunLifeTest4.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<Cell> life(row, col, new FredkinCell());
        readCell(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<ConwayCell> 4x4 ***" << endl << endl;
        fstream f("RunLifeTest5.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<ConwayCell> life(row, col, ConwayCell());
        readConway(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<ConwayCell> 10x80 ***" << endl << endl;
        fstream f("RunLifeTest6.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<ConwayCell> life(row, col, ConwayCell());
        readConway(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<ConwayCell> 10x80 ***" << endl << endl;
        fstream f("RunLifeTest7.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<ConwayCell> life(row, col, ConwayCell());
        readConway(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<FredkinCell> 10x80 ***" << endl << endl;
        fstream f("RunLifeTest8.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<FredkinCell> life(row, col, FredkinCell());
        readFredkin(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<FredkinCell> 10x8 ***" << endl << endl;
        fstream f("RunLifeTest9.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<FredkinCell> life(row, col, FredkinCell());
        readFredkin(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<Cell> 12x80 ***" << endl << endl;
        fstream f("RunLifeTest10.in");
        unsigned int row, col;
        f >> row;
        f >> col;
        Life<Cell> life(row, col, new FredkinCell());
        readCell(f, row, col, life);
        f.close();

        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        life.simulate(1);
        life.print();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
