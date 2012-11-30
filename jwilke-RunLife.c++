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
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_LATEX = NO

To document the program:
doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // cout, endl
#include <fstream> //ifstream
#include <sstream> //istringstream
#include <string.h> //string
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"
#include "Cell.h"

using namespace std;

// ---------------
// char_is_conway
// ---------------

bool char_is_conway(char x) {
	if(x == '*' || x == '.') return true;
	return false;
}

// ---------------
// read_for_conway
// ---------------

void read_for_conway(deque< deque< ConwayCell > >& grid, ifstream& file, int rows, int cols) {
	string line;
	for(int r = 0; r < rows+2; r++) {
		if(r > 0 && r <= rows) {
			getline(file, line);
		}

		for(int c = 0; c < cols+2; c++) {
			if(r > 0 && r <= rows && c > 0 && c <= cols) {
				grid[r].push_back(ConwayCell(line[c-1]));
			} else {
				grid[r].push_back(ConwayCell());
			}
		}
	}
}


// ----------------
// read_for_fredkin
// ----------------

void read_for_fredkin(deque< deque< FredkinCell > >& grid, ifstream& file, int rows, int cols) {
	string line;
	for(int r = 0; r < rows+2; r++) {
		if(r > 0 && r <= rows) {
			getline(file, line);
		}

		for(int c = 0; c < cols+2; c++) {
			if(r > 0 && r <= rows && c > 0 && c <= cols) {
				grid[r].push_back(FredkinCell(line[c-1]));
			} else {
				grid[r].push_back(FredkinCell());
			}
		}
	}
}

// ----------------
// read_for_cell
// ----------------

void read_for_cell(deque< deque< Cell > >& grid, ifstream& file, int rows, int cols) {
	string line;
	for(int r = 0; r < rows+2; r++) {
		if(r > 0 && r <= rows) {
			getline(file, line);
		}
		
		for(int c = 0; c < cols+2; c++) {
			if(r > 0 && r <= rows && c > 0 && c <= cols) {
				if(char_is_conway(line[c-1])) {
					ConwayCell* cCell = new ConwayCell(line[c-1]);
					grid[r].push_back(Cell(cCell));
				} else {
					FredkinCell* fCell = new FredkinCell(line[c-1]);
					grid[r].push_back(Cell(fCell));
				}
			} else {
				FredkinCell* moat = new FredkinCell(false);
				grid[r].push_back(Cell(moat));
			}
		}
	}
}

// ---------
// read_line
// ---------

int read_line(string line) {
	istringstream in(line);
	int x = 0;
	in >> x;
	return x;
}


// ----
// main
// ----

int main () {
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	ifstream Conwayfile;
	ifstream Fredkinfile;
	ifstream Cellfile;
	ofstream ConwayOut;
	ofstream FredkinOut;
	//ofstream CellOut;
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
		Print grid. */
		Conwayfile.open("RunLifeConway.in");
		ConwayOut.open("RunLifeConway.out");
		ConwayOut << "*** Life<ConwayCell> 109x69 ***" << endl;
		int rows = 0, cols = 0;
		
		string line;
		getline(Conwayfile, line);
		rows = read_line(line);
		getline(Conwayfile, line);
		cols = read_line(line);
		
		deque< deque< ConwayCell > > cell_grid = deque< deque< ConwayCell > >(rows+2, deque<ConwayCell>());
		read_for_conway(cell_grid, Conwayfile, rows, cols);
		Life<ConwayCell> sim(rows, cols, cell_grid);
		
		sim.print(ConwayOut);
		sim.simulate(283);
		sim.print(ConwayOut);
		sim.simulate(40);
		sim.print(ConwayOut);
		sim.simulate(2500);
		sim.print(ConwayOut);

	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	// ------------------
	// Fredkin Cell 20x20
	// ------------------

	try {
		cout << "*** Life<FredkinCell> 20x20 ***" << endl;
		/*
		read RunLifeFredkin.in // assume all Fredkin cells
		Print grid.
		Simulate 2 moves.
		Print every grid. */
		Fredkinfile.open("RunLifeFredkin.in");
		FredkinOut.open("RunLifeFredkin.out");
		FredkinOut << "*** Life<FredkinCell> 20x20 ***" << endl;
		int rows = 0, cols = 0;
		
		string line;
		getline(Fredkinfile, line);
		rows = read_line(line);
		getline(Fredkinfile, line);
		cols = read_line(line);

		deque< deque< FredkinCell > > cell_grid = deque< deque< FredkinCell > >(rows+2, deque<FredkinCell>());
		read_for_fredkin(cell_grid, Fredkinfile, rows, cols);
		
		Life<FredkinCell> sim2(rows, cols, cell_grid);
		
		sim2.print(FredkinOut);
		sim2.simulate(1);
		sim2.print(FredkinOut);
		sim2.simulate(1);
		sim2.print(FredkinOut);
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
		read RunLifeCell.in // assume all Fredkin cells
		Print grid.
		Simulate 5 moves.
		Print every grid.
		*/
		Cellfile.open("RunLife.in");
		//CellOut.open("RunLife.out");
		cout << "*** Life<Cell> 20x20 ***" << endl;
		int rows = 0, cols = 0;
		
		string line;
		getline(Cellfile, line);
		rows = read_line(line);
		getline(Cellfile, line);
		cols = read_line(line);

		deque< deque< Cell > > cell_grid = deque< deque< Cell > >(rows+2, deque<Cell>());
		read_for_cell(cell_grid, Cellfile, rows, cols);
		
		Life<Cell> sim3(rows, cols, cell_grid);
		
		sim3.print();
		for(int i = 0; i < 5; ++i) {
			sim3.simulate(1);
			sim3.print();
		}

		
		
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	try {
		/*
		Finish reading RunLifeConway.in, RunLifeFredkin.in, and RunLifeCell.in
		For each remaining case:		
		Print grid.
		Simulate 100 moves.
		Print every grid.
		*/
		int rows = 0, cols = 0;
		string line;

		while(true) { //Finish RunLifeConway.in
			getline(Conwayfile, line);
			if(line.compare("END") == 0) break;
			rows = read_line(line);
			getline(Conwayfile, line);
			cols = read_line(line);
			ConwayOut << "*** Life<ConwayCell> " << rows << "x" << cols << " ***" << endl;
			
			deque< deque< ConwayCell > > cell_grid = deque< deque< ConwayCell > >(rows+2, deque<ConwayCell>());
			read_for_conway(cell_grid, Conwayfile, rows, cols);
			Life<ConwayCell> sim(rows, cols, cell_grid);
		
			sim.print(ConwayOut);
			for(int i = 0; i < 100; ++i) {
				sim.simulate(1);
				sim.print(ConwayOut);
			}
		}

		while(true) { //Finish RunLifeFredkin.in
			getline(Fredkinfile, line);
			if(line.compare("END") == 0) break;
			rows = read_line(line);
			getline(Fredkinfile, line);
			cols = read_line(line);
			FredkinOut << "*** Life<FredkinCell> " << rows << "x" << cols << " ***" << endl;
			
			deque< deque< FredkinCell > > cell_grid = deque< deque< FredkinCell > >(rows+2, deque<FredkinCell>());
			read_for_fredkin(cell_grid, Fredkinfile, rows, cols);
			Life<FredkinCell> sim(rows, cols, cell_grid);
		
			sim.print(FredkinOut);
			for(int i = 0; i < 100; ++i) {
				sim.simulate(1);
				sim.print(FredkinOut);
			}
		}

		while(true) { //Finish RunLifeCell.in
			getline(Cellfile, line);
			if(line.compare("END") == 0) break;
			rows = read_line(line);
			getline(Cellfile, line);
			cols = read_line(line);
			cout << "*** Life<Cell> " << rows << "x" << cols << " ***" << endl;
			
			deque< deque< Cell > > cell_grid = deque< deque< Cell > >(rows+2, deque<Cell>());
			read_for_cell(cell_grid, Cellfile, rows, cols);
			Life<Cell> sim(rows, cols, cell_grid);
		
			sim.print();
			for(int i = 0; i < 100; ++i) {
				sim.simulate(1);
				sim.print();
			}
		}		
		
	} catch (const invalid_argument&) {
		assert(false);
	} catch (const out_of_range&) {
		assert(false);
	}

	Conwayfile.close();
	Fredkinfile.close();
	Cellfile.close();
	ConwayOut.close();
	FredkinOut.close();
    return 0;
}
