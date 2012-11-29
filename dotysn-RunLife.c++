// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// From: Glenn P. Downing
// Implemented by: Simon Doty
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

#include <sstream> // istringstream
#include <cassert> // assert
#include <iostream> // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Life.h"
#include "AbstractCell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
/*

	// Test 1 - ConwayCell

    // ------------------
    // Conway Cell 109x69 - TEMPLATE CONWAYCELL
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 50x50 ***" << endl;
        string filename = "RunLifeConway.in";
        Life<ConwayCell> life(109, 69, ConwayCell(true) , filename);
        life.printBoard(cout, 'c');
        life.simulate(283);
        life.printBoard(cout, 'c');
        life.simulate(40);
        life.printBoard(cout, 'c');
        life.simulate(2500);
		life.printBoard(cout, 'c');
        }
    catch (const invalid_argument& e) {
    cout << e.what() <<endl;
        assert(false);}
    catch (const out_of_range& e) {
     cout << e.what() <<endl;
        assert(false);}
    
	// Test 2 - Fredkin
	// ------------------
	// Fredkin Cell 20x20 TEMPLATED AS FREDKIN
	// ------------------

	try {
	cout << "*** Life<FredkinCell> 20x20 ***" << endl;
string filename = "RunLifeFredkin.in";
Life<FredkinCell> life(20, 20, FredkinCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}


// ----------
// Cell 20x20
// ----------

*/
try {
cout << "*** Life<Cell> 20x20 ***" << endl;
string filename = "RunLife.in";
Life<Cell> life(20, 20, new FredkinCell(true), filename);
// gen 0
life.printBoard(cout, 'c');
life.simulate(1);
// gen 1
life.printBoard(cout, 'c');
life.simulate(1);
// gen 2
life.printBoard(cout, 'c');
life.simulate(1);
// gen 3
life.printBoard(cout, 'c');
life.simulate(1);
// gen 4
life.printBoard(cout, 'c');
life.simulate(1);
// gen 5
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}



/*
 // Test 4

 //------------
 // Conway 10x10
 //------------


try {
cout << "*** Life<ConwayCell> 10x10 ***" << endl;
string filename = "RunLifeConway10x10.in";
Life<ConwayCell> life(10, 10, ConwayCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(100);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}


 // Test 5

 //------------
 // Conway 30x25
 //------------


try {
cout << "*** Life<ConwayCell> 30x25 ***" << endl;
string filename = "RunLifeConway30x25.in";
Life<ConwayCell> life(30, 25, ConwayCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(10);
life.printBoard(cout, 'c');
life.simulate(10);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}


 // Test 6

 //------------
 // Fredkin 30x25
 //------------


try {
cout << "*** Life<FredkinCell> 30x25 ***" << endl;
string filename = "RunLifeFredkin30x25.in";
Life<FredkinCell> life(30, 25, FredkinCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(10);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}


 // Test 7

 //---------------
 // Fredkin 44x103
 //---------------


try {
cout << "*** Life<FredkinCell> 44x103 ***" << endl;
string filename = "RunLifeFredkin44x103.in";
Life<FredkinCell> life(44, 103, FredkinCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(15);
life.printBoard(cout, 'c');
life.simulate(20);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}


 // Test 8 

 //------------------
 // Fredkin 44x103 #2
 //------------------


try {
cout << "*** Life<FredkinCell> 44x103 ***" << endl;
string filename = "RunLifeFredkin_2_44x103.in";
Life<FredkinCell> life(44, 103, FredkinCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(5);
life.printBoard(cout, 'c');
life.simulate(15);
life.printBoard(cout, 'c');
life.simulate(20);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}



 // Test 9

 //------------
 // Conway 100x100
 //------------


try {
cout << "*** Life<ConwayCell> 100x100 ***" << endl;
string filename = "RunLifeConway100x100.in";
Life<ConwayCell> life(100, 100, ConwayCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(10);
life.printBoard(cout, 'c');
life.simulate(50);
life.printBoard(cout, 'c');
life.simulate(400);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}

// Test 10

//------------------
// RunLife Cell 54x100
//------------------
try {
        cout << "*** Life<Cell> 54x100 ***" << endl;
        string filename = "RunLifeCell54x100.in";
        Life<Cell> life(54, 100, Cell(new FredkinCell(true)) , filename);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
        life.simulate(1);
        life.printBoard(cout, 'c');
            
        life.simulate(1);
        life.printBoard(cout, 'c');
        }
    catch (const invalid_argument& e) {
    cout << e.what() <<endl;
        assert(false);}
    catch (const out_of_range& e) {
     cout << e.what() <<endl;
        assert(false);}

	

 // Test 11

 //------------
 // Cell 30x30
 //------------


try {
cout << "*** Life<Cell> 30x30 ***" << endl;
string filename = "RunLifeCell30x30.in";
Life<Cell> life(30, 30, new FredkinCell(true), filename);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(1);
life.printBoard(cout, 'c');
life.simulate(10);
life.printBoard(cout, 'c');
life.simulate(50);
life.printBoard(cout, 'c');
life.simulate(400);
life.printBoard(cout, 'c');
}
catch (const invalid_argument&) {
assert(false);}
catch (const out_of_range&) {
assert(false);}

	*/

    return 0;}


