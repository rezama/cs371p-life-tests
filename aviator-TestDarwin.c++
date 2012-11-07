// --------------------------------
// Copyright (C) 2012
// 
// --------------------------------

/*
To test the program:
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.c++.app
    % valgrind TestDarwin.c++.app >& TestDarwin.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <stdlib.h>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public

#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {

    // -----
    // tests
    // -----

    // -------------
    // species tests
    // -------------

    void species_test1() {
      Species null;
      Species null2;
      CPPUNIT_ASSERT(null.name().compare(".") == 0);
      CPPUNIT_ASSERT(null == null2);
    }

    void species_test2() {
      Species cat("c");
      Species cat2("c");
      cat.add_instruction("test", 0);
      CPPUNIT_ASSERT(cat.name().compare("c") == 0);
      CPPUNIT_ASSERT(cat.instruction(0).compare("test") == 0);
      CPPUNIT_ASSERT(cat.location(0) == 0);
      CPPUNIT_ASSERT(cat == cat2);
    }

    void species_test3() {
      Species dog("d");
      Species dog2("d");
      dog.add_instruction("test2");
      dog.add_instruction("test3", 1);
      CPPUNIT_ASSERT(dog.name().compare("d") == 0);
      CPPUNIT_ASSERT(dog.instruction(0).compare("test2") == 0);
      CPPUNIT_ASSERT(dog.location(0) == -1);
      CPPUNIT_ASSERT(dog.instruction(1).compare("test3") == 0);
      CPPUNIT_ASSERT(dog.location(1) == 1);
      CPPUNIT_ASSERT(dog == dog2);
    }

    // --------------
    // creature tests
    // --------------

    void creature_test1() {
      Creature null;
      Creature null2;
      CPPUNIT_ASSERT(null.direction() == 0);
      CPPUNIT_ASSERT(null.num_turns() == 0);
      CPPUNIT_ASSERT(null.program_counter() == 0);
      CPPUNIT_ASSERT(null.species().name().compare(".") == 0);
      null.left();
      CPPUNIT_ASSERT(null.direction() == 3);
      null.right();
      null.right();
      CPPUNIT_ASSERT(null.direction() == 1);
      null.inc_turns();
      CPPUNIT_ASSERT(null.num_turns() == 1);
      null.set_program_counter(2);
      CPPUNIT_ASSERT(null.program_counter() == 2);
      CPPUNIT_ASSERT(null == null2);
      null.infect(Species("T"));
      CPPUNIT_ASSERT(null.species().name().compare("T") == 0);
      CPPUNIT_ASSERT(null.program_counter() == 0);
    }

    void creature_test2() {
      Creature copy1;
      Creature copy2(Species("D"), 0);
      CPPUNIT_ASSERT(!(copy1 == copy2));
      copy1.copy_creature(copy2);
      CPPUNIT_ASSERT(copy1.species().name().compare("D") == 0);
      CPPUNIT_ASSERT(copy1 == copy2);
    }

    void creature_test3() {
      Species test("t");
      test.add_instruction("test", 0);
      test.add_instruction("test2");
      Creature test2(test, 1);
      CPPUNIT_ASSERT(test2.direction() == 1);
      CPPUNIT_ASSERT(test2.num_turns() == 0);
      CPPUNIT_ASSERT(test2.program_counter() == 0);
      CPPUNIT_ASSERT(test2.species().name().compare("t") == 0);
      CPPUNIT_ASSERT(test2.location() == 0);
      CPPUNIT_ASSERT(test2.step().compare("test") == 0);
      CPPUNIT_ASSERT(test2.program_counter() == 1);
      CPPUNIT_ASSERT(test2.location() == -1);
      CPPUNIT_ASSERT(test2.step().compare("test2") == 0);
      CPPUNIT_ASSERT(test2.program_counter() == 2);
    }

    // ----------
    // grid tests
    // ----------

    void grid_test1() {
      Grid grid(1, 1);
      CPPUNIT_ASSERT(grid.is_empty(0, 0));
      CPPUNIT_ASSERT(!grid.is_empty(3, -1));
      CPPUNIT_ASSERT(grid.is_wall(1, 0));
      CPPUNIT_ASSERT(grid.is_wall(1, 3));
      CPPUNIT_ASSERT(!grid.is_enemy(0, 0, Species()));
      CPPUNIT_ASSERT(!grid.is_enemy(3, 5, Species()));
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 0.\n  0\n0 .\n\n") == 0);
      grid.step();
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 1.\n  0\n0 .\n\n") == 0);
      grid.step();
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 2.\n  0\n0 .\n\n") == 0);
    }

    void grid_test2() {
      Grid grid(1, 1);
      Species test("t");
      test.add_instruction("left");
      test.add_instruction("go", 0);
      grid.add_creature(Creature(test, 0), 0, 0);
      CPPUNIT_ASSERT(!grid.is_empty(0, 0));
      CPPUNIT_ASSERT(!grid.is_empty(3, -1));
      CPPUNIT_ASSERT(grid.is_wall(1, 0));
      CPPUNIT_ASSERT(grid.is_wall(1, 3));
      CPPUNIT_ASSERT(grid.is_enemy(0, 0, Species()));
      CPPUNIT_ASSERT(!grid.is_enemy(3, 5, Species()));
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 0.\n  0\n0 t\n\n") == 0);
      grid.step();
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 1.\n  0\n0 t\n\n") == 0);
      grid.step();
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 2.\n  0\n0 t\n\n") == 0);
    }

    void grid_test3() {
      Grid grid(2, 2);
      Species test("h");
      test.add_instruction("hop");
      test.add_instruction("go", 0);
      grid.add_creature(Creature(test, 2), 0, 0);
      CPPUNIT_ASSERT(!grid.is_empty(0, 0));
      CPPUNIT_ASSERT(!grid.is_empty(3, -1));
      CPPUNIT_ASSERT(grid.is_wall(1, -2));
      CPPUNIT_ASSERT(grid.is_wall(1, 3));
      CPPUNIT_ASSERT(grid.is_enemy(0, 0, Species()));
      CPPUNIT_ASSERT(!grid.is_enemy(1, 1, Species()));
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 0.\n  01\n0 h.\n1 ..\n\n") == 0);
      grid.step();
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 1.\n  01\n0 .h\n1 ..\n\n") == 0);
      grid.step();
      CPPUNIT_ASSERT(grid.print_grid().compare("Turn = 2.\n  01\n0 .h\n1 ..\n\n") == 0);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(species_test1);
    CPPUNIT_TEST(species_test2);
    CPPUNIT_TEST(species_test3);
    CPPUNIT_TEST(creature_test1);
    CPPUNIT_TEST(creature_test2);
    CPPUNIT_TEST(creature_test3);
    CPPUNIT_TEST(grid_test1);
    CPPUNIT_TEST(grid_test2);
    CPPUNIT_TEST(grid_test3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
