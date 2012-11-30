// ------------------------------
// projects/matlab/TestLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
* To test the program:
* g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
* valgrind TestLife.app >& TestLife.out
*/

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner
#define private public
#define protected public

#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"


// ----------
// TestLife
// ----------
struct TestLife : CppUnit::TestFixture {

  //CONWAY TESTS
	void test_conway_initial_1() {
		ConwayCell x(true);
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '*');
	}
	
	void test_conway_initial_2() {
		ConwayCell x(false);
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '.');
	}
	
	void test_conway_takeTurn_1() {
		ConwayCell x(true);
		x.takeTurn();
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '.');
	}
				
	void test_conway_takeTurn_2() {
		ConwayCell x(false);
		x.incrementNeighbors(true);
		x.incrementNeighbors(true);
		x.incrementNeighbors(true);
		x.takeTurn();		
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '*');
	}
	
	void test_conway_takeTurn_3() {
		ConwayCell x(true);
		x.incrementNeighbors(true);
		x.incrementNeighbors(true);
		x.incrementNeighbors(true);
		x.incrementNeighbors(true);
		x.takeTurn();		
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '.');
	}
	
	
	//FREDKIN TESTS
	
	void test_fredkin_initial_1() {
		FredkinCell x(true);
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '0');
	}
	
	void test_fredkin_initial_2() {
		FredkinCell x(false);
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '-');
	}
	
	void test_fredkin_takeTurn_1() {
		FredkinCell x(true);
		x.takeTurn();
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '-');
	}
				
	void test_fredkin_takeTurn_2() {
		FredkinCell x(false);
		x.incrementNeighbors(false); //neighbors = 1
		x.takeTurn(); //cell alive
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5					
		x.takeTurn();		
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '1');
	}
	
	void test_fredkin_takeTurn_3() {
		FredkinCell x(true);
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.takeTurn(); //cell dead		
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '-');
	}
	
	void test_fredkin_cellAgeTwo_1() {
		FredkinCell x(true); //alive, neighbors = 0
		x.incrementNeighbors(false); //alive, neighbors = 1
		x.incrementNeighbors(false); //alive, neighbors = 2
		x.takeTurn(); //cell dead, 0 neighbors
		x.incrementNeighbors(false); //dead, neighbors = 1
		x.takeTurn(); //cell alive, neighbors = 0
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5										
		x.takeTurn(); //age = 1
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5			
		x.takeTurn(); //age = 2					
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '2');
	}

	void test_fredkin_cellAgeTwo_2() {
		FredkinCell x(true);
		x.incrementNeighbors(false);
		x.takeTurn(); //age = 1
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5			
		x.takeTurn();	 //age = 2	
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '2');
	}
	
	void test_fredkin_cellAgeTwo_3() {
		FredkinCell x(false);
		x.incrementNeighbors(false); //dead, 1
		x.takeTurn(); //cell is alive, 0
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5			
		x.takeTurn();	 //age = 1
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5			
		x.takeTurn();	
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '2');
	}
	
	//CELL TESTS
	void test_cell_initial_1() {
		Cell x(true);
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '0');
	}
	
	void test_cell_initial_2() {
		Cell x(false);
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '-');		
	}
	
	void test_cell_takeTurn_1() {
		Cell x(true);
		x.takeTurn();
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '-');
	}
				
	void test_cell_takeTurn_2() {
		Cell x(false);
		x.incrementNeighbors(false); //neighbors = 1
		x.takeTurn(); //cell alive
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5					
		x.takeTurn();		
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '1');
	}
	
	void test_cell_takeTurn_3() { //switch to Conway here
		Cell x(true);		
		x.incrementNeighbors(false);
		x.takeTurn(); //age = 1
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5			
		x.takeTurn();	 //age = 2				
		char y = x.printCell();
		CPPUNIT_ASSERT(y == '*');
	}
	
	void test_cell_isCellAlive_1() { 
		Cell x(true);		
		x.takeTurn(); //age = 1
		x.takeTurn(); //age = 2					
		bool y = x.isCellAlive();
		CPPUNIT_ASSERT(y == false);
	}
	
	void test_cell_isCellAlive_2() { 
		Cell x(false);							
		bool y = x.isCellAlive();
		CPPUNIT_ASSERT(y == false);
	}
	
	void test_cell_isCellAlive_3() { 
		Cell x(true);		
		x.incrementNeighbors(false);
		x.takeTurn(); //age = 1
		x.incrementNeighbors(false); //neighbors = 1
		x.incrementNeighbors(false); //neighbors = 2
		x.incrementNeighbors(false); //neighbors = 3
		x.incrementNeighbors(false); //neighbors = 4
		x.incrementNeighbors(false); //neighbors = 5			
		x.takeTurn();	 //age = 2, now a Conway Cell	
		x.incrementNeighbors(false); //neighbors = 1	
		x.takeTurn(); //neighbors = 1						
		bool y = x.isCellAlive();
		CPPUNIT_ASSERT(y == false);
	}				
	
	
	//LIFE TESTS
						
    // -----
    // suite
    // -----

CPPUNIT_TEST_SUITE(TestLife);
	CPPUNIT_TEST(test_conway_initial_1);
	CPPUNIT_TEST(test_conway_initial_2);
	CPPUNIT_TEST(test_conway_takeTurn_1);
	CPPUNIT_TEST(test_conway_takeTurn_2);
	CPPUNIT_TEST(test_conway_takeTurn_3);
	CPPUNIT_TEST(test_fredkin_initial_1);
	CPPUNIT_TEST(test_fredkin_initial_2);
	CPPUNIT_TEST(test_fredkin_takeTurn_1);
	CPPUNIT_TEST(test_fredkin_takeTurn_2);
	CPPUNIT_TEST(test_fredkin_takeTurn_3);
	CPPUNIT_TEST(test_fredkin_cellAgeTwo_1);
	CPPUNIT_TEST(test_fredkin_cellAgeTwo_2);
	CPPUNIT_TEST(test_fredkin_cellAgeTwo_3);
	CPPUNIT_TEST(test_cell_initial_1);
	CPPUNIT_TEST(test_cell_initial_2);
	CPPUNIT_TEST(test_cell_takeTurn_1);
	CPPUNIT_TEST(test_cell_takeTurn_2);
	CPPUNIT_TEST(test_cell_takeTurn_3);
	CPPUNIT_TEST(test_cell_isCellAlive_1);
	CPPUNIT_TEST(test_cell_isCellAlive_2);
	CPPUNIT_TEST(test_cell_isCellAlive_3);		
   	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

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
