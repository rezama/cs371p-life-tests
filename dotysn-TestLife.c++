// -------------------------
// projects/life/FredkinCell.h
// Copyright (C) 2012
// From: Glenn P. Downing
// Implemented by: Simon Doty 
// -------------------------

/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestLife.c++ -o TestLife.c++.app
    % valgrind TestLife.c++.app >& TestLife.c++.out
*/

// --------
// includes
// --------

#define private public
#include <stdexcept>
#include <sstream>   // istringstream
#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <vector>    // testing vecotr
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#include "Life.h"
#include "AbstractCell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"


using namespace std;

// -----------
// TestLife
// -----------

struct TestLife : CppUnit::TestFixture {

    //////////////////////Life.h////////////////////////
	
	
	// ----
	// Life_Constructor
	// ----
	void test_Life_Constructor_1 () {
		   
		string filename = "RunLifeConway.in";       
		Life<ConwayCell> life1(109, 69, ConwayCell(true), "RunLifeConway.in");
		CPPUNIT_ASSERT (life1._generation == 0 && life1._population == 35);	
		CPPUNIT_ASSERT(true);	        	
	}

	void test_Life_Constructor_2 () {        
		string filename = "RunLifeFredkin.in";       
		Life<FredkinCell> life1(20, 20, FredkinCell(true), filename);
		CPPUNIT_ASSERT(life1._population == 4 );	        	
	}

	void test_Life_Constructor_3 () {        
		string filename = "RunLife.in";       
		Life<Cell> life1(20, 20, new FredkinCell(true), filename);
		CPPUNIT_ASSERT(life1._population == 6 &&  life1.current[0][0].getState() == false &&  life1.current[9][10].getState() == true);	        	
	}

	// ----------------------
	// test_Life_simulate
	//-----------------------

	void test_Life_simulate_1 () {        
		string filename = "RunLife.in";       
		Life<Cell> life1(20, 20, new FredkinCell(true), filename);
		life1.simulate(1);
		CPPUNIT_ASSERT(life1._generation == 1);
	}


	void test_Life_simulate_2 () {        
		string filename = "RunLifeFredkin.in"; 
		Life<FredkinCell> life1(20, 20, FredkinCell(true), filename);
		life1.simulate(2);
		CPPUNIT_ASSERT(life1._generation == 2 && life1._population == 16 && life1.current[0][0].getState() == false);
	}

	void test_Life_simulate_3 () {        
		string filename = "RunLifeConway.in"; 
		Life<ConwayCell> life1(109, 69, ConwayCell(true), filename);
		life1.simulate(283);
		CPPUNIT_ASSERT(life1._generation == 283 && life1._population == 492 && life1.current[9][0].getState() == false );
	}

	// -----------------
	// Life_printBoard
	// -----------------
	void test_Life_printBoard_1 () { 
		string filename = "Test_printBoard_1.in";
		ostringstream w; 
		Life<ConwayCell> life1(5, 5, ConwayCell(true), filename );   		
		life1.printBoard(w, 'c');
		string board = "Generation = 0, Population = 5.\n..*..\n..*..\n..*..\n..*..\n..*..\n\n";
		CPPUNIT_ASSERT(w.str() ==  board);
	}

	void test_Life_printBoard_2 () { 
		string filename = "Test_printBoard_2.in";
		ostringstream w; 
		Life<ConwayCell> life1(12, 5, ConwayCell(true), filename );   		
		life1.printBoard(w, 'c');
		string board = "Generation = 0, Population = 7.\n*****\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n*...*\n\n";
		CPPUNIT_ASSERT(w.str() ==  board);
	}

	void test_Life_printBoard_3 () { 
		string filename = "Test_printBoard_2.in";
		ostringstream w; 
		Life<ConwayCell> life1(12, 5, ConwayCell(true), filename );   		
		life1.simulate(1);
		life1.printBoard(w, 'c');
		string board = "Generation = 1, Population = 6.\n.***.\n.***.\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n.....\n\n";
		CPPUNIT_ASSERT(w.str() ==  board);
	}


	///////////////////AbstractCell.h////////////////

	//----------------
	//test_Abstract_Constructor
	//-----------------

	void test_Abstract_constructor_1 () { 
		FredkinCell cell; //since abstract has pure virtual, it can't be constructed
			          // only tested through concrete cells
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}


	void test_Abstract_constructor_2 () { 
		FredkinCell cell; //since abstract has pure virtual, it can't be constructed
		cell.setState('0');             
		CPPUNIT_ASSERT(cell._state == true);        		        	
	}


	void test_Abstract_constructor_3 () { 
		ConwayCell cell; //since abstract has pure virtual, it can't be constructed
			          // only tested through concrete cells
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}

	//---------------
	//Test_abstract_constructor2
	//----------------

	void test_Abstract2_constructor_1 () { 
		FredkinCell cell(false); //since abstract has pure virtual, it can't be constructed
			          // only tested through concrete cells
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}


	void test_Abstract2_constructor_2 () { 
		FredkinCell cell(true); //since abstract has pure virtual, it can't be constructed
		cell.setState('0');             
		CPPUNIT_ASSERT(cell._state == true);        		        	
	}


	void test_Abstract2_constructor_3 () { 
		ConwayCell cell(false); //since abstract has pure virtual, it can't be constructed
			          // only tested through concrete cells
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}


	/////////////////////////////FredkinCell/////////////////////////////

	//-----------------------
	// test_fredkin_constructors
	//-----------------------

	void test_fredkin_constructor_1 () { 
		FredkinCell cell(false); 
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}

	void test_fredkin_constructor_2 () { 
		FredkinCell cell(false); 
		cell.setState('0');             
		CPPUNIT_ASSERT(cell._state == true && cell._age == 0);        		        	
	}

	void test_fredkin_constructor_3 () { 
		FredkinCell cell; 
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}

	//-----------------------
	// test_fredkin_copy_constructor
	//-----------------------

	void test_fredkin_copy_1 () { 
		FredkinCell cell; 
		FredkinCell newCell(cell);
		CPPUNIT_ASSERT(newCell._state == false);        		        	
	}

	void test_fredkin_copy_2 () { 
		FredkinCell cell(true); 
		FredkinCell newCell(cell);             
		CPPUNIT_ASSERT(newCell._state == true && newCell._age == 0);        		        	
	}

	void test_fredkin_copy_3 () { 
		FredkinCell cell;
		cell.setState('0');
		FredkinCell newCell(cell);
		CPPUNIT_ASSERT(newCell._state == true);        		        	
	}

	//----------------------
	// test_fredkin_clone
	//---------------------

	void test_fredkin_clone_1 () {	
		FredkinCell cell;
		cell.setState('0');
		FredkinCell* ptr = cell.clone();
		CPPUNIT_ASSERT( (*ptr)._age == 0 && (*ptr)._state == true);
		delete ptr;
	}

	void test_fredkin_clone_2 () {	
		FredkinCell cell(true);
		cell.setState('-');
		FredkinCell* ptr = cell.clone();
		CPPUNIT_ASSERT( (*ptr)._age == 0 && (*ptr)._state == false);
		delete ptr;
	}

	void test_fredkin_clone_3 () {	
		FredkinCell cell;
		cell.setState('8');
		FredkinCell* ptr = cell.clone();
		CPPUNIT_ASSERT( (*ptr)._age == 8 && (*ptr)._state == true);
		delete ptr;
	}

	//---------------------
	//test_fredkin_setstate
	//---------------------

	void test_fredkin_setState_1 () {
		FredkinCell cell;
		cell.setState('0');
		CPPUNIT_ASSERT(cell._age == 0 && cell._state == true);
	}
	void test_fredkin_setState_2() {
		FredkinCell cell(true);
		cell.setState('-');
		CPPUNIT_ASSERT(cell._state == false);
	}

	void test_fredkin_setState_3() {
		FredkinCell cell(false);
		cell.setState('5');
		CPPUNIT_ASSERT(cell._state == true);
	}

	//---------------------
	//test_fredkin_getstate
	//---------------------

	void test_fredkin_getState_1 () {
		FredkinCell cell;
		cell.setState('0');
		CPPUNIT_ASSERT(cell.getState() == true);
	}
	void test_fredkin_getState_2() {
		FredkinCell cell(true);
		cell.setState('-');
		CPPUNIT_ASSERT(cell.getState() == false);
	}

	void test_fredkin_getState_3() {
		FredkinCell cell(false);
		cell.setState('5');
		CPPUNIT_ASSERT(cell.getState() == true);
	}

	//-----------------------
	//test_fredkin_changeState
	//----------------------

	void test_fredkin_changeState_1 () {
		vector<FredkinCell> row(2, FredkinCell());
		vector<vector<FredkinCell> > grid(2, row);
		grid[0][0].setState('-');
		grid[0][1].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('-');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == false);
	}

	void test_fredkin_changeState_2 () {
		vector<FredkinCell> row(2, FredkinCell());
		vector<vector<FredkinCell> > grid(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('-');
		
		bool change = grid[0][1].changeState(grid, 0, 1);
		CPPUNIT_ASSERT(change == true);
	}

	void test_fredkin_changeState_3 () {
		vector<FredkinCell> row(3, FredkinCell());
		vector<vector<FredkinCell> > grid(3, row);
		grid[0][0].setState('-');
		grid[0][1].setState('0');
		grid[0][2].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('0');
		grid[1][2].setState('-');
		grid[2][0].setState('-');
		grid[2][1].setState('-');
		grid[2][2].setState('0');
	
		
		bool change = grid[1][2].changeState(grid, 1, 2);
		bool change2 = grid[1][1].changeState(grid, 1, 1);
		CPPUNIT_ASSERT(change == false && change2 == false);
	}


	//-----------------
	//test_fredkin_updateState
	//-----------------

	void test_fredkin_updateState_1 () {
		vector<FredkinCell> row(2, FredkinCell());
		vector<vector<FredkinCell> > grid(2, row);
		vector<FredkinCell> rown(2, FredkinCell());
		vector<vector<FredkinCell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('-');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('-');
		gridn[1][1].setState('-');
	
		gridn[0][0].updateState(grid, 0, 0, true);
		CPPUNIT_ASSERT(gridn[0][0].getState() == false);
	
	}

	void test_fredkin_updateState_2 () {
		vector<FredkinCell> row(2, FredkinCell());
		vector<vector<FredkinCell> > grid(2, row);
		vector<FredkinCell> rown(2, FredkinCell());
		vector<vector<FredkinCell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('-');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('-');
		gridn[1][1].setState('-');
	
		gridn[0][1].updateState(grid, 0, 1, true);
		CPPUNIT_ASSERT(gridn[0][0].getState() == true);		
	}

	void test_fredkin_updateState_3 () {
		vector<FredkinCell> row(2, FredkinCell());
		vector<vector<FredkinCell> > grid(2, row);
		vector<FredkinCell> rown(2, FredkinCell());
		vector<vector<FredkinCell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('7');
		grid[1][1].setState('7');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('7');
		gridn[1][1].setState('-');
	
		gridn[1][0].updateState(grid, 1, 0, false);
		CPPUNIT_ASSERT(gridn[1][0].getState() == true && gridn[1][0]._age == 8);
	
	}

	//------------------------
	// change_State_cell_in_fredkin
	//------------------------

	void test_fredkinC_changeState_1 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('-');
		
		bool change = grid[0][1].changeState(grid, 0, 1);
		CPPUNIT_ASSERT(change == true);
	}

	void test_fredkinC_changeState_2 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('3');
		grid[1][1].setState('5');
		
		bool change = grid[0][1].changeState(grid, 0, 1);
		CPPUNIT_ASSERT(change == false);
	}

	void test_fredkinC_changeState_3 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('-');
		grid[0][1].setState('0');
		grid[1][0].setState('0');
		grid[1][1].setState('-');
		
		bool change = grid[0][1].changeState(grid, 0, 1);
		CPPUNIT_ASSERT(change == true);
	}


	//---------------
	//updateState_cel_in_fredkin
	//---------------
	void test_fredkinC_updateState_1 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('7');
		grid[1][1].setState('7');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('7');
		gridn[1][1].setState('-');
	
		gridn[1][0].updateState(grid, 1, 0, false);
		CPPUNIT_ASSERT(gridn[1][0].getState() == true);		
	}

	void test_fredkinC_updateState_2 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('7');
		grid[1][1].setState('7');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('7');
		gridn[1][1].setState('-');
	
		gridn[1][0].updateState(grid, 1, 0, false);
		CPPUNIT_ASSERT(gridn[1][1].getState() == false);		
	}

	void test_fredkinC_updateState_3 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('7');
		grid[1][1].setState('7');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('7');
		gridn[1][1].setState('-');
	
		gridn[1][1].updateState(grid, 1, 0, false);
		CPPUNIT_ASSERT(gridn[1][1].getState() == true);		
	}

	//-------------------------
	// fredkin_printCell
	//------------------------

	void test_fredkin_printCell_1() {
		FredkinCell cell;
		cell.setState('0');
		char ch = cell.printCell();
		CPPUNIT_ASSERT(ch == '0');	
	}
	void test_fredkin_printCell_2() {
		FredkinCell cell;
		cell.setState('-');
		char ch = cell.printCell();
		CPPUNIT_ASSERT(ch == '-');	
	}

	void test_fredkin_printCell_3() {
		FredkinCell cell;
		cell.setState('5');
		char ch = cell.printCell();
		CPPUNIT_ASSERT(ch == '5');	
	}

	///////////////////////////CONWAYCELL/////////////////////////

	//-----------------------
	// test_conway_constructors
	//-----------------------

	void test_conway_constructor_1 () { 
		ConwayCell cell(false); 
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}

	void test_conway_constructor_2 () { 
		ConwayCell cell(false); 
		try { 
			cell.setState('0');             
		}
		catch (out_of_range& e){
			CPPUNIT_ASSERT(true);
		}
	}

	void test_conway_constructor_3 () { 
		ConwayCell cell; 
		CPPUNIT_ASSERT(cell._state == false);        		        	
	}

	//-----------------------
	// test_conway_copy_constructor
	//-----------------------

	void test_conway_copy_1 () { 
		ConwayCell cell; 
		ConwayCell newCell(cell);
		CPPUNIT_ASSERT(newCell._state == false);        		        	
	}

	void test_conway_copy_2 () { 
		ConwayCell cell(true); 
		ConwayCell newCell(cell);             
		CPPUNIT_ASSERT(newCell._state == true);        		        	
	}

	void test_conway_copy_3 () { 
		ConwayCell cell;
		cell.setState('*');
		ConwayCell newCell(cell);
		CPPUNIT_ASSERT(newCell._state == true);        		        	
	}


	//----------------------
	// test_conway_clone
	//---------------------

	void test_conway_clone_1 () {	
		ConwayCell cell;
		cell.setState('*');
		ConwayCell* ptr = cell.clone();
		CPPUNIT_ASSERT( (*ptr)._state == true);
		delete ptr;
	}

	void test_conway_clone_2 () {	
	 	ConwayCell cell(true);
		cell.setState('.');
		ConwayCell* ptr = cell.clone();
		CPPUNIT_ASSERT((*ptr)._state == false);
		delete ptr;
	}

	void test_conway_clone_3 () {	
		ConwayCell cell;
		cell.setState('*');
		ConwayCell* ptr = cell.clone();
		CPPUNIT_ASSERT( (*ptr)._state == true);
		delete ptr;
	}

	//---------------------
	//test_conway_setstate
	//---------------------

	void test_conway_setState_1 () {
		ConwayCell cell;
		cell.setState('*');
		CPPUNIT_ASSERT( cell._state == true);
	}
	void test_conway_setState_2() {
		ConwayCell cell(true);
		cell.setState('.');
		CPPUNIT_ASSERT(cell._state == false);
	}

	void test_conway_setState_3() {
		ConwayCell cell(false);
		cell.setState('*');
		CPPUNIT_ASSERT(cell._state == true);
	}

	//---------------------
	//test_conway_getstate
	//---------------------

	void test_conway_getState_1 () {
		ConwayCell cell;
		cell.setState('*');
		CPPUNIT_ASSERT(cell.getState() == true);
	}
	void test_conway_getState_2() {
		ConwayCell cell(true);
		cell.setState('.');
		CPPUNIT_ASSERT(cell.getState() == false);
	}

	void test_conway_getState_3() {
		ConwayCell cell(false);
		cell.setState('*');
		CPPUNIT_ASSERT(cell.getState() == true);
	}

	//-----------------------
	//test_conway_changeState
	//----------------------

	void test_conway_changeState_1 () {
		vector<ConwayCell> row(2, ConwayCell());
		vector<vector<ConwayCell> > grid(2, row);
		grid[0][0].setState('.');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == false);
	}

	void test_conway_changeState_2 () {
		vector<ConwayCell> row(2, ConwayCell());
		vector<vector<ConwayCell> > grid(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == true);
	}

	void test_conway_changeState_3 () {
		vector<ConwayCell> row(2, ConwayCell());
		vector<vector<ConwayCell> > grid(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][1].changeState(grid, 0, 1);
		CPPUNIT_ASSERT(change == false);
	}



	//-----------------
	//test_conway_updateState
	//-----------------

	void test_conway_updateState_1 () {
		vector<ConwayCell> row(2, ConwayCell());
		vector<vector<ConwayCell> > grid(2, row);
		vector<ConwayCell> rown(2, ConwayCell());
		vector<vector<ConwayCell> > gridn(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('.');
		gridn[1][1].setState('.');
	
		gridn[0][0].updateState(grid, 0, 0, true);
		CPPUNIT_ASSERT(gridn[0][0].getState() == false);
	
	}

	void test_conway_updateState_2 () {
		vector<ConwayCell> row(2, ConwayCell());
		vector<vector<ConwayCell> > grid(2, row);
		vector<ConwayCell> rown(2, ConwayCell());
		vector<vector<ConwayCell> > gridn(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('.');
		gridn[1][1].setState('.');
	
		gridn[0][0].updateState(grid, 0, 0, false);
		CPPUNIT_ASSERT(gridn[0][0].getState() == true);
	
	}

	void test_conway_updateState_3 () {
		vector<ConwayCell> row(2, ConwayCell());
		vector<vector<ConwayCell> > grid(2, row);
		vector<ConwayCell> rown(2, ConwayCell());
		vector<vector<ConwayCell> > gridn(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('*');
		grid[1][0].setState('.');
		grid[1][1].setState('*');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('.');
		gridn[1][1].setState('.');
	
		gridn[1][1].updateState(grid, 1, 1, true);
		CPPUNIT_ASSERT(gridn[1][1].getState() == false);
	
	}

	//----------------------------
	// test_conway_changeState_through_Cell
	//----------------------------

	void test_conwayC_changeState_1 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('.');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == false);
	}

	void test_conwayC_changeState_2 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == true);
	}

	void test_conwayC_changeState_3 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('*');
		grid[1][0].setState('*');
		grid[1][1].setState('*');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == false);
	}

	//------------------------
	// test_conway_updateState_in_Cell
	//------------------------


	void test_conwayC_updateState_1 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, rown);
		grid[0][0].setState('*');
		grid[0][1].setState('*');
		grid[1][0].setState('.');
		grid[1][1].setState('*');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('.');
		gridn[1][1].setState('.');
	
		gridn[1][1].updateState(grid, 1, 1, true);
		CPPUNIT_ASSERT(gridn[1][1].getState() == false);
	
	}

	void test_conwayC_updateState_2 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, rown);
		grid[0][0].setState('*');
		grid[0][1].setState('*');
		grid[1][0].setState('.');
		grid[1][1].setState('*');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('*');
		gridn[1][1].setState('*');
	
		gridn[1][1].updateState(grid, 1, 1, true);
		CPPUNIT_ASSERT(gridn[1][1].getState() == false);
	
	}

	void test_conwayC_updateState_3 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, rown);
		grid[0][0].setState('.');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('.');
		gridn[1][1].setState('.');
	
		gridn[1][1].updateState(grid, 1, 1, true);
		CPPUNIT_ASSERT(gridn[1][1].getState() == true);
	
	}

	//---------------------
	//test_conway_printCell
	//---------------------

	void test_conway_printCell_1() {
		ConwayCell cell;
		cell.setState('.');
		char ch = cell.printCell();
		CPPUNIT_ASSERT(ch == '.');	
	}
	void test_conway_printCell_2() {
		ConwayCell cell;
		cell.setState('*');
		char ch = cell.printCell();
		CPPUNIT_ASSERT(ch == '*');	
	}

	void test_conway_printCell_3() {
		ConwayCell cell;
		cell.setState('.');
		char ch = cell.printCell();
		CPPUNIT_ASSERT(ch == '.');	
	}


	////////////////////////CELL////////////////////////////////////////

	//-----------------------
	// test_cell_constructors
	//-----------------------

	void test_cell_constructor_1 () { 
		FredkinCell* fc = new FredkinCell(true);
		Cell cc = fc;
		CPPUNIT_ASSERT(dynamic_cast<FredkinCell*>(cc.myCell) == fc);        		        	
	}

	void test_cell_constructor_2 () { 
		FredkinCell* fc = new FredkinCell(true);
		Cell cc = fc;
		cc.myCell->setState('-');
		CPPUNIT_ASSERT(cc.myCell->_state == false);        		        	
	}

	void test_cell_constructor_3 () { 
		ConwayCell* c = new ConwayCell(true);
		Cell cc = c;
		CPPUNIT_ASSERT(dynamic_cast<ConwayCell*>(cc.myCell) == c);        		        	
	}

	//-----------------
	// test_cell_copy
	//-----------------

	void test_cell_copy_1 () { 
		ConwayCell* c = new ConwayCell(true);
		Cell cc = c;
		Cell newC(cc);
		CPPUNIT_ASSERT(dynamic_cast<ConwayCell*>(newC.myCell) != c);        		        	
	}

	void test_cell_copy_2 () { 
		ConwayCell* c = new ConwayCell(true);
		Cell cc = c;
		Cell newC(cc);
		CPPUNIT_ASSERT(cc.myCell != newC.myCell);        		        	
	}

	void test_cell_copy_3 () { 
		FredkinCell* fc = new FredkinCell(true);
		Cell cc = fc;
		Cell newF(cc);

		CPPUNIT_ASSERT(newF.myCell->_state == cc.myCell->_state);        		        	
	}


	//---------------------
	//test_cell_setstate
	//---------------------

	void test_cell_setState_1 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell Ccell = cell;
		Ccell.setState('*');
		CPPUNIT_ASSERT( Ccell.myCell->_state == true);
	}
	void test_cell_setState_2() {
		ConwayCell* cell = new ConwayCell(true);
		Cell Ccell = cell;
		Ccell.setState('.');
		CPPUNIT_ASSERT(Ccell.myCell->_state == false);
	}

	void test_cell_setState_3() {
		FredkinCell* cell = new FredkinCell(true);
		Cell Ccell = cell;
		Ccell.setState('0');
		CPPUNIT_ASSERT(Ccell.myCell->_state == true);
	}


	//---------------------
	//test_cell_getstate
	//---------------------

	void test_cell_getState_1 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell Ccell = cell;
		bool state = Ccell.getState();
		CPPUNIT_ASSERT( state == true);
	}

	void test_cell_getState_2 () {
		ConwayCell* cell = new ConwayCell(false);
		Cell Ccell = cell;
		bool state = Ccell.getState();
		CPPUNIT_ASSERT( state == false);
	}

	void test_cell_getState_3 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell Ccell = cell;
		Ccell.setState('-');
		bool state = Ccell.getState();
		CPPUNIT_ASSERT( state == false);
	}

	//-----------------------
	//test_cell_changeState
	//----------------------

	void test_cell_changeState_1 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('.');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == false);
	}

	void test_cell_changeState_2 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('*');
		grid[0][1].setState('.');
		grid[1][0].setState('.');
		grid[1][1].setState('.');
		
		bool change = grid[0][0].changeState(grid, 0, 0);
		CPPUNIT_ASSERT(change == true);
	}

	void test_cell_changeState_3 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('-');
		grid[1][1].setState('-');
		
		bool change = grid[0][1].changeState(grid, 0, 1);
		CPPUNIT_ASSERT(change == true);
	}


	//--------------------------
	// test_cell_updateState
	//-------------------------

	void test_cell_updateState_1 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('7');
		grid[1][1].setState('7');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('7');
		gridn[1][1].setState('-');
	
		gridn[1][0].updateState(grid, 1, 0, false);
		CPPUNIT_ASSERT(gridn[1][0].getState() == true);		
	}

	void test_cell_updateState_2 () {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, row);
		grid[0][0].setState('0');
		grid[0][1].setState('-');
		grid[1][0].setState('7');
		grid[1][1].setState('7');
		
		gridn[0][0].setState('0');
		gridn[0][1].setState('-');
		gridn[1][0].setState('7');
		gridn[1][1].setState('-');
	
		gridn[1][0].updateState(grid, 1, 0, false);
		CPPUNIT_ASSERT(gridn[1][1].getState() == false);		
	}

	void test_cell_updateState_3 () {
		ConwayCell* cell = new ConwayCell(true);
		Cell cCell = cell;
		vector<Cell> row(2, cCell);
		vector<vector<Cell> > grid(2, row);
		vector<Cell> rown(2, cCell);
		vector<vector<Cell> > gridn(2, rown);
		grid[0][0].setState('*');
		grid[0][1].setState('*');
		grid[1][0].setState('.');
		grid[1][1].setState('*');
		
		gridn[0][0].setState('.');
		gridn[0][1].setState('.');
		gridn[1][0].setState('.');
		gridn[1][1].setState('.');
	
		gridn[1][1].updateState(grid, 1, 1, true);
		CPPUNIT_ASSERT(gridn[1][1].getState() == false);
	
	}


	//-------------------------
	// cell_printCell
	//------------------------

	void test_cell_printCell_1() {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		cCell.setState('7');
		char ch = cCell.printCell();
		CPPUNIT_ASSERT(ch == '7');	
	}
	void test_cell_printCell_2() {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		cCell.setState('-');
		char ch = cCell.printCell();
		CPPUNIT_ASSERT(ch == '-');	
	}

	void test_cell_printCell_3() {
		FredkinCell* cell = new FredkinCell(true);
		Cell cCell = cell;
		cCell.setState('0');
		char ch = cCell.printCell();
		CPPUNIT_ASSERT(ch == '0');	
	}



	// -----
    // suite
    // -----

	CPPUNIT_TEST_SUITE(TestLife);

	/////////////Life Tests////////////
	CPPUNIT_TEST(test_Life_Constructor_1);
	CPPUNIT_TEST(test_Life_Constructor_2);
	CPPUNIT_TEST(test_Life_Constructor_3);
	CPPUNIT_TEST(test_Life_simulate_1);
	CPPUNIT_TEST(test_Life_simulate_2);
	CPPUNIT_TEST(test_Life_simulate_3);
	CPPUNIT_TEST(test_Life_printBoard_1);
	CPPUNIT_TEST(test_Life_printBoard_2);
	CPPUNIT_TEST(test_Life_printBoard_3);
	///////////AbstractCell Tests////////////
	CPPUNIT_TEST(test_Abstract_constructor_1);
	CPPUNIT_TEST(test_Abstract_constructor_2);
	CPPUNIT_TEST(test_Abstract_constructor_3);
	CPPUNIT_TEST(test_Abstract2_constructor_1);
	CPPUNIT_TEST(test_Abstract2_constructor_2);
	CPPUNIT_TEST(test_Abstract2_constructor_3);
	/////////////FredkinCell///////////////////
	CPPUNIT_TEST(test_fredkin_constructor_1);
	CPPUNIT_TEST(test_fredkin_constructor_2);
	CPPUNIT_TEST(test_fredkin_constructor_3);
	CPPUNIT_TEST(test_fredkin_copy_1);
	CPPUNIT_TEST(test_fredkin_copy_2);
	CPPUNIT_TEST(test_fredkin_copy_3);
	CPPUNIT_TEST(test_fredkin_clone_1);
	CPPUNIT_TEST(test_fredkin_clone_2);
	CPPUNIT_TEST(test_fredkin_clone_3);
	CPPUNIT_TEST(test_fredkin_setState_1);
	CPPUNIT_TEST(test_fredkin_setState_2);
	CPPUNIT_TEST(test_fredkin_setState_3);
	CPPUNIT_TEST(test_fredkin_getState_1);
	CPPUNIT_TEST(test_fredkin_getState_2);
	CPPUNIT_TEST(test_fredkin_getState_3);
	CPPUNIT_TEST(test_fredkin_changeState_1);
	CPPUNIT_TEST(test_fredkin_changeState_2);
	CPPUNIT_TEST(test_fredkin_changeState_3);
	CPPUNIT_TEST(test_fredkin_updateState_1);
	CPPUNIT_TEST(test_fredkin_updateState_2);
	CPPUNIT_TEST(test_fredkin_updateState_3);
	CPPUNIT_TEST(test_fredkinC_updateState_1);
	CPPUNIT_TEST(test_fredkinC_updateState_2);
	CPPUNIT_TEST(test_fredkinC_updateState_3);
	CPPUNIT_TEST(test_fredkinC_changeState_1);
	CPPUNIT_TEST(test_fredkinC_changeState_2);
	CPPUNIT_TEST(test_fredkinC_changeState_3);
	CPPUNIT_TEST(test_fredkin_printCell_1);
	CPPUNIT_TEST(test_fredkin_printCell_2);
	CPPUNIT_TEST(test_fredkin_printCell_3);
	//////////////ConwayCell Tests///////////
	CPPUNIT_TEST(test_conway_constructor_1);
	CPPUNIT_TEST(test_conway_constructor_2);
	CPPUNIT_TEST(test_conway_constructor_3);
	CPPUNIT_TEST(test_conway_copy_1);
	CPPUNIT_TEST(test_conway_copy_2);
	CPPUNIT_TEST(test_conway_copy_3);
	CPPUNIT_TEST(test_conway_clone_1);
	CPPUNIT_TEST(test_conway_clone_2);
	CPPUNIT_TEST(test_conway_clone_3);
	CPPUNIT_TEST(test_conway_setState_1);
	CPPUNIT_TEST(test_conway_setState_2);
	CPPUNIT_TEST(test_conway_setState_3);
	CPPUNIT_TEST(test_conway_getState_1);
	CPPUNIT_TEST(test_conway_getState_2);
	CPPUNIT_TEST(test_conway_getState_3);
	CPPUNIT_TEST(test_conway_changeState_1);
	CPPUNIT_TEST(test_conway_changeState_2);
	CPPUNIT_TEST(test_conway_changeState_3);
	CPPUNIT_TEST(test_conway_updateState_1);
	CPPUNIT_TEST(test_conway_updateState_2);
	CPPUNIT_TEST(test_conway_updateState_3); 
	CPPUNIT_TEST(test_conwayC_changeState_1);
	CPPUNIT_TEST(test_conwayC_changeState_2);
	CPPUNIT_TEST(test_conwayC_changeState_3);
	CPPUNIT_TEST(test_conwayC_updateState_1);
	CPPUNIT_TEST(test_conwayC_updateState_2);
	CPPUNIT_TEST(test_conwayC_updateState_3); 
	CPPUNIT_TEST(test_conway_printCell_1);
	CPPUNIT_TEST(test_conway_printCell_2);
	CPPUNIT_TEST(test_conway_printCell_3);	
	/////////////Cell Tests/////////////
	CPPUNIT_TEST(test_cell_constructor_1);
	CPPUNIT_TEST(test_cell_constructor_2);
	CPPUNIT_TEST(test_cell_constructor_3);  
	CPPUNIT_TEST(test_cell_copy_1);
	CPPUNIT_TEST(test_cell_copy_2);
	CPPUNIT_TEST(test_cell_copy_3);
	CPPUNIT_TEST(test_cell_setState_1);
	CPPUNIT_TEST(test_cell_setState_2);
	CPPUNIT_TEST(test_cell_setState_3);
	CPPUNIT_TEST(test_cell_getState_1);
	CPPUNIT_TEST(test_cell_getState_2);
	CPPUNIT_TEST(test_cell_getState_3);	
	CPPUNIT_TEST(test_cell_changeState_1);
	CPPUNIT_TEST(test_cell_changeState_2);
	CPPUNIT_TEST(test_cell_changeState_3);
	CPPUNIT_TEST(test_cell_updateState_1);
	CPPUNIT_TEST(test_cell_updateState_2);
	CPPUNIT_TEST(test_cell_updateState_3);
	CPPUNIT_TEST(test_cell_printCell_1);
	CPPUNIT_TEST(test_cell_printCell_2);
	CPPUNIT_TEST(test_cell_printCell_3);

	CPPUNIT_TEST_SUITE_END();};
	

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

