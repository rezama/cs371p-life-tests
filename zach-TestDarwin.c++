// ------------------------------
// projects/matlab/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing & Jon Tucker
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include <stdexcept>

#define private public
#include "Darwin.h"

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {

  // species constructor tests
  void species_ctor_1() {
    vector<vector<int> > p(2);
    p[0] = { LEFT, -1};
    p[1] = {GO, 0};
    Species test(p, 't');
    CPPUNIT_ASSERT(&p == &test.program);
    CPPUNIT_ASSERT(test.type == 't');
  }
    
  void species_ctor_2() {
    vector<vector<int> > p(9);
    p[0] = {HOP, -1};
    p[1] = {LEFT, -1};
    p[2] = {RIGHT, -1};
    p[3] = {INFECT, -1};
    p[4] = {IF_EMPTY, 0};
    p[5] = {IF_WALL, 1};
    p[6] = {IF_RANDOM, 2};
    p[7] = {IF_ENEMY, 3};
    p[8] = {GO, 0};
    Species test(p, 't');
    CPPUNIT_ASSERT(&p == &test.program);
    CPPUNIT_ASSERT(test.type == 't');
    for (int i = 0; i < 9; ++i) {
      CPPUNIT_ASSERT(test.program[i][0] == i);
    }
  }

  void species_ctor_3() {
    vector<vector<int> > p(2);
    p[0] = { GO, 5};
    Species test(p, 't');
    CPPUNIT_ASSERT(&p == &test.program);
    CPPUNIT_ASSERT(test.type == 't');
    CPPUNIT_ASSERT(test.program[0][1] == 5);
  }

  void creature_ctor_1() {
    vector<vector<int> > p(2);
    p[0] = { LEFT, -1};
    p[1] = {GO, 0};
    Species test(p, 't');
    Creature c(&test, NORTH);
    CPPUNIT_ASSERT(c.s == &test);
    CPPUNIT_ASSERT(c.direction == NORTH);
    CPPUNIT_ASSERT(c.pc == 0);
  }

  void creature_ctor_2() {
    vector<vector<int> > p(2);
    p[0] = { LEFT, -1};
    p[1] = {GO, 0};
    Species test(p, 't');
    Creature c(&test, SOUTH);
    CPPUNIT_ASSERT(c.s == &test);
    CPPUNIT_ASSERT(c.direction == SOUTH);
    CPPUNIT_ASSERT(c.pc == 0);
  }

  void creature_ctor_3() {
    vector<vector<int> > p(2);
    p[0] = { LEFT, -1};
    p[1] = {GO, 0};
    Species test(p, 't');
    Creature c(&test, EAST);
    CPPUNIT_ASSERT(c.s == &test);
    CPPUNIT_ASSERT(c.direction == EAST);
    CPPUNIT_ASSERT(c.pc == 0);
  }

  void controller_makeGrid_1() {
    Controller controller;
    controller.makeGrid(5,5);
    CPPUNIT_ASSERT(controller.rows == 5);
    CPPUNIT_ASSERT(controller.cols == 5);
  }

  void controller_makeGrid_2() {
    Controller controller;
    controller.makeGrid(10,1);
    CPPUNIT_ASSERT(controller.rows == 10);
    CPPUNIT_ASSERT(controller.cols == 1);
  }

  void controller_makeGrid_3() {
    std::ostringstream w;
    Controller controller;
    controller.makeGrid(4,4);
    controller.printBoard(w, 0);
    string result = 
              "Turn = 0.\n";
    result += "  0123\n";
    result += "0 ....\n";
    result += "1 ....\n";
    result += "2 ....\n";
    result += "3 ....\n";
    CPPUNIT_ASSERT(w.str() == result);
  }

  void controller_placeCreature_1() {
    Controller controller;
    vector<vector<int> > p(1);
    p[0] = { GO, 5 };
    Species test(p, 't');
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, NORTH, 1, 1);
    CPPUNIT_ASSERT(controller.grid[1][1] == 0);
    CPPUNIT_ASSERT(controller.creatures[controller.grid[1][1]].s->type == 't');
  }

  void controller_placeCreature_2() {
    Controller controller;
    vector<vector<int> > p(1);
    p[0] = { GO, 5 };
    Species test(p, 't');
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, SOUTH, 2, 2);
    CPPUNIT_ASSERT(controller.grid[2][2] == 0);
    CPPUNIT_ASSERT(controller.creatures[controller.grid[2][2]].s->type == 't');
  }

  void controller_placeCreature_3() {
    Controller controller;
    vector<vector<int> > p(1);
    p[0] = { GO, 5 };
    Species test(p, 't');
    controller.makeGrid(1, 1);
    controller.placeCreature(&test, SOUTH, 0, 0);
    CPPUNIT_ASSERT(controller.grid[0][0] == 0);
    CPPUNIT_ASSERT(controller.creatures[controller.grid[0][0]].s->type == 't');
  }

  void controller_run_1() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, NORTH, 2, 2);
    controller.run(2, 0);
    CPPUNIT_ASSERT(controller.grid[0][2] == 0);
    CPPUNIT_ASSERT(controller.grid[2][2] == -1);
  }

  void controller_run_2() {
    vector<vector<int> > p(5);
    p[0] = { IF_WALL, 3 };
    p[1] = { HOP, -1 };
    p[2] = { GO, 0 };
    p[3] = { LEFT, -1 };
    p[4] = { GO, 1 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(10, 10);
    controller.placeCreature(&test, NORTH, 4, 2);
    controller.run(5, 0);
    CPPUNIT_ASSERT(controller.grid[0][1] == 0);
  }

  void controller_run_3() {
    vector<vector<int> > p(5);
    p[0] = { IF_WALL, 3 };
    p[1] = { HOP, -1 };
    p[2] = { GO, 0 };
    p[3] = { LEFT, -1 };
    p[4] = { GO, 1 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, SOUTH, 2, 2);
    controller.run(5, 0);
    CPPUNIT_ASSERT(controller.grid[4][4] == 0);
  }

  void controller_printBoard_1() {
    std::ostringstream w;  
    Controller controller;
    controller.makeGrid(5,5);
    controller.printBoard(w, 0);
    string result = "Turn = 0.\n";
        result += "  01234\n";
        result += "0 .....\n";
        result += "1 .....\n";
        result += "2 .....\n";
        result += "3 .....\n";
        result += "4 .....\n";
    CPPUNIT_ASSERT(w.str() == result);
  }

  void controller_printBoard_2() {
    std::ostringstream w;  
    Controller controller;
    controller.makeGrid(1,1);
    controller.printBoard(w, 0);
    string result = "Turn = 0.\n";
        result += "  0\n";
        result += "0 .\n";
    CPPUNIT_ASSERT(w.str() == result);
  }

  void controller_printBoard_3() {
    vector<vector<int> > p;
    Species test(p, 't');
    std::ostringstream w;  
    Controller controller;
    controller.makeGrid(5,5);
    controller.placeCreature(&test, NORTH, 1, 2);
    controller.printBoard(w, 0);
    string result = "Turn = 0.\n";
        result += "  01234\n";
        result += "0 .....\n";
        result += "1 ..t..\n";
        result += "2 .....\n";
        result += "3 .....\n";
        result += "4 .....\n";
    CPPUNIT_ASSERT(w.str() == result);
  }

  void controller_execute_1() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, NORTH, 2, 2);
    Creature &c = controller.creatures.at(0);
    controller.execute(c, 2, 2);
    CPPUNIT_ASSERT(controller.grid[1][2] == 0);
    CPPUNIT_ASSERT(controller.grid[2][2] == -1);
  }

  void controller_execute_2() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, NORTH, 2, 2);
    Creature &c = controller.creatures.at(0);
    c.totalTurns++;
    controller.execute(c, 2, 2);
    CPPUNIT_ASSERT(c.pc == 1);
  }

  void controller_execute_3() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, SOUTH, 2, 2);
    Creature &c = controller.creatures.at(0);
    controller.execute(c, 2, 2);
    CPPUNIT_ASSERT(controller.grid[3][2] == 0);
    CPPUNIT_ASSERT(controller.grid[2][2] == -1);
  }

  void controller_spaceAhead_1() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 5);
    controller.placeCreature(&test, NORTH, 2, 2);
    Creature &c = controller.creatures.at(0);
    CPPUNIT_ASSERT(controller.spaceAhead(c, 2, 2) == 7);
  }

  void controller_spaceAhead_2() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(4, 5);
    controller.placeCreature(&test, SOUTH, 2, 2);
    Creature &c = controller.creatures.at(0);
    CPPUNIT_ASSERT(controller.spaceAhead(c, 2, 2) == 17);
  }

  void controller_spaceAhead_3() {
    vector<vector<int> > p(2);
    p[0] = { HOP, -1 };
    p[1] = { GO, 0 };
    Species test(p, 't');
    Controller controller;
    controller.makeGrid(5, 4);
    controller.placeCreature(&test, EAST, 2, 2);
    Creature &c = controller.creatures.at(0);
    CPPUNIT_ASSERT(controller.spaceAhead(c, 2, 2) == 11);
  }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(species_ctor_1);
    CPPUNIT_TEST(species_ctor_2);
    CPPUNIT_TEST(species_ctor_3);
    CPPUNIT_TEST(creature_ctor_1);
    CPPUNIT_TEST(creature_ctor_2);
    CPPUNIT_TEST(creature_ctor_3);
    CPPUNIT_TEST(controller_makeGrid_1);
    CPPUNIT_TEST(controller_makeGrid_2);
    CPPUNIT_TEST(controller_makeGrid_3);
    CPPUNIT_TEST(controller_placeCreature_1);
    CPPUNIT_TEST(controller_placeCreature_2);
    CPPUNIT_TEST(controller_placeCreature_3);
    CPPUNIT_TEST(controller_run_1);
    CPPUNIT_TEST(controller_run_2);
    CPPUNIT_TEST(controller_run_3);
    CPPUNIT_TEST(controller_printBoard_1);
    CPPUNIT_TEST(controller_printBoard_2);
    CPPUNIT_TEST(controller_printBoard_3);
    CPPUNIT_TEST(controller_execute_1);
    CPPUNIT_TEST(controller_execute_2);
    CPPUNIT_TEST(controller_execute_3);
    CPPUNIT_TEST(controller_spaceAhead_1);
    CPPUNIT_TEST(controller_spaceAhead_2);
    CPPUNIT_TEST(controller_spaceAhead_3);

    CPPUNIT_TEST_SUITE_END();};

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
