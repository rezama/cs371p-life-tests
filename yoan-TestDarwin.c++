// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <stdexcept> // invalid_argument, out_of_range

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public
#define protected public
#define class struct
#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture
{
	
	void test_command_ctor1() {
		Command c(OP_INFECT, 0);
		CPPUNIT_ASSERT(c.opcode == OP_INFECT);
		CPPUNIT_ASSERT(c.param == 0);
	}
	void test_command_ctor2() {
		Command c('E', 23);
		CPPUNIT_ASSERT(c.opcode == OP_IF_ENEMY);
		CPPUNIT_ASSERT(c.param == 23);
	}
	void test_command_ctor3() {
		Command c(OP_GO, 46);
		CPPUNIT_ASSERT(c.opcode == OP_GO);
		CPPUNIT_ASSERT(c.param == 46);
	}
	
	void test_command_debug1() {
		stringstream ss (stringstream::in | stringstream::out);
		Command c(OP_INFECT, 0);
		c.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "I 0");
	}
	void test_command_debug2() {
		stringstream ss (stringstream::in | stringstream::out);
		Command c('E', 56);
		c.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "E 56");
	}
	void test_command_debug3() {
		stringstream ss (stringstream::in | stringstream::out);
		Command c(OP_GO, 46);
		c.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "G 46");
	}
	
	void test_species_ctor1() {
		char actions[] = {
			OP_RIGHT, 0,
			OP_IF_EMPTY, 1,
			OP_GO, 0
		};
		Species x('X', actions, sizeof actions);
		CPPUNIT_ASSERT(x.icon == 'X');
		CPPUNIT_ASSERT(x.behavior.size() == 3);
		CPPUNIT_ASSERT(x.behavior[0].opcode == OP_RIGHT);
		CPPUNIT_ASSERT(x.behavior[0].param == 0);
		CPPUNIT_ASSERT(x.behavior[1].opcode == OP_IF_EMPTY);
		CPPUNIT_ASSERT(x.behavior[1].param == 1);
		CPPUNIT_ASSERT(x.behavior[2].opcode == OP_GO);
		CPPUNIT_ASSERT(x.behavior[2].param == 0);
	}
	void test_species_ctor2() {
		Species x('F', NULL, 0);
		CPPUNIT_ASSERT(x.icon == 'F');
		CPPUNIT_ASSERT(x.behavior.size() == 0);
	}
	void test_species_ctor3() {
		char actions[] = {
			OP_RIGHT,
			OP_GO, 0
		};
		try {
			Species x('X', actions, sizeof actions);
			CPPUNIT_ASSERT(false);
		} catch (const invalid_argument&) {
			CPPUNIT_ASSERT(true);
		}
	}
	void test_species_ctor4() {
		char actions[] = {
			OP_RIGHT, 0,
			OP_GO, 0
		};
		try {
			Species x(0, actions, sizeof actions);
			CPPUNIT_ASSERT(false);
		} catch (const invalid_argument&) {
			CPPUNIT_ASSERT(true);
		}
	}
	
	void test_species_debug1() {
		char actions[] = {
			OP_RIGHT, 0,
			OP_IF_EMPTY, 1,
			OP_GO, 0
		};
		Species x('X', actions, sizeof actions);
		stringstream ss (stringstream::in | stringstream::out);
		x.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "X\n> 0\nB 1\nG 0");
	}
	void test_species_debug2() {
		Species x('X', NULL, 0);
		stringstream ss (stringstream::in | stringstream::out);
		x.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "X");
	}
	void test_species_debug3() {
		Species x('\n', NULL, 0);
		stringstream ss (stringstream::in | stringstream::out);
		x.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "\n");
	}
	
	void test_creature_ctor1() {
		Species x('X', NULL, 0);
		Creature c(&x, DIR_NORTH);
		CPPUNIT_ASSERT(c.species == &x);
		CPPUNIT_ASSERT(c.dir == DIR_NORTH);
		CPPUNIT_ASSERT(c.pc == 0);
	}
	void test_creature_ctor2() {
		Creature c(NULL, DIR_NORTH);
		CPPUNIT_ASSERT(c.species == NULL);
		CPPUNIT_ASSERT(c.dir == DIR_NORTH);
		CPPUNIT_ASSERT(c.pc == 0);
	}
	void test_creature_ctor3() {
		Species x('X', NULL, 0);
		Creature c(&x, DIR_SOUTH);
		CPPUNIT_ASSERT(c.species == &x);
		CPPUNIT_ASSERT(c.dir == DIR_SOUTH);
		CPPUNIT_ASSERT(c.pc == 0);
	}
	
	void test_creature_debug1() {
		Species x('X', NULL, 0);
		Creature c(&x, DIR_NORTH);
		stringstream ss (stringstream::in | stringstream::out);
		c.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "X N 0");
	}
	void test_creature_debug2() {
		Species x('X', NULL, 0);
		Creature c(&x, DIR_NORTH);
		c.pc = 3;
		stringstream ss (stringstream::in | stringstream::out);
		c.debug(ss);
		CPPUNIT_ASSERT(ss.str() == "X N 3");
	}
	void test_creature_debug3() {
		Creature c(NULL, DIR_NORTH);
		c.pc = 3;
		stringstream ss (stringstream::in | stringstream::out);
		c.debug(ss);
		CPPUNIT_ASSERT(ss.str() == ". N 3");
	}
	
	void test_simulation_ctor1() {
		try {
			Simulation s(0,0);
			CPPUNIT_ASSERT(false);
		} catch (const invalid_argument&) {
			CPPUNIT_ASSERT(true);
		}
	}
	void test_simulation_ctor2() {
		try {
			Simulation s(0,1);
			CPPUNIT_ASSERT(false);
		} catch (const invalid_argument&) {
			CPPUNIT_ASSERT(true);
		}
	}
	void test_simulation_ctor3() {
		try {
			Simulation s(1,0);
			CPPUNIT_ASSERT(false);
		} catch (const invalid_argument&) {
			CPPUNIT_ASSERT(true);
		}
	}
	void test_simulation_ctor4() {
		Simulation s(4,5);
		CPPUNIT_ASSERT(s.grid.size() == 4);
		for (int i = 0; i < 4; i++) {
			CPPUNIT_ASSERT(s.grid[i].size() == 5);
			for (int j = 0; j < 5; j++) {
				CPPUNIT_ASSERT(s.grid[i][j] == NULL);
			}
		}
		CPPUNIT_ASSERT(s.creatures.size() == 0);
	}
	
	void test_simulation_run1() {
		char foodActions[] = {
			OP_LEFT, 0,
			OP_GO, 0
		};
		Species food('F', foodActions, sizeof foodActions);
		
		char hopperActions[] = {
			OP_HOP, 0,
			OP_GO, 0
		};
		Species hopper('H', hopperActions, sizeof hopperActions);
		
		char trapActions[] = {
			OP_IF_ENEMY, 3,
			OP_LEFT, 0,
			OP_GO, 0,
			OP_INFECT, 0,
			OP_GO, 0
		};
		Species trap('T', trapActions, sizeof trapActions);
		
		stringstream ss (stringstream::in | stringstream::out);
		stringstream rr (stringstream::in | stringstream::out);
		
		Simulation s(3,3);
		
		s.spawn(&food, DIR_EAST, 1, 0);
		s.spawn(&trap, DIR_SOUTH, 0, 1);
		s.spawn(&hopper, DIR_NORTH, 2, 1);
		
		Simulation r(3,3);
		
		r.spawn(&food, DIR_EAST, 1, 0);
		r.spawn(&trap, DIR_SOUTH, 0, 1);
		r.spawn(&hopper, DIR_NORTH, 2, 1);
		
		s.step();
		s.step();
		s.step();
		s.print(ss);
		
		r.run(3);
		r.print(rr);
		CPPUNIT_ASSERT(ss.str() == rr.str());
	}
	void test_simulation_run2() {
		char foodActions[] = {
			OP_LEFT, 0,
			OP_GO, 0
		};
		Species food('F', foodActions, sizeof foodActions);
		
		char hopperActions[] = {
			OP_HOP, 0,
			OP_GO, 0
		};
		Species hopper('H', hopperActions, sizeof hopperActions);
		
		char trapActions[] = {
			OP_IF_ENEMY, 3,
			OP_LEFT, 0,
			OP_GO, 0,
			OP_INFECT, 0,
			OP_GO, 0
		};
		Species trap('T', trapActions, sizeof trapActions);
		
		stringstream ss (stringstream::in | stringstream::out);
		stringstream rr (stringstream::in | stringstream::out);
		
		Simulation s(3,3);
		
		s.spawn(&food, DIR_EAST, 1, 0);
		s.spawn(&trap, DIR_SOUTH, 0, 1);
		s.spawn(&hopper, DIR_NORTH, 2, 1);
		
		Simulation r(3,3);
		
		r.spawn(&food, DIR_EAST, 1, 0);
		r.spawn(&trap, DIR_SOUTH, 0, 1);
		r.spawn(&hopper, DIR_NORTH, 2, 1);
		
		s.step();
		s.step();
		s.step();
		s.print(ss);
		
		r.run(2);
		r.run(1);
		r.print(rr);
		CPPUNIT_ASSERT(ss.str() == rr.str());
	}
	void test_simulation_run3() {
		char foodActions[] = {
			OP_LEFT, 0,
			OP_GO, 0
		};
		Species food('F', foodActions, sizeof foodActions);
		
		char hopperActions[] = {
			OP_HOP, 0,
			OP_GO, 0
		};
		Species hopper('H', hopperActions, sizeof hopperActions);
		
		char trapActions[] = {
			OP_IF_ENEMY, 3,
			OP_LEFT, 0,
			OP_GO, 0,
			OP_INFECT, 0,
			OP_GO, 0
		};
		Species trap('T', trapActions, sizeof trapActions);
		
		stringstream ss (stringstream::in | stringstream::out);
		stringstream rr (stringstream::in | stringstream::out);
		
		Simulation s(3,3);
		
		s.spawn(&food, DIR_EAST, 1, 0);
		s.spawn(&trap, DIR_SOUTH, 0, 1);
		s.spawn(&hopper, DIR_NORTH, 2, 1);
		
		s.print(ss);
		s.run(0);
		s.print(rr);
		CPPUNIT_ASSERT(ss.str() == rr.str());
	}
	
	void test_simulation_spawn1() {
		Simulation s(1,1);
		try {
			s.spawn(NULL, DIR_NORTH, 1, 0); 
			CPPUNIT_ASSERT(false);
		} catch (const out_of_range&) {
			CPPUNIT_ASSERT(true);
		}
	}
	void test_simulation_spawn2() {
		Simulation s(1,1);
		try {
			s.spawn(NULL, DIR_NORTH, 0, 1); 
			CPPUNIT_ASSERT(false);
		} catch (const out_of_range&) {
			CPPUNIT_ASSERT(true);
		}
	}
	void test_simulation_spawn3() {
		Simulation s(3,3);
		Creature* c = s.spawn(NULL, DIR_SOUTH, 1, 1);
		CPPUNIT_ASSERT(c != NULL);
		CPPUNIT_ASSERT(c->species == NULL);
		CPPUNIT_ASSERT(c->dir == DIR_SOUTH);
		CPPUNIT_ASSERT(c->pc == 0);
		CPPUNIT_ASSERT(s.grid[1][1] == c);
		CPPUNIT_ASSERT(s.creatures.size() == 1);
		CPPUNIT_ASSERT(&s.creatures.front() == c);
	}
	
	void test_simulation_print1() {
		Simulation s(3,3);
		Species food('F', NULL, 0);
		Species trap('T', NULL, 0);
		s.spawn(&food, DIR_EAST, 1, 0);
		s.spawn(&trap, DIR_SOUTH, 0, 1);
		s.spawn(&food, DIR_NORTH, 2, 1);
		stringstream ss (stringstream::in | stringstream::out);
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 0.\n"
			"  012\n"
			"0 .T.\n"
			"1 F..\n"
			"2 .F.\n\n"
		);
	}
	void test_simulation_print2() {
		Simulation s(12,3);
		Species food('F', NULL, 0);
		Species trap('T', NULL, 0);
		s.spawn(&food, DIR_EAST, 1, 0);
		s.spawn(&trap, DIR_SOUTH, 0, 1);
		s.spawn(&food, DIR_NORTH, 2, 1);
		stringstream ss (stringstream::in | stringstream::out);
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 0.\n"
			"  012\n"
			"0 .T.\n"
			"1 F..\n"
			"2 .F.\n"
			"3 ...\n"
			"4 ...\n"
			"5 ...\n"
			"6 ...\n"
			"7 ...\n"
			"8 ...\n"
			"9 ...\n"
			"0 ...\n"
			"1 ...\n\n"
		);
	}
	void test_simulation_print3() {
		Simulation s(3,12);
		Species food('F', NULL, 0);
		Species trap('T', NULL, 0);
		s.spawn(&food, DIR_EAST, 1, 0);
		s.spawn(&trap, DIR_SOUTH, 0, 1);
		s.spawn(&food, DIR_NORTH, 2, 1);
		s.spawn(NULL, DIR_WEST, 1, 8);
		stringstream ss (stringstream::in | stringstream::out);
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 0.\n"
			"  012345678901\n"
			"0 .T..........\n"
			"1 F...........\n"
			"2 .F..........\n\n"
		);
	}
	
	void test_simulation_step1() {
		Simulation s(3,3);
		
		char foodActions[] = {
			OP_LEFT, 0,
			OP_GO, 0
		};
		Species food('F', foodActions, sizeof foodActions);
		
		char hopperActions[] = {
			OP_HOP, 0,
			OP_GO, 0
		};
		Species hopper('H', hopperActions, sizeof hopperActions);
		
		char trapActions[] = {
			OP_IF_ENEMY, 3,
			OP_LEFT, 0,
			OP_GO, 0,
			OP_INFECT, 0,
			OP_GO, 0
		};
		Species trap('T', trapActions, sizeof trapActions);
		
		Creature* f = s.spawn(&food, DIR_EAST, 1, 0);
		Creature* t = s.spawn(&trap, DIR_SOUTH, 0, 1);
		Creature* h = s.spawn(&hopper, DIR_NORTH, 2, 1);
		stringstream ss (stringstream::in | stringstream::out);
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 0.\n"
			"  012\n"
			"0 .T.\n"
			"1 F..\n"
			"2 .H.\n\n"
		);
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 1.\n"
			"  012\n"
			"0 .T.\n"
			"1 FH.\n"
			"2 ...\n\n"
		);
		CPPUNIT_ASSERT(f->dir == DIR_NORTH);
		CPPUNIT_ASSERT(f->pc == 1);
		CPPUNIT_ASSERT(t->dir == DIR_EAST);
		CPPUNIT_ASSERT(t->pc == 2);
		CPPUNIT_ASSERT(h->dir == DIR_NORTH);
		CPPUNIT_ASSERT(h->pc == 1);
	}
	void test_simulation_step2() {
		Simulation s(3,3);
		
		char foodActions[] = {
			OP_LEFT, 0,
			OP_GO, 0
		};
		Species food('F', foodActions, sizeof foodActions);
		
		char hopperActions[] = {
			OP_HOP, 0,
			OP_GO, 0
		};
		Species hopper('H', hopperActions, sizeof hopperActions);
		
		char trapActions[] = {
			OP_IF_ENEMY, 3,
			OP_LEFT, 0,
			OP_GO, 0,
			OP_INFECT, 0,
			OP_GO, 0
		};
		Species trap('T', trapActions, sizeof trapActions);
		
		Creature* f = s.spawn(&food, DIR_EAST, 1, 0);
		Creature* t = s.spawn(&trap, DIR_SOUTH, 0, 1);
		Creature* h = s.spawn(&hopper, DIR_NORTH, 2, 1);
		stringstream ss (stringstream::in | stringstream::out);
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 0.\n"
			"  012\n"
			"0 .T.\n"
			"1 F..\n"
			"2 .H.\n\n"
		);
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 1.\n"
			"  012\n"
			"0 .T.\n"
			"1 FH.\n"
			"2 ...\n\n"
		);
		CPPUNIT_ASSERT(f->dir == DIR_NORTH);
		CPPUNIT_ASSERT(f->pc == 1);
		CPPUNIT_ASSERT(t->dir == DIR_EAST);
		CPPUNIT_ASSERT(t->pc == 2);
		CPPUNIT_ASSERT(h->dir == DIR_NORTH);
		CPPUNIT_ASSERT(h->pc == 1);
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 2.\n"
			"  012\n"
			"0 .T.\n"
			"1 FH.\n"
			"2 ...\n\n"
		);
		CPPUNIT_ASSERT(f->dir == DIR_WEST);
		CPPUNIT_ASSERT(f->pc == 1);
		CPPUNIT_ASSERT(t->dir == DIR_NORTH);
		CPPUNIT_ASSERT(t->pc == 2);
		CPPUNIT_ASSERT(h->dir == DIR_NORTH);
		CPPUNIT_ASSERT(h->pc == 1);
	}
	void test_simulation_step3() {
		Simulation s(3,3);
		
		char foodActions[] = {
			OP_LEFT, 0,
			OP_GO, 0
		};
		Species food('F', foodActions, sizeof foodActions);
		
		char hopperActions[] = {
			OP_HOP, 0,
			OP_GO, 0
		};
		Species hopper('H', hopperActions, sizeof hopperActions);
		
		char trapActions[] = {
			OP_IF_ENEMY, 3,
			OP_LEFT, 0,
			OP_GO, 0,
			OP_INFECT, 0,
			OP_GO, 0
		};
		Species trap('T', trapActions, sizeof trapActions);
		
		Creature* f = s.spawn(&food, DIR_EAST, 1, 0);
		Creature* t = s.spawn(&trap, DIR_SOUTH, 0, 1);
		Creature* h = s.spawn(&hopper, DIR_NORTH, 2, 1);
		stringstream ss (stringstream::in | stringstream::out);
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 0.\n"
			"  012\n"
			"0 .T.\n"
			"1 F..\n"
			"2 .H.\n\n"
		);
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 1.\n"
			"  012\n"
			"0 .T.\n"
			"1 FH.\n"
			"2 ...\n\n"
		);
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 2.\n"
			"  012\n"
			"0 .T.\n"
			"1 FH.\n"
			"2 ...\n\n"
		);
		CPPUNIT_ASSERT(f->dir == DIR_WEST);
		CPPUNIT_ASSERT(f->pc == 1);
		CPPUNIT_ASSERT(t->dir == DIR_NORTH);
		CPPUNIT_ASSERT(t->pc == 2);
		CPPUNIT_ASSERT(h->dir == DIR_NORTH);
		CPPUNIT_ASSERT(h->pc == 1);
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 3.\n"
			"  012\n"
			"0 .T.\n"
			"1 FH.\n"
			"2 ...\n\n"
		);
		CPPUNIT_ASSERT(f->dir == DIR_SOUTH);
		CPPUNIT_ASSERT(f->pc == 1);
		CPPUNIT_ASSERT(t->dir == DIR_WEST);
		CPPUNIT_ASSERT(t->pc == 2);
		CPPUNIT_ASSERT(h->dir == DIR_NORTH);
		CPPUNIT_ASSERT(h->pc == 1);
		CPPUNIT_ASSERT(h->species != &trap);
		s.step();
		s.step();
		ss.str("");
		s.print(ss);
		CPPUNIT_ASSERT(ss.str() ==
			"Turn = 5.\n"
			"  012\n"
			"0 .T.\n"
			"1 FT.\n"
			"2 ...\n\n"
		);
		CPPUNIT_ASSERT(f->dir == DIR_NORTH);
		CPPUNIT_ASSERT(f->pc == 1);
		CPPUNIT_ASSERT(t->dir == DIR_SOUTH);
		CPPUNIT_ASSERT(t->pc == 4);
		CPPUNIT_ASSERT(h->dir == DIR_WEST);
		CPPUNIT_ASSERT(h->pc == 2);
		CPPUNIT_ASSERT(h->species == &trap);
	}
	
	// -----
	// suite
	// -----
	
	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(test_command_ctor1);
	CPPUNIT_TEST(test_command_ctor2);
	CPPUNIT_TEST(test_command_ctor3);
	CPPUNIT_TEST(test_command_debug1);
	CPPUNIT_TEST(test_command_debug2);
	CPPUNIT_TEST(test_command_debug3);
	CPPUNIT_TEST(test_species_ctor1);
	CPPUNIT_TEST(test_species_ctor2);
	CPPUNIT_TEST(test_species_ctor3);
	CPPUNIT_TEST(test_species_ctor4);
	CPPUNIT_TEST(test_species_debug1);
	CPPUNIT_TEST(test_species_debug2);
	CPPUNIT_TEST(test_species_debug3);
	CPPUNIT_TEST(test_creature_ctor1);
	CPPUNIT_TEST(test_creature_ctor2);
	CPPUNIT_TEST(test_creature_ctor3);
	CPPUNIT_TEST(test_creature_debug1);
	CPPUNIT_TEST(test_creature_debug2);
	CPPUNIT_TEST(test_creature_debug3);
	CPPUNIT_TEST(test_simulation_ctor1);
	CPPUNIT_TEST(test_simulation_ctor2);
	CPPUNIT_TEST(test_simulation_ctor3);
	CPPUNIT_TEST(test_simulation_ctor4);
	CPPUNIT_TEST(test_simulation_spawn1);
	CPPUNIT_TEST(test_simulation_spawn2);
	CPPUNIT_TEST(test_simulation_spawn3);
	CPPUNIT_TEST(test_simulation_print1);
	CPPUNIT_TEST(test_simulation_print2);
	CPPUNIT_TEST(test_simulation_print3);
	CPPUNIT_TEST(test_simulation_step1);
	CPPUNIT_TEST(test_simulation_step2);
	CPPUNIT_TEST(test_simulation_step3);
	CPPUNIT_TEST(test_simulation_run1);
	CPPUNIT_TEST(test_simulation_run2);
	CPPUNIT_TEST(test_simulation_run3);
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main ()
{
	using namespace std;
	ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
	cout << "TestDarwin.c++" << endl;
	
	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();
	
	cout << "Done." << endl;
	return 0;
}
