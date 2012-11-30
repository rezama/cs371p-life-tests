// -----------------------------
// projects/life/TestLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -ansi -pedantic -Wall TestLife.c++ -lcppunit -ldl -o TestLife.c++.app 
    % valgrind ./TestLife.c++.app &> TestLife.out

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

#define private public
#define protected public
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

// ----
// main
// ----


struct TestLife : CppUnit::TestFixture {
	void test_ConwayCell_1(){
		ConwayCell x;
		CPPUNIT_ASSERT(x.isAlive() == false);
		CPPUNIT_ASSERT(x.getRepresentation() == '.');
		x.addNeighbor(0,0,1,1);
		x.addNeighbor(0,0,0,1);
		x.addNeighbor(0,0,1,0);
		CPPUNIT_ASSERT(x.neighborCount == 3);
		x.evolve();
		CPPUNIT_ASSERT(x.neighborCount == 0);
		CPPUNIT_ASSERT(x.isAlive() == true);
		CPPUNIT_ASSERT(x.getRepresentation() == '*');
		
	}
	
	void test_ConwayCell_2(){
		ConwayCell x(true);
		CPPUNIT_ASSERT(x.isAlive() == true);
		CPPUNIT_ASSERT(x.getRepresentation() == '*');
		x.addNeighbor(0,0,1,1);
		CPPUNIT_ASSERT(x.neighborCount = 1);
		x.evolve();
		CPPUNIT_ASSERT(x.isAlive() == false);
		CPPUNIT_ASSERT(x.neighborCount == 0);
		CPPUNIT_ASSERT(x.getRepresentation() == '.');	
	}

	void test_ConwayCell_3(){
		ConwayCell x(true);
		CPPUNIT_ASSERT(x.isAlive() == true);
		CPPUNIT_ASSERT(x.getRepresentation() == '*');
		x.addNeighbor(0,0,1,1);
		x.addNeighbor(0,0,0,1);
		x.addNeighbor(0,0,1,0);
		CPPUNIT_ASSERT(x.neighborCount == 3);
		x.evolve();
		CPPUNIT_ASSERT(x.neighborCount == 0);
		CPPUNIT_ASSERT(x.isAlive() == true);
		CPPUNIT_ASSERT(x.getRepresentation() == '*');
	}

	void test_FredkinCell_1(){
		FredkinCell x(false);
		CPPUNIT_ASSERT(x.isAlive() == false);
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
		x.addNeighbor(0,0,0,1);
		CPPUNIT_ASSERT(x.neighborCount == 1);
		x.evolve();
		CPPUNIT_ASSERT(x.getRepresentation() == '0');
		CPPUNIT_ASSERT(x.neighborCount == 0);
		CPPUNIT_ASSERT(x.getAge() == 0);	
		x.addNeighbor(0,0,0,1);
		x.evolve();
		CPPUNIT_ASSERT(x.getRepresentation() == '1');
		CPPUNIT_ASSERT(x.neighborCount == 0);
		CPPUNIT_ASSERT(x.getAge() == 1);
		x.die();
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
	}

	void test_FredkinCell_2(){
		FredkinCell x(true);
		CPPUNIT_ASSERT(x.getRepresentation() == '0');	
		for(int i= 1;i<11;i++){		
			x.addNeighbor(0,0,0,1);
			x.evolve();
			CPPUNIT_ASSERT(x.getAge() == i);	
		}
		CPPUNIT_ASSERT(x.getAge() == 10);
		CPPUNIT_ASSERT(x.getRepresentation() == '+');
		x.die();
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
		x.die();
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
			
	}

	void test_FredkinCell_3(){
		FredkinCell x(true);	
		CPPUNIT_ASSERT(x.getRepresentation() == '0');
		x.evolve();
		CPPUNIT_ASSERT(x.getAge() == 0);
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
		CPPUNIT_ASSERT(x.neighborCount == 0);
		x.live();
		CPPUNIT_ASSERT(x.getRepresentation() == '0');
		x.die();
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
	}

	void test_Cell_1(){
		Cell x = new ConwayCell();
		CPPUNIT_ASSERT(x.isAlive() == false);	
		CPPUNIT_ASSERT(x.getRepresentation() == '.');
		x.addNeighbor(0,0,1,1);
		x.addNeighbor(0,0,0,1);
		x.addNeighbor(0,0,1,0);
		x.evolve();
		CPPUNIT_ASSERT(x.isAlive() == true);
		CPPUNIT_ASSERT(x.getRepresentation() == '*');
	}

	void test_Cell_2(){

		Cell x = new FredkinCell(true);
		CPPUNIT_ASSERT(x.getRepresentation() == '0');	
		x.addNeighbor(0,0,0,1);	
		x.evolve();
		CPPUNIT_ASSERT(x.getRepresentation() == '1');	
		x.addNeighbor(0,0,0,1);	
		x.evolve();
		CPPUNIT_ASSERT(x.getRepresentation() == '*');
		x.addNeighbor(0,0,0,1);	
		x.evolve();
		CPPUNIT_ASSERT(x.getRepresentation() == '.');
	}

	void test_Cell_3(){
		Cell x = new FredkinCell(true);	
		CPPUNIT_ASSERT(x.getRepresentation() == '0');
		x.evolve();
		CPPUNIT_ASSERT(x.getRepresentation() == '-');
	}
	void test_Life_1(){
		Life<ConwayCell> x(10,10);
		CPPUNIT_ASSERT(x.isValid(0,0));
		CPPUNIT_ASSERT(!x.isValid(-1,-1));
		CPPUNIT_ASSERT(!x.isValid(0,-1));
		CPPUNIT_ASSERT(!x.isValid(10,10));
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				CPPUNIT_ASSERT(x._board[i][j].getRepresentation() == '.');
			}
		}
		x.runTurn();	
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				CPPUNIT_ASSERT(x._board[i][j].getRepresentation() == '.');
			}
		}
		CPPUNIT_ASSERT(x._currentGen == 1);
		x.place(1,5, ConwayCell(true));	
		x.place(2,5, ConwayCell(true));
		x.place(3,5, ConwayCell(true));
		CPPUNIT_ASSERT(x._board[1][5].getRepresentation() == '*');
		CPPUNIT_ASSERT(x._board[2][5].getRepresentation() == '*');
		CPPUNIT_ASSERT(x._board[3][5].getRepresentation() == '*');
		x.contactNeighbors(1, 5);
		x.runTurn();
		CPPUNIT_ASSERT(x._board[1][4].getRepresentation() == '*');
		CPPUNIT_ASSERT(x._board[1][6].getRepresentation() == '*');
		CPPUNIT_ASSERT(x._board[2][5].getRepresentation() == '*');	
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				if(!(i==1 && j==4) && !(i==1 && j==6) && !(i==2 && j==5)){
					if(!(x._board[i][j].getRepresentation() == '.'))
						std::cout << i << " " << j << std::endl;
					CPPUNIT_ASSERT(x._board[i][j].getRepresentation() == '.');
				}
			}
		}
		x.place(2,5, ConwayCell(false));
		x.run(1);
		
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				CPPUNIT_ASSERT(x._board[i][j].getRepresentation() == '.');
			}
		}
	}

	void test_Life_2(){
		Life<FredkinCell> x(3,3, FredkinCell(true));
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				CPPUNIT_ASSERT(x._board[i][j].getRepresentation() == '0');
			}
		}
		x.run(1);
		CPPUNIT_ASSERT(x._board[0][0].getRepresentation() == '-');
		CPPUNIT_ASSERT(x._board[0][1].getRepresentation() == '1');
		CPPUNIT_ASSERT(x._board[0][2].getRepresentation() == '-');
		CPPUNIT_ASSERT(x._board[1][0].getRepresentation() == '1');
		CPPUNIT_ASSERT(x._board[1][1].getRepresentation() == '-');
		CPPUNIT_ASSERT(x._board[1][2].getRepresentation() == '1');
		CPPUNIT_ASSERT(x._board[2][0].getRepresentation() == '-');
		CPPUNIT_ASSERT(x._board[2][1].getRepresentation() == '1');
		CPPUNIT_ASSERT(x._board[2][2].getRepresentation() == '-');
		x.run(2);

		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				CPPUNIT_ASSERT(x._board[i][j].getRepresentation() == '-');
			}
		}
	}


	void test_Life_3(){
		Life<Cell> x(3, 3, new FredkinCell(true));
		x.run(1);
		CPPUNIT_ASSERT(x._board[0][1].getRepresentation() == '1');	
		CPPUNIT_ASSERT(x._board[1][0].getRepresentation() == '1');
		CPPUNIT_ASSERT(x._board[1][2].getRepresentation() == '1');
		CPPUNIT_ASSERT(x._board[2][1].getRepresentation() == '1');
		x.place(1,1, new FredkinCell(true));
		x.run(1);
		CPPUNIT_ASSERT(x._board[0][1].getRepresentation() == '*');	
		CPPUNIT_ASSERT(x._board[1][0].getRepresentation() == '*');
		CPPUNIT_ASSERT(x._board[1][2].getRepresentation() == '*');
		CPPUNIT_ASSERT(x._board[2][1].getRepresentation() == '*');
	}

	CPPUNIT_TEST_SUITE(TestLife);
	CPPUNIT_TEST(test_ConwayCell_1);
	CPPUNIT_TEST(test_ConwayCell_2);
	CPPUNIT_TEST(test_ConwayCell_3);
	CPPUNIT_TEST(test_FredkinCell_1);
	CPPUNIT_TEST(test_FredkinCell_2);
	CPPUNIT_TEST(test_FredkinCell_3);
	CPPUNIT_TEST(test_Cell_1);
	CPPUNIT_TEST(test_Cell_2);
	CPPUNIT_TEST(test_Cell_3);
	CPPUNIT_TEST(test_Life_1);
	CPPUNIT_TEST(test_Life_2);
	CPPUNIT_TEST(test_Life_3);
	CPPUNIT_TEST_SUITE_END();
};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
