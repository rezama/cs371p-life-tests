/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
    % valgrind TestLife.app >& TestLife.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <cstdlib>   // rand, srand
#include <stdexcept>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public

#include "Life.h"
#include "AbstractCell.h"
#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

// -----------
// TestLife
// -----------

struct TestLife : CppUnit::TestFixture {

	// ---------------
	// ConwayCell test
	// ---------------

	void test_conway_construct1 () {
		ConwayCell cc('.');
		CPPUNIT_ASSERT(cc._display == '.');
		CPPUNIT_ASSERT(cc._isAlive == false);

		ConwayCell cc2;
		CPPUNIT_ASSERT(cc2._display == '.');
		CPPUNIT_ASSERT(cc2._isAlive == false);
	}

	void test_conway_construct2 () {
		ConwayCell cc2('*');
		CPPUNIT_ASSERT(cc2._isAlive == true);
		CPPUNIT_ASSERT(cc2._display == '*');
	}

	void test_conway_construct3 () {
		CPPUNIT_ASSERT_THROW(ConwayCell('-'), std::invalid_argument);
	}

	void test_conway_evalGeneration1 () {
		ConwayCell cc1('.');
		cc1.evalGeneration(2);
		CPPUNIT_ASSERT(cc1.isAlive() == false);
		CPPUNIT_ASSERT(cc1.display() == '.');

		ConwayCell cc2('*');
		cc2.evalGeneration(2);
		CPPUNIT_ASSERT(cc2.isAlive() == true);
		CPPUNIT_ASSERT(cc2.display() == '*');
	}

	void test_conway_evalGeneration2 () {
		ConwayCell cc1('.');
		cc1.evalGeneration(3);
		CPPUNIT_ASSERT(cc1.isAlive() == true);
		CPPUNIT_ASSERT(cc1.display() == '*');
	}

	void test_conway_evalGeneration3 () {
		ConwayCell cc1('*');
		cc1.evalGeneration(4);
		CPPUNIT_ASSERT(cc1.isAlive() == false);
		CPPUNIT_ASSERT(cc1.display() == '.');
	}
	
	void test_conway_clone1 () {
		ConwayCell cc1('.');
		ConwayCell* ccp = cc1.clone();
		
		CPPUNIT_ASSERT(ccp->isAlive() == false);
		CPPUNIT_ASSERT(ccp->display() == '.');
		
		ccp->_display = '*';
		ccp->_isAlive = true;
		CPPUNIT_ASSERT(ccp->isAlive() != cc1.isAlive());
		CPPUNIT_ASSERT(ccp->display() != cc1.display());
		
		delete ccp;
	}
	
	void test_conway_clone2 () {
		ConwayCell cc1('*');
		ConwayCell* ccp1 = cc1.clone();
		ConwayCell* ccp2 = cc1.clone();
		
		CPPUNIT_ASSERT(ccp1 != ccp2);
		delete ccp1;
		delete ccp2;
	}
	
	void test_conway_clone3 () {
		ConwayCell cc1('*');
		ConwayCell cc2('.');
		
		AbstractCell* ap = cc1.clone();
		CPPUNIT_ASSERT(ap->isAlive() == true);
		CPPUNIT_ASSERT(ap->display() == '*');
		delete ap;
		
		ap = cc2.clone();
		CPPUNIT_ASSERT(ap->isAlive() == false);
		CPPUNIT_ASSERT(ap->display() == '.');
		delete ap;
		
	}

	// ----------------
	// FredkinCell test
	// ----------------

	void test_fredkin_construct1 () {
		FredkinCell fc1;
		CPPUNIT_ASSERT(fc1._display == '-');
		CPPUNIT_ASSERT(fc1._isAlive == false);
		CPPUNIT_ASSERT(fc1._age == 0);

		FredkinCell fc2('-');
		CPPUNIT_ASSERT(fc2._display == '-');
		CPPUNIT_ASSERT(fc2._isAlive == false);
		CPPUNIT_ASSERT(fc2._age == 0);
	}

	void test_fredkin_construct2 () {
		FredkinCell fc1('0');
		CPPUNIT_ASSERT(fc1._display == '0');
		CPPUNIT_ASSERT(fc1._isAlive == true);
		CPPUNIT_ASSERT(fc1._age == 0);

		FredkinCell fc2('9');
		CPPUNIT_ASSERT(fc2._display == '9');
		CPPUNIT_ASSERT(fc2._isAlive == true);
		CPPUNIT_ASSERT(fc2._age == 9);
	}

	void test_fredkin_construct3 ()  {
		CPPUNIT_ASSERT_THROW(FredkinCell('+'), std::invalid_argument);
	}
	
	void test_fredkin_updateAliveDisplay1 () {
		FredkinCell fc1;
		CPPUNIT_ASSERT(fc1.display() == '-');
		CPPUNIT_ASSERT(fc1.isAlive() == false);
		
		fc1.updateAliveDisplay();
		CPPUNIT_ASSERT(fc1.display() == '0');
		CPPUNIT_ASSERT(fc1.isAlive() == true);
	}
	
	void test_fredkin_updateAliveDisplay2 () {
		FredkinCell fc1;
		CPPUNIT_ASSERT(fc1.display() == '-');
		CPPUNIT_ASSERT(fc1.isAlive() == false);
		
		fc1._age = 6;
		fc1.updateAliveDisplay();
		CPPUNIT_ASSERT(fc1.display() == '6');
		CPPUNIT_ASSERT(fc1.isAlive() == true);
	}
	
	void test_fredkin_updateAliveDisplay3 () {
		FredkinCell fc1;
		CPPUNIT_ASSERT(fc1.display() == '-');
		CPPUNIT_ASSERT(fc1.isAlive() == false);
		
		fc1._age = 13;
		fc1.updateAliveDisplay();
		CPPUNIT_ASSERT(fc1.display() == '+');
		CPPUNIT_ASSERT(fc1.isAlive() == true);
	}

	void test_fredkin_evalGeneration1 () {
		FredkinCell fc1('-');
		fc1.evalGeneration(2);
		CPPUNIT_ASSERT(fc1.isAlive() == false);
		CPPUNIT_ASSERT(fc1.display() == '-');
	}

	void test_fredkin_evalGeneration2 () {
		FredkinCell fc1('0');
		fc1.evalGeneration(1);
		CPPUNIT_ASSERT(fc1.isAlive() == true);
		CPPUNIT_ASSERT(fc1._age == 1);
		CPPUNIT_ASSERT(fc1.display() == '1');
	}

	void test_fredkin_evalGeneration3 () {
		FredkinCell fc1('-');

		fc1.evalGeneration(1);
		CPPUNIT_ASSERT(fc1.isAlive() == true);
		CPPUNIT_ASSERT(fc1._age == 0);
		CPPUNIT_ASSERT(fc1.display() == '0');

		fc1._age = 9;
		fc1.evalGeneration(3);
		CPPUNIT_ASSERT(fc1.isAlive() == true);
		CPPUNIT_ASSERT(fc1._age == 10);
		CPPUNIT_ASSERT(fc1.display() == '+');

		fc1.evalGeneration(4);
		CPPUNIT_ASSERT(fc1.isAlive() == false);
		CPPUNIT_ASSERT(fc1._age == 10);
		CPPUNIT_ASSERT(fc1.display() == '-');
	}

	// ---------
	// Cell Test
	// ---------

	void test_cell_construct1 () {
		Cell cc1;
		CPPUNIT_ASSERT(cc1.isAlive() == false);
		CPPUNIT_ASSERT(cc1.display() == '.');
	}

	void test_cell_construct2 () {
		Cell cc1(new ConwayCell('*'));
		CPPUNIT_ASSERT(cc1.isAlive() == true);
		CPPUNIT_ASSERT(cc1.display() == '*');
	}

	void test_cell_construct3 () {
		Cell cc1(new FredkinCell('0'));
		CPPUNIT_ASSERT(cc1.isAlive() == true);
		CPPUNIT_ASSERT(cc1.display() == '0');
	}
	
	void test_cell_copyConstruct1 () {
		Cell c1 = new ConwayCell('*');
		Cell c2 = c1;
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');
		CPPUNIT_ASSERT(c2.isAlive() == true);
		CPPUNIT_ASSERT(c2.display() == '*');
		
		c1._ap->_isAlive = false;
		c1._ap->_display = '.';
		CPPUNIT_ASSERT(c1.isAlive() != c2.isAlive());
		CPPUNIT_ASSERT(c1.display() != c2.display());
	}
	
	void test_cell_copyConstruct2 () {
		Cell c1 = new FredkinCell('3');
		Cell c2 = c1;
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '3');
		CPPUNIT_ASSERT(c2.isAlive() == true);
		CPPUNIT_ASSERT(c2.display() == '3');
	}
	
	void test_cell_copyConstruct3 () {
		Cell c1 = new ConwayCell('*');
		Cell c2 = c1;
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');
		CPPUNIT_ASSERT(c2.isAlive() == true);
		CPPUNIT_ASSERT(c2.display() == '*');
		
		c2._ap->_isAlive = false;
		c2._ap->_display = '.';
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');;
	}
	
	// copyAssignment
	void test_cell_copyAssignment1 () {
		Cell c1 = new ConwayCell('*');
		Cell c2 = new ConwayCell('.');
		c2 = c1;
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
		CPPUNIT_ASSERT(c2.isAlive() == true);
		CPPUNIT_ASSERT(c2.display() == '*');
		CPPUNIT_ASSERT(c2.countsCorners() == true);
				
		CPPUNIT_ASSERT(c1._ap != c2._ap);
	}
	
	void test_cell_copyAssignment2 () {
		Cell c1 = new ConwayCell('.');
		Cell c2 = new FredkinCell('-');	
		c2 = c1;
		
		CPPUNIT_ASSERT(c1.isAlive() == false);
		CPPUNIT_ASSERT(c1.display() == '.');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
		CPPUNIT_ASSERT(c2.isAlive() == false);
		CPPUNIT_ASSERT(c2.display() == '.');
		CPPUNIT_ASSERT(c2.countsCorners() == true);
		
		CPPUNIT_ASSERT(c1._ap != c2._ap);
	}
	
	void test_cell_copyAssignment3 () {
		Cell c1 = new FredkinCell('0');
		Cell c2 = new ConwayCell('.');
		c2 = c1;
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '0');
		CPPUNIT_ASSERT(c1.countsCorners() == false);
		CPPUNIT_ASSERT(c2.isAlive() == true);
		CPPUNIT_ASSERT(c2.display() == '0');
		CPPUNIT_ASSERT(c2.countsCorners() == false);
		
		CPPUNIT_ASSERT(c1._ap != c2._ap);
	}
	
	// evalGeneration
	void test_cell_evalGeneration1 () {
		Cell c1 = new ConwayCell('*'); // Alive
		c1.evalGeneration(2);	// Still Alive
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
		
		c1.evalGeneration(1);	// Now Dead
		CPPUNIT_ASSERT(c1.isAlive() == false);
		CPPUNIT_ASSERT(c1.display() == '.');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
		
		c1.evalGeneration(8);	// Still Dead
		CPPUNIT_ASSERT(c1.isAlive() == false);
		CPPUNIT_ASSERT(c1.display() == '.');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
		
		c1.evalGeneration(3);	// Now live
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
	}
	
	void test_cell_evalGeneration2 () {
		Cell c1 = new FredkinCell('0'); // Alive
		c1.evalGeneration(1);	// Still Alive
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '1');
		CPPUNIT_ASSERT(c1.countsCorners() == false);
		
		c1.evalGeneration(0);	// Now Dead
		CPPUNIT_ASSERT(c1.isAlive() == false);
		CPPUNIT_ASSERT(c1.display() == '-');
		CPPUNIT_ASSERT(c1.countsCorners() == false);
		
		c1.evalGeneration(0);	// Still Dead
		CPPUNIT_ASSERT(c1.isAlive() == false);
		CPPUNIT_ASSERT(c1.display() == '-');
		CPPUNIT_ASSERT(c1.countsCorners() == false);
		
		c1.evalGeneration(3);	// Now live
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '1');
		CPPUNIT_ASSERT(c1.countsCorners() == false);
	}
	
	void test_cell_evalGeneration3 () {
		Cell c1 = new FredkinCell('1'); // Alive
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '1');
		CPPUNIT_ASSERT(c1.countsCorners() == false);
		
		c1.evalGeneration(1);	// Still Alive - Now Conway
		
		CPPUNIT_ASSERT(c1.isAlive() == true);
		CPPUNIT_ASSERT(c1.display() == '*');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
		
		c1.evalGeneration(8);	// Now Dead - Still Conway
		CPPUNIT_ASSERT(c1.isAlive() == false);
		CPPUNIT_ASSERT(c1.display() == '.');
		CPPUNIT_ASSERT(c1.countsCorners() == true);
	}
	
	void test_countsCorners1 () {
		ConwayCell cc1('.');
		CPPUNIT_ASSERT(cc1.countsCorners());
	}

	void test_countsCorners2 () {
		FredkinCell fc1('-');
		CPPUNIT_ASSERT(!fc1.countsCorners());
	}
	
	void test_countsCorners3 () {
		Cell c = new ConwayCell();
		CPPUNIT_ASSERT(c.countsCorners() == true);
		c = new FredkinCell();
		CPPUNIT_ASSERT(c.countsCorners() == false);
	}


	// ---------
	// Life Test
	// ---------

	void test_life_construct1 () {
		Life<ConwayCell> lc(4, 4);
		CPPUNIT_ASSERT(lc._grid.size() == 6);
		CPPUNIT_ASSERT(lc._grid[0].size() == 6);

		ConwayCell&  ccr = lc._grid[3][3];
		CPPUNIT_ASSERT(ccr.isAlive() == false);
		CPPUNIT_ASSERT(ccr.display() == '.');
	}

	void test_life_construct2 () {
		Life<FredkinCell> lf(7, 5);
		CPPUNIT_ASSERT(lf._grid.size() == 9);
		CPPUNIT_ASSERT(lf._grid[0].size() == 7);

		FredkinCell& fcr = lf._grid[1][1];
		CPPUNIT_ASSERT(fcr.isAlive() == false);
		CPPUNIT_ASSERT(fcr.display() == '-');
		CPPUNIT_ASSERT(fcr._age == 0);
	}

	void test_life_construct3 () {
		Life<Cell> lc(3, 6);
		CPPUNIT_ASSERT(lc._grid.size() == 5);
		CPPUNIT_ASSERT(lc._grid[0].size() == 8);
		
		Cell& cr = lc._grid[1][1];
		CPPUNIT_ASSERT(cr.isAlive() == false);
		CPPUNIT_ASSERT(cr.display() == '.');
	}

	void test_life_construct4 () {
		Life<Cell> lc(3, 6, new FredkinCell());
		CPPUNIT_ASSERT(lc._grid.size() == 5);
		CPPUNIT_ASSERT(lc._grid[0].size() == 8);
		
		Cell& cr = lc._grid[1][1];
		CPPUNIT_ASSERT(cr.isAlive() == false);
		CPPUNIT_ASSERT(cr.display() == '-');
	}

	void test_life_insert1 () {
		Life<ConwayCell> lc (3, 3);
		CPPUNIT_ASSERT(lc._grid[3][3].isAlive() == false);
		CPPUNIT_ASSERT(lc._grid[3][3].display() == '.');

		lc.insert(ConwayCell('*'), 2, 2);
		CPPUNIT_ASSERT(lc._grid[3][3].isAlive() == true);
		CPPUNIT_ASSERT(lc._grid[3][3].display() == '*');
	}

	void test_life_insert2 () {
		Life<FredkinCell> fc (4, 2);
		CPPUNIT_ASSERT(fc._grid[5][1].isAlive() == false);
		CPPUNIT_ASSERT(fc._grid[5][1].display() == '-');

		fc.insert(FredkinCell('1'), 4, 0);
		CPPUNIT_ASSERT(fc._grid[5][1].isAlive() == true);
		CPPUNIT_ASSERT(fc._grid[5][1].display() == '1');
	}

	void test_life_insert3 () {
		Life<Cell> lc (5, 5);
		CPPUNIT_ASSERT(lc._grid[3][4].isAlive() == false);
		CPPUNIT_ASSERT(lc._grid[3][4].display() == '.');

		lc.insert(new FredkinCell('5'), 2, 3);
		CPPUNIT_ASSERT(lc._grid[3][4].isAlive() == true);
		CPPUNIT_ASSERT(lc._grid[3][4].display() == '5');
		CPPUNIT_ASSERT(lc._grid[3][4].countsCorners() == false);
		
		lc. insert(new ConwayCell('*'), 0, 0);
		CPPUNIT_ASSERT(lc._grid[1][1].isAlive() == true);
		CPPUNIT_ASSERT(lc._grid[1][1].display() == '*');
		CPPUNIT_ASSERT(lc._grid[1][1].countsCorners() == true);
	}


	// printGeneration
	void test_life_printGeneration1 () {
		Life<ConwayCell> lc (1, 1);
		std::ostringstream w;
		
		lc.printGeneration(w);
		
		CPPUNIT_ASSERT(w.str() == "Generation = 0, Population = 0.\n.\n\n");
	}
	
	void test_life_printGeneration2 () {
		Life<FredkinCell> lc (2, 2);
		std::ostringstream w;
		
		lc.printGeneration(w);
		
		CPPUNIT_ASSERT(w.str() == "Generation = 0, Population = 0.\n--\n--\n\n");
	}
	
	void test_life_printGeneration3 () {
		Life<Cell> lc (2, 2);
		std::ostringstream w;
		
		lc.insert(new ConwayCell('*'), 0, 0);
		
		lc.printGeneration(w);
		
		CPPUNIT_ASSERT(w.str() == "Generation = 0, Population = 1.\n*.\n..\n\n");
	}
	
	// runNextGeneration
	void test_life_runNextGeneration1 () {
		Life<ConwayCell> lc (1, 1, ConwayCell('*'));

		CPPUNIT_ASSERT(lc._grid[1][1].isAlive() == true);
		CPPUNIT_ASSERT(lc._grid[1][1].display() == '*');
		
		lc.runNextGeneration();
		
		CPPUNIT_ASSERT(lc._grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(lc._grid[1][1].display() == '.');
	}
	
	void test_life_runNextGeneration2 () {
		Life<FredkinCell> lc (1, 1);

		lc.runNextGeneration();
		
		CPPUNIT_ASSERT(lc._grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(lc._grid[0][0].display() == '-');
	}
	
	void test_life_runNextGeneration3 () {
		Life<Cell> lc (1, 1);

		lc.runNextGeneration();
		
		CPPUNIT_ASSERT(lc._grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(lc._grid[0][0].display() == '.');
	}
	
	// clearNeighborGrid
	void test_life_clearNeighborGrid1 () {
		Life<Cell> lc (1, 1);

		lc.clearNeighborGrid();
		
		for(size_t i = 0; i < lc._neighborGrid.size(); ++i){
			for(size_t j = 0; j < lc._neighborGrid[0].size(); ++j){
				CPPUNIT_ASSERT(lc._neighborGrid[i][j] == 0);
			}
		}
	}
	
	void test_life_clearNeighborGrid2 () {
		Life<Cell> lc (1, 1);
		
		for(size_t i = 0; i < lc._neighborGrid.size(); ++i){
			for(size_t j = 0; j < lc._neighborGrid[0].size(); ++j){
				lc._neighborGrid[i][j] = 1;
			}
		}

		lc.clearNeighborGrid();
		
		for(size_t i = 0; i < lc._neighborGrid.size(); ++i){
			for(size_t j = 0; j < lc._neighborGrid[0].size(); ++j){
				CPPUNIT_ASSERT(lc._neighborGrid[i][j] == 0);
			}
		}
	}
	
	void test_life_clearNeighborGrid3 () {
		Life<Cell> lc (100, 100);
		
		for(size_t i = 0; i < lc._neighborGrid.size(); ++i){
			for(size_t j = 0; j < lc._neighborGrid[0].size(); ++j){
				lc._neighborGrid[i][j] = 1;
			}
		}

		lc.clearNeighborGrid();
		
		for(size_t i = 0; i < lc._neighborGrid.size(); ++i){
			for(size_t j = 0; j < lc._neighborGrid[0].size(); ++j){
				CPPUNIT_ASSERT(lc._neighborGrid[i][j] == 0);
			}
		}
	}
	
	// increaseNeighborsCount
	void test_life_increaseNeighborsCount1 () {
		Life<ConwayCell> lc (1, 1);
		
		lc.increaseNeighborsCount(1,1);

		CPPUNIT_ASSERT(lc._neighborGrid[0][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[0][1] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[0][2] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[1][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[1][1] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[1][2] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][1] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][2] == 1);
	}
	
	void test_life_increaseNeighborsCount2 () {
		Life<FredkinCell> lc (1, 1);
		
		lc.increaseNeighborsCount(1,1);

		CPPUNIT_ASSERT(lc._neighborGrid[0][0] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[0][1] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[0][2] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[1][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[1][1] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[1][2] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][0] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[2][1] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][2] == 0);
	}
	
	void test_life_increaseNeighborsCount3 () {
		Life<Cell> lc (2, 2);
		
		lc.insert(new FredkinCell('0'), 0, 0);
		lc.insert(new FredkinCell('9'), 1, 1);
		
		lc.increaseNeighborsCount(1,1);
		lc.increaseNeighborsCount(2,2);	
		/*  1110
			1021
			1201
			0111
		*/	
		CPPUNIT_ASSERT(lc._neighborGrid[0][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[0][1] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[0][2] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[0][3] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[1][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[1][1] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[1][2] == 2);
		CPPUNIT_ASSERT(lc._neighborGrid[1][3] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][0] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[2][1] == 2);
		CPPUNIT_ASSERT(lc._neighborGrid[2][2] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[2][3] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[3][0] == 0);
		CPPUNIT_ASSERT(lc._neighborGrid[3][1] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[3][2] == 1);
		CPPUNIT_ASSERT(lc._neighborGrid[3][3] == 1);
	}	
	
	// updatePopulation
	void test_life_updatePopulation1 () {
		Life<ConwayCell> lc (1, 1);
		
		CPPUNIT_ASSERT(lc._populationCount == 0);
		
		ConwayCell ccAlive('*');
		ConwayCell ccDead('.');
		
		lc.updatePopulation(ccDead, ccAlive);
		
		CPPUNIT_ASSERT(lc._populationCount == 1);
	}
	
	void test_life_updatePopulation2 () {
		Life<FredkinCell> lc (1, 1);
		
		CPPUNIT_ASSERT(lc._populationCount == 0);
		
		FredkinCell ccAlive('9');
		FredkinCell ccDead('-');
		
		lc.updatePopulation(ccDead, ccAlive);
		
		CPPUNIT_ASSERT(lc._populationCount == 1);
	}
	
	void test_life_updatePopulation3 () {
		Life<Cell> lc (1, 1);
		
		CPPUNIT_ASSERT(lc._populationCount == 0);
		
		Cell ccAlive = new ConwayCell('*');
		Cell ccDead = new FredkinCell('-');
		
		lc.updatePopulation(ccDead, ccAlive);
		
		CPPUNIT_ASSERT(lc._populationCount == 1);
	}
	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);		

	CPPUNIT_TEST(test_conway_construct1);
	CPPUNIT_TEST(test_conway_construct2);
	CPPUNIT_TEST(test_conway_construct3);
	CPPUNIT_TEST(test_conway_evalGeneration1);
	CPPUNIT_TEST(test_conway_evalGeneration2);
	CPPUNIT_TEST(test_conway_evalGeneration3);
	CPPUNIT_TEST(test_conway_clone1);
	CPPUNIT_TEST(test_conway_clone2);
	CPPUNIT_TEST(test_conway_clone3);

	CPPUNIT_TEST(test_fredkin_construct1);
	CPPUNIT_TEST(test_fredkin_construct2);
	CPPUNIT_TEST(test_fredkin_construct3);
	CPPUNIT_TEST(test_fredkin_updateAliveDisplay1);
	CPPUNIT_TEST(test_fredkin_updateAliveDisplay2);
	CPPUNIT_TEST(test_fredkin_updateAliveDisplay3);
	CPPUNIT_TEST(test_fredkin_evalGeneration1);
	CPPUNIT_TEST(test_fredkin_evalGeneration2);
	CPPUNIT_TEST(test_fredkin_evalGeneration3);

	CPPUNIT_TEST(test_cell_construct1);
	CPPUNIT_TEST(test_cell_construct2);
	CPPUNIT_TEST(test_cell_construct3);
	CPPUNIT_TEST(test_cell_copyConstruct1);
	CPPUNIT_TEST(test_cell_copyConstruct2);
	CPPUNIT_TEST(test_cell_copyConstruct3);
	CPPUNIT_TEST(test_cell_copyAssignment1);
	CPPUNIT_TEST(test_cell_copyAssignment2);
	CPPUNIT_TEST(test_cell_copyAssignment3);
	CPPUNIT_TEST(test_cell_evalGeneration1);
	CPPUNIT_TEST(test_cell_evalGeneration2);
	CPPUNIT_TEST(test_cell_evalGeneration3);
	CPPUNIT_TEST(test_countsCorners1);
	CPPUNIT_TEST(test_countsCorners2);
	CPPUNIT_TEST(test_countsCorners3);

	CPPUNIT_TEST(test_life_construct1);
	CPPUNIT_TEST(test_life_construct2);
	CPPUNIT_TEST(test_life_construct3);
	CPPUNIT_TEST(test_life_construct4);
	CPPUNIT_TEST(test_life_insert1);
	CPPUNIT_TEST(test_life_insert2);
	CPPUNIT_TEST(test_life_insert3);
	CPPUNIT_TEST(test_life_printGeneration1);
	CPPUNIT_TEST(test_life_printGeneration2);
	CPPUNIT_TEST(test_life_printGeneration3);
	CPPUNIT_TEST(test_life_runNextGeneration1);
	CPPUNIT_TEST(test_life_runNextGeneration2);
	CPPUNIT_TEST(test_life_runNextGeneration3);
	CPPUNIT_TEST(test_life_clearNeighborGrid1);
	CPPUNIT_TEST(test_life_clearNeighborGrid2);
	CPPUNIT_TEST(test_life_clearNeighborGrid3);
	CPPUNIT_TEST(test_life_increaseNeighborsCount1);
	CPPUNIT_TEST(test_life_increaseNeighborsCount2);
	CPPUNIT_TEST(test_life_increaseNeighborsCount3);
	CPPUNIT_TEST(test_life_updatePopulation1);
	CPPUNIT_TEST(test_life_updatePopulation2);
	CPPUNIT_TEST(test_life_updatePopulation3);

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
