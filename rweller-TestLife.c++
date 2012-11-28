// ------------------------------
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 *To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app 
 *     valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include "Life.h"
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

using namespace std;

struct TestLife : CppUnit::TestFixture {


	void test_printGrid1(){
		Life<FredkinCell> x ("RunLifeFredkin.in");
		x.printGrid(std::cout);
	}

	void test_printGrid2(){
		Life<FredkinCell> x ("RunLife.in");
		x.printGrid(std::cout);
	}
	
	void test_printGrid3(){
		Life<ConwayCell> x ("RunLifeConway.in");
		x.printGrid(std::cout);
	}
	void test_run1(){
		Life<ConwayCell> x ("RunLifeConway3x3.in");
		x.run(1);
                x.updateAliveNeighbors();
                int result = x.aliveNeighborsOfCellAt(1,1);
		CPPUNIT_ASSERT(result == 0);
	}

	void test_run2(){
		Life<FredkinCell> x ("RunLifeFredkin3x3.in");
		x.run(1);
                int result = x.aliveNeighborsOfCellAt(1,1);
		CPPUNIT_ASSERT(result == 4);
	}
	
	void test_run3(){
		Life<Cell> x ("RunLifeFredkin3x3.in", new FredkinCell());
		x.run(1);
                int result = x.aliveNeighborsOfCellAt(1,1);

		CPPUNIT_ASSERT(result == 4);
	}

	
	void test_fredkin_setStatus1(){
		FredkinCell alpha;
		alpha.setStatus('-');
		char result = alpha.getStatus();
		CPPUNIT_ASSERT(result == '-');
	}
	void test_fredkin_setStatus2(){
		FredkinCell alpha;
		alpha.setStatus('0');
		char result = alpha.getStatus();
		CPPUNIT_ASSERT(result == '0');
	}
	void test_fredkin_setStatus3(){
		FredkinCell alpha;
		bool result = alpha.setStatus('.');
		CPPUNIT_ASSERT(result == false);
	}
        void test_conway_setStatus1(){
		ConwayCell alpha;
		alpha.setStatus('.');
		char result = alpha.getStatus();
		CPPUNIT_ASSERT(result == '.');
	}
        void test_conway_setStatus2(){
		ConwayCell alpha;
		alpha.setStatus('*');
		char result = alpha.getStatus();
		CPPUNIT_ASSERT(result == '*');
	}
        void test_conway_setStatus3(){
		ConwayCell alpha;
		bool result = alpha.setStatus('0');
		CPPUNIT_ASSERT(result == false);
	}
	void test_getType1(){
		FredkinCell beta;
		int result = beta.getType();
		CPPUNIT_ASSERT(result == 1);
	}
	void test_getType2(){
		ConwayCell beta;
		int result = beta.getType();
		CPPUNIT_ASSERT(result == 0);
	}
	void test_getType3(){
		ConwayCell beta;
		int a = beta.getType();
		FredkinCell alpha;
		int b = alpha.getType();
		CPPUNIT_ASSERT(a != b);
	}
	
	void test_incrementNeighbors1(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 1);
	}
	void test_incrementNeighbors2(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 2);
	}
	void test_incrementNeighbors3(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 3);
	}
	void test_zeroNeighbors1(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 1);
		gamma.zeroNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 0);
	}
	void test_zeroNeighbors2(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 2);
		gamma.zeroNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 0);
	}
	void test_zeroNeighbors3(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 3);
		gamma.zeroNeighbors();
		CPPUNIT_ASSERT(gamma.getNeighbors() == 0);
	}
	void test_updateAliveNeighbors1(){
		Life<ConwayCell> life("RunLifeConway3x3.in");
		life.updateAliveNeighbors();
                int result = life.aliveNeighborsOfCellAt(1,1);
		CPPUNIT_ASSERT(result == 0);
	}
	void test_updateAliveNeighbors2(){
		Life<ConwayCell> life("RunLifeConway3x3.in");
		life.updateAliveNeighbors();
                int result = life.aliveNeighborsOfCellAt(0,0);
		CPPUNIT_ASSERT(result == 1);
	}
	void test_updateAliveNeighbors3(){
		Life<FredkinCell> life("RunLifeFredkin3x3.in");
		life.updateAliveNeighbors();
                int result = life.aliveNeighborsOfCellAt(1,1);
		CPPUNIT_ASSERT(result == 0);
	}
	void test_fredkin_execute1(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.setStatus('0');
                gamma.execute();
		CPPUNIT_ASSERT(gamma.getStatus() == '1');
	}
	void test_fredkin_execute2(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		gamma.setStatus('0');
                gamma.execute();
		CPPUNIT_ASSERT(gamma.getStatus() == '-');
	}
	void test_fredkin_execute3(){
		FredkinCell gamma;
		gamma.incrementNeighbors();
		gamma.setStatus('0');
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
                gamma.execute();
		CPPUNIT_ASSERT(gamma.getStatus() == '+');
	}
	void test_conway_execute1(){
		ConwayCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		gamma.setStatus('.');
                gamma.execute();
		CPPUNIT_ASSERT(gamma.getStatus() == '.');
	}
	void test_conway_execute2(){
		ConwayCell gamma;
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		gamma.incrementNeighbors();
		gamma.setStatus('.');
                gamma.execute();
		CPPUNIT_ASSERT(gamma.getStatus() == '*');
	}
	void test_conway_execute3(){
		ConwayCell gamma;
		gamma.incrementNeighbors();
		gamma.setStatus('*');
                gamma.execute();
		CPPUNIT_ASSERT(gamma.getStatus() == '.');
	}
        void test_fredkin_morph1(){
		AbstractCell* p = new FredkinCell();
		AbstractCell* q = p;
                p = p->morph();
		CPPUNIT_ASSERT(p != q);
                delete p;
                delete q;
	}
        void test_fredkin_morph2(){
		AbstractCell* p = new FredkinCell();
		AbstractCell* q = p;
                p = p->morph();
		CPPUNIT_ASSERT(p->getType() == 0);
                delete p;
                delete q;
	}
        void test_fredkin_morph3(){
		AbstractCell* p = new FredkinCell();
		AbstractCell* q = p->morph();;
		CPPUNIT_ASSERT(p->getType() == 1);
		CPPUNIT_ASSERT(q->getType() == 0);
                delete p;
                delete q;
	}
        void test_conway_morph1(){
		AbstractCell* p = new ConwayCell();
		AbstractCell* q = p;
                p = p->morph();
		CPPUNIT_ASSERT(p == q);
                delete p;

	}
        void test_conway_morph2(){
		AbstractCell* p = new ConwayCell();
                p = p->morph();
		CPPUNIT_ASSERT(p->getType() == 0);
                delete p;

	}
        void test_conway_morph3(){
		AbstractCell* p = new ConwayCell();
		AbstractCell* q = p->morph();;
		CPPUNIT_ASSERT(p->getType() == 0);
		CPPUNIT_ASSERT(q->getType() == 0);
                delete p;

	}


	CPPUNIT_TEST_SUITE(TestLife);
	CPPUNIT_TEST(test_printGrid1);
	CPPUNIT_TEST(test_printGrid2);
	CPPUNIT_TEST(test_printGrid3);
	CPPUNIT_TEST(test_run1);
	CPPUNIT_TEST(test_run2);
	CPPUNIT_TEST(test_run3);
	CPPUNIT_TEST(test_updateAliveNeighbors1);
	CPPUNIT_TEST(test_updateAliveNeighbors2);
	CPPUNIT_TEST(test_updateAliveNeighbors3);
	CPPUNIT_TEST(test_fredkin_setStatus1);
	CPPUNIT_TEST(test_fredkin_setStatus2);
	CPPUNIT_TEST(test_fredkin_setStatus3);
	CPPUNIT_TEST(test_conway_setStatus1);
	CPPUNIT_TEST(test_conway_setStatus2);
	CPPUNIT_TEST(test_conway_setStatus3);
	CPPUNIT_TEST(test_getType1);
	CPPUNIT_TEST(test_getType2);
	CPPUNIT_TEST(test_getType3);
	CPPUNIT_TEST(test_incrementNeighbors1);
	CPPUNIT_TEST(test_incrementNeighbors2);
	CPPUNIT_TEST(test_incrementNeighbors3);
	CPPUNIT_TEST(test_zeroNeighbors1);
	CPPUNIT_TEST(test_zeroNeighbors2);
	CPPUNIT_TEST(test_zeroNeighbors3);
	CPPUNIT_TEST(test_fredkin_execute1);
	CPPUNIT_TEST(test_fredkin_execute2);
	CPPUNIT_TEST(test_fredkin_execute3);
	CPPUNIT_TEST(test_conway_execute1);
	CPPUNIT_TEST(test_conway_execute2);
	CPPUNIT_TEST(test_conway_execute3);
	CPPUNIT_TEST(test_fredkin_morph1);
	CPPUNIT_TEST(test_fredkin_morph2);
	CPPUNIT_TEST(test_fredkin_morph3);
	CPPUNIT_TEST(test_conway_morph1);
	CPPUNIT_TEST(test_conway_morph2);
	CPPUNIT_TEST(test_conway_morph3);
	CPPUNIT_TEST_SUITE_END();};

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
	cout << "TestLife.c++" <<endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestLife::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;}
