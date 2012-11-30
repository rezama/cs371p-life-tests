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
#include <stdexcept>
#include <fstream>


#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Life.h"
#include "AbstractCell.h"
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

		ifstream run1_file ("RunLifeConway.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file);
		run1_file.close();
		run_cell.print();

		run_cell.evolve(283);
		run_cell.print();
		run_cell.evolve(40);
		run_cell.print();
		run_cell.evolve(2500);
		run_cell.print();

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
		ifstream input_file ("RunLifeFredkin.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(input_file);
		input_file.close();

		run_cell.print();
		run_cell.evolve();
		run_cell.print();
		run_cell.evolve();
		run_cell.print() ;

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
		ifstream input_file ("RunLife.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(input_file, true);
		input_file.close();

		run_cell.print();

		for (int i = 0; i < 5; ++i) {
			run_cell.evolve();
			run_cell.print();
		}



	}
	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------------
	// Conway Cell 10x10 custom
	// ------------------

	try {
		cout << "*** Life<ConwayCell> 10x10 ***" << endl;
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

		ifstream run1_file ("RunLifeF.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 5; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}


	// ------------------
	// Conway Cell 20x20 custom
	// ------------------

	try {
		cout << "*** Life<ConwayCell> 20x20 ***" << endl;
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

		ifstream run1_file ("RunLifeF2.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 4; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------------
	// Fredkin Cell 10x10 custom
	// ------------------

	try {
		cout << "*** Life<FredkinCell> 10x10 ***" << endl;


		ifstream run1_file ("RunLifeF3.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 5; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}


	// ------------------
	// Fredkin Cell 20x20 custom
	// ------------------

	try {
		cout << "*** Life<FredkinCell> 20x20 ***" << endl;


		ifstream run1_file ("RunLifeF4.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 5; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------------
	// Cell Cell 10x10 custom
	// ------------------

	try {
		cout << "*** Life<CellCell> 10x10 ***" << endl;


		ifstream run1_file ("RunLifeF5.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file, true);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 2; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}


	// ------------------
	// Cell Cell 20x20 custom
	// ------------------

	try {
		cout << "*** Life<CellCell> 20x20 ***" << endl;


		ifstream run1_file ("RunLifeF6.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file, true);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 8; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}

	// ------------------
	// Conway Cell 20x20 custom
	// ------------------

	try {
		cout << "*** Life<ConwayCell> 20x20 ***" << endl;


		ifstream run1_file ("RunLifeF7.in", ios::app);
		Life<Cell> run_cell = run_cell.read_and_create(run1_file);
		run1_file.close();
		run_cell.print();

		for (int i = 0; i < 4; ++i) {
			run_cell.evolve();
			run_cell.print();
		}

	}

	catch (const invalid_argument&) {
		assert(false);}
	catch (const out_of_range&) {
		assert(false);}


	return 0;}
