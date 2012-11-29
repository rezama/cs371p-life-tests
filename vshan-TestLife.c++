// ------------------------------
// projects/Life/TestLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind ./TestLife.app >& TestLife.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public

#include "Life.h"
#include "FredkinCell.h"
#include "ConwayCell.h"
#include "AbstractCell.h"
#include "Cell.h"


// ----------
// TestLife
// ----------

struct TestLife : CppUnit::TestFixture {
    
    
    void test_add_1 () {
    	Life<ConwayCell> l(2,2, ConwayCell());
    	ConwayCell x('*');
    	l.add(x, 0, 0);
    	CPPUNIT_ASSERT(l[0][0].getState() == '*');
    }

    void test_add_2 () {
    	Life<FredkinCell> l(2,2, FredkinCell());
    	FredkinCell f(9,'9');
    	l.add(f, 0, 0);
    	CPPUNIT_ASSERT(l[0][0].getState() == '9');
		CPPUNIT_ASSERT(l[0][0].getAge() == 9);
    }

    void test_add_3 () {
    	Life<FredkinCell> l(2,2, FredkinCell());
    	FredkinCell f(9,'9');
    	l.add(f, 0, 0);
    	CPPUNIT_ASSERT(l[0][0].getState() == '9');
		CPPUNIT_ASSERT(l[0][0].getAge() == 9);
		
		Life<ConwayCell> l2(2,2, ConwayCell());
		ConwayCell x('*');
    	l2.add(x, 1, 1);
    	CPPUNIT_ASSERT(l2[1][1].getState() == '*');
    }
	
	void test_neighbor_count_1 (){
		int rows = 2;
		int cols = 2;
		Life<ConwayCell> l(rows,cols, ConwayCell());
		
		vector<vector<int> > n;
		for(int i = 0; i < rows; i++) {
			vector<int> row(cols, 0);
			n.push_back(row);
		}
		
    	for(int r = 0; r<rows; r++)
		{
			for(int c =0; c<cols; c++)
			{
				CPPUNIT_ASSERT(l._n[r][c] == n[r][c]);
			}
		}
	}
	
	void test_neighbor_count_2 (){
		int rows = 4;
		int cols = 4;
		Life<ConwayCell> l(rows,cols, ConwayCell());
		//*...
		//.*..
		//..*.
		//...*
		l.add(ConwayCell('*'), 0, 0);
		l.add(ConwayCell('*'), 1, 1);
		l.add(ConwayCell('*'), 2, 2);
		l.add(ConwayCell('*'), 3, 3);
		
		vector<vector<int> > n;
		for(int i = 0; i < rows; i++) {
			vector<int> row(cols, 2);
			n.push_back(row);
		}

		//1210
		//2221
		//1222
		//0121
		n[0][0] = 1;
		n[0][2] = 1;
		n[0][3] = 0;
		n[1][3] = 1;
		n[2][0] = 1;
		n[3][0] = 0;
		n[3][1] = 1;
		n[3][3] = 1;

		l.getNeighborCounts();
    	for(int r = 0; r<rows; r++)
		{
			for(int c = 0; c<cols; c++)
			{
				CPPUNIT_ASSERT(l._n[r][c] == n[r][c]);
			}
		}
	}
	
	void test_neighbor_count_3 (){
		int rows = 4;
		int cols = 4;
		Life<FredkinCell> l(rows,cols, FredkinCell());
		//----
		//-0--
		//--9-
		//----
		l.add(FredkinCell(0,'0'), 1, 1);
		l.add(FredkinCell(9,'9'), 2, 2);
		
		vector<vector<int> > n;
		for(int i = 0; i < rows; i++) {
			vector<int> row(cols, 0);
			n.push_back(row);
		}
		//0100
		//1020
		//0201
		//0010
		n[0][1] = 1;
		n[1][0] = 1;
		n[1][2] = 2;
		n[2][1] = 2;
		n[2][3] = 1;
		n[3][2] = 1;
		l.getNeighborCounts();
		
    	for(int r = 0; r<rows; r++)
		{
			for(int c =0; c<cols; c++)
			{
				CPPUNIT_ASSERT(l._n[r][c] == n[r][c]);
			}
		}
	}
	
	void test_execute_1 (){
		int rows = 3;
		int cols = 3;
		Life<ConwayCell> l(rows,cols, ConwayCell());
		//...
		//...
		//...
		
		l.execute();
		for(int r = 0; r< rows; r++)
		{
			for(int c = 0; c<cols; c++)
			{
				CPPUNIT_ASSERT(l[r][c].getState() == '.');
			}
		}
	}
	
	void test_execute_2 (){
		int rows = 3;
		int cols = 3;
		Life<ConwayCell> l(rows,cols, ConwayCell());
		//...
		//.**
		//.*.
		l.add(ConwayCell('*'), 1, 1);
		l.add(ConwayCell('*'), 1, 2);
		l.add(ConwayCell('*'), 2, 1);
		
		l.execute();
		//...
		//.**
		//.**
		CPPUNIT_ASSERT(l[1][1].getState() == '*');
		CPPUNIT_ASSERT(l[1][2].getState() == '*');
		CPPUNIT_ASSERT(l[2][1].getState() == '*');
		CPPUNIT_ASSERT(l[2][2].getState() == '*');
	}
	
	void test_execute_3 (){
		int rows = 4;
		int cols = 4;
		Life<FredkinCell> l(rows,cols, FredkinCell());
		//----
		//-00-
		//-00-
		//----
		l.add(FredkinCell(0,'0'), 1, 1);
		l.add(FredkinCell(0,'0'), 1, 2);
		l.add(FredkinCell(0,'0'), 2, 1);
		l.add(FredkinCell(0,'0'), 2, 2);

		l.execute();

		//-00-
		//0--0
		//0--0
		//-00-
		CPPUNIT_ASSERT(l[0][0].getState() == '-');
		CPPUNIT_ASSERT(l[0][1].getState() == '0');
		CPPUNIT_ASSERT(l[0][2].getState() == '0');
		CPPUNIT_ASSERT(l[0][3].getState() == '-');
		CPPUNIT_ASSERT(l[1][0].getState() == '0');
		CPPUNIT_ASSERT(l[1][1].getState() == '-');
		CPPUNIT_ASSERT(l[1][2].getState() == '-');
		CPPUNIT_ASSERT(l[1][3].getState() == '0');
		CPPUNIT_ASSERT(l[2][0].getState() == '0');
		CPPUNIT_ASSERT(l[2][1].getState() == '-');
		CPPUNIT_ASSERT(l[2][2].getState() == '-');
		CPPUNIT_ASSERT(l[2][3].getState() == '0');
		CPPUNIT_ASSERT(l[3][0].getState() == '-');
		CPPUNIT_ASSERT(l[3][1].getState() == '0');
		CPPUNIT_ASSERT(l[3][2].getState() == '0');
		CPPUNIT_ASSERT(l[3][3].getState() == '-');
	}
	
	
	void test_states_1 (){
		ConwayCell cc;
		FredkinCell f;
		Cell c_cell(new ConwayCell());
		Cell f_cell(new FredkinCell());
		
		f.setState('-');
		CPPUNIT_ASSERT(f.getState() == '-');
	}
	
	void test_states_2 (){
		ConwayCell cc;
		FredkinCell f;
		Cell c_cell(new ConwayCell());
		Cell f_cell(new FredkinCell());
		
		cc.setState('*');
		CPPUNIT_ASSERT(cc.getState() == '*');
	}
	
	void test_states_3(){
		ConwayCell cc;
		FredkinCell f;
		Cell c_cell(new ConwayCell());
		Cell f_cell(new FredkinCell());
		
		f.setState('+');
		CPPUNIT_ASSERT(f.getState() == '+');
	}
	
	void test_num_neighbors_1(){
		ConwayCell cc;
		FredkinCell f;
		Cell c_cell(new ConwayCell());
		Cell f_cell(new FredkinCell());
		
		cc.setNumNeighbors(0);
		CPPUNIT_ASSERT(cc.getNumNeighbors() == 0);
	}
	
	void test_num_neighbors_2(){
		ConwayCell cc;
		FredkinCell f;
		Cell c_cell(new ConwayCell());
		Cell f_cell(new FredkinCell());
		
		cc.setNumNeighbors(999);
		CPPUNIT_ASSERT(cc.getNumNeighbors() == 999);
	}
	
	void test_num_neighbors_3(){
		ConwayCell cc;
		FredkinCell f;
		Cell c_cell(new ConwayCell());
		Cell f_cell(new FredkinCell());
		
		f.setNumNeighbors(999);
		CPPUNIT_ASSERT(f.getNumNeighbors() == 999);
	}

	void test_constructors_1() {
		ConwayCell c;
		CPPUNIT_ASSERT(c.getState() == '.');
		ConwayCell c1('*');
		CPPUNIT_ASSERT(c1.getState() == '*');
	}

	void test_constructors_2() {
		FredkinCell c;
		CPPUNIT_ASSERT(c.getState() == '-');
		CPPUNIT_ASSERT(c.getAge() == 0);
		FredkinCell c1(5,'5');
		CPPUNIT_ASSERT(c1.getState() == '5');
		CPPUNIT_ASSERT(c1.getAge() == 5);
	}

	void test_constructors_3() {
		Cell c;
		CPPUNIT_ASSERT(c.getState() == '-');
		Cell c1(new FredkinCell(5,'5'));
		CPPUNIT_ASSERT(c1.getState() == '5');

		Cell c2(new ConwayCell());
		CPPUNIT_ASSERT(c2.getState() == '.');
		Cell c3(new ConwayCell('*'));
		CPPUNIT_ASSERT(c3.getState() == '*');
	}

	void test_alive_1() {
		ConwayCell c;
		CPPUNIT_ASSERT(!c.isAlive());
		ConwayCell c1('*');
		CPPUNIT_ASSERT(c1.isAlive());
	}

	void test_alive_2() {
		FredkinCell c;
		CPPUNIT_ASSERT(!c.isAlive());
		FredkinCell c1(1,'1');
		CPPUNIT_ASSERT(c1.isAlive());
	}

	void test_alive_3() {
		Cell c;
		CPPUNIT_ASSERT(!c.isAlive());
		Cell c1(new FredkinCell(5,'5'));
		CPPUNIT_ASSERT(c1.isAlive());

		Cell c2(new ConwayCell());
		CPPUNIT_ASSERT(!c2.isAlive());
		Cell c3(new ConwayCell('*'));
		CPPUNIT_ASSERT(c3.isAlive());
	}

	void test_clone_1() {
		ConwayCell c;
		AbstractCell* cc = c.clone();
		CPPUNIT_ASSERT(cc->getState() == '.');

		ConwayCell c1('*');
		AbstractCell* cc1 = c1.clone();
		CPPUNIT_ASSERT(cc1->getState() == '*');
	}

	void test_clone_2() {
		FredkinCell c;
		AbstractCell* cc = c.clone();
		CPPUNIT_ASSERT(cc->getState() == '-');

		FredkinCell c1(1,'1');
		AbstractCell* cc1 = c1.clone();
		CPPUNIT_ASSERT(cc1->getState() == '1');
	}

	void test_clone_3() {
		Cell c(new ConwayCell('*'));
		Cell c1(c);
		c.get()->setState('.');
		CPPUNIT_ASSERT(c1.get()->getState() == '*');
		CPPUNIT_ASSERT(c.get()->getState() == '.');

		Cell c2(new FredkinCell(1,'1'));
		Cell c3(c2);
		c2.get()->setState('2');
		CPPUNIT_ASSERT(c3.getState() == '1');
		CPPUNIT_ASSERT(c2.getState() == '2');
	}

	void test_will_die_1() {
		ConwayCell c('*');
		CPPUNIT_ASSERT(c.willDie(1));
		CPPUNIT_ASSERT(c.willDie(4));
		CPPUNIT_ASSERT(!c.willDie(2));
		CPPUNIT_ASSERT(!c.willDie(3));
	}

	void test_will_die_2() {
		FredkinCell c(1,'1');
		CPPUNIT_ASSERT(c.willDie(0));
		CPPUNIT_ASSERT(c.willDie(2));
		CPPUNIT_ASSERT(c.willDie(4));
	}

	void test_will_die_3() {
		Cell c(new ConwayCell('*'));
		CPPUNIT_ASSERT(c.willDie(1));
		CPPUNIT_ASSERT(c.willDie(4));

		Cell cc(new FredkinCell(1,'1'));
		CPPUNIT_ASSERT(cc.willDie(0));
		CPPUNIT_ASSERT(cc.willDie(2));
		CPPUNIT_ASSERT(cc.willDie(4));

	}

	void test_will_live_1() {
		ConwayCell c('.');
		CPPUNIT_ASSERT(c.willLive(3));
	}

	void test_will_live_2() {
		FredkinCell c(0,'-');
		CPPUNIT_ASSERT(c.willLive(1));
		CPPUNIT_ASSERT(c.willLive(3));
	}

	void test_will_live_3() {
		Cell c(new ConwayCell('.'));
		CPPUNIT_ASSERT(c.willLive(3));

		Cell cc(new FredkinCell(0,'-'));
		CPPUNIT_ASSERT(cc.willLive(1));
		CPPUNIT_ASSERT(cc.willLive(3));
	}

	void test_die_1() {
		ConwayCell c('*');
		c.die();
		CPPUNIT_ASSERT(c.getState() == '.');
	}

	void test_die_2() {
		FredkinCell c(1,'1');
		c.die();
		CPPUNIT_ASSERT(c.getState() == '-');
		CPPUNIT_ASSERT(c.getAge() == 1);
	}

	void test_die_3() {
		Cell c(new ConwayCell('*'));
		c.die();
		CPPUNIT_ASSERT(c.getState() == '.');

		Cell cc(new FredkinCell(1,'1'));
		cc.die();
		CPPUNIT_ASSERT(cc.getState() == '-');
	}

	void test_live_1() {
		ConwayCell c('.');
				c.live();
				CPPUNIT_ASSERT(c.getState() == '*');
	}

	void test_live_2() {
		FredkinCell c(0,'-');
		c.live();
		CPPUNIT_ASSERT(c.getState() == '0');
		CPPUNIT_ASSERT(c.getAge() == 0);
	}

	void test_live_3() {
		Cell c(new ConwayCell('*'));
		c.die();
		CPPUNIT_ASSERT(c.getState() == '.');

		Cell cc(new FredkinCell(1,'1'));
		cc.die();
		CPPUNIT_ASSERT(cc.getState() == '-');
	}

	void test_update_1() {
		ConwayCell c('*');
		c.update();
		c.update();
		c.update();
		c.update();
		CPPUNIT_ASSERT(c.getState() == '*');
	}

	void test_update_2() {
		FredkinCell c(5,'5');
		c.update();
		CPPUNIT_ASSERT(c.getState() == '6');
		CPPUNIT_ASSERT(c.getAge() == 6);
		c.update();
		CPPUNIT_ASSERT(c.getState() == '7');
		CPPUNIT_ASSERT(c.getAge() == 7);
		c.update();
		CPPUNIT_ASSERT(c.getState() == '8');
		CPPUNIT_ASSERT(c.getAge() == 8);
		c.update();
		CPPUNIT_ASSERT(c.getState() == '9');
		CPPUNIT_ASSERT(c.getAge() == 9);
		c.update();
		CPPUNIT_ASSERT(c.getState() == '+');
		CPPUNIT_ASSERT(c.getAge() == 10);
	}
	void test_update_3() {
		Cell c(new ConwayCell('*'));
		c.update();
		CPPUNIT_ASSERT(c.getState() == '*');

		Cell cc(new FredkinCell(0,'0'));
		cc.update();
		CPPUNIT_ASSERT(cc.getState() == '1');
		cc.update();
		CPPUNIT_ASSERT(cc.getState() == '*');
	}

	void test_age_1() {
		FredkinCell c;
		CPPUNIT_ASSERT(c.getAge() == 0);
	}

	void test_age_2() {
		FredkinCell c;
		c.update();
		CPPUNIT_ASSERT(c.getAge() == 1);
	}
	void test_age_3() {
		FredkinCell c;
		c.update();
		CPPUNIT_ASSERT(c.getAge() == 1);
		c.die();
		c.live();
		CPPUNIT_ASSERT(c.getAge() == 1);
	}

    // -----
    // suite
    // -----
	
    CPPUNIT_TEST_SUITE(TestLife);
	
	CPPUNIT_TEST(test_add_1);
	CPPUNIT_TEST(test_add_2);
	CPPUNIT_TEST(test_add_3);
	CPPUNIT_TEST(test_neighbor_count_1);
	CPPUNIT_TEST(test_neighbor_count_2);
	CPPUNIT_TEST(test_neighbor_count_3);
	CPPUNIT_TEST(test_execute_1);
	CPPUNIT_TEST(test_execute_2);
	CPPUNIT_TEST(test_execute_3);
	CPPUNIT_TEST(test_states_1);
	CPPUNIT_TEST(test_states_2);
	CPPUNIT_TEST(test_states_3);
	CPPUNIT_TEST(test_num_neighbors_1);
	CPPUNIT_TEST(test_num_neighbors_2);
	CPPUNIT_TEST(test_num_neighbors_3);
	
	CPPUNIT_TEST(test_constructors_1);
	CPPUNIT_TEST(test_constructors_2);
	CPPUNIT_TEST(test_constructors_3);
	CPPUNIT_TEST(test_alive_1);
	CPPUNIT_TEST(test_alive_2);
	CPPUNIT_TEST(test_alive_3);
	CPPUNIT_TEST(test_clone_1);
	CPPUNIT_TEST(test_clone_2);
	CPPUNIT_TEST(test_clone_3);
	CPPUNIT_TEST(test_will_die_1);
	CPPUNIT_TEST(test_will_die_2);
	CPPUNIT_TEST(test_will_die_3);
	CPPUNIT_TEST(test_will_live_1);
	CPPUNIT_TEST(test_will_live_2);
	CPPUNIT_TEST(test_will_live_3);
	CPPUNIT_TEST(test_die_1);
	CPPUNIT_TEST(test_die_2);
	CPPUNIT_TEST(test_die_3);
	CPPUNIT_TEST(test_live_1);
	CPPUNIT_TEST(test_live_2);
	CPPUNIT_TEST(test_live_3);
	CPPUNIT_TEST(test_update_1);
	CPPUNIT_TEST(test_update_2);
	CPPUNIT_TEST(test_update_3);
	CPPUNIT_TEST(test_age_1);
	CPPUNIT_TEST(test_age_2);
	CPPUNIT_TEST(test_age_3);

    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
