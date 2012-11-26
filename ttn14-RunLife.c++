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
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "Cell.h"
#include "Life.h"

// -----------------
// Conway Cell Tests
// -----------------
void conway_cell_109_69();
void conway_cell_109_69_2();
void conway_cell_5_5();
void conway_cell_20_20();
void conway_cell_30_30();

// -----------------
// Fredkin Cell Tests
// -----------------
void fredkin_cell_20_20();
void fredkin_cell_20_20_2();
void fredkin_cell_20_20_3();
void fredkin_cell_20_20_4();

// -----------------
// Cell Tests
// -----------------
void cell_20_20();
void cell_20_20_2();
void cell_20_20_3();
void cell_20_20_4();
// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O

    try {
        conway_cell_109_69();
        conway_cell_109_69_2();
        conway_cell_5_5();
        conway_cell_20_20();
        conway_cell_30_30();

        fredkin_cell_20_20();
        fredkin_cell_20_20_2();
        fredkin_cell_20_20_3();
        fredkin_cell_20_20_4();

        cell_20_20();
        cell_20_20_2();
        cell_20_20_3();
        cell_20_20_4();
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    return 0;
}

// ------------------
// Conway Cell 109x69
// ------------------

void conway_cell_109_69() {
    /**
     read RunLifeConway.in // assume all Conway cells
     Print grid.
     Simulate 283 moves.
     Print grid.
     Simulate 40 moves.
     Print grid.
     Simulate 2500 moves.
     Print grid.
     */

    cout << "*** Life<ConwayCell> 109x69 ***" << endl;
    Life<ConwayCell> life("RunLifeConway.in");
    life.print();
    life.run(283);
    life.print();
    life.run(40);
    life.print();
    life.run(2500);
    life.print();

}

// ------------------
// Conway Cell 109x69x2
// ------------------

void conway_cell_109_69_2() {
    cout << "*** Life<ConwayCell> 109x69x2 ***" << endl;
    Life<ConwayCell> life("RunLifeConway.in");
    life.print();
    life.run(1000);
    life.print();
}

// ------------------
// Conway Cell 5x5
// ------------------
void conway_cell_5_5() {
    cout << "*** Life<ConwayCell> 5x5 ***" << endl;
    Life<ConwayCell> life("RunLifeConway5x5.in");
    life.print();
    life.run(3, true);
}

// ------------------
// Conway Cell 20x20
// ------------------

void conway_cell_20_20() {
    cout << "*** Life<ConwayCell> 20x20 ***" << endl;
    Life<ConwayCell> life("RunLifeConway20x20.in");
    life.print();
    life.run(2);
    life.print();
    life.run(5);
    life.print();
}



// ------------------
// Conway Cell 30x30
// ------------------

void conway_cell_30_30() {
    cout << "*** Life<ConwayCell> 30x30 ***" << endl;
    Life<ConwayCell> life("RunLifeConway30x30.in");
    life.print();
    life.run(5);
    life.print();
    life.run(10);
    life.print();
}
// ------------------
// Fredkin Cell 20x20
// ------------------

void fredkin_cell_20_20() {
    cout << "*** Life<FredkinCell> 20x20 ***" << endl;
    /**
     read RunLifeFredkin.in
     Print grid.
     Simulate 2 moves.
     Print every grid.
     */
    Life<FredkinCell> life("RunLifeFredkin.in");
    life.print();
    life.run(2, true);
}

// ------------------
// Fredkin Cell 20x20 2nd
// ------------------

void fredkin_cell_20_20_2() {
    cout << "*** Life<FredkinCell> 20x20x2 ***" << endl;
     Life<FredkinCell> life("RunLifeFredkin.in");
    life.print();
    life.run(20);
    life.print();
}

// ------------------
// Fredkin Cell 20x20 3rd
// ------------------

void fredkin_cell_20_20_3() {
    cout << "*** Life<FredkinCell> 20x20x3 ***" << endl;

    Life<FredkinCell> life("RunLifeFredkin.in");
    life.print();
    life.run(200);
    life.print();
}

// ------------------
// Fredkin Cell 20x20 4rd
// ------------------

void fredkin_cell_20_20_4() {
    cout << "*** Life<FredkinCell> 20x20x4 ***" << endl;

    Life<FredkinCell> life("RunLifeFredkin.in");
    life.print();
    life.run(400);
    life.print();
}

// ----------
// Cell 20x20
// ----------

void cell_20_20() {
    cout << "*** Life<Cell> 20x20 ***" << endl;
    /**
     read RunLife.in // assume all Fredkin cells
     Print grid.
     Simulate 5 moves.
     Print every grid.
     */
    Life<Cell> life("RunLife.in");
    life.print();
    life.run(5, true);
}

// ----------
// Cell 20x20x2
// ----------

void cell_20_20_2() {
    cout << "*** Life<Cell> 20x20x2 ***" << endl;

    Life<Cell> life("RunLife.in");
    life.print();
    life.run(50);
    life.print();
}

// ----------
// Cell 20x20x3
// ----------

void cell_20_20_3() {
    cout << "*** Life<Cell> 20x20x3 ***" << endl;
    Life<Cell> life("RunLife.in");
    life.print();
    life.run(100);
    life.print();
}

// ----------
// Cell 20x20x4
// ----------

void cell_20_20_4() {
    cout << "*** Life<Cell> 20x20x4 ***" << endl;
    Life<Cell> life("RunLife.in");
    life.print();
    life.run(200);
    life.print();
}
