/*
 * TestLife.c++
 *
 *  Created on: 24 Nov 2012
 *      Author: fiofou
 *
 *       To run:
 *       g++ TestLife.c++ -pedantic -lcppunit -ldl -std=c++0x -Wall  -o TestLife.c++.app
 *
 */



#include <iostream>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner
#include <string>
#include <stdexcept>


#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Life.h"
#include "AbstractCell.h"
using namespace std;

template <typename T>
struct TestLife : CppUnit::TestFixture {




	void test_grid0() {
		Life<Cell> test_grid (3, 3, new ConwayCell());
		CPPUNIT_ASSERT(true);
	}

	void test_conway(){
		Cell x = new ConwayCell();
		CPPUNIT_ASSERT (x.cell_char() == '.');
	}

	void test_conway2(){
		Cell x = new ConwayCell('*');
		x.die();
		CPPUNIT_ASSERT (x.cell_char() == '.');
	}

	void test_conway3(){
		Cell x = new ConwayCell('*');
		CPPUNIT_ASSERT (x.cell_char() == '*');
	}

	void test_cell_char(){
		Cell x = new ConwayCell();
		x.live();
		CPPUNIT_ASSERT (x.cell_char() == '*');
	}

	void test_count_neighbors(){
		Cell x = new ConwayCell();
		short neighbors[] = {1,1,1,1,1,1,1,1};
		CPPUNIT_ASSERT (x.count_neighbors(neighbors) == 8);
	}



	void test_fredkin(){
		Cell x = new FredkinCell();
		CPPUNIT_ASSERT (x.cell_char() == '-');
	}

	void test_fredkin2(){
		Cell x = new FredkinCell('0');
		CPPUNIT_ASSERT (x.cell_char() == '0');
	}

	void test_fredkin3(){
		Cell x = new FredkinCell('0');
		x.die();
		CPPUNIT_ASSERT (x.cell_char() == '-');
	}

	void test_cell_char2(){
		Cell x = new FredkinCell();
		x.live();
		CPPUNIT_ASSERT (x.cell_char() == '0');
	}

	void test_cell_char3(){
		Cell x = new FredkinCell();
		x.live();
		x.die();
		x.live();
		CPPUNIT_ASSERT (x.cell_char() == '0');
	}


	void test_cell_char4(){
	istringstream input("2\n"
				"2\n"
				"--\n"
				"--\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid[0][0] = new ConwayCell();
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '.');
	}

	void test_cell_char5(){
	istringstream input("2\n"
				"2\n"
				"*.\n"
				"**\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve();
		CPPUNIT_ASSERT(test_grid[0][1].cell_char() == '*');
	}

	void test_live_die(){
		Cell x = new FredkinCell();
		x.die();
		CPPUNIT_ASSERT (x.cell_char() == '-');
	}

	void test_live_die2(){
		Cell x = new FredkinCell();
		x.live();
		x.die();
		x.die();
		x.die();
		x.live();
		CPPUNIT_ASSERT (x.cell_char() == '0');
	}

	void test_live_die3(){
		Cell x = new ConwayCell();
		x.live();
		x.live();
		CPPUNIT_ASSERT (x.cell_char() == '*');
	}

	void test_live_die4(){
		Cell x = new ConwayCell('*');
		x.live();
		x.live();
		x.live();
		x.live();
		CPPUNIT_ASSERT (x.cell_char() == '*');
	}

	void test_live_die5(){
		Cell x = new ConwayCell('*');
		x.die();
		CPPUNIT_ASSERT (x.cell_char() == '.');
	}

	void test_count_neighbors2(){
		Cell x = new FredkinCell();
		short neighbors[] = {1,1,1,1,1,1,1,1};
		CPPUNIT_ASSERT (x.count_neighbors(neighbors) == 4);
	}

	void test_count_neighbors3(){
		Cell x = new FredkinCell();
		short neighbors[] = {0,1,0,1,0,1,0,1};
		CPPUNIT_ASSERT (x.count_neighbors(neighbors) == 0);
	}

	void test_grid() {
		Life<Cell> test_grid (3, 3, new ConwayCell());

		Cell x = new FredkinCell();
		test_grid[0][0] = x;
		CPPUNIT_ASSERT(x.cell_char() == '-');
	}



	void test_grid2() {
		Life<Cell> test_grid (3, 3, new ConwayCell());

		Cell x = new ConwayCell();
		test_grid[0][0] = x;
		test_grid[0][0] = new FredkinCell();
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-');
	}

	void test_grid3() {
		bool caught = false;
		try {
			Life<Cell> test_grid (-3, 3, new ConwayCell());
		}
		catch(...) {
			caught = true;
		}
		CPPUNIT_ASSERT(caught);
	}

	void test_grid4() {
		istringstream input("2\n"
				"2\n"
				"**\n"
				"*.\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		CPPUNIT_ASSERT(test_grid[1][0].cell_char() == '*' && test_grid[0][0].cell_char() == '*' && test_grid[0][1].cell_char() == '*' && test_grid[1][1].cell_char() == '.');
	}

	void test_grid5() {
		istringstream input("2\n"
				"2\n"
				"--\n"
				"-0\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		CPPUNIT_ASSERT(test_grid[1][0].cell_char() == '-' && test_grid[0][0].cell_char() == '-' && test_grid[0][1].cell_char() == '-' && test_grid[1][1].cell_char() == '0');
	}

	void test_brackets() {
		bool caught = false;
		try {
			Life<Cell> test_grid (0, 0, new ConwayCell());
			test_grid[0][1];
		}
		catch(...) {
			caught = true;
		}
		CPPUNIT_ASSERT(caught);
	}

	void test_brackets2() {
		bool caught = false;
		try {
			Life<Cell> test_grid (3, 3, new ConwayCell());
			test_grid[-1][0];
		}
		catch(...) {
			caught = true;
		}
		CPPUNIT_ASSERT(caught);
	}

	void test_brackets3() {
		bool caught = false;
		try {
			Life<Cell> test_grid (3, 3, new ConwayCell());
			test_grid[1][1];
			test_grid[0][0];
			test_grid[2][2];
		}
		catch(...) {
			caught = true;
		}
		CPPUNIT_ASSERT(!caught);
	}

	void test_reader() {
		istringstream input("3\n"
				"3\n"
				"...\n"
				".*.\n"
				"...\n");
		int row, col;
		input >> row;
		input >> col;
		CPPUNIT_ASSERT(row == 3 && col == 3);
	}

	void test_reader2() {
		istringstream input("3\n"
				"3\n"
				"...\n"
				".*.\n"
				"...\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		CPPUNIT_ASSERT(test_grid[1][1].cell_char() == '*' && test_grid[2][2].cell_char() == '.');
	}

	void test_reader3() {
		istringstream input("2\n"
				"2\n"
				"..\n"
				".*\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid[0][0] = new FredkinCell();

		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-');
	}

	void test_reader4() {
		istringstream input("2\n"
				"2\n"
				". .\n"
				".*\n");
		bool caught = false;
		try {
			Life<T> test_grid = test_grid.read_and_create(input);
		}
		catch(...){
			caught = true;
		}
		CPPUNIT_ASSERT(caught);
	}

	void test_reader5() {
		istringstream input("2\n"
				"2\n"
				"@@\n"
				"@@\n");
		bool caught = false;
		try {
			Life<T> test_grid = test_grid.read_and_create(input);
		}
		catch(...){
			caught = true;
		}
		CPPUNIT_ASSERT(caught);
	}


	void test_copy() {
		istringstream input("2\n"
				"2\n"
				"..\n"
				".*\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		Life<T> test_grid_copy = test_grid;
		test_grid[0][0] = new FredkinCell();

		CPPUNIT_ASSERT(test_grid_copy[0][0].cell_char() == '.');
	}

	void test_copy2() {
		istringstream input("2\n"
				"2\n"
				"*.\n"
				".*\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		Life<T> test_grid_copy = test_grid;
		test_grid[0][0] = new FredkinCell();

		CPPUNIT_ASSERT(test_grid_copy[1][1].cell_char() == '*');
	}

	void test_copy3() {
		istringstream input("2\n"
				"2\n"
				"*.\n"
				".*\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		Life<T> test_grid_copy = test_grid;
		test_grid[0][0] = new FredkinCell();
		test_grid[0][0].die();

		CPPUNIT_ASSERT(test_grid_copy[0][0].cell_char() == '*');
	}

	void test_copy4() {
		istringstream input("2\n"
				"2\n"
				"*.\n"
				".*\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		Life<T> test_grid_copy = test_grid;
		test_grid[0][0] = new FredkinCell();
		test_grid[0][0].die();

		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-');
	}


	void test_cell_is_alive() {
		Cell x  = new ConwayCell();
		CPPUNIT_ASSERT(x.cell_is_alive() == 0);
	}

	void test_cell_is_alive2() {
		Cell x  = new ConwayCell();
		x.live();
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
	}

	void test_cell_is_alive3() {
		Cell x  = new ConwayCell();
		x.live();
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
		x.die();
		CPPUNIT_ASSERT(x.cell_is_alive() == 0);
	}

	void test_cell_is_alive4() {
		Cell x  = new FredkinCell();
		CPPUNIT_ASSERT(x.cell_is_alive() == 0);
		x.live();
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);

	}

	void test_cell_is_alive5() {
		Cell x  = new FredkinCell('0');
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
		x.die();
		x.die();
		x.die();
		x.die();
		x.live();
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);

	}

	void test_cell_is_alive6() {
		Cell x  = new FredkinCell('-');
		CPPUNIT_ASSERT(x.cell_is_alive() == 0);
		x.live();
		x.live();
		x.live();
		x.live();
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);

	}

	void test_update() {
		Cell x  = new ConwayCell();
		short neighbors[] = {0, 1, 1, 1, 0, 0, 0, 0};
		int neighborcount = x.count_neighbors(neighbors);
		x.update(neighborcount);
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
	}

	void test_update2() {
		Cell x  = new ConwayCell();
		x.live();
		short neighbors[] = {1, 0, 1, 0, 0, 0, 0, 1};
		int neighborcount = x.count_neighbors(neighbors);
		x.update(neighborcount);
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
	}

	void test_update3() {
		Cell x  = new ConwayCell();
		x.live();
		short neighbors[] = {0, 1, 1, 0, 0, 0, 0, 0};
		int neighborcount = x.count_neighbors(neighbors);
		x.update(neighborcount);
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
	}

	void test_update4() {
		Cell x  = new ConwayCell();
		x.live();
		short neighbors[] = {0, 1, 1, 0, 1, 0, 0, 1};
		int neighborcount = x.count_neighbors(neighbors);
		x.update(neighborcount);
		CPPUNIT_ASSERT(x.cell_is_alive() == 0);
	}

	void test_update5() {
		Cell x  = new ConwayCell();
		x.live();
		short neighbors[] = {0, 1, 1, 1, 1, 0, 0, 1};
		int neighborcount = x.count_neighbors(neighbors);
		x.update(neighborcount);
		CPPUNIT_ASSERT(x.cell_is_alive() == 0);
	}

	void test_update6() {
		Cell x  = new ConwayCell();
		x.live();
		short neighbors[] = {1, 0, 0, 0, 0, 0, 0, 1};
		int neighborcount = x.count_neighbors(neighbors);
		x.update(neighborcount);
		CPPUNIT_ASSERT(x.cell_is_alive() == 1);
	}

	void test_evolve() {
		istringstream input("2\n"
				"2\n"
				"**\n"
				"*.\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve();
		CPPUNIT_ASSERT(test_grid[1][0].cell_char() == '*' && test_grid[0][0].cell_char() == '*' && test_grid[0][1].cell_char() == '*' && test_grid[1][1].cell_char() == '*');
	}


	void test_evolve2() {
		istringstream input("2\n"
				"2\n"
				"--\n"
				"-0\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve(1);
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-' && test_grid[0][1].cell_char() == '0' && test_grid[1][0].cell_char() == '0' && test_grid[1][1].cell_char() == '-');
	}

	void test_evolve3() {
		istringstream input("2\n"
				"2\n"
				"--\n"
				"-0\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve(2);
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-' && test_grid[0][1].cell_char() == '-' && test_grid[1][0].cell_char() == '-' && test_grid[1][1].cell_char() == '-');
	}

	void test_evolve4() {
		istringstream input("3\n"
				"3\n"
				".*.\n"
				".*.\n"
				".*.\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve();
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '.' && test_grid[0][1].cell_char() == '.'
				&& test_grid[0][2].cell_char() == '.' && test_grid[1][0].cell_char() == '*' &&
				test_grid[1][1].cell_char() == '*' && test_grid[1][2].cell_char() == '*' &&
				test_grid[2][0].cell_char() == '.' && test_grid[2][1].cell_char() == '.' && test_grid[2][2].cell_char() == '.');

	}

	void test_evolve5() {
		istringstream input("2\n"
				"2\n"
				"0-\n"
				"-0\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve(1);
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-' && test_grid[0][1].cell_char() == '-' && test_grid[1][0].cell_char() == '-' && test_grid[1][1].cell_char() == '-');
	}

	void test_evolve6() {
		istringstream input("2\n"
				"2\n"
				"--\n"
				"--\n");
		Life<T> test_grid = test_grid.read_and_create(input);
		test_grid.evolve(1);
		CPPUNIT_ASSERT(test_grid[0][0].cell_char() == '-' && test_grid[0][1].cell_char() == '-' && test_grid[1][0].cell_char() == '-' && test_grid[1][1].cell_char() == '-');
	}


	CPPUNIT_TEST_SUITE(TestLife);

	CPPUNIT_TEST( test_conway );
	CPPUNIT_TEST( test_fredkin );


	CPPUNIT_TEST( test_conway2 );
	CPPUNIT_TEST( test_conway3 );
	CPPUNIT_TEST( test_fredkin2 );
	CPPUNIT_TEST( test_fredkin3 );

	CPPUNIT_TEST( test_cell_char );
	CPPUNIT_TEST( test_cell_char2 );
	CPPUNIT_TEST( test_cell_char3 );
	CPPUNIT_TEST( test_cell_char4 );
	CPPUNIT_TEST( test_cell_char5 );

	CPPUNIT_TEST( test_live_die );
	CPPUNIT_TEST( test_live_die2 );
	CPPUNIT_TEST( test_live_die3 );
	CPPUNIT_TEST( test_live_die4 );
	CPPUNIT_TEST( test_live_die5 );

	CPPUNIT_TEST( test_count_neighbors );
	CPPUNIT_TEST( test_count_neighbors2 );
	CPPUNIT_TEST( test_count_neighbors3 );

	CPPUNIT_TEST( test_grid0 );
	CPPUNIT_TEST( test_grid );
	CPPUNIT_TEST( test_grid2 );
	CPPUNIT_TEST( test_grid3 );
	CPPUNIT_TEST( test_grid4 );
	CPPUNIT_TEST( test_grid5 );

	CPPUNIT_TEST( test_copy );
	CPPUNIT_TEST( test_copy2 );
	CPPUNIT_TEST( test_copy3 );
	CPPUNIT_TEST( test_copy4 );

	CPPUNIT_TEST( test_brackets );
	CPPUNIT_TEST( test_brackets2 );
	CPPUNIT_TEST( test_brackets3 );

	CPPUNIT_TEST( test_reader );
	CPPUNIT_TEST( test_reader2 );
	CPPUNIT_TEST( test_reader3 );
	CPPUNIT_TEST( test_reader4 );
	CPPUNIT_TEST( test_reader5 );

	CPPUNIT_TEST( test_cell_is_alive );
	CPPUNIT_TEST( test_cell_is_alive2 );
	CPPUNIT_TEST( test_cell_is_alive3 );
	CPPUNIT_TEST( test_cell_is_alive4 );
	CPPUNIT_TEST( test_cell_is_alive5 );
	CPPUNIT_TEST( test_cell_is_alive6 );

	CPPUNIT_TEST( test_update );
	CPPUNIT_TEST( test_update2 );
	CPPUNIT_TEST( test_update3 );
	CPPUNIT_TEST( test_update4 );
	CPPUNIT_TEST( test_update5 );
	CPPUNIT_TEST( test_update6 );

	CPPUNIT_TEST( test_evolve );
	CPPUNIT_TEST( test_evolve2 );
	CPPUNIT_TEST( test_evolve3 );
	CPPUNIT_TEST( test_evolve4 );
	CPPUNIT_TEST( test_evolve5 );
	CPPUNIT_TEST( test_evolve6 );

	CPPUNIT_TEST_SUITE_END();
};

int main() {
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	CppUnit::TextTestRunner tr;
	tr.addTest(TestLife<Cell>::suite());
	tr.run();	cout << "Done!";
	return 1;
}

