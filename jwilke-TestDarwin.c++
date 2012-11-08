// ------------------------------
// TestDarwin.c++
// Copyright (C) 2012
// Jacob Wilke & Graham Benevelli
// ------------------------------

/**
 * To test the program:
 *     make test2
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#define private public
#define protected public
#define class struct
#include "Darwin.h"

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {

  // ------------
  // test_species
  // ------------

  void test_Species_constructor_1 () {
    Species s(0);
    CPPUNIT_ASSERT(s.dir == 0);
    CPPUNIT_ASSERT(s.symbol == '?');
    CPPUNIT_ASSERT(s.takenTurn == false);
    CPPUNIT_ASSERT(s.pc == 0);
  }

  void test_Species_constructor_2 () {
    Species s(1);
    CPPUNIT_ASSERT(s.dir == 1);
    CPPUNIT_ASSERT(s.symbol == '?');
    CPPUNIT_ASSERT(s.takenTurn == false);
    CPPUNIT_ASSERT(s.pc == 0);
  }

  void test_Species_constructor_3 () {
    Species s(3);
    CPPUNIT_ASSERT(s.dir == 3);
    CPPUNIT_ASSERT(s.symbol == '?');
    CPPUNIT_ASSERT(s.takenTurn == false);
    CPPUNIT_ASSERT(s.pc == 0);
  }

  void test_Species_turn_1 () {
    Species s(0);
    s.turn(false);
    CPPUNIT_ASSERT(s.dir == 1);
    s.turn(false);
    CPPUNIT_ASSERT(s.dir == 2);
    s.turn(false);
    CPPUNIT_ASSERT(s.dir == 3);
  }

  void test_Species_turn_2 () {
    Species s(2);
    s.turn(false);
    CPPUNIT_ASSERT(s.dir == 3);
    s.turn(false);
    CPPUNIT_ASSERT(s.dir == 0);
    s.turn(false);
    CPPUNIT_ASSERT(s.dir == 1);
  }

  void test_Species_turn_3 () {
    Species s(1);
    s.turn(true);
    CPPUNIT_ASSERT(s.dir == 0);
    s.turn(true);
    CPPUNIT_ASSERT(s.dir == 3);
    s.turn(true);
    CPPUNIT_ASSERT(s.dir == 2);
  }

  void test_Species_canMove_1 () {
    Food s(0);
    CPPUNIT_ASSERT(s.canMove());
  }

  void test_Species_canMove_2 () {
    Food s(0);
    int arr[3];
    s.next_move(arr);
    CPPUNIT_ASSERT(!s.canMove());
  }

  void test_Species_canMove_3 () {
    Food s(0);
    int arr[3];
    s.next_move(arr);
    s.reset();
    CPPUNIT_ASSERT(s.canMove());
  }

  void test_Species_reset_1 () {
    Food s(0);
    s.reset();
    CPPUNIT_ASSERT(!s.takenTurn);
  }

  void test_Species_reset_2 () {
    Food s(0);
    s.reset();
    int arr[3];
    s.next_move(arr);
    CPPUNIT_ASSERT(s.takenTurn);
  }

  void test_Species_reset_3 () {
    Food s(0);
    int arr[3];
    s.next_move(arr);
    s.reset();
    CPPUNIT_ASSERT(!s.takenTurn);
  }

  void test_Species_print_1 () {
    Species s(0);
    CPPUNIT_ASSERT(s.print() == '?');
  }

    // -----------
    // test_hopper
    // -----------

    void test_hopper1 () {
    		Hopper h(0);
        CPPUNIT_ASSERT(h.dir == 0);
        CPPUNIT_ASSERT(h.symbol == 'h');
        CPPUNIT_ASSERT(h.takenTurn == false);
        CPPUNIT_ASSERT(h.pc == 0);
        CPPUNIT_ASSERT(h.program[0][0] == HOP);
				CPPUNIT_ASSERT(h.program[1][0] == GO);
				CPPUNIT_ASSERT(h.program[1][1] == 0);
    }
    
    void test_hopper2 () {
    		Hopper h(1);
        CPPUNIT_ASSERT(h.dir == 1);
        CPPUNIT_ASSERT(h.pc == 0);
        CPPUNIT_ASSERT(h.symbol == 'h');
        CPPUNIT_ASSERT(h.takenTurn == false);
        int move[3];
        h.next_move(move);
				CPPUNIT_ASSERT(h.takenTurn == true);
				CPPUNIT_ASSERT(move[0] == HOP);
				CPPUNIT_ASSERT(move[2] == 1);
				CPPUNIT_ASSERT(h.pc == 1);
        h.next_move(move);
        CPPUNIT_ASSERT(move[0] == GO);
        CPPUNIT_ASSERT(move[1] == 0);
				CPPUNIT_ASSERT(move[2] == 1);
				CPPUNIT_ASSERT(h.pc == 0);
				h.control_move();
				CPPUNIT_ASSERT(h.pc == 0);
				h.next_move(move);
				CPPUNIT_ASSERT(move[0] == HOP);
				CPPUNIT_ASSERT(move[2] == 1);
				CPPUNIT_ASSERT(h.pc == 1);
    }
    
    void test_hopper3 () {
    	Hopper h(2);
        CPPUNIT_ASSERT(h.dir == 2);
        CPPUNIT_ASSERT(h.pc == 0);
        CPPUNIT_ASSERT(h.symbol == 'h');
        CPPUNIT_ASSERT(h.takenTurn == false);
        int move[3];
        h.next_move(move);
	CPPUNIT_ASSERT(h.takenTurn == true);
	CPPUNIT_ASSERT(move[0] == HOP);
	CPPUNIT_ASSERT(move[2] == 2);
	CPPUNIT_ASSERT(h.pc == 1);
	h.reset();
	CPPUNIT_ASSERT(h.takenTurn == false);
	h.turn(true);
	CPPUNIT_ASSERT(h.dir == 1);
	h.turn(true);
	CPPUNIT_ASSERT(h.dir == 0);
	h.turn(true);
	CPPUNIT_ASSERT(h.dir == 3);
	h.turn(true);
	CPPUNIT_ASSERT(h.dir == 2);
    }
    
    
    // ---------
    // test_food
    // ---------
    
    void test_food1 () {
    	Food f(0);
        CPPUNIT_ASSERT(f.dir == 0);
        CPPUNIT_ASSERT(f.symbol == 'f');
        CPPUNIT_ASSERT(f.takenTurn == false);
        CPPUNIT_ASSERT(f.pc == 0);
        CPPUNIT_ASSERT(f.program[0][0] == LEFT);
	CPPUNIT_ASSERT(f.program[1][0] == GO);
	CPPUNIT_ASSERT(f.program[1][1] == 0);
    }
    
    void test_food2 () {
    	Food f(1);
        CPPUNIT_ASSERT(f.dir == 1);
        CPPUNIT_ASSERT(f.pc == 0);
        CPPUNIT_ASSERT(f.symbol == 'f');
        CPPUNIT_ASSERT(f.takenTurn == false);
        int move[3];
        f.next_move(move);
	CPPUNIT_ASSERT(f.takenTurn == true);
	CPPUNIT_ASSERT(move[0] == LEFT);
	CPPUNIT_ASSERT(move[2] == 1);
	CPPUNIT_ASSERT(f.pc == 1);
        f.next_move(move);
        CPPUNIT_ASSERT(move[0] == GO);
        CPPUNIT_ASSERT(move[1] == 0);
	CPPUNIT_ASSERT(move[2] == 1);
	CPPUNIT_ASSERT(f.pc == 0);
	f.control_move();
	CPPUNIT_ASSERT(f.pc == 0);
	f.next_move(move);
	CPPUNIT_ASSERT(move[0] == LEFT);
	CPPUNIT_ASSERT(move[2] == 1);
	CPPUNIT_ASSERT(f.pc == 1);
    }
    
    
    // ---------
    // test_trap
    // ---------
    
    void test_trap1 () {
    	Trap t(0);
        CPPUNIT_ASSERT(t.dir == 0);
        CPPUNIT_ASSERT(t.symbol == 't');
        CPPUNIT_ASSERT(t.takenTurn == false);
        CPPUNIT_ASSERT(t.pc == 0);
        CPPUNIT_ASSERT(t.program[0][0] == IF_ENEMY); 
        CPPUNIT_ASSERT(t.program[0][1] == 3);
	CPPUNIT_ASSERT(t.program[1][0] == LEFT);
	CPPUNIT_ASSERT(t.program[2][0] == GO);
	CPPUNIT_ASSERT(t.program[2][1] == 0);
	CPPUNIT_ASSERT(t.program[3][0] == INFECT);
	CPPUNIT_ASSERT(t.program[4][0] == GO);
	CPPUNIT_ASSERT(t.program[4][1] == 0);
    }
    
    void test_trap2 () {
    	Trap t(1);
        CPPUNIT_ASSERT(t.dir == 1);
        CPPUNIT_ASSERT(t.symbol == 't');
        CPPUNIT_ASSERT(t.takenTurn == false);
        CPPUNIT_ASSERT(t.pc == 0);
        int move[3];
        t.next_move(move);
        CPPUNIT_ASSERT(move[0] == IF_ENEMY);
        CPPUNIT_ASSERT(move[1] == 3);
        CPPUNIT_ASSERT(move[2] == 1);
        CPPUNIT_ASSERT(t.pc == 1);
        t.next_move(move);
        CPPUNIT_ASSERT(move[0] == LEFT);
        CPPUNIT_ASSERT(move[2] == 1);
        CPPUNIT_ASSERT(t.pc == 2);
        t.next_move(move);
        CPPUNIT_ASSERT(move[0] == GO);
        CPPUNIT_ASSERT(move[1] == 0);
        CPPUNIT_ASSERT(move[2] == 1);
        CPPUNIT_ASSERT(t.pc == 3);
        t.next_move(move);
        CPPUNIT_ASSERT(move[0] == INFECT);
        CPPUNIT_ASSERT(move[2] == 1);
        CPPUNIT_ASSERT(t.pc == 4);
        t.next_move(move);
        CPPUNIT_ASSERT(move[0] == GO);
        CPPUNIT_ASSERT(move[1] == 0);
        CPPUNIT_ASSERT(move[2] == 1);
        CPPUNIT_ASSERT(t.pc == 0);
    }
    
    // ---------
    // test_grid
    // ---------
    
    void test_Grid_at_spot_1 () {
    	Grid g(1,1);
    		
    	CPPUNIT_ASSERT(g._gridables.size() == 1);
    	CPPUNIT_ASSERT(g._gridables[0].size() == 1);
    	Species* test = g.at_spot(0,0);
    	CPPUNIT_ASSERT(test == NULL);
    	Trap t(1);
    	g.insert_species(&t,0,0);
    	test = g.at_spot(0,0);
    	CPPUNIT_ASSERT(test != NULL);
    	CPPUNIT_ASSERT(test == &t);
    }

    void test_Grid_at_spot_2 () {
    	Grid g(2,2);
    	
    	Species* test = g.at_spot(1,1);
    	CPPUNIT_ASSERT(test == NULL);
    	Rover t(1);
    	g.insert_species(&t,1,1);
    	test = g.at_spot(1,1);
    	CPPUNIT_ASSERT(test != NULL);
    	CPPUNIT_ASSERT(test == &t);
	g.insert_species(&t, 0, 1);
	test = g.at_spot(0,1);
	CPPUNIT_ASSERT(test != NULL);
    	CPPUNIT_ASSERT(test == &t);
    }

    void test_Grid_at_spot_3 () {
    	Grid g(32,32);
    	Hopper t(1);
    	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			g.insert_species(&t, i, j);
		}
	}

	for(int i = 0; i < 32; i++) {
		for(int j = 0; j < 32; j++) {
			Species* test = g.at_spot(1,1);
			CPPUNIT_ASSERT(test == &t);
		}
	}
    }
    
    void test_Grid_at_spot_4 () {
    	Grid g(2,2);
    	
    	Species* test = g.at_spot(0,0);
    	CPPUNIT_ASSERT(test == NULL);
    	test = g.at_spot(-1, 0);
    	CPPUNIT_ASSERT(test == NULL);
    	test = g.at_spot(0, 1);
    	CPPUNIT_ASSERT(test == NULL);
    	test = g.at_spot(2, 0);
    	CPPUNIT_ASSERT(test == NULL);
    	test = g.at_spot(0, 2);
    	CPPUNIT_ASSERT(test == NULL);
    }

  void test_Grid_constructor_1 () {
    Grid g;
    CPPUNIT_ASSERT(g._gridables.size() == 0);
  }

  void test_Grid_constructor_2 () {
    Grid g(1, 1);
    CPPUNIT_ASSERT(g._gridables.size() == 1);
    CPPUNIT_ASSERT(g._gridables[0].size() == 1);
  }

  void test_Grid_constructor_3 () {
    Grid g(89, 17);
    CPPUNIT_ASSERT(g._gridables.size() == 89);
    CPPUNIT_ASSERT(g._gridables[0].size() == 17);
  }

  void test_Grid_insert_species_1 () {
    Grid g(20, 20);
    Food f(2);
    g.insert_species(&f, 4, 5);
    CPPUNIT_ASSERT(&f == (g._gridables[4][5]));
  }

  void test_Grid_insert_species_2 () {
    Grid g(20, 20);
    Food f1(2);
    Food f2(0);
    g.insert_species(&f1, 4, 5);
    g.insert_species(&f2, 1, 1);
    CPPUNIT_ASSERT(&f1 == (g._gridables[4][5]));
    CPPUNIT_ASSERT(&f2 == (g._gridables[1][1]));
  }

  void test_Grid_insert_species_3 () {
    Grid g(20, 20);
    Food f1(2);
    Food f2(2);
    g.insert_species(&f1, 4, 5);
    g.insert_species(&f2, 4, 5);
    CPPUNIT_ASSERT(&f2 == (g._gridables[4][5]));
  }

  void test_Grid_reset_1 () {
    Grid g(20, 20);
    Food f(2);
    g.insert_species(&f, 4, 5);
    int arr[3];
    f.next_move(arr);
    CPPUNIT_ASSERT(!g._gridables[4][5]->canMove());
    g.reset();
    CPPUNIT_ASSERT(g._gridables[4][5]->canMove());
  }

  void test_Grid_reset_2 () {
    Grid g(20, 20);
    Food f1(2);
    Food f2(3);
    g.insert_species(&f1, 4, 5);
    g.insert_species(&f2, 1, 1);
    int arr[3];
    f1.next_move(arr);
    f2.next_move(arr);
    CPPUNIT_ASSERT(!g._gridables[1][1]->canMove());
    CPPUNIT_ASSERT(!g._gridables[4][5]->canMove());
    g.reset();
    CPPUNIT_ASSERT(g._gridables[1][1]->canMove());
    CPPUNIT_ASSERT(g._gridables[4][5]->canMove());
  }

  void test_Grid_reset_3 () {
    Grid g(20, 20);
    Food f1(2);
    Food f2(3);
    g.insert_species(&f1, 4, 5);
    g.insert_species(&f2, 1, 1);
    int arr[3];
    f1.next_move(arr);
    CPPUNIT_ASSERT(g._gridables[1][1]->canMove());
    CPPUNIT_ASSERT(!g._gridables[4][5]->canMove());
    g.reset();
    CPPUNIT_ASSERT(g._gridables[1][1]->canMove());
    CPPUNIT_ASSERT(g._gridables[4][5]->canMove());
  }

  void test_Grid_change_species_1 () {
    Grid g(1, 1);
    Food f(0);
    Trap t(1);
    g.insert_species(&f, 0, 0);
    CPPUNIT_ASSERT(&f == g._gridables[0][0]);
    g.change_species(&t, 0, 0);
    CPPUNIT_ASSERT(&t == g._gridables[0][0]);
  }

  void test_Grid_change_species_2 () {
    Grid g(1, 1);
    Food f(0);
    Trap t(1);
    g.insert_species(&t, 0, 0);
    CPPUNIT_ASSERT(&t == g._gridables[0][0]);
    g.change_species(&f, 0, 0);
    CPPUNIT_ASSERT(&f == g._gridables[0][0]);
  }

  void test_Grid_change_species_3 () {
    Grid g(1, 1);
    Food f(0);
    Rover r(1);
    g.insert_species(&r, 0, 0);
    CPPUNIT_ASSERT(&r == g._gridables[0][0]);
    g.change_species(&f, 0, 0);
    CPPUNIT_ASSERT(&f == g._gridables[0][0]);
  }

  void test_Grid_print_1 () {
    Grid g(1,1);
    std::ostringstream w;
    g.print(w);
    string s =  "  0\n";
    s +=        "0 .\n\n";
    CPPUNIT_ASSERT(w.str() == s);
  }

  void test_Grid_print_2 () {
    Grid g(1,1);
    std::ostringstream w;
    g.print(w);
    string s =  "  0\n";
    s +=        "0 .\n\n";
    CPPUNIT_ASSERT(w.str() == s);
  }

  void test_Grid_print_3 () {
    Grid g(1,1);
    std::ostringstream w;
    g.print(w);
    string s =  "  0\n";
    s +=        "0 .\n\n";
    CPPUNIT_ASSERT(w.str() == s);
  }

  // ------
  // Darwin
  // ------

  void test_Darwin_setTurns_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.setTurns("5 4");
    CPPUNIT_ASSERT(d._turns_to_take == 5);
    CPPUNIT_ASSERT(d._step_size == 4);
  }

  void test_Darwin_setTurns_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.setTurns("10 49");
    CPPUNIT_ASSERT(d._turns_to_take == 10);
    CPPUNIT_ASSERT(d._step_size == 49);
  }

  void test_Darwin_setTurns_3 () {
    std::istringstream in("");
    Darwin d(in);
    try{
      d.setTurns("5 ");
      CPPUNIT_ASSERT(false);
    } catch(...) {
      CPPUNIT_ASSERT(true);
    }
  }

  // -----------------------
  // createGrid(string line)
  // -----------------------

  void test_Darwin_createGrid_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("72 72");
    CPPUNIT_ASSERT(d._g._gridables.size() == 72);
    CPPUNIT_ASSERT(d._g._gridables[0].size() == 72);
  }

  void test_Darwin_createGrid_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("8 9");
    CPPUNIT_ASSERT(d._g._gridables.size() == 8);
    CPPUNIT_ASSERT(d._g._gridables[0].size() == 9);
  }

  void test_Darwin_createGrid_3 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("72 0");
    CPPUNIT_ASSERT(d._g._gridables.size() == 72);
    CPPUNIT_ASSERT(d._g._gridables[0].size() == 0);
  }

  // ------------------------------------
  // add_creature(string creature_string)
  // ------------------------------------

  void test_Darwin_add_creature_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("h 2 5 5");
    CPPUNIT_ASSERT(d._g._gridables[5][5] != NULL);
    CPPUNIT_ASSERT(d._g._gridables[5][5]->print() == 'h');
    CPPUNIT_ASSERT(d._g._gridables[5][5]->getDir() == 2);
  } 

  void test_Darwin_add_creature_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("f 1 0 0");
    d.add_creature("f 1 1 1");
    CPPUNIT_ASSERT(d._g._gridables[0][0] != NULL);
    CPPUNIT_ASSERT(d._g._gridables[0][0]->print() == 'f');
    CPPUNIT_ASSERT(d._g._gridables[0][0]->getDir() == 1);
  }

  void test_Darwin_add_creature_3 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r -1");
    d.add_creature("r 1 0 0");
    CPPUNIT_ASSERT(d._g._gridables[8][3] != NULL);
    CPPUNIT_ASSERT(d._g._gridables[8][3]->print() == 'r');
    CPPUNIT_ASSERT(d._g._gridables[8][3]->getDir() == 2);
  }

  // -----------------------------------------------------------------------
  // hop(Species* spec, int length, int dir, unsigned int r, unsigned int c)
  // -----------------------------------------------------------------------

  void test_Darwin_hop_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 0 0");
    Species* spec = d._g._gridables[0][0];
    d.hop(spec, 1, 0, 0);
    CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
  }

  void test_Darwin_hop_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 0 0");
    d.add_creature("r 1 0 1");
    Species* spec1 = d._g._gridables[0][0];
    Species* spec2 = d._g._gridables[0][1];
    d.hop(spec1, 1, 0, 0);
    CPPUNIT_ASSERT(d._g._gridables[0][0] == spec1);
    CPPUNIT_ASSERT(d._g._gridables[0][1] == spec2);
  }

  void test_Darwin_hop_3 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 0 0 0");
    Species* spec = d._g._gridables[0][0];
    d.hop(spec, 0, 0, 0);
    CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
  }

  // ---------------------------------------------------
  // left(Species* spec, unsigned int r, unsigned int c)
  // ---------------------------------------------------

  void test_Darwin_left_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 0 0");
    Species* spec = d._g._gridables[0][0];
    d.left(spec, 0, 0);
    CPPUNIT_ASSERT(spec->dir == 0);
  }

  void test_Darwin_left_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 2 0 0");
    Species* spec = d._g._gridables[0][0];
    d.left(spec, 0, 0);
    CPPUNIT_ASSERT(spec->dir == 1);
  }

  void test_Darwin_left_3 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 0 0 0");
    Species* spec = d._g._gridables[0][0];
    d.left(spec, 0, 0);
    CPPUNIT_ASSERT(spec->dir == 3);
  }

  // ----------------------------------------------------
  // right(Species* spec, unsigned int r, unsigned int c)
  // ----------------------------------------------------

  void test_Darwin_right_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 0 0");
    Species* spec = d._g._gridables[0][0];
    d.right(spec, 0, 0);
    CPPUNIT_ASSERT(spec->dir == 2);
  }

  void test_Darwin_right_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 0 0");
    Species* spec = d._g._gridables[0][0];
    d.right(spec, 0, 0);
    CPPUNIT_ASSERT(spec->dir == 2);
  }

  void test_Darwin_right_3 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 0 0");
    Species* spec = d._g._gridables[0][0];
    d.right(spec, 0, 0);
    CPPUNIT_ASSERT(spec->dir == 2);
  }

  // --------------------------------------------------------------
  // infect(Species* spec, int dir, unsigned int r, unsigned int c)
  // --------------------------------------------------------------

  void test_Darwin_infect_1 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 2 0 0");
    Species* spec1 = d._g._gridables[0][0];
    d.add_creature("f 3 0 1");
    d.infect(spec1, 2, 0, 0);
    std::ostringstream w;
    d._g.print(w);
    CPPUNIT_ASSERT(d._g._gridables[0][0] == spec1);
    CPPUNIT_ASSERT(d._g._gridables[0][1]->print() == 'r');
    CPPUNIT_ASSERT(d._g._gridables[0][1]->dir == 3);
  }

  void test_Darwin_infect_2 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 2 2 3");
    Species* spec1 = d._g._gridables[2][3];
    d.add_creature("f 1 2 4");
    d.infect(spec1, 2, 2, 3);
    std::ostringstream w;
    d._g.print(w);
    CPPUNIT_ASSERT(d._g._gridables[2][3] == spec1);
    CPPUNIT_ASSERT(d._g._gridables[2][4]->print() == 'r');
    CPPUNIT_ASSERT(d._g._gridables[2][4]->dir == 1);
  }

  void test_Darwin_infect_3 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 1 2 3");
    Species* spec1 = d._g._gridables[2][3];
    d.add_creature("f 2 3 4");
    d.infect(spec1, 1, 2, 3);
    std::ostringstream w;
    d._g.print(w);
    CPPUNIT_ASSERT(d._g._gridables[2][3] == spec1);
    CPPUNIT_ASSERT(d._g._gridables[2][4] == NULL);
  }

  void test_Darwin_infect_4 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("r 0 0 0");
    Species* spec1 = d._g._gridables[0][0];
    d.add_creature("f 2 2 4");
    d.infect(spec1, 1, 2, 3);
    std::ostringstream w;
    d._g.print(w);
    CPPUNIT_ASSERT(d._g._gridables[0][0] == spec1);
    CPPUNIT_ASSERT(d._g._gridables[2][4] != NULL);
  }
  
  void test_Darwin_infect_5 () {
    std::istringstream in("");
    Darwin d(in);
    d.createGrid("10 10");
    d.add_creature("t 0 9 3");
    Species* spec1 = d._g._gridables[9][3];
    d.add_creature("t 1 9 2");
    d.infect(spec1, 0, 9, 3);
    std::ostringstream w;
    d._g.print(w);
    CPPUNIT_ASSERT(d._g._gridables[9][3] == spec1);
    CPPUNIT_ASSERT(d._g._gridables[9][2]->print() == 't');
    CPPUNIT_ASSERT(d._g._gridables[9][2]->dir == 1);
  }

	// ----------------------------------------------------------------------------
	// if_empty(Species* spec, int length, int dir, unsigned int r, unsigned int c)
	// ----------------------------------------------------------------------------
	
	void test_Darwin_if_empty_1 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 2 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_empty(spec, 1, 2, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_empty_2 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("r 1 0 0");
    		d.add_creature("r 1 0 1");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 4;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_empty(spec, 1, 1, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 0);
	}
	
	void test_Darwin_if_empty_3 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("r 0 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 4;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_empty(spec, 1, 0, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc != 4);
	}
	
	// if_wall(Species* spec, int length, int dir, unsigned int r, unsigned int c) 
	
	void test_Darwin_if_wall_1 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 1 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 4;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_wall(spec, 1, 1, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 4);
	}
	
	void test_Darwin_if_wall_2 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 0 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_wall(spec, 1, 0, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_wall_3 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 3 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_wall(spec, 1, 3, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 0);
	}

	// if_random(Species* spec, unsigned int r, unsigned int c)
	
	void test_Darwin_if_random_1 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 2 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_random(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_random_2 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 2 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_random(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_random_3 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 2 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_random(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_random_4 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 2 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_random(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_random_5 () {
		std::istringstream in("");
    		Darwin d(in);
    		d.createGrid("10 10");
    		d.add_creature("h 2 0 0");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_random(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 0);
	}

	// if_enemy(Species* spec, int dir, unsigned int r, unsigned int c)
	
	void test_Darwin_if_enemy_1 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
    		d.add_creature("t 2 0 0");
    		d.add_creature("f 2 0 1");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_enemy(spec, 2, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_if_enemy_2 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
    		d.add_creature("t 2 0 0");
    		d.add_creature("t 2 0 1");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_enemy(spec, 2, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 0);
	}
	
	void test_Darwin_if_enemy_3 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
    		d.add_creature("t 2 0 0");
    		d.add_creature("f 2 0 2");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.if_enemy(spec, 2, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 0);
	}

	// go(Species* spec, unsigned int r, unsigned int c)
	
	void test_Darwin_go_1 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("t 2 0 0");
    		d.add_creature("f 2 0 2");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.go(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_go_2 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("t 2 0 0");
    		d.add_creature("f 2 0 2");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.go(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}
	
	void test_Darwin_go_3 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("t 2 0 0");
    		d.add_creature("f 2 0 2");
    		Species* spec = d._g._gridables[0][0];
    		spec->temp_pc = 1;
    		CPPUNIT_ASSERT(spec != NULL);
    		d.go(spec, 0, 0);
    		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec);
    		CPPUNIT_ASSERT(spec->pc == 1);
	}

	// move(Species* spec, int move, int length, int dir, unsigned int r, unsigned int c)

	void test_Darwin_move_1 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("f 2 0 0");
		Species* spec = d._g._gridables[0][0];
		int arr[3];
		spec->next_move(arr);
		d.move(spec, arr[0], arr[1], arr[2], 0, 0);
		CPPUNIT_ASSERT(spec->getDir() == 1);
		spec->next_move(arr);
		d.move(spec, arr[0], arr[1], arr[2], 0, 0);
		CPPUNIT_ASSERT(spec->getDir() == 0);
	}
	
	void test_Darwin_move_2 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("h 2 0 0");
		Species* spec = d._g._gridables[0][0];
		int arr[3];
		spec->next_move(arr);
		d.move(spec, arr[0], arr[1], arr[2], 0, 0);
		CPPUNIT_ASSERT(spec->getDir() == 2);
		CPPUNIT_ASSERT(d._g._gridables[0][1] == spec);
		spec->next_move(arr);
		d.move(spec, arr[0], arr[1], arr[2], 0, 1);
		CPPUNIT_ASSERT(spec->getDir() == 2);
		CPPUNIT_ASSERT(d._g._gridables[0][2] == spec);
	}
	
	void test_Darwin_move_3 () {
		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("t 2 1 0");
		d.add_creature("f 2 0 0");
		Species* spec = d._g._gridables[1][0];
		int arr[3];
		spec->next_move(arr);
		d.move(spec, arr[0], arr[1], arr[2], 1, 0);
		CPPUNIT_ASSERT(spec->getDir() == 1);
		CPPUNIT_ASSERT(d._g._gridables[1][0] == spec);
		spec->next_move(arr);
		d.move(spec, arr[0], arr[1], arr[2], 1, 0);
		CPPUNIT_ASSERT(spec->getDir() == 1);
		CPPUNIT_ASSERT(d._g._gridables[1][0] == spec);
		CPPUNIT_ASSERT(d._g._gridables[0][0]->print() == 't');
	}
	
 	// make_turn()
 	
 	void test_Darwin_make_turn_1 () {
 		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("h 2 0 0");
		d.add_creature("h 0 9 9");
		Species* spec1 = d._g._gridables[0][0];
		Species* spec2 = d._g._gridables[9][9];
		int arr[3];
		spec1->next_move(arr);
		d.move(spec1, arr[0], arr[1], arr[2], 0, 0);
		spec2->next_move(arr);
		d.move(spec2, arr[0], arr[1], arr[2], 9, 9);
		CPPUNIT_ASSERT(d._g._gridables[0][1] == spec1);
		CPPUNIT_ASSERT(d._g._gridables[9][8] == spec2);
 	}
 	
 	void test_Darwin_make_turn_2 () {
 		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("t 2 0 0");
		d.add_creature("t 0 9 9");
		Species* spec1 = d._g._gridables[0][0];
		Species* spec2 = d._g._gridables[9][9];
		int arr[3];
		spec1->next_move(arr);
		d.move(spec1, arr[0], arr[1], arr[2], 0, 0);
		spec2->next_move(arr);
		d.move(spec2, arr[0], arr[1], arr[2], 9, 9);
		CPPUNIT_ASSERT(d._g._gridables[0][0] == spec1);
		CPPUNIT_ASSERT(d._g._gridables[0][0]->getDir() == 1);
		CPPUNIT_ASSERT(d._g._gridables[9][9] == spec2);
		CPPUNIT_ASSERT(d._g._gridables[9][9]->getDir() == 3);
 	}
 	
 	void test_Darwin_make_turn_3 () {
 		std::istringstream in("");
		Darwin d(in);
		d.createGrid("10 10");
		d.add_creature("f 2 0 0");
		d.add_creature("t 0 0 1");
		Species* spec1 = d._g._gridables[0][0];
		Species* spec2 = d._g._gridables[0][1];
		int arr[3];
		spec1->next_move(arr);
		d.move(spec1, arr[0], arr[1], arr[2], 0, 0);
		spec2->next_move(arr);
		d.move(spec2, arr[0], arr[1], arr[2], 0, 1);
		CPPUNIT_ASSERT(d._g._gridables[0][0] != spec1);
		CPPUNIT_ASSERT(d._g._gridables[0][0]->getDir() == 1);	
		CPPUNIT_ASSERT(d._g._gridables[0][0]->print() == 't');
		CPPUNIT_ASSERT(d._g._gridables[0][1] == spec2);
		CPPUNIT_ASSERT(d._g._gridables[0][1]->getDir() == 0);
 	}

	// simulate(std::ostream& w) 
	
	void test_Darwin_simulate_1 () {
		string s = "1 1\r\n";
		s += "10 10\r\n";
		s += "h 2 0 0\r\n";
		s += "END";
		std::istringstream in(s);
		Darwin d(in);
		std::ostringstream w;
		d.simulate(w);
		CPPUNIT_ASSERT(d._g._gridables[0][1]->print() == 'h');
	}

  void test_Darwin_simulate_2 () {
    string s = "1 1\r\n";
    s += "10 10\r\n";
    s += "f 2 0 0\r\n";
    s += "END";
    std::istringstream in(s);
    Darwin d(in);
    std::ostringstream w;
    d.simulate(w);
    CPPUNIT_ASSERT(d._g._gridables[0][0]->print() == 'f');
  }

  void test_Darwin_simulate_3 () {
    string s = "20 1\r\n";
    s += "10 10\r\n";
    s += "h 2 0 0\r\n";
    s += "END";
    std::istringstream in(s);
    Darwin d(in);
    std::ostringstream w;
    d.simulate(w);
    CPPUNIT_ASSERT(d._g._gridables[0][9]->print() == 'h');
  }

  

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_Species_constructor_1);
    CPPUNIT_TEST(test_Species_constructor_2);
    CPPUNIT_TEST(test_Species_constructor_3);
    CPPUNIT_TEST(test_Species_turn_1);
    CPPUNIT_TEST(test_Species_turn_2);
    CPPUNIT_TEST(test_Species_turn_3);
    CPPUNIT_TEST(test_Species_reset_1);
    CPPUNIT_TEST(test_Species_reset_2);
    CPPUNIT_TEST(test_Species_reset_3);
    CPPUNIT_TEST(test_Species_print_1);
    CPPUNIT_TEST(test_hopper1);
    CPPUNIT_TEST(test_hopper2);
    CPPUNIT_TEST(test_hopper3);
    CPPUNIT_TEST(test_food1);
    CPPUNIT_TEST(test_food2);
    CPPUNIT_TEST(test_trap1);
    CPPUNIT_TEST(test_trap2);
    
    CPPUNIT_TEST(test_Grid_at_spot_1);
    CPPUNIT_TEST(test_Grid_at_spot_2);
    CPPUNIT_TEST(test_Grid_at_spot_3);
    CPPUNIT_TEST(test_Grid_at_spot_4);
    CPPUNIT_TEST(test_Grid_constructor_1);
    CPPUNIT_TEST(test_Grid_constructor_2);
    CPPUNIT_TEST(test_Grid_constructor_3);
    CPPUNIT_TEST(test_Grid_insert_species_1);
    CPPUNIT_TEST(test_Grid_insert_species_2);
    CPPUNIT_TEST(test_Grid_insert_species_3);
    CPPUNIT_TEST(test_Grid_reset_1);
    CPPUNIT_TEST(test_Grid_reset_2);
    CPPUNIT_TEST(test_Grid_reset_3);
    CPPUNIT_TEST(test_Grid_change_species_1);
    CPPUNIT_TEST(test_Grid_change_species_2);
    CPPUNIT_TEST(test_Grid_change_species_3);
    CPPUNIT_TEST(test_Grid_print_1);
    CPPUNIT_TEST(test_Grid_print_2);
    CPPUNIT_TEST(test_Grid_print_3);
  CPPUNIT_TEST(test_Darwin_setTurns_1);
  CPPUNIT_TEST(test_Darwin_setTurns_2);
  CPPUNIT_TEST(test_Darwin_setTurns_3);
  CPPUNIT_TEST(test_Darwin_createGrid_1);
  CPPUNIT_TEST(test_Darwin_createGrid_2);
  CPPUNIT_TEST(test_Darwin_createGrid_3);
  CPPUNIT_TEST(test_Darwin_add_creature_1);
  CPPUNIT_TEST(test_Darwin_add_creature_1);
  CPPUNIT_TEST(test_Darwin_add_creature_2);
  CPPUNIT_TEST(test_Darwin_add_creature_3);
  CPPUNIT_TEST(test_Darwin_hop_1);
  CPPUNIT_TEST(test_Darwin_hop_2);
  CPPUNIT_TEST(test_Darwin_hop_3);
  CPPUNIT_TEST(test_Darwin_left_1);
  CPPUNIT_TEST(test_Darwin_left_2);
  CPPUNIT_TEST(test_Darwin_left_3);
  CPPUNIT_TEST(test_Darwin_right_1);
  CPPUNIT_TEST(test_Darwin_right_2);
  CPPUNIT_TEST(test_Darwin_right_3);
  CPPUNIT_TEST(test_Darwin_infect_1);
  CPPUNIT_TEST(test_Darwin_infect_2);
  CPPUNIT_TEST(test_Darwin_infect_3);
  CPPUNIT_TEST(test_Darwin_infect_4);
  CPPUNIT_TEST(test_Darwin_infect_5);
    CPPUNIT_TEST(test_Darwin_if_empty_1);
    CPPUNIT_TEST(test_Darwin_if_empty_2);
    CPPUNIT_TEST(test_Darwin_if_empty_3);
    CPPUNIT_TEST(test_Darwin_if_wall_1);
    CPPUNIT_TEST(test_Darwin_if_wall_2);
    CPPUNIT_TEST(test_Darwin_if_wall_3);
    CPPUNIT_TEST(test_Darwin_if_random_1);
    CPPUNIT_TEST(test_Darwin_if_random_2);
    CPPUNIT_TEST(test_Darwin_if_random_3);
    CPPUNIT_TEST(test_Darwin_if_random_4);
    CPPUNIT_TEST(test_Darwin_if_random_5);
    CPPUNIT_TEST(test_Darwin_if_enemy_1);
    CPPUNIT_TEST(test_Darwin_if_enemy_2);
    CPPUNIT_TEST(test_Darwin_if_enemy_3);
    CPPUNIT_TEST(test_Darwin_go_1);
    CPPUNIT_TEST(test_Darwin_go_2);
    CPPUNIT_TEST(test_Darwin_go_3);
    CPPUNIT_TEST(test_Darwin_move_1);
    CPPUNIT_TEST(test_Darwin_move_2);
    CPPUNIT_TEST(test_Darwin_move_3);
    CPPUNIT_TEST(test_Darwin_make_turn_1);
    CPPUNIT_TEST(test_Darwin_make_turn_2);
    CPPUNIT_TEST(test_Darwin_make_turn_3);
    CPPUNIT_TEST(test_Darwin_simulate_1);
  CPPUNIT_TEST(test_Darwin_simulate_2);
  CPPUNIT_TEST(test_Darwin_simulate_3);    
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestConstruct.c++" << endl;
    srand(0);

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

