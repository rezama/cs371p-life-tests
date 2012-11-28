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
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
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
        cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLifeConway.in");
	f >> row;
	f >> col;
	Life<ConwayCell> myLife(row, col);
	
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current == '*')
				myLife.place(r, c, ConwayCell(true));
		}
	myLife.printBoard();
	myLife.run(283);
	myLife.printBoard();
	myLife.run(40);
	myLife.printBoard();
	myLife.run(2500);
	myLife.printBoard();
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
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLifeFredkin.in");
	f >> row;
	f >> col;
	Life<FredkinCell> myLife(row, col);
	
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-'){
				int newAge = current - '0';
				myLife.place(r, c, FredkinCell(true, newAge));
			}
		}
	myLife.printBoard();
	myLife.run(2,1);

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
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(5,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<Cell> 3x3 ***" << endl;
        /*
        read RunLife1.in // assume all Fredkin cells
        Print grid.
        Simulate 2 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife1.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(5,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<Cell> 5x5 ***" << endl;
        /*
        read RunLife2.in // assume all Fredkin cells
        Print grid.
        Simulate 15 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife2.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(15,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Life<Cell> 10x10 ***" << endl;
        /*
        read RunLife1.in // assume all Fredkin cells
        Print grid.
        Simulate 15 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife3.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(15,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<Cell> 5x5 ***" << endl;
        /*
        read RunLife4.in // assume all Fredkin cells
        Print grid.
        Simulate 15 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife4.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(15,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Life<Cell> 5x5 ***" << endl;
        /*
        read RunLife5.in // assume all Fredkin cells
        Print grid.
        Simulate 15 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife5.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(15,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    try {
        cout << "*** Life<Cell> 10x5 ***" << endl;
        /*
        read RunLife6.in // assume all Fredkin cells
        Print grid.
        Simulate 15 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife6.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(15,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Life<Cell> 5x10 ***" << endl;
        /*
        read RunLife7.in // assume all Fredkin cells
        Print grid.
        Simulate 15 move.
        Print every grid.
        */
	cout << endl;
	int row = 0;
	int col = 0;	
	fstream f("RunLife7.in");
	f >> row;
	f >> col;
	Life<Cell> myLife(row, col, Cell(new FredkinCell()));
	char current;
	for(int r = 0; r < row; r++)
		for(int c = 0; c < col; c++){
			f >> current;
			if(current != '-' && current != '.' && current != '*'){
				int newAge = current - '0';
				myLife.place(r, c, Cell(new FredkinCell(true, newAge)));
			}
			else if(current == '.')
				myLife.place(r, c, Cell(new ConwayCell(false)));
			else if(current == '*')
				myLife.place(r, c, Cell(new ConwayCell(true)));
		}
	myLife.printBoard();
	myLife.run(15,1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
