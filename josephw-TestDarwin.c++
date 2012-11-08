// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2012
// Joseph S. Wang
// Based off template by Glenn P. Downing
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

#include <iostream>
#include <sstream>
#include <string>

#define private public
#include "Darwin.h"



// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {
    // ----------
    // test_board
    // ----------

    void test_board_1 () {
        Board x(1, 1);
        CPPUNIT_ASSERT(x._grid.size() == 1);
        CPPUNIT_ASSERT(x._grid[0].size() == 1);}

    void test_board_2 () {
        Board x(2, 2);
        CPPUNIT_ASSERT(x._grid.size() == 2);
        CPPUNIT_ASSERT(x._grid[0].size() == 2);}

    void test_board_3 () {
        Board x(40, 40);
        CPPUNIT_ASSERT(x._grid.size() == 40);
        for (int i=0; i<40; ++i)
            CPPUNIT_ASSERT(x._grid[i].size() == 40);}

    // ----------
    // test_print
    // ----------
    void test_print_1 () {
        std::ostringstream w;
        Board x(1, 1);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  0\n0 .\n\n");
    }

    void test_print_2 () {
        std::ostringstream w;
        Board x(2, 2);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
    }

    void test_print_3 () {
        std::ostringstream w;
        Board x(1, 3);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  012\n0 ...\n\n");
    }


    // ----------
    // test_addCreature
    // ----------

    void test_addCreature_1 () {
        Board x(1, 1);
        x.addCreature(FOOD, RIGHT, 0, 0);
        CPPUNIT_ASSERT(x._creatures[0].dir == RIGHT);
        CPPUNIT_ASSERT(x._creatures[0].counter == 0);
        CPPUNIT_ASSERT(x._creatures[0].hadturn == false);
        CPPUNIT_ASSERT(x._grid[0][0].type == FOOD);
        CPPUNIT_ASSERT(x._grid[0][0].cr_index == 0);
    }

    void test_addCreature_2 () {
        Board x(3, 3);
        x.addCreature(HOPPER, LEFT, 1, 2);
        CPPUNIT_ASSERT(x._creatures[0].dir == LEFT);
        CPPUNIT_ASSERT(x._creatures[0].counter == 0);
        CPPUNIT_ASSERT(x._creatures[0].hadturn == false);
        CPPUNIT_ASSERT(x._grid[1][2].type == HOPPER);
        CPPUNIT_ASSERT(x._grid[1][2].cr_index == 0);
    }

    void test_addCreature_3 () {
        Board x(5, 5);
        x.addCreature(TRAP, UP, 1, 1);
        x.addCreature(ROVER, DOWN, 3, 3);
        CPPUNIT_ASSERT(x._creatures[0].dir == UP);
        CPPUNIT_ASSERT(x._creatures[0].counter == 0);
        CPPUNIT_ASSERT(x._creatures[0].hadturn == false);
        CPPUNIT_ASSERT(x._grid[1][1].type == TRAP);
        CPPUNIT_ASSERT(x._grid[1][1].cr_index == 0);
        
        CPPUNIT_ASSERT(x._creatures[1].dir == DOWN);
        CPPUNIT_ASSERT(x._creatures[1].counter == 0);
        CPPUNIT_ASSERT(x._creatures[1].hadturn == false);
        CPPUNIT_ASSERT(x._grid[3][3].type == ROVER);
        CPPUNIT_ASSERT(x._grid[3][3].cr_index == 1);
    }

    // ----------
    // test_addWall
    // ----------

    void test_addWall_1 () {
        Board x(1, 1);
        x.addWall(0, 0);
        CPPUNIT_ASSERT(x._grid[0][0].type == WALL);
    }

    void test_addWall_2 () {
        Board x(5, 5);
        x.addWall(2, 3);
        CPPUNIT_ASSERT(x._grid[2][3].type == WALL);
    }

    void test_addWall_3 () {
        Board x(1, 7);
        x.addWall(0, 4);
        CPPUNIT_ASSERT(x._grid[0][4].type == WALL);
    }


    // ----------
    // test_simulate
    // ----------
    void test_simulate_1 () {
        std::ostringstream w, w2, gb;
        Board x(1, 1);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  0\n0 .\n\n");
        x.simulate(5, 100, gb);
        x.print(w2);
        CPPUNIT_ASSERT(w2.str() == "Turn = 5.\n  0\n0 .\n\n");
    }

    void test_simulate_2 () {
        std::ostringstream w, w2, gb;
        Board x(2, 2);
        x.addWall(0, 0);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  01\n0 w.\n1 ..\n\n");
        x.simulate(3, 100, gb);
        x.print(w2);
        CPPUNIT_ASSERT(w2.str() == "Turn = 3.\n  01\n0 w.\n1 ..\n\n");
    }

    void test_simulate_3 () {
        std::ostringstream w, w2, gb;
        Board x(2, 3);
        x.addCreature(HOPPER, LEFT, 0, 2);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  012\n0 ..h\n1 ...\n\n");
        x.simulate(2, 100, gb);
        x.print(w2);
        CPPUNIT_ASSERT(w2.str() == "Turn = 2.\n  012\n0 h..\n1 ...\n\n");
    }

    // ----------
    // test_update
    // ----------
    void test_update_1 () {
        std::ostringstream w, w2;
        Board x(1, 1);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  0\n0 .\n\n");
        x.update();
        x.print(w2);
        CPPUNIT_ASSERT(w2.str() == "Turn = 1.\n  0\n0 .\n\n");
    }

    void test_update_2 () {
        std::ostringstream w, w2;
        Board x(2, 2);
        x.addCreature(FOOD, LEFT, 0, 0);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  01\n0 f.\n1 ..\n\n");
        x.update();
        x.print(w2);
        CPPUNIT_ASSERT(w2.str() == "Turn = 1.\n  01\n0 f.\n1 ..\n\n");
    }

    void test_update_3 () {
        std::ostringstream w, w2;
        Board x(2, 3);
        x.addCreature(HOPPER, LEFT, 1, 2);
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  012\n0 ...\n1 ..h\n\n");
        x.update();
        x.update();
        x.print(w2);
        CPPUNIT_ASSERT(w2.str() == "Turn = 2.\n  012\n0 ...\n1 h..\n\n");
    }

    // ----------
    // test_creature
    // ----------

    void test_creature_1 () {
        Creature x(FOOD, LEFT);
        CPPUNIT_ASSERT(x.spc.programSize() == 2);
        CPPUNIT_ASSERT(x.dir == LEFT);
        CPPUNIT_ASSERT(x.counter == 0);
        CPPUNIT_ASSERT(x.hadturn == false);}

    void test_creature_2 () {
        Creature x(HOPPER, RIGHT);
        CPPUNIT_ASSERT(x.spc.programSize() == 2);
        CPPUNIT_ASSERT(x.dir == RIGHT);
        CPPUNIT_ASSERT(x.counter == 0);
        CPPUNIT_ASSERT(x.hadturn == false);}

    void test_creature_3 () {
        Creature x(ROVER, DOWN);
        CPPUNIT_ASSERT(x.spc.programSize() == 11);
        CPPUNIT_ASSERT(x.dir == DOWN);
        CPPUNIT_ASSERT(x.counter == 0);
        CPPUNIT_ASSERT(x.hadturn == false);}

    // ----------
    // test_programSize
    // ----------

    void test_programSize_1 () {
        Species x;
        x.makeFood();
        CPPUNIT_ASSERT(x.programSize() == 2);}

    void test_programSize_2 () {
        Species x;
        x.makeHopper();
        CPPUNIT_ASSERT(x.programSize() == 2);}

    void test_programSize_3 () {
        Species x;
        x.makeRover();
        CPPUNIT_ASSERT(x.programSize() == 11);}

    // ----------
    // test_getInstruction
    // ----------

    void test_getInstruction_1 () {
        Species x;
        x.makeFood();
        CPPUNIT_ASSERT(x.getInstruction(0).instr == FACE_LEFT);}

    void test_getInstruction_2 () {
        Species x;
        x.makeHopper();
        CPPUNIT_ASSERT(x.getInstruction(1).instr == GO);
        CPPUNIT_ASSERT(x.getInstruction(1).val == 0);}

    void test_getInstruction_3 () {
        Species x;
        x.makeRover();
        CPPUNIT_ASSERT(x.getInstruction(4).instr == GO);
        CPPUNIT_ASSERT(x.getInstruction(4).val == 0);}

    // ----------
    // test_maketests
    // ----------

    void test_makeFood () {
        Species x;
        x.makeFood();
        CPPUNIT_ASSERT(x.programSize() == 2);
        CPPUNIT_ASSERT(x.getInstruction(0).instr == FACE_LEFT);}

    void test_makeHopper () {
        Species x;
        x.makeHopper();
        CPPUNIT_ASSERT(x.programSize() == 2);
        CPPUNIT_ASSERT(x.getInstruction(1).instr == GO);
        CPPUNIT_ASSERT(x.getInstruction(1).val == 0);}

    void test_makeRover () {
        Species x;
        x.makeRover();
        CPPUNIT_ASSERT(x.programSize() == 11);
        CPPUNIT_ASSERT(x.getInstruction(4).instr == GO);
        CPPUNIT_ASSERT(x.getInstruction(4).val == 0);}

    void test_makeTrap () {
        Species x;
        x.makeTrap();
        CPPUNIT_ASSERT(x.programSize() == 5);
        CPPUNIT_ASSERT(x.getInstruction(4).instr == GO);
        CPPUNIT_ASSERT(x.getInstruction(4).val == 0);}

    void test_makeBest () {
        Species x;
        x.makeBest();
        CPPUNIT_ASSERT(x.programSize() == 12);
        CPPUNIT_ASSERT(x.getInstruction(4).instr == FACE_LEFT);}


    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_board_1);
    CPPUNIT_TEST(test_board_2);
    CPPUNIT_TEST(test_board_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_board_3);
    CPPUNIT_TEST(test_addCreature_1);
    CPPUNIT_TEST(test_addCreature_2);
    CPPUNIT_TEST(test_addCreature_3);
    CPPUNIT_TEST(test_addWall_1);
    CPPUNIT_TEST(test_addWall_2);
    CPPUNIT_TEST(test_addWall_3);
    CPPUNIT_TEST(test_simulate_1);
    CPPUNIT_TEST(test_simulate_2);
    CPPUNIT_TEST(test_simulate_3);
    CPPUNIT_TEST(test_update_1);
    CPPUNIT_TEST(test_update_2);
    CPPUNIT_TEST(test_update_3);
    CPPUNIT_TEST(test_creature_1);
    CPPUNIT_TEST(test_creature_2);
    CPPUNIT_TEST(test_creature_3);
    CPPUNIT_TEST(test_programSize_1);
    CPPUNIT_TEST(test_programSize_2);
    CPPUNIT_TEST(test_programSize_3);
    CPPUNIT_TEST(test_getInstruction_1);
    CPPUNIT_TEST(test_getInstruction_2);
    CPPUNIT_TEST(test_getInstruction_3);
    CPPUNIT_TEST(test_makeFood);
    CPPUNIT_TEST(test_makeHopper);
    CPPUNIT_TEST(test_makeRover);
    CPPUNIT_TEST(test_makeTrap);
    CPPUNIT_TEST(test_makeBest);

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