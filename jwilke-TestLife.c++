#include <iostream>
#include <sstream>
#include <string>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public
#define class struct

#include "Life.h"
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"



using namespace std;

struct TestLife : CppUnit::TestFixture {
// ~~~~~~~~~~~~
// ConwayCell Tests
//~~~~~~~~~~~~~
	// ------------------
	// Constructors Tests
	// ------------------
	void test_ConwayCell_1() {
		ConwayCell c (true);
		CPPUNIT_ASSERT(c.alive == true);
	}
	void test_ConwayCell_2() {
		ConwayCell c (false);
		CPPUNIT_ASSERT(c.alive == false);
	}
	void test_ConwayCell_3() {
		ConwayCell c ('*');
		CPPUNIT_ASSERT(c.alive == true);
	}
	void test_ConwayCell_4() {
		ConwayCell c ('.');
		CPPUNIT_ASSERT(c.alive == false);
	}

	// -------------
	// getChar Tests
	// -------------
	void test_conway_getChar_1 (){
		ConwayCell c ('.');
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_conway_getChar_2 (){
		ConwayCell c ('*');
		CPPUNIT_ASSERT(c.getChar() == '*');
	}
	void test_conway_getChar_3 (){
		ConwayCell c (false);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_conway_getChar_4 (){
		ConwayCell c (true);
		CPPUNIT_ASSERT(c.getChar() == '*');
	}

	// ------------
	// update Tests
	// ------------
	void test_conway_update_1 () {
		ConwayCell c (true);
		c.update(0, 1);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_conway_update_2 () {
		ConwayCell c (true);
		c.update(4, 3);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_conway_update_3 () {
		ConwayCell c (true);
		c.update(2, 1);
		CPPUNIT_ASSERT(c.getChar() == '*');
	}
	void test_conway_update_4 () {
		ConwayCell c (false);
		c.update(2, 2);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_conway_update_5 () {
		ConwayCell c (false);
		c.update(1, 2);
		CPPUNIT_ASSERT(c.getChar() == '*');
	}

	// -----------
	// clone Tests
	// -----------
	void  test_conway_clone_1() {
		ConwayCell a = (true);
		ConwayCell* clonep = a.clone();
		CPPUNIT_ASSERT(clonep->getChar() == '*');
		a.update(4,4);
		CPPUNIT_ASSERT(clonep->getChar() == '*'); 
	}
	void  test_conway_clone_2() {
		ConwayCell a = (false);
		ConwayCell* clonep = a.clone();
		CPPUNIT_ASSERT(clonep->getChar() == '.');
		a.update(2,1);
		CPPUNIT_ASSERT(clonep->getChar() == '.'); 
	}
	void test_conway_clone_3() {
		ConwayCell* clonep = 0;
		{
			ConwayCell a = (true);
			clonep = a.clone();
			CPPUNIT_ASSERT(clonep->getChar() == '*');
		}
		CPPUNIT_ASSERT(clonep->getChar() == '*');
	}

	// ---------------
	// transform Tests
	// ---------------
	void test_conway_transform_1() {
		ConwayCell c = (true);
		AbstractCell* tp = c.transform();
		CPPUNIT_ASSERT(tp->getChar() == '*');
	}
	void test_conway_transform_2() {
		ConwayCell c = (false);
		AbstractCell* tp = c.transform();
		CPPUNIT_ASSERT(tp->getChar() == '.');
	}
	void test_conway_transform_3() {
		ConwayCell c = (true);
		AbstractCell* tp = c.transform(); //returns pointer to c, so nothing should change
		CPPUNIT_ASSERT(tp->getChar() == '*');
		c.update(0,0);
		CPPUNIT_ASSERT(tp->getChar() == '.');
	}

// ~~~~~~~~~~~~~~~~~
// FredkinCell Tests 
// ~~~~~~~~~~~~~~~~~
	// ------------------
	// Constructors Tests
	// ------------------
	void test_FredkinCell_1 () {
		FredkinCell f (true);
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 0);
	}
	void test_FredkinCell_2 () {
		FredkinCell f (false, 7);
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 7);
	}
	void test_FredkinCell_3 () {
		FredkinCell f ('-');
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 0);
	}
	void test_FredkinCell_4 () {
		FredkinCell f ('+');
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 10);
	}
	void test_FredkinCell_5 () {
		FredkinCell f ('3');
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 3);
	}

	// -------------
	// getChar Tests
	// -------------
	void test_fredkin_getChar_1 () {
		FredkinCell f (true);
		CPPUNIT_ASSERT(f.getChar() == '0');
	}
	void test_fredkin_getChar_2 () {
		FredkinCell f (false);
		CPPUNIT_ASSERT(f.getChar() == '-');
	}
	void test_fredkin_getChar_3 () {
		FredkinCell f (true, 8);
		CPPUNIT_ASSERT(f.getChar() == '8');
	}
	void test_fredkin_getChar_4 () {
		FredkinCell f (true, 21);
		CPPUNIT_ASSERT(f.getChar() == '+');
	}

	// ------------
	// update Tests
	// ------------
	void test_fredkin_update_1 () {
		FredkinCell f (true);
		f.update(1,0);
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 1);
	}
	void test_fredkin_update_2 () {
		FredkinCell f (true, 3);
		f.update(3,5);
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 4);
	}
	void test_fredkin_update_3 () {
		FredkinCell f (true, 2);
		f.update(0,0);
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 2);
	}
	void test_fredkin_update_4 () {
		FredkinCell f (true, 1);
		f.update(2,1);
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 1);
	}
	void test_fredkin_update_5 () {
		FredkinCell f (true, 21);
		f.update(4,0);
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 21);
	}
	void test_fredkin_update_6 () {
		FredkinCell f (false, 1);
		f.update(1,0);
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 1);
	}
	void test_fredkin_update_7 () {
		FredkinCell f (false, 9);
		f.update(3,9);
		CPPUNIT_ASSERT(f.alive == true);
		CPPUNIT_ASSERT(f.age == 9);
	}
	void test_fredkin_update_8 () {
		FredkinCell f (false, 3);
		f.update(2,0);
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 3);
	}
	void test_fredkin_update_9 () {
		FredkinCell f (false, 8);
		f.update(4,11);
		CPPUNIT_ASSERT(f.alive == false);
		CPPUNIT_ASSERT(f.age == 8);
	}

	// -----------
	// clone Tests 
	// -----------
	void test_fredkin_clone_1 () {
		FredkinCell f (true, 2);
		FredkinCell* fp = f.clone();
		CPPUNIT_ASSERT(fp->alive == true);
		CPPUNIT_ASSERT(fp->age == 2);
		f.update(2, 0);
		CPPUNIT_ASSERT(fp->alive == true);
		CPPUNIT_ASSERT(fp->age == 2);
	}
	void test_fredkin_clone_2 () {
		FredkinCell f (false, 7);
		FredkinCell* fp = f.clone();
		CPPUNIT_ASSERT(fp->alive == false);
		CPPUNIT_ASSERT(fp->age == 7);
		f.update(3, 0);
		CPPUNIT_ASSERT(fp->alive == false);
		CPPUNIT_ASSERT(fp->age == 7);
	}
	void test_fredkin_clone_3 () {
		FredkinCell* fp = 0; 
		{
			FredkinCell f (false, 7);
			fp = f.clone();
			CPPUNIT_ASSERT(fp->alive == false);
			CPPUNIT_ASSERT(fp->age == 7);
		}
		CPPUNIT_ASSERT(fp->alive == false);
		CPPUNIT_ASSERT(fp->age == 7);
	}

	// ---------------
	// transform Tests
	// ---------------
	void test_fredkin_transform_1 () {
		FredkinCell f (true, 2);
		AbstractCell* tp = f.transform();
		CPPUNIT_ASSERT(tp->alive == true);
	}
	void test_fredkin_transform_2 () {
		FredkinCell f (false);
		AbstractCell* tp = f.transform();
		CPPUNIT_ASSERT(tp->alive == true);
	}
	void test_fredkin_transform_3 () {
		AbstractCell* tp = 0; 
		{
			FredkinCell f (true, 100);
			tp = f.transform();
			CPPUNIT_ASSERT(tp->alive == true);
		}
			CPPUNIT_ASSERT(tp->alive == true);
	}

// ~~~~~~~~~~
// Cell Tests
// ~~~~~~~~~~
	// -----------------------
	// Constructors Tests
	// -----------------------
	void test_Cell_1 () {
		Cell c (new ConwayCell(true));
		CPPUNIT_ASSERT(c._cell->alive == true);
		CPPUNIT_ASSERT(c._cell->age == 0);
	}
	void test_Cell_2 () {
		Cell c (new FredkinCell(true, 7));
		CPPUNIT_ASSERT(c._cell->alive == true);
		CPPUNIT_ASSERT(c._cell->age == 7);
	}
	void test_Cell_3 () {
		Cell a (new FredkinCell(true, 11));
		CPPUNIT_ASSERT(a._cell->alive == true);
		CPPUNIT_ASSERT(a._cell->age == 11);
		Cell b (a);
		CPPUNIT_ASSERT(b._cell->alive == true);
		CPPUNIT_ASSERT(b._cell->age == 11);
	}

	// ----------------
	// Assignment Tests
	// ----------------
	void test_cell_assignment_1 () {
		Cell a (new ConwayCell(true));
		Cell b (new ConwayCell(false));
		CPPUNIT_ASSERT(a._cell->alive == true);
		CPPUNIT_ASSERT(a._cell->age == 0);
		CPPUNIT_ASSERT(b._cell->alive == false);
		CPPUNIT_ASSERT(b._cell->age == 0);
		b = a;
		CPPUNIT_ASSERT(b._cell->alive == true);
		CPPUNIT_ASSERT(b._cell->age == 0);
	}
	void test_cell_assignment_2 () {
		Cell a (new FredkinCell(true, 3));
		Cell b (new FredkinCell(false, 34));
		CPPUNIT_ASSERT(a._cell->alive == true);
		CPPUNIT_ASSERT(a._cell->age == 3);
		CPPUNIT_ASSERT(b._cell->alive == false);
		CPPUNIT_ASSERT(b._cell->age == 34);
		b = a;
		CPPUNIT_ASSERT(b._cell->alive == true);
		CPPUNIT_ASSERT(b._cell->age == 3);
	}
	void test_cell_assignment_3 () {
		Cell a (new FredkinCell(true, 7));
		Cell b (new ConwayCell(false));
		CPPUNIT_ASSERT(a._cell->alive == true);
		CPPUNIT_ASSERT(a._cell->age == 7);
		CPPUNIT_ASSERT(b._cell->alive == false);
		CPPUNIT_ASSERT(b._cell->age == 0);
		b = a;
		CPPUNIT_ASSERT(b._cell->alive == true);
		CPPUNIT_ASSERT(b._cell->age == 7);
	}
	void test_cell_assignment_4 () {
		Cell a (new ConwayCell(true));
		Cell b (new FredkinCell(false, 9));
		CPPUNIT_ASSERT(a._cell->alive == true);
		CPPUNIT_ASSERT(a._cell->age == 0);
		CPPUNIT_ASSERT(b._cell->alive == false);
		CPPUNIT_ASSERT(b._cell->age == 9);
		b = a;
		CPPUNIT_ASSERT(b._cell->alive == true);
		CPPUNIT_ASSERT(b._cell->age == 0);
	}

	// ---------
	// age Tests
	// ---------
	void test_cell_age_1 () {
		Cell c (new ConwayCell(true));
		CPPUNIT_ASSERT(c.age() == 0);
	}
	void test_cell_age_2 () {
		Cell c (new FredkinCell(false));
		CPPUNIT_ASSERT(c.age() == 0);
	}
	void test_cell_age_3 () {
		Cell c (new FredkinCell(true, 31));
		CPPUNIT_ASSERT(c.age() == 31);
	}

	// -------
	// isAlive
	// -------
	void test_cell_isAlive_1 () {
		Cell c (new ConwayCell(true));
		CPPUNIT_ASSERT(c.isAlive() == true);
	}
	void test_cell_isAlive_2 () {
		Cell c (new FredkinCell(false));
		CPPUNIT_ASSERT(c.isAlive() == false);
	}
	void test_cell_isAlive_3 () {
		Cell c (new FredkinCell(true, 3));
		CPPUNIT_ASSERT(c.isAlive() == true);
	}

	// -------
	// getChar
	// -------
	void test_cell_getChar_1 () {
		Cell c (new ConwayCell(true));
		CPPUNIT_ASSERT(c.getChar() == '*');
	}
	void test_cell_getChar_2 () {
		Cell c (new ConwayCell(false));
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_cell_getChar_3 () {
		Cell c (new FredkinCell(false));
		CPPUNIT_ASSERT(c.getChar() == '-');
	}
	void test_cell_getChar_4 () {
		Cell c (new FredkinCell(true, 6));
		CPPUNIT_ASSERT(c.getChar() == '6');
	}
	void test_cell_getChar_5 () {
		Cell c (new FredkinCell(true, 99));
		CPPUNIT_ASSERT(c.getChar() == '+');
	}

	// ------
	// update
	// ------
	void test_cell_update_1 () {
		Cell c(new ConwayCell(true));
		c.update(0, 1);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_cell_update_2 () {
		Cell c(new ConwayCell(true));
		c.update(4, 3);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_cell_update_3 () {
		Cell c(new ConwayCell(true));
		c.update(2, 1);
		CPPUNIT_ASSERT(c.getChar() == '*');
	}
	void test_cell_update_4 () {
		Cell c(new ConwayCell(false));
		c.update(2, 2);
		CPPUNIT_ASSERT(c.getChar() == '.');
	}
	void test_cell_update_5 () {
		Cell c(new ConwayCell(false));
		c.update(1, 2);
		CPPUNIT_ASSERT(c.getChar() == '*');
	}
	void test_cell_update_6 () {
		Cell c(new FredkinCell(true));
		c.update(1,0);
		CPPUNIT_ASSERT(c.isAlive() == true);
		CPPUNIT_ASSERT(c.age() == 1);
	}
	void test_cell_update_7 () {
		Cell c(new FredkinCell(true, 3));
		c.update(3,5);
		CPPUNIT_ASSERT(c.isAlive() == true);
		CPPUNIT_ASSERT(c.age() == 4);
	}
	void test_cell_update_8 () {
		Cell c(new FredkinCell(true, 1));
		c.update(0,0);
		CPPUNIT_ASSERT(c.isAlive() == false);
		CPPUNIT_ASSERT(c.age() == 1);
	}
	void test_cell_update_9 () {
		Cell c(new FredkinCell(true, 1));
		c.update(3,1);
		CPPUNIT_ASSERT(c.isAlive() == true);
		CPPUNIT_ASSERT(c.age() == 0);
	}

// ~~~~~~~~~~
// Life Tests
// ~~~~~~~~~~
	// -----------------
	// Constructor Tests
	// -----------------
	void test_life_1 () {
		deque< deque< ConwayCell > > cell_grid = deque< deque< ConwayCell > >(5, deque<ConwayCell>(5));
		Life<ConwayCell> test(3, 3, cell_grid);
		CPPUNIT_ASSERT(test._grid.size() == 5);
		CPPUNIT_ASSERT(test._grid[0].size() == 5);
	}
	
	void test_life_2 () {
		deque< deque< FredkinCell > > cell_grid = deque< deque< FredkinCell > >(7, deque<FredkinCell>(5));
		Life<FredkinCell> test(5, 3, cell_grid);
		CPPUNIT_ASSERT(test._r == 5);
		CPPUNIT_ASSERT(test._c == 3);
	}
	
	void test_life_3 () {
		deque< deque< Cell > > cell_grid = deque< deque< Cell > >(7, deque<Cell>(9, Cell(new ConwayCell())));
		Life<Cell> test(5, 7, cell_grid);
		CPPUNIT_ASSERT(test.a_neighbors.size() == 7);
		CPPUNIT_ASSERT(test.d_neighbors[0].size() == 9);
	}
	void test_life_4 () {
		deque< deque< Cell > > cell_grid = deque< deque< Cell > >(4, deque<Cell>(4, Cell(new FredkinCell())));
		Life<Cell> test(2, 2, cell_grid);
		CPPUNIT_ASSERT(test.a_neighbors.size() == 4);
		CPPUNIT_ASSERT(test.d_neighbors[0].size() == 4);
	}
	
	// -----------
	// print Tests
	// -----------
	void test_print_1() {
		deque< deque< ConwayCell > > cell_grid = deque< deque< ConwayCell > >(5, deque<ConwayCell>(5));
		ostringstream out;
		Life<ConwayCell> test(3, 3, cell_grid);
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 0, Population = 0.\n...\n...\n...\n\n");
	}
	void test_print_2() {
		deque< deque< FredkinCell > > cell_grid = deque< deque< FredkinCell > >(5, deque<FredkinCell>(5));
		ostringstream out;
		Life<FredkinCell> test(3, 3, cell_grid);
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 0, Population = 0.\n---\n---\n---\n\n");
	}
	void test_print_3() {
		deque< deque< FredkinCell > > cell_grid = deque< deque< FredkinCell > >(5, deque<FredkinCell>(5));
		ostringstream out;
		Life<FredkinCell> test(3, 3, cell_grid);
		test._grid[2][2].alive = true;
		test._grid[2][2].age = 7;
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 0, Population = 0.\n---\n-7-\n---\n\n");
		test._grid[2][2].age = 11;
		out.str("");
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 0, Population = 0.\n---\n-+-\n---\n\n");
	}

	// --------------
	// simulate Tests
	// --------------
	void test_simulate_1() {
		deque< deque< ConwayCell > > cell_grid = deque< deque< ConwayCell > >(5, deque<ConwayCell>(5));
		ostringstream out;
		Life<ConwayCell> test(3, 3, cell_grid);
		test._grid[2][2].alive = true;
		test.simulate(1);
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 1, Population = 0.\n...\n...\n...\n\n");
	}

	void test_simulate_2() {
		deque< deque< FredkinCell > > cell_grid = deque< deque< FredkinCell > >(5, deque<FredkinCell>(7));
		ostringstream out;
		Life<FredkinCell> test(3, 5, cell_grid);
		test._grid[1][2].alive = true;
		test._grid[2][1].alive = true;
		test._grid[3][2].alive = true;
		test.simulate(1);
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 1, Population = 3.\n--0--\n-0---\n--0--\n\n");
	}
	void test_simulate_3() {
		deque< deque< Cell > > cell_grid = deque< deque< Cell > > (5, deque<Cell>(5, Cell(new FredkinCell())));
		ostringstream out;
		Life<Cell> test(3, 3, cell_grid);
		test._grid[1][2]._cell->alive = true;
		test._grid[2][2]._cell->alive = true;
		test._grid[2][2]._cell->age = 1;
		test.simulate(1);
		test.print(out);
		CPPUNIT_ASSERT(out.str() == "Generation = 1, Population = 7.\n010\n0*0\n-0-\n\n");
	}

// ~~~~~
// suite
// ~~~~~
	CPPUNIT_TEST_SUITE(TestLife);

	CPPUNIT_TEST(test_ConwayCell_1);
	CPPUNIT_TEST(test_ConwayCell_2);
	CPPUNIT_TEST(test_ConwayCell_3);
	CPPUNIT_TEST(test_ConwayCell_4);

	CPPUNIT_TEST(test_conway_getChar_1);
	CPPUNIT_TEST(test_conway_getChar_2);
	CPPUNIT_TEST(test_conway_getChar_3);
	CPPUNIT_TEST(test_conway_getChar_4);

	CPPUNIT_TEST(test_conway_update_1);
	CPPUNIT_TEST(test_conway_update_2);
	CPPUNIT_TEST(test_conway_update_3);
	CPPUNIT_TEST(test_conway_update_4);
	CPPUNIT_TEST(test_conway_update_5);

	CPPUNIT_TEST(test_conway_clone_1);
	CPPUNIT_TEST(test_conway_clone_2);
	CPPUNIT_TEST(test_conway_clone_3);

	CPPUNIT_TEST(test_conway_transform_1);
	CPPUNIT_TEST(test_conway_transform_2);
	CPPUNIT_TEST(test_conway_transform_3);

	CPPUNIT_TEST(test_FredkinCell_1);
	CPPUNIT_TEST(test_FredkinCell_2);
	CPPUNIT_TEST(test_FredkinCell_3);
	CPPUNIT_TEST(test_FredkinCell_4);
	CPPUNIT_TEST(test_FredkinCell_5);

	CPPUNIT_TEST(test_fredkin_getChar_1);
	CPPUNIT_TEST(test_fredkin_getChar_2);
	CPPUNIT_TEST(test_fredkin_getChar_3);
	CPPUNIT_TEST(test_fredkin_getChar_4);

	CPPUNIT_TEST(test_fredkin_update_1);
	CPPUNIT_TEST(test_fredkin_update_2);
	CPPUNIT_TEST(test_fredkin_update_3);
	CPPUNIT_TEST(test_fredkin_update_4);
	CPPUNIT_TEST(test_fredkin_update_5);
	CPPUNIT_TEST(test_fredkin_update_6);
	CPPUNIT_TEST(test_fredkin_update_7);
	CPPUNIT_TEST(test_fredkin_update_8);
	CPPUNIT_TEST(test_fredkin_update_9);

	CPPUNIT_TEST(test_fredkin_clone_1);
	CPPUNIT_TEST(test_fredkin_clone_2);
	CPPUNIT_TEST(test_fredkin_clone_3);

	CPPUNIT_TEST(test_fredkin_transform_1);
	CPPUNIT_TEST(test_fredkin_transform_2);
	CPPUNIT_TEST(test_fredkin_transform_3);

	CPPUNIT_TEST(test_Cell_1);
	CPPUNIT_TEST(test_Cell_2);
	CPPUNIT_TEST(test_Cell_3);

	CPPUNIT_TEST(test_cell_assignment_1);
	CPPUNIT_TEST(test_cell_assignment_2);
	CPPUNIT_TEST(test_cell_assignment_3);
	CPPUNIT_TEST(test_cell_assignment_4);

	CPPUNIT_TEST(test_cell_age_1);
	CPPUNIT_TEST(test_cell_age_2);
	CPPUNIT_TEST(test_cell_age_3);

	CPPUNIT_TEST(test_cell_isAlive_1);
	CPPUNIT_TEST(test_cell_isAlive_2);
	CPPUNIT_TEST(test_cell_isAlive_3);

	CPPUNIT_TEST(test_cell_getChar_1);
	CPPUNIT_TEST(test_cell_getChar_2);
	CPPUNIT_TEST(test_cell_getChar_3);
	CPPUNIT_TEST(test_cell_getChar_4);
	CPPUNIT_TEST(test_cell_getChar_5);

	CPPUNIT_TEST(test_cell_update_1);
	CPPUNIT_TEST(test_cell_update_2);
	CPPUNIT_TEST(test_cell_update_3);
	CPPUNIT_TEST(test_cell_update_4);
	CPPUNIT_TEST(test_cell_update_5);
	CPPUNIT_TEST(test_cell_update_6);
	CPPUNIT_TEST(test_cell_update_7);
	CPPUNIT_TEST(test_cell_update_8);
	CPPUNIT_TEST(test_cell_update_9);

	CPPUNIT_TEST(test_life_1);
	CPPUNIT_TEST(test_life_2);
	CPPUNIT_TEST(test_life_3);
	CPPUNIT_TEST(test_life_4);
	
	CPPUNIT_TEST(test_print_1);
	CPPUNIT_TEST(test_print_2);
	CPPUNIT_TEST(test_print_3);

	CPPUNIT_TEST(test_simulate_1);
	CPPUNIT_TEST(test_simulate_2);
	CPPUNIT_TEST(test_simulate_3);

	CPPUNIT_TEST_SUITE_END();
};

int main() {
	ios_base::sync_with_stdio(false);
	cout << "TestLife.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestLife::suite());
	tr.run();
}
