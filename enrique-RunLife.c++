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
#include <fstream>
#include <string>
#include <stdexcept> // invalid_argument, out_of_range
#include "ConwayCell.h"
#include "Life.h"

// ----
// main
// ----

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	ofstream fout;

	fout.open("RunLifeConway.out");

	// ------------------
	// Conway Cell 109x69
	// ------------------
	try {
		Life<ConwayCell> grid("RunLifeConway.in");
		cout << "*** Life<ConwayCell> 109x69 ***" << endl;
		fout << "*** Life<ConwayCell> 109x69 ***" << endl;

		grid.display(cout, &fout);
		grid.run(283);
		grid.display(cout, &fout);
		grid.run(40);
		grid.display(cout, &fout);
		grid.run(2500);
		grid.display(cout, &fout);

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ------------------
	// Conway Cell 20x39
	// ------------------

	try {
		Life<ConwayCell> grid("RunLifeConway2.in");
		cout << "*** Life<ConwayCell> 20x39 ***" << endl;
		fout << "*** Life<ConwayCell> 20x39 ***" << endl;
		grid.display(cout, &fout);

		for (int i = 0; i < 20; i++) {
			grid.run();
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ------------------
	// Conway Cell 40x100
	// ------------------
	try {
		Life<ConwayCell> grid("RunLifeConway3.in");
		cout << "*** Life<ConwayCell> 40x100 ***" << endl;
		fout << "*** Life<ConwayCell> 40x100 ***" << endl;
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(100);
		grid.display(cout, &fout);

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// -----------------
	// Conway Cell 10x10
	// -----------------
	try {
		Life<ConwayCell> grid("RunLifeConway4.in");
		cout << "*** Life<ConwayCell> 10x10 ***" << endl;
		fout << "*** Life<ConwayCell> 10x10 ***" << endl;
		grid.display(cout, &fout);

		for (int i = 0; i < 5; i++) {
			grid.run();
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ---------------
	// Conway Cell 8x8
	// ---------------
	try {
		Life<ConwayCell> grid("RunLifeConway5.in");
		cout << "*** Life<ConwayCell> 8x8 ***" << endl;
		fout << "*** Life<ConwayCell> 8x8 ***" << endl;
		grid.display(cout, &fout);

		for (int i = 0; i < 5; i++) {
			grid.run();
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	fout.close();

	fout.open("RunLifeFredkin.out");

	// ------------------
	// Fredkin Cell 20x20
	// ------------------

	try {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		cout << "*** Life<FredkinCell> 20x20 ***" << endl;
		fout << "*** Life<FredkinCell> 20x20 ***" << endl;

		grid.display(cout, &fout);
		grid.run();
		grid.display(cout, &fout);
		grid.run();
		grid.display(cout, &fout);

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ------------------
	// Fredkin Cell 30x69
	// ------------------
	try {
		Life<FredkinCell> grid("RunLifeFredkin2.in");
		cout << "*** Life<FredkinCell> 30x69 ***" << endl;
		fout << "*** Life<FredkinCell> 30x69 ***" << endl;
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(10);
		grid.display(cout, &fout);
		grid.run(100);
		grid.display(cout, &fout);

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ------------------
	// Fredkin Cell 18x18
	// ------------------
	try {
		Life<FredkinCell> grid("RunLifeFredkin3.in");
		cout << "*** Life<FredkinCell> 18x18 ***" << endl;
		fout << "*** Life<FredkinCell> 18x18 ***" << endl;
		grid.display(cout, &fout);

		for (int i = 0; i < 10; i++) {
			grid.run();
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ------------------
	// Fredkin Cell 23x27
	// ------------------
	try {
		Life<FredkinCell> grid("RunLifeFredkin4.in");
		cout << "*** Life<FredkinCell> 23x27 ***" << endl;
		fout << "*** Life<FredkinCell> 23x27 ***" << endl;
		grid.display(cout, &fout);

		for (int i = 0; i < 10; i++) {
			grid.run();
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	fout.close();

	// ----------
	// Cell 20x20
	// ----------

	try {
		ofstream fout;
		cout << "*** Life<Cell> 20x20 ***" << endl;
		Life<Cell> grid("RunLife.in");

		grid.display(cout);
		grid.run();
		grid.display(cout);
		grid.run();
		grid.display(cout);
		grid.run();
		grid.display(cout);
		grid.run();
		grid.display(cout);
		grid.run();
		grid.display(cout);

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ----------
	// Cell 24x24
	// ----------

	try {
		ofstream fout;
		cout << "*** Life<Cell> 24x24 ***" << endl;
		Life<Cell> grid("RunLife2.in");
		grid.display(cout, &fout);

		for (int i = 0; i < 10; i++) {
			grid.run(10);
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ----------
	// Cell 30x69
	// ----------

	try {
		ofstream fout;
		cout << "*** Life<Cell> 30x69 ***" << endl;
		Life<Cell> grid("RunLife3.in");
		grid.display(cout, &fout);

		for (int i = 0; i < 11; i++) {
			grid.run(10);
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// --------
	// Cell 5x5
	// --------

	try {
		ofstream fout;
		cout << "*** Life<Cell> 5x5 ***" << endl;
		Life<Cell> grid("RunLife4.in");
		grid.display(cout, &fout);

		for (int i = 0; i < 10; i++) {
			grid.run();
			grid.display(cout, &fout);
		}

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}



	return 0;
}
