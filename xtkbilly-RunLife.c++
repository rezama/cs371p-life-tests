// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.app
    % valgrind RunLife.app > RunLife.out

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
#include <string>

#include "Life.h"
#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

template <typename T>
Life<T> readGameBoard(std::string filename) {
	ifstream inf;
	inf.open(filename);
	if (inf.fail()) {
		throw std::invalid_argument("Attempted to open bad file" + filename);
	}
	
	int row,col;
	inf >> row;
	inf >> col;
	
	Life<T> game(row, col);
	char c;
	int i=0, j=0;
	
	while (inf >> c) {
		if (j >= col) {
			++i;
			j = 0;
		}
		
		/* switch (c){
			case '.':
				game.insert(ConwayCell('.'), i, j);
			//case '-':
			default:
				throw exception();
					
		} */
		
		if (c != '.' && c != '-') {
			game.insert(T(c), i, j);
		}
		
		++j;
		
	}
	
	inf.close();
	return game;
}
//<ConwayCell>readGameBoard

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    ifstream infile;
	ofstream outfile;
	
	cout << "RunLife.c++" << endl;

    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
		outfile.open("RunLifeConway.out");
        outfile << "*** Life<ConwayCell> 109x69 ***" << endl;
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
		
		Life<ConwayCell> game = readGameBoard<ConwayCell>("RunLifeConway.in");
		
		
		game.printGeneration(outfile);
		int n = 1;
		while (n <= 2823) {
			game.runNextGeneration();
			if (n == 283 || n == 323 || n == 2823) {
				game.printGeneration(outfile);
			}
			++n;
		}

		outfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
		outfile.open("RunLifeFredkin.out");
        outfile << "*** Life<FredkinCell> 20x20 ***" << endl << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
		Life<FredkinCell> game = readGameBoard<FredkinCell>("RunLifeFredkin.in");
		game.printGeneration(outfile);
		
		int n = 0;
		while (n < 2) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		}
		
		outfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
		outfile.open("RunLife.out");
        outfile << "*** Life<Cell> 20x20 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
		
		ifstream inf;
		inf.open("RunLife.in");
		if (inf.fail()) {
			throw std::invalid_argument("Attempted to open bad file RunLife.in");
		}
		
		int row,col;
		inf >> row;
		inf >> col;
		
		Life<Cell> game(row, col);
		char c;
		int i=0, j=0;
		
		while (inf >> c) {
			if (j >= col) {
				++i;
				j = 0;
			}
			
			if(c == '.' || c == '*'){
				game.insert(new ConwayCell(c), i, j);
			}
			else{
				game.insert(new FredkinCell(c), i, j);
			} 
			
			++j;
			
		}
		
		inf.close();

		//Life<Cell> game = readGameBoard<Cell>("RunLife.in");
		game.printGeneration(outfile);
			
		int n = 0;
		while (n < 5) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		} 
		
		outfile.close();
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ------------------
    // Conway Cell 6x6
    // ------------------

    try {
		outfile.open("RunLifeConway2.out");
        outfile << "*** Life<ConwayCell> 6x6 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 5 moves.
		Print every grid.
        */
		
		Life<ConwayCell> game = readGameBoard<ConwayCell>("RunLifeConway2.in");
		
		
		game.printGeneration(outfile);
		int n = 1;
		while (n <= 5) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		}

		outfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ------------------
    // Conway Cell 15x15
    // ------------------

    try {
		outfile.open("RunLifeConway3.out");
        outfile << "*** Life<ConwayCell> 15x15 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 6 moves.
		Print every grid.
        */
		
		Life<ConwayCell> game = readGameBoard<ConwayCell>("RunLifeConway3.in");
		
		game.printGeneration(outfile);
		int n = 1;
		while (n <= 6) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		}

		outfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ------------------
    // Fredkin Cell 32x32
    // ------------------

    try {
		outfile.open("RunLifeFredkin2.out");
        outfile << "*** Life<FredkinCell> 32x32 ***" << endl << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 100 moves.
        Print every grid.
        */
		Life<FredkinCell> game = readGameBoard<FredkinCell>("RunLifeFredkin2.in");
		game.printGeneration(outfile);
		
		int n = 0;
		while (n < 100) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		}
		
		outfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
	
	// ------------------
    // Fredkin Cell 8x8
    // ------------------

    try {
		outfile.open("RunLifeFredkin3.out");
        outfile << "*** Life<FredkinCell> 8x8 ***" << endl << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 100 moves.
        Print every grid.
        */
		Life<FredkinCell> game = readGameBoard<FredkinCell>("RunLifeFredkin3.in");
		game.printGeneration(outfile);
		
		int n = 0;
		while (n < 100) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		}
		
		outfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // Cell 10x10
    // ----------

    try {
		outfile.open("RunLife2.out");
        outfile << "*** Life<Cell> 10x10 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 61 moves.
        Print every grid.
        */
		
		ifstream inf;
		inf.open("RunLife2.in");
		if (inf.fail()) {
			throw std::invalid_argument("Attempted to open bad file RunLife2.in");
		}
		
		int row,col;
		inf >> row;
		inf >> col;
		
		Life<Cell> game(row, col);
		char c;
		int i=0, j=0;
		
		while (inf >> c) {
			if (j >= col) {
				++i;
				j = 0;
			}
			
			if(c == '.' || c == '*'){
				game.insert(new ConwayCell(c), i, j);
			}
			else{
				game.insert(new FredkinCell(c), i, j);
			} 
			
			++j;
			
		}
		
		inf.close();

		//Life<Cell> game = readGameBoard<Cell>("RunLife.in");
		game.printGeneration(outfile);
			
		int n = 0;
		while (n < 61) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		} 
		
		outfile.close();
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // Cell 24x24
    // ----------

    try {
		outfile.open("RunLife3.out");
        outfile << "*** Life<Cell> 24x24 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 100 moves.
        Print every grid.
        */
		
		ifstream inf;
		inf.open("RunLife3.in");
		if (inf.fail()) {
			throw std::invalid_argument("Attempted to open bad file RunLife3.in");
		}
		
		int row,col;
		inf >> row;
		inf >> col;
		
		Life<Cell> game(row, col);
		char c;
		int i=0, j=0;
		
		while (inf >> c) {
			if (j >= col) {
				++i;
				j = 0;
			}
			
			if(c == '.' || c == '*'){
				game.insert(new ConwayCell(c), i, j);
			}
			else{
				game.insert(new FredkinCell(c), i, j);
			} 
			
			++j;
			
		}
		
		inf.close();

		//Life<Cell> game = readGameBoard<Cell>("RunLife.in");
		game.printGeneration(outfile);
			
		int n = 0;
		while (n < 100) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		} 
		
		outfile.close();
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	// ----------
    // Cell 16x16
    // ----------

    try {
		outfile.open("RunLife4.out");
        outfile << "*** Life<Cell> 16x16 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 66 moves.
        Print every grid.
        */
		
		ifstream inf;
		inf.open("RunLife4.in");
		if (inf.fail()) {
			throw std::invalid_argument("Attempted to open bad file RunLife4.in");
		}
		
		int row,col;
		inf >> row;
		inf >> col;
		
		Life<Cell> game(row, col);
		char c;
		int i=0, j=0;
		
		while (inf >> c) {
			if (j >= col) {
				++i;
				j = 0;
			}
			
			if(c == '.' || c == '*'){
				game.insert(new ConwayCell(c), i, j);
			}
			else{
				game.insert(new FredkinCell(c), i, j);
			} 
			
			++j;
			
		}
		
		inf.close();

		//Life<Cell> game = readGameBoard<Cell>("RunLife.in");
		game.printGeneration(outfile);
			
		int n = 0;
		while (n < 66) {
			game.runNextGeneration();
			game.printGeneration(outfile);
			++n;
		} 
		
		outfile.close();
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
		
	cout << "Done." << endl;
    return 0;}
