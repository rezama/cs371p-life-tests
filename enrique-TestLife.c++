// ------------------------------
// Copyright (C) 2012
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Life.h"
#define CONWAY 0
#define FREDKIN 1

using namespace std;

struct TestLife: CppUnit::TestFixture {

	// --------
	// Test Life Constructor
	// --------

	void testLifeConstructor_1() {
		Life<ConwayCell> grid("RunLifeConway.in");
		CPPUNIT_ASSERT(grid[0][0].getType() == CONWAY);
		CPPUNIT_ASSERT(grid[0][0].getCh() == '.');
	}

	void testLifeConstructor_2() {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		CPPUNIT_ASSERT(grid[0][0].getType() == FREDKIN);
		CPPUNIT_ASSERT(grid[0][0].getCh() == '-');
	}

	void testLifeConstructor_3() {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		CPPUNIT_ASSERT(grid[9][9].getType() == FREDKIN);
		CPPUNIT_ASSERT(grid[9][9].getCh() == '0');
	}

	// --------
	// Test Life::getPopulation()
	// --------

	void testGetPopulation_1() {
		Life<ConwayCell> grid("RunLifeConway.in");
		CPPUNIT_ASSERT(grid.getPopulation() == 35);

	}

	void testGetPopulation_2() {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		CPPUNIT_ASSERT(grid.getPopulation() == 4);

	}

	// --------
	// Test ConwayCell::isAlive()
	// --------

	void testisAliveConway_1() {
		ConwayCell cCell;
		CPPUNIT_ASSERT(cCell.isAlive() == false);
	}

	void testisAliveConway_2() {
		ConwayCell cCell('*');
		CPPUNIT_ASSERT(cCell.isAlive() == true);
	}

	// --------
	// Test FredkinCell::isAlive()
	// --------

	void testisAliveFredkin_1() {
		FredkinCell fCell;
		CPPUNIT_ASSERT(fCell.isAlive() == false);
	}

	void testisAliveFredkin_2() {
		FredkinCell fCell('-');
		CPPUNIT_ASSERT(fCell.isAlive() == false);
	}

	void testisAliveFredkin_3() {
		FredkinCell fCell('+');
		CPPUNIT_ASSERT(fCell.isAlive() == true);
	}

	// --------
	// Test Life::getNeighbor
	// --------

	void testgetNeighborConway_1() {
		Life<ConwayCell> grid("RunLifeConway.in");
		CPPUNIT_ASSERT(grid.getNeighbor(0, 0, CONWAY) == 0);
	}

	void testgetNeighborConway_2() {
		Life<ConwayCell> grid("RunLifeConway.in");
		CPPUNIT_ASSERT(grid.getNeighbor(2, 0, CONWAY) == 0);
	}

	void testgetNeighborConway_3() {
		Life<ConwayCell> grid("RunLifeConway.in");
		CPPUNIT_ASSERT(grid.getNeighbor(35, 33, CONWAY) == 3);
	}

	void testgetNeighborFredkin_1() {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		CPPUNIT_ASSERT(grid.getNeighbor(0, 0, FREDKIN) == 0);
	}

	void testgetNeighborFredkin_2() {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		CPPUNIT_ASSERT(grid.getNeighbor(3, 0, FREDKIN) == 0);
	}

	void testgetNeighborFredkin_3() {
		Life<FredkinCell> grid("RunLifeFredkin.in");
		CPPUNIT_ASSERT(grid.getNeighbor(9, 9, FREDKIN) == 2);
	}

	// --------
	// Test cell action
	// --------

	void testactionConway_1() {
		ConwayCell cCell;
		CPPUNIT_ASSERT(cCell.getCh() == '.');

		ConwayCell *pcCell = &cCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pcCell);

		pt->action(pt, 3);
		CPPUNIT_ASSERT(cCell.getCh() == '*');
	}

	void testactionConway_2() {
		ConwayCell cCell;
		CPPUNIT_ASSERT(cCell.getCh() == '.');

		ConwayCell *pcCell = &cCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pcCell);

		pt->action(pt, 4);
		CPPUNIT_ASSERT(cCell.getCh() == '.');
	}

	void testactionConway_3() {
		ConwayCell cCell('*');
		CPPUNIT_ASSERT(cCell.getCh() == '*');

		ConwayCell *pcCell = &cCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pcCell);

		pt->action(pt, 3);
		CPPUNIT_ASSERT(cCell.getCh() == '*');
	}

	void testactionConway_4() {
		ConwayCell cCell('*');
		CPPUNIT_ASSERT(cCell.getCh() == '*');

		ConwayCell *pcCell = &cCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pcCell);

		pt->action(pt, 0);
		CPPUNIT_ASSERT(cCell.getCh() == '.');
	}

	void testactionFredkin_1() {
		FredkinCell fCell;
		CPPUNIT_ASSERT(fCell.getCh() == '-');

		FredkinCell *pfCell = &fCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pfCell);

		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '0');
	}

	void testactionFredkin_2() {
		FredkinCell fCell;
		CPPUNIT_ASSERT(fCell.getCh() == '-');

		FredkinCell *pfCell = &fCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pfCell);

		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '0');
		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '1');
		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '2');
		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '3');
		pt->action(pt, 2);
		CPPUNIT_ASSERT(fCell.getCh() == '-');
		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '3');
	}

	void testactionFredkin_3() {
		FredkinCell fCell('9');
		CPPUNIT_ASSERT(fCell.getCh() == '9');

		FredkinCell *pfCell = &fCell;
		AbstractCell* pt = dynamic_cast<AbstractCell*>(pfCell);

		pt->action(pt, 3);
		CPPUNIT_ASSERT(fCell.getCh() == '+');
		pt->action(pt, 2);
		CPPUNIT_ASSERT(fCell.getCh() == '-');
	}

	// --------
	// Test Cell
	// --------

	void testCell_1() {
		FredkinCell *p = new FredkinCell();

		Cell cell = p;
		CPPUNIT_ASSERT(cell.getCh() == '-');
		cell.setCh('3');
		CPPUNIT_ASSERT(cell.getCh() == '3');
	}

	void testCell_2() {
		FredkinCell *p = new FredkinCell();

		Cell cell = p;
		CPPUNIT_ASSERT(cell.isAlive() == false);
		cell.setCh('3');
		CPPUNIT_ASSERT(cell.isAlive() == true);
	}

	void testCell_3() {
		ConwayCell *p = new ConwayCell('*');

		Cell cell = p;
		CPPUNIT_ASSERT(cell.getCh() == '*');

		Cell* pt = &cell;
		cell.action(pt, 0);
		CPPUNIT_ASSERT(cell.getCh() == '.');

	}

CPPUNIT_TEST_SUITE(TestLife);

		CPPUNIT_TEST(testLifeConstructor_1);
		CPPUNIT_TEST(testLifeConstructor_2);
		CPPUNIT_TEST(testLifeConstructor_3);

		CPPUNIT_TEST(testGetPopulation_1);
		CPPUNIT_TEST(testGetPopulation_2);

		CPPUNIT_TEST(testisAliveConway_1);
		CPPUNIT_TEST(testisAliveConway_2);

		CPPUNIT_TEST(testisAliveFredkin_1);
		CPPUNIT_TEST(testisAliveFredkin_2);
		CPPUNIT_TEST(testisAliveFredkin_3);

		CPPUNIT_TEST(testgetNeighborConway_1);
		CPPUNIT_TEST(testgetNeighborConway_2);
		CPPUNIT_TEST(testgetNeighborConway_3);

		CPPUNIT_TEST(testgetNeighborFredkin_1);
		CPPUNIT_TEST(testgetNeighborFredkin_2);
		CPPUNIT_TEST(testgetNeighborFredkin_3);

		CPPUNIT_TEST(testactionConway_1);
		CPPUNIT_TEST(testactionConway_2);
		CPPUNIT_TEST(testactionConway_3);
		CPPUNIT_TEST(testactionConway_4);

		CPPUNIT_TEST(testactionFredkin_1);
		CPPUNIT_TEST(testactionFredkin_2);
		CPPUNIT_TEST(testactionFredkin_3);

		CPPUNIT_TEST(testCell_1);
		CPPUNIT_TEST(testCell_2);
		CPPUNIT_TEST(testCell_3);

	CPPUNIT_TEST_SUITE_END();
};

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	cout << "TestLife.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestLife::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}

