// -------------------------
// cs371p-life/TestLife.c++
// Copyright (C) 2012
// Nathaniel B Gass
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
    % valgrind TestLife.c++.app >& TestLife.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <cstdlib>   // rand, srand

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public
#define protected public

#include "Life.h"
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"

// -----------
// TestLife
// -----------

struct TestLife : CppUnit::TestFixture {

	// ########
    // Cell Tests
    // ########
	void cell_cellToString_1 () {
		Cell testCell('.');
		CPPUNIT_ASSERT(testCell.cellToString() == '.');
	}
	
	void cell_cellToString_2 () {
		Cell testCell('-');
		CPPUNIT_ASSERT(testCell.cellToString() == '-');
	}
	
	void cell_cellToString_3 () {
		Cell testCell('w');
		CPPUNIT_ASSERT(testCell.cellToString() == 'w');
	}

	void cell_ageCell_1 () {
		Cell testCell('.');
		CPPUNIT_ASSERT(testCell.cellToString() == '.');
		CPPUNIT_ASSERT(testCell.isLiving() == false);
		testCell.ageCell(3);
		CPPUNIT_ASSERT(testCell.cellToString() == '*');
		CPPUNIT_ASSERT(testCell.isLiving());
	}
	
	void cell_ageCell_2 () {
		Cell testCell('-');
		CPPUNIT_ASSERT(testCell.cellToString() == '-');
		CPPUNIT_ASSERT(testCell.isLiving() == false);
		testCell.ageCell(1);
		CPPUNIT_ASSERT(testCell.cellToString() == '0');
		CPPUNIT_ASSERT(testCell.isLiving());
	}
	
	void cell_ageCell_3 () {
		Cell testCell('1');
		CPPUNIT_ASSERT(testCell.cellToString() == '1');
		CPPUNIT_ASSERT(testCell.isLiving());
		testCell.ageCell(1);
		CPPUNIT_ASSERT(testCell.cellToString() == '*');
		CPPUNIT_ASSERT(testCell.isLiving());
	}

	void cell_isLiving_1 () {
		Cell testCell('1');
		CPPUNIT_ASSERT(testCell.isLiving());
	}
	
	void cell_isLiving_2 () {
		Cell testCell('.');
		CPPUNIT_ASSERT(testCell.isLiving() == false);
	}
	
	void cell_isLiving_3 () {
		Cell testCell('w');
		CPPUNIT_ASSERT(testCell.isLiving());		
	}

	void cell_isDiagNeighborsCount_1 () {
		Cell testCell('1');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == false);
	}

	void cell_isDiagNeighborsCount_2 () {
		Cell testCell('.');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount());
	}

	void cell_isDiagNeighborsCount_3 () { 
		Cell testCell('-');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == false);
	}

	void cell_clone_1 () {
		Cell testCell('.');
		Cell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		delete testCellClone;
	}
	
	void cell_clone_2 () {
		Cell testCell('+');
		Cell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		delete testCellClone;
	}
	
	void cell_clone_3 () {
		Cell testCell('-');
		Cell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		delete testCellClone;
	}
	
	void cell_construct_1 () {
		Cell testCell('.');
		CPPUNIT_ASSERT(testCell.isLiving() == false);
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount());
		CPPUNIT_ASSERT(testCell.cellToString() == '.');
	}
	
	void cell_construct_2 () {
		Cell testCell('*');
		CPPUNIT_ASSERT(testCell.isLiving());
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount());
		CPPUNIT_ASSERT(testCell.cellToString() == '*');
	}
	
	void cell_construct_3 () {
		Cell testCell('5');
		CPPUNIT_ASSERT(testCell.isLiving());
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == false);
		CPPUNIT_ASSERT(testCell.cellToString() == '5');
	}

	
	// ########
    // ConwayCell Tests
    // ########	
	void conwayCell_cellToString_1 () { 
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell.cellToString() == '.');
	}
	
	void conwayCell_cellToString_2 () {
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell.cellToString() == '*');	
	}
	
	void conwayCell_cellToString_3 () {
		ConwayCell testCell('w');
		CPPUNIT_ASSERT(testCell._symbol == 'w');
		CPPUNIT_ASSERT(testCell.cellToString() == 'w');	
	}

	void conwayCell_ageCell_1 () {
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		testCell.ageCell(3);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._isLiving);
	}
	
	void conwayCell_ageCell_2 () {
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		testCell.ageCell(1);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
	}
	
	void conwayCell_ageCell_3 () {
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		testCell.ageCell(4);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
	}

	void conwayCell_isLiving_1 () {
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell.isLiving() == false);
	}

	void conwayCell_isLiving_2 () { 
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell.isLiving() == true);
	}
	
	void conwayCell_isLiving_3 () {
		ConwayCell testCell('w');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell.isLiving() == true);
	}

	void conwayCell_isDiagNeighborsCount_1 () {
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == true);
	}
	
	void conwayCell_isDiagNeighborsCount_2 () { 
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == true);		
	}
	
	void conwayCell_isDiagNeighborsCount_3 () { 
		ConwayCell testCell('w');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == true);
	}

	void conwayCell_clone_1 () { 
		ConwayCell testCell('.');
		ConwayCell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		CPPUNIT_ASSERT(testCellClone != &testCell);
		delete testCellClone;
	}
	
	void conwayCell_clone_2 () { 
		ConwayCell testCell('*');
		ConwayCell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		CPPUNIT_ASSERT(testCellClone != &testCell);	
		delete testCellClone;
	}
	
	void conwayCell_clone_3 () {
		ConwayCell testCell('w');
		ConwayCell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		CPPUNIT_ASSERT(testCellClone != &testCell);
		delete testCellClone;
	}
	
	void conwayCell_construct_1 () {
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);		
	}

	void conwayCell_construct_2 () { 
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);	
	}

	void conwayCell_construct_3 () { 
		ConwayCell testCell('w');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == 'w');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);	
	}

	void conwayCell_killCell_1 () {
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
		testCell.killCell();
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
	}
	
	void conwayCell_killCell_2 () {
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
		testCell.killCell();
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
	}
	
	void conwayCell_killCell_3 () {
		ConwayCell testCell('w');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == 'w');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
		testCell.killCell();
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);	
	}
	
	void conwayCell_ressurectCell_1 () { 
		ConwayCell testCell('.');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '.');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
		testCell.ressurectCell();
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
	}
	
	void conwayCell_ressurectCell_2 () { 
		ConwayCell testCell('*');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
		testCell.ressurectCell();
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
	}
	
	void conwayCell_ressurectCell_3 () {
		ConwayCell testCell('w');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == 'w');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
		testCell.ressurectCell();
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '*');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == true);
	}
	
    
	// ########
    // FredkinCell Tests
    // ########
	void fredkinCell_cellToString_1 () {
		FredkinCell testCell('-');
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell.cellToString() == '-');
	}
	
	void fredkinCell_cellToString_2 () {
		FredkinCell testCell('+');
		CPPUNIT_ASSERT(testCell._symbol == '+');
		CPPUNIT_ASSERT(testCell.cellToString() == '+');
	}
	
	void fredkinCell_cellToString_3 () {
		FredkinCell testCell('w');
		CPPUNIT_ASSERT(testCell._symbol == 'w');
		CPPUNIT_ASSERT(testCell.cellToString() == 'w');
	}

	void fredkinCell_ageCell_1 () { 
		FredkinCell testCell('4');
		CPPUNIT_ASSERT(testCell._symbol == '4');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		testCell.ageCell(3);
		CPPUNIT_ASSERT(testCell._symbol == '5');
		CPPUNIT_ASSERT(testCell._isLiving == true);
	}
	
	void fredkinCell_ageCell_2 () {
		FredkinCell testCell('4');
		CPPUNIT_ASSERT(testCell._symbol == '4');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		testCell.ageCell(2);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._isLiving == false);
	}
	
	void fredkinCell_ageCell_3 () {
		FredkinCell testCell('-');
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		testCell.ageCell(1);
		CPPUNIT_ASSERT(testCell._symbol == '0');
		CPPUNIT_ASSERT(testCell._isLiving == true);
	}

	void fredkinCell_isLiving_1 () { 
		FredkinCell testCell('+');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell.isLiving() == true);
	}
	
	void fredkinCell_isLiving_2 () {
		FredkinCell testCell('-');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell.isLiving() == false);	
	}
	
	void fredkinCell_isLiving_3 () { 
		FredkinCell testCell('4');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell.isLiving() == true);	
	}

	void fredkinCell_isDiagNeighborsCount_1 () { 
		FredkinCell testCell('.');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == false);
	}
	
	void fredkinCell_isDiagNeighborsCount_2 () { 
		FredkinCell testCell('.');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == false);
	}
	
	void fredkinCell_isDiagNeighborsCount_3 () {
		FredkinCell testCell('.');
		CPPUNIT_ASSERT(testCell.isDiagNeighborsCount() == false);
	}

	void fredkinCell_clone_1 () {
		FredkinCell testCell('-');
		FredkinCell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		CPPUNIT_ASSERT(testCellClone != &testCell);
		delete testCellClone;
	}
	
	void fredkinCell_clone_2 () { 
		FredkinCell testCell('+');
		FredkinCell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		CPPUNIT_ASSERT(testCellClone != &testCell);	
		delete testCellClone;
	}
	
	void fredkinCell_clone_3 () { 
		FredkinCell testCell('4');
		FredkinCell* testCellClone = testCell.clone();
		CPPUNIT_ASSERT(testCellClone->cellToString() == testCell.cellToString());
		CPPUNIT_ASSERT(testCellClone->isLiving() == testCell.isLiving());
		CPPUNIT_ASSERT(testCellClone != &testCell);	
		delete testCellClone;
	}
	
	void fredkinCell_construct_1 () {
		FredkinCell testCell('-');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);	
	}
	
	void fredkinCell_construct_2 () { 
		FredkinCell testCell('+');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '+');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);		
	}
	
	void fredkinCell_construct_3 () {
		FredkinCell testCell('3');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '3');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);	
	}
	
	void fredkinCell_killCell_1 () {
		FredkinCell testCell('3');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '3');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
		testCell.killCell();
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
	}

	void fredkinCell_killCell_2 () {
		FredkinCell testCell('-');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
		testCell.killCell();
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
	}

	void fredkinCell_killCell_3 () {
		FredkinCell testCell('+');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '+');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
		testCell.killCell();
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
	}
	
	void fredkinCell_ressurectCell_1 () {
		FredkinCell testCell('3');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '3');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
		testCell.ressurectCell();
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '3');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);	
	}
	
	void fredkinCell_ressurectCell_2 () {
		FredkinCell testCell('-');
		CPPUNIT_ASSERT(testCell._isLiving == false);
		CPPUNIT_ASSERT(testCell._symbol == '-');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
		testCell.ressurectCell();
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '0');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);	
	}
	
	void fredkinCell_ressurectCell_3 () {
		FredkinCell testCell('+');
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '+');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);
		testCell.ressurectCell();
		CPPUNIT_ASSERT(testCell._isLiving == true);
		CPPUNIT_ASSERT(testCell._symbol == '+');
		CPPUNIT_ASSERT(testCell._diagNeighborsCount == false);	
	}
	
	// ########
    // Life Tests
    // ########
	void life_updateNeighborCountBoard_1 () {
		ConwayCell dummyCell('.');
		vector< vector<ConwayCell> > newBoard(2, vector<ConwayCell>(2, dummyCell));
		vector< vector<int> > countBoard(2, vector<int>(2));
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		countBoard[0][0] = 2;
		countBoard[0][1] = 1;
		countBoard[1][0] = 1;
		countBoard[1][1] = 2;
		Life<ConwayCell> lifeGame(newBoard, 2);
		lifeGame.updateNeighborCountBoard();
		CPPUNIT_ASSERT(countBoard == lifeGame._neighborCountBoard);
	}
	void life_updateNeighborCountBoard_2 () {
		FredkinCell dummyCell('-');
		vector< vector<FredkinCell> > newBoard(2, vector<FredkinCell>(2, dummyCell));
		vector< vector<int> > countBoard(2, vector<int>(2));
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		countBoard[0][0] = 2;
		countBoard[0][1] = 0;
		countBoard[1][0] = 0;
		countBoard[1][1] = 2;
		Life<FredkinCell> lifeGame(newBoard, 2);
		lifeGame.updateNeighborCountBoard();
		CPPUNIT_ASSERT(countBoard == lifeGame._neighborCountBoard);
	}
	
	void life_updateNeighborCountBoard_3 () {
		FredkinCell dummyCell('-');
		vector< vector<FredkinCell> > newBoard(2, vector<FredkinCell>(2, dummyCell));
		vector< vector<int> > countBoard(2, vector<int>(2));
		newBoard[0][0].ressurectCell();
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		newBoard[1][1].ressurectCell();
		countBoard[0][0] = 2;
		countBoard[0][1] = 2;
		countBoard[1][0] = 2;
		countBoard[1][1] = 2;
		Life<FredkinCell> lifeGame(newBoard, 2);
		lifeGame.updateNeighborCountBoard();
		CPPUNIT_ASSERT(countBoard == lifeGame._neighborCountBoard);
	}

	void life_driveGeneration_1 () {
		FredkinCell dummyCell('-');
		vector< vector<FredkinCell> > newBoard(2, vector<FredkinCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		newBoard[1][1].ressurectCell();
		Life<FredkinCell> lifeGame(newBoard,4);
		CPPUNIT_ASSERT(lifeGame._generation == 0);
		CPPUNIT_ASSERT(lifeGame._population == 4);
		lifeGame.driveGeneration();
		CPPUNIT_ASSERT(lifeGame._generation == 1);
		CPPUNIT_ASSERT(lifeGame._population == 0);
	}
	
	void life_driveGeneration_2 () { 
		ConwayCell dummyCell('.');
		vector< vector<ConwayCell> > newBoard(2, vector<ConwayCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		newBoard[1][1].ressurectCell();
		Life<ConwayCell> lifeGame(newBoard,4);
		CPPUNIT_ASSERT(lifeGame._generation == 0);
		CPPUNIT_ASSERT(lifeGame._population == 4);
		lifeGame.driveGeneration();
		CPPUNIT_ASSERT(lifeGame._generation == 1);
		CPPUNIT_ASSERT(lifeGame._population == 4);
	}
	
	void life_driveGeneration_3 () { 
		ConwayCell dummyCell('.');
		vector< vector<ConwayCell> > newBoard(2, vector<ConwayCell>(2, dummyCell));
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		Life<ConwayCell> lifeGame(newBoard,2);
		CPPUNIT_ASSERT(lifeGame._generation == 0);
		CPPUNIT_ASSERT(lifeGame._population == 2);
		lifeGame.driveGeneration();
		CPPUNIT_ASSERT(lifeGame._generation == 1);
		CPPUNIT_ASSERT(lifeGame._population == 0);
	}

	void life_gameBoardToString_1 () { 
		FredkinCell dummyCell('-');
		vector< vector<FredkinCell> > newBoard(2, vector<FredkinCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		newBoard[0][1].ressurectCell();		
		newBoard[1][0].ressurectCell();
		newBoard[1][1].ressurectCell();
		string expected = "Generation = 0, Population = 4.\n00\n00\n";
		Life<FredkinCell> lifeGame(newBoard, 4);
		lifeGame.updateNeighborCountBoard();
		CPPUNIT_ASSERT(lifeGame.gameBoardToString() == expected);
	}
	
	void life_gameBoardToString_2 () {
		FredkinCell dummyCell('-');
		vector< vector<FredkinCell> > newBoard(2, vector<FredkinCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		string expected = "Generation = 0, Population = 1.\n0-\n--\n";
		Life<FredkinCell> lifeGame(newBoard, 1);
		lifeGame.updateNeighborCountBoard();
		CPPUNIT_ASSERT(lifeGame.gameBoardToString() == expected);
	}
	
	void life_gameBoardToString_3 () {
		ConwayCell dummyCell('.');
		vector< vector<ConwayCell> > newBoard(2, vector<ConwayCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		string expected = "Generation = 0, Population = 1.\n*.\n..\n";
		Life<ConwayCell> lifeGame(newBoard, 1);
		lifeGame.updateNeighborCountBoard();
		CPPUNIT_ASSERT(lifeGame.gameBoardToString() == expected);
	}
	
	void life_constructor_1 () { 
		ConwayCell dummyCell('.');
		vector< vector<ConwayCell> > newBoard(2, vector<ConwayCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		Life<ConwayCell> lifeGame(newBoard, 1);
		CPPUNIT_ASSERT(lifeGame._population == 1);
		CPPUNIT_ASSERT(lifeGame._generation == 0);			
	}
	
	void life_constructor_2 () { 
		FredkinCell dummyCell('-');
		vector< vector<FredkinCell> > newBoard(2, vector<FredkinCell>(2, dummyCell));
		newBoard[0][0].ressurectCell();
		Life<FredkinCell> lifeGame(newBoard, 3);
		CPPUNIT_ASSERT(lifeGame._population == 3);
		CPPUNIT_ASSERT(lifeGame._generation == 0);	
	}
	
	void life_constructor_3 () { 
		Cell dummyCell('-');
		vector< vector<Cell> > newBoard(2, vector<Cell>(2, dummyCell));
		Life<Cell> lifeGame(newBoard, 92);
		CPPUNIT_ASSERT(lifeGame._population == 92);
		CPPUNIT_ASSERT(lifeGame._generation == 0);	
	}

	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
	
	// ########
    // Cell Tests
    // ########
	CPPUNIT_TEST(cell_construct_1);
	CPPUNIT_TEST(cell_construct_2);
	CPPUNIT_TEST(cell_construct_3);
			
	CPPUNIT_TEST(cell_cellToString_1);
	CPPUNIT_TEST(cell_cellToString_2);
	CPPUNIT_TEST(cell_cellToString_3);	
	
	CPPUNIT_TEST(cell_ageCell_1);
	CPPUNIT_TEST(cell_ageCell_2);
	CPPUNIT_TEST(cell_ageCell_3);		
	
	CPPUNIT_TEST(cell_isLiving_1);
	CPPUNIT_TEST(cell_isLiving_2);
	CPPUNIT_TEST(cell_isLiving_3);	

	CPPUNIT_TEST(cell_isDiagNeighborsCount_1);
	CPPUNIT_TEST(cell_isDiagNeighborsCount_2);
	CPPUNIT_TEST(cell_isDiagNeighborsCount_3);

	CPPUNIT_TEST(cell_clone_1);
	CPPUNIT_TEST(cell_clone_2);
	CPPUNIT_TEST(cell_clone_3);

	// ########
    // ConwayCell Tests
    // ########	
	CPPUNIT_TEST(conwayCell_cellToString_1);
	CPPUNIT_TEST(conwayCell_cellToString_2);
	CPPUNIT_TEST(conwayCell_cellToString_3);
	
	CPPUNIT_TEST(conwayCell_ageCell_1);
	CPPUNIT_TEST(conwayCell_ageCell_2);
	CPPUNIT_TEST(conwayCell_ageCell_3);	

	CPPUNIT_TEST(conwayCell_isLiving_1);
	CPPUNIT_TEST(conwayCell_isLiving_2);
	CPPUNIT_TEST(conwayCell_isLiving_3);

	CPPUNIT_TEST(conwayCell_isDiagNeighborsCount_1);
	CPPUNIT_TEST(conwayCell_isDiagNeighborsCount_2);
	CPPUNIT_TEST(conwayCell_isDiagNeighborsCount_3);

	CPPUNIT_TEST(conwayCell_clone_1);
	CPPUNIT_TEST(conwayCell_clone_2);
	CPPUNIT_TEST(conwayCell_clone_3);	

	CPPUNIT_TEST(conwayCell_construct_1);
	CPPUNIT_TEST(conwayCell_construct_2);
	CPPUNIT_TEST(conwayCell_construct_3);

	CPPUNIT_TEST(conwayCell_killCell_1);
	CPPUNIT_TEST(conwayCell_killCell_2);
	CPPUNIT_TEST(conwayCell_killCell_3);
	
	CPPUNIT_TEST(conwayCell_ressurectCell_1);
	CPPUNIT_TEST(conwayCell_ressurectCell_2);
	CPPUNIT_TEST(conwayCell_ressurectCell_3);
	
	// ########
    // FredkinCell Tests
    // ########
	CPPUNIT_TEST(fredkinCell_cellToString_1);
	CPPUNIT_TEST(fredkinCell_cellToString_2);
	CPPUNIT_TEST(fredkinCell_cellToString_3);

	CPPUNIT_TEST(fredkinCell_ageCell_1);
	CPPUNIT_TEST(fredkinCell_ageCell_2);
	CPPUNIT_TEST(fredkinCell_ageCell_3);	

	CPPUNIT_TEST(fredkinCell_isLiving_1);
	CPPUNIT_TEST(fredkinCell_isLiving_2);
	CPPUNIT_TEST(fredkinCell_isLiving_3);

	CPPUNIT_TEST(fredkinCell_isDiagNeighborsCount_1);
	CPPUNIT_TEST(fredkinCell_isDiagNeighborsCount_2);
	CPPUNIT_TEST(fredkinCell_isDiagNeighborsCount_3);	

	CPPUNIT_TEST(fredkinCell_clone_1);
	CPPUNIT_TEST(fredkinCell_clone_2);
	CPPUNIT_TEST(fredkinCell_clone_3);		
	
	CPPUNIT_TEST(fredkinCell_construct_1);
	CPPUNIT_TEST(fredkinCell_construct_2);
	CPPUNIT_TEST(fredkinCell_construct_3);
	
	CPPUNIT_TEST(fredkinCell_killCell_1);
	CPPUNIT_TEST(fredkinCell_killCell_2);
	CPPUNIT_TEST(fredkinCell_killCell_3);	

	CPPUNIT_TEST(fredkinCell_ressurectCell_1);
	CPPUNIT_TEST(fredkinCell_ressurectCell_2);
	CPPUNIT_TEST(fredkinCell_ressurectCell_3);	
	
	// ########
    // Life Tests
    // ########	
	CPPUNIT_TEST(life_updateNeighborCountBoard_1);
	CPPUNIT_TEST(life_updateNeighborCountBoard_2);
	CPPUNIT_TEST(life_updateNeighborCountBoard_3);	

	CPPUNIT_TEST(life_driveGeneration_1);
	CPPUNIT_TEST(life_driveGeneration_2);
	CPPUNIT_TEST(life_driveGeneration_3);
	
	CPPUNIT_TEST(life_gameBoardToString_1);
	CPPUNIT_TEST(life_gameBoardToString_2);
	CPPUNIT_TEST(life_gameBoardToString_3);	

	CPPUNIT_TEST(life_constructor_1);
	CPPUNIT_TEST(life_constructor_2);
	CPPUNIT_TEST(life_constructor_3);		
	
	
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
