
// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
    % valgrind RunLife.c++.app > RunLife.out

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
#include "AbstractCell.h"
#include "ConwayCell.h"



// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
//        cout << "*** in main ***" << endl;
    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
        ofstream output;
        output.open("RunLifeConway.out");
        output << "*** Life<ConwayCell> 109x69 ***" << endl;
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
        Life<ConwayCell> life("RunLifeConway.in");
        life.printGrid(output);
        life.run(283);
        life.printGrid(output);
        life.run(40);
        life.printGrid(output);
        life.run(2500);
        life.printGrid(output);
        output.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        ofstream output;
        output.open("RunLifeFredkin.out");
	output << "*** Life<FredkinCell> 20x20 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.*/
        Life<FredkinCell> life("RunLifeFredkin.in");
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output); 
        output.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        ofstream output;
        output.open("RunLife.out");
        output << "*** Life<Cell> 20x20 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.*/
      
        Life<Cell> life("RunLife.in", new FredkinCell());
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output); 
        output.close(); 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // ConwayCell 3x3
    // ----------

    try {
        ofstream output;
        output.open("RunLifeConway3x3.out");
        output << "*** Life<ConwayCell> 3x3 ***" << endl;
        Life<ConwayCell> life("RunLifeConway3x3.in");
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // FredkinCell 3x3
    // ----------

    try {
        ofstream output;
        output.open("RunLifeFredkin3x3.out");
        output << "*** Life<FredkinCell> 3x3 ***" << endl;
        Life<FredkinCell> life("RunLifeFredkin3x3.in");
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 3x3
    // ----------
    try {
        ofstream output;
        output.open("RunLifeCell3x3.out");
        output << "*** Life<Cell> 3x3 ***" << endl;
        Life<Cell> life("RunLifeCell3x3.in", new FredkinCell());
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // ConwayCell 20x20
    // ----------

    try {
        ofstream output;
        output.open("RunLifeConway20x20.out");
        output << "*** Life<ConwayCell> 20x20 ***" << endl;
        Life<ConwayCell> life("RunLifeConway20x20.in");
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(100);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // FredkinCell 20x20
    // ----------

    try {
        ofstream output;
        output.open("RunLifeFredkin20x20.out");
        output << "*** Life<FredkinCell> 20x20 ***" << endl;
        Life<FredkinCell> life("RunLifeFredkin20x20.in");
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(9);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(9);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(100);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // Cell 20x20
    // ----------
    try {
        ofstream output;
        output.open("RunLifeCell20x20.out");
        output << "*** Life<Cell> 20x20 ***" << endl;
        Life<Cell> life("RunLifeCell20x20.in", new FredkinCell());
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(50);
        life.printGrid(output);
        life.run(50);
        life.printGrid(output);


        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // ConwayCell 30x69
    // ----------

    try {
        ofstream output;
        output.open("RunLifeConway30x69.out");
        output << "*** Life<ConwayCell> 30x69 ***" << endl;
        Life<ConwayCell> life("RunLifeConway30x69.in");
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // FredkinCell 30x69
    // ----------

    try {
        ofstream output;
        output.open("RunLifeFredkin30x69.out");
        output << "*** Life<FredkinCell> 30x69 ***" << endl;
        Life<FredkinCell> life("RunLifeFredkin30x69.in");
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(9);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(9);
        life.printGrid(output);
        life.run(1);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(100);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // Cell 30x69
    // ----------
    try {
        ofstream output;
        output.open("RunLifeCell30x69.out");
        output << "*** Life<Cell> 30x69 ***" << endl;
        Life<Cell> life("RunLifeCell30x69.in", new FredkinCell());
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(50);
        life.printGrid(output);
        life.run(50);
        life.printGrid(output);


        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // ConwayCell 40x100
    // ----------

    try {
        ofstream output;
        output.open("RunLifeConway40x100.out");
        output << "*** Life<ConwayCell> 40x100 ***" << endl;
        Life<ConwayCell> life("RunLifeConway40x100.in");
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(10);
        life.printGrid(output);
        life.run(100);
        life.printGrid(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
