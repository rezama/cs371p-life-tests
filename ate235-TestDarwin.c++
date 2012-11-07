/*
To test the program:
% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.c++.app
% valgrind TestDarwin.c++.app >& TestDarwin.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>
#include <stdlib.h>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#include "darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {

    // -----
    // tests
    // -----

	void g_cons_1() {
      Grid g(1,1);
	  CPPUNIT_ASSERT(true);
    }
	void g_cons_2() {
      Grid g(10,15);
	  CPPUNIT_ASSERT(true);
    }
	void g_cons_3() {
      Grid g(127,123);
	  CPPUNIT_ASSERT(true);
    }

	void s_cons_1() {
		Species s('a');
		CPPUNIT_ASSERT(s._n == 'a');
	}
	void s_cons_2() {
		Species s('a');
		CPPUNIT_ASSERT(s._n == 'a');
		s.add_inst("captainamerica");
		CPPUNIT_ASSERT(s._sInst[0] == "captainamerica");
		CPPUNIT_ASSERT(s._iInst[0] == 0);

	}
	void s_cons_3() {
		Species s('a');
		CPPUNIT_ASSERT(s._n == 'a');
		s.add_inst("captainamerica", 3);
		CPPUNIT_ASSERT(s._sInst[0] == "captainamerica");
		CPPUNIT_ASSERT(s._iInst[0] == 3);
	}

	void c_cons_1() {
		Species s('a');
		Creature c(&s, 'w');
		CPPUNIT_ASSERT(c._s->_n == 'a');
		CPPUNIT_ASSERT(c.count == 0);
		CPPUNIT_ASSERT(c.dir == 'w');
	}

	void c_cons_2() {
		Species s('x');
		Creature c(&s, 'n');
		CPPUNIT_ASSERT(c._s->_n == 'x');
		CPPUNIT_ASSERT(c.count == 0);
		CPPUNIT_ASSERT(c.dir == 'n');
	}

	void c_cons_3() {
		Species s('w');
		Creature c(&s, 'e');
		CPPUNIT_ASSERT(c._s->_n == 'w');
		CPPUNIT_ASSERT(c.count == 0);
		CPPUNIT_ASSERT(c.dir == 'e');
	}



	void s_add_inst_1() {
		Species s('a');
		CPPUNIT_ASSERT(s._n == 'a');
		s.add_inst("go", 3);
		CPPUNIT_ASSERT(s._sInst[0] == "go");
		CPPUNIT_ASSERT(s._iInst[0] == 3);
	}

	void s_add_inst_2() {
		Species s('a');
		CPPUNIT_ASSERT(s._n == 'a');
		s.add_inst("go", 3);
		s.add_inst("infect", 0);
		s.add_inst("infect");
		s.add_inst("woots");
		CPPUNIT_ASSERT(s._sInst[0] == "go");
		CPPUNIT_ASSERT(s._iInst[0] == 3);
		CPPUNIT_ASSERT(s._sInst[1] == "infect");
		CPPUNIT_ASSERT(s._iInst[1] == 0);
		CPPUNIT_ASSERT(s._sInst[2] == "infect");
		CPPUNIT_ASSERT(s._iInst[2] == 0);
		CPPUNIT_ASSERT(s._sInst[3] == "woots");
		CPPUNIT_ASSERT(s._iInst[3] == 0);
	}

	void s_add_inst_3() {
		Species s('q');
		CPPUNIT_ASSERT(s._n == 'q');
		s.add_inst("asdf", 1);
		CPPUNIT_ASSERT(s._sInst[0] == "asdf");
		CPPUNIT_ASSERT(s._iInst[0] == 1);
	}


	void g_place_1() {
		Grid g(1,1);
		Species s('q');
		g.place(&s, 'w', 0, 0);
		CPPUNIT_ASSERT(true);
    }
	void g_place_2() {
		Grid g(10,15);
		Species s('q');
		g.place(&s, 'w', 0, 0);
		Species x('x');
		g.place(&x, 'n', 2, 3);
		g.place(&x, 'n', 6, 1);
		g.place(&s, 'n', 9, 14);
		CPPUNIT_ASSERT(true);
    }
	void g_place_3() {
		Grid g(127,123);
		Species s('b');
		g.place(&s, 'd', 123, 111);
		CPPUNIT_ASSERT(true);
    }

	void g_simulate_1() {
		Grid g(1,1);
		Species s('q');
		s.add_inst("hop");
		s.add_inst("go");
		g.place(&s, 'w', 0, 0);
		g.simulate(300, 301);
		CPPUNIT_ASSERT(true);
    }
	void g_simulate_2() {
		Grid g(10,15);
		Species s('q');
		s.add_inst("hop");
		s.add_inst("infect");
		s.add_inst("go", 1);
		g.place(&s, 'w', 0, 0);
		Species x('x');
		x.add_inst("left");
		x.add_inst("right");
		x.add_inst("left");
		x.add_inst("go");
		g.place(&x, 'n', 2, 3);
		g.place(&x, 'n', 6, 1);
		g.place(&s, 'n', 9, 14);
		g.simulate(2,4);
		
		CPPUNIT_ASSERT(true);
    }
	void g_simulate_3() {
		Grid g(9,10);
		Species s('q');
		s.add_inst("left");
		s.add_inst("go");
		g.place(&s, 'w', 0, 0);
		g.simulate(3,5);
		CPPUNIT_ASSERT(true);
    }



	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(g_cons_1);
	CPPUNIT_TEST(g_cons_2);
	CPPUNIT_TEST(g_cons_3);
	CPPUNIT_TEST(s_cons_1);
	CPPUNIT_TEST(s_cons_2);
	CPPUNIT_TEST(s_cons_3);
	CPPUNIT_TEST(c_cons_1);
	CPPUNIT_TEST(c_cons_2);
	CPPUNIT_TEST(c_cons_3);
	CPPUNIT_TEST(s_add_inst_1);
	CPPUNIT_TEST(s_add_inst_2);
	CPPUNIT_TEST(s_add_inst_3);
	CPPUNIT_TEST(g_place_1);
	CPPUNIT_TEST(g_place_2);
	CPPUNIT_TEST(g_place_3);
	CPPUNIT_TEST(g_simulate_1);
	CPPUNIT_TEST(g_simulate_2);
	CPPUNIT_TEST(g_simulate_3);


	CPPUNIT_TEST_SUITE_END();
};






// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
