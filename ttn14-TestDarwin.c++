// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
 To run the program:
 % g++ -pedantic -std=c++0x -Wall TestDarwin.c++ -o TestDarwin.c++.app
 % valgrind TestDarwin.c++.app >& TestDarwin.out

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
#include <iostream>
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner
#include "Darwin.h"

using namespace std;
struct TestDarwin : CppUnit::TestFixture {

    void test_blank_board() {
        Board testBoard(1, 1);
        string state = testBoard.to_string();
        CPPUNIT_ASSERT( state == ".\n");
    }

    void test_species() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');

        CPPUNIT_ASSERT(hopper.inst(0) == "hop");
        CPPUNIT_ASSERT(hopper.inst(1) == "go");
    }

    void test_place() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        CPPUNIT_ASSERT(testBoard.view(5, 5) == 'h');
        CPPUNIT_ASSERT(testBoard.view(4, 4) == '.');
    }

    void test_place2() {
        bool caught = false;

        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        try {
            testBoard.place(testHopper, 10, 10);
        } catch (invalid_argument& e) {
            caught = true;
        }
        CPPUNIT_ASSERT(caught);
    }

    void test_place3() {
        bool caught = false;

        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        try {
            testBoard.place(testHopper, -1, -1);
        } catch (invalid_argument& e) {
            caught = true;
        }
        CPPUNIT_ASSERT(caught);
    }

    void test_hop_1() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 2);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 9, 9);
        testBoard.run();
        CPPUNIT_ASSERT(testBoard.view(9, 9) == 'h');
    }

    void test_hop_2() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 2);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.run();
        CPPUNIT_ASSERT(testBoard.view(5, 5) == '.');
        CPPUNIT_ASSERT(testBoard.view(5, 6) == 'h');
    }

    void test_hop_3() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.run(4);
        CPPUNIT_ASSERT(testBoard.view(5, 5) == '.');
        CPPUNIT_ASSERT(testBoard.view(4, 5) == '.');
        CPPUNIT_ASSERT(testBoard.view(3, 5) == '.');
        CPPUNIT_ASSERT(testBoard.view(2, 5) == '.');
        CPPUNIT_ASSERT(testBoard.view(1, 5) == 'h');
    }

    void test_left_1() {
        vector<string> foodProg;
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testHopper(food, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);

        CPPUNIT_ASSERT(testHopper.direction() == 1);

    }

    void test_left_2() {
        vector<string> foodProg;
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testHopper(food, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);

        CPPUNIT_ASSERT(testBoard[5][5].direction() == 1);
        testBoard.run();
        CPPUNIT_ASSERT(testBoard[5][5].direction() == 0);
    }

    void test_left_3() {
        vector<string> foodProg;
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testHopper(food, 3);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        CPPUNIT_ASSERT(testHopper.direction() == 3);
        for (int i = 2; i >= 0; --i) {
            testBoard.run();
            CPPUNIT_ASSERT(testBoard[5][5].direction() == i);
        }
    }

    void test_right_1() {
        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testHopper(food, 0);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        for (int i = 0; i <= 3; ++i) {
            CPPUNIT_ASSERT(testBoard[5][5].direction() == i);
            testBoard.run();
        }
        CPPUNIT_ASSERT(testBoard[5][5].direction() == 0);
    }

    void test_right_left() {
        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testHopper(food, 2);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        CPPUNIT_ASSERT(testHopper.direction() == 2);
        for (int i = 1; i <= 4; ++i) {
            testBoard.run(2);
            CPPUNIT_ASSERT(testBoard[5][5].direction() == 2);
        }
    }

    void test_right_left_right() {
        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("left");
        foodProg.push_back("right");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testHopper(food, 0);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        CPPUNIT_ASSERT(testHopper.direction() == 0);
        for (int i = 1; i <= 3; ++i) {
            testBoard.run(3);
            CPPUNIT_ASSERT(testBoard[5][5].direction() == i);
        }
    }

    void test_if_wall_1() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 2);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 9, 9);
        testBoard.run();
        CPPUNIT_ASSERT(testBoard.view(9, 9) == 'h');
    }

    void test_if_wall_2() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 0, 9);
        testBoard.run();
        CPPUNIT_ASSERT(testBoard.view(0, 9) == 'h');
    }

    void test_if_wall_3() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 0);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 9, 0);
        testBoard.run();
        CPPUNIT_ASSERT(testBoard.view(9, 0) == 'h');
    }

    void test_if_empty_1() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.place(testHopper, 6, 5);
        CPPUNIT_ASSERT(!testBoard.if_empty(6, 5, testHopper, -1));
        CPPUNIT_ASSERT(testBoard.if_empty(5, 5, testHopper, -1));
    }

    void test_if_empty_2() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Creature testHopper2(hopper, 3);
        Board testBoard(10, 10);

        testBoard.place(testHopper, 5, 5);
        testBoard.place(testHopper2, 1, 5);
        testBoard.run(3);

        CPPUNIT_ASSERT(testBoard.view(3, 5) == 'h');
        CPPUNIT_ASSERT(testBoard.view(4, 5) == 'h');

    }

    void test_if_empty_3() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Creature testHopper2(hopper, 2);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.place(testHopper2, 2, 2);
        testBoard.run(50);

        CPPUNIT_ASSERT(testBoard.view(0, 5) == 'h');
        CPPUNIT_ASSERT(testBoard.view(2, 9) == 'h');
    }

    void test_if_enemy_1() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.place(testHopper, 6, 5);
        CPPUNIT_ASSERT(!testBoard.if_enemy(6, 5, testHopper, -1));
        CPPUNIT_ASSERT(!testBoard.if_enemy(5, 5, testHopper, -1));
    }

    void test_if_enemy_2() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");
        Species hopper(hopperprog, "Hopper", 'h');
        Creature testHopper(hopper, 1);

        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testFood(food, 1);

        Board testBoard(10, 10);
        testBoard.place(testFood, 5, 5);
        testBoard.place(testHopper, 6, 5);

        CPPUNIT_ASSERT(testBoard.if_enemy(6, 5, testHopper, -1));
        CPPUNIT_ASSERT(!testBoard.if_enemy(5, 5, testFood, -1));
    }

    void test_if_enemy_3() {

        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');
        Creature testFood(food, 2);

        Board testBoard(10, 10);
        testBoard.place(testFood, 0, 0);
        testBoard.place(testFood, 1, 1);
        testBoard.place(testFood, 0, 1);
        testBoard.place(testFood, 1, 0);

        CPPUNIT_ASSERT(!testBoard.if_enemy(0, 0, testFood, -1));
    }

    void test_infect_1() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("infect");
        hopperprog.push_back("go 0");

        Species hopper(hopperprog, "Hopper", 'h');

        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("left");
        foodProg.push_back("go 0");

        Species food(foodProg, "Food", 'f');

        Creature testHopper(hopper, 2);
        Creature testFood(food, 2);

        Board testBoard(1, 2);

        testBoard.place(testHopper, 0, 0);
        testBoard.place(testFood, 0, 1);
        testBoard.run(2);

        CPPUNIT_ASSERT(testBoard.view(0, 0) == 'h');
        CPPUNIT_ASSERT(testBoard.view(0, 1) == 'h');
    }

    void test_infect_2() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("infect");
        hopperprog.push_back("go 0");

        Species hopper(hopperprog, "Hopper", 'h');

        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');

        Creature testHopper(hopper, 1);
        Creature testFood(food, 2);
        Board testBoard(5, 1);
        testBoard.place(testHopper, 4, 0);
        testBoard.place(testFood, 1, 0);

        testBoard.run(4);

        CPPUNIT_ASSERT(testBoard.view(1, 0) == 'h');
        CPPUNIT_ASSERT(testBoard.view(2, 0) == 'h');
    }

    void test_infect_3() {
        vector<string> hopperprog;
        hopperprog.push_back("if_enemy 2");
        hopperprog.push_back("hop");
        hopperprog.push_back("infect");
        hopperprog.push_back("go 0");

        Species hopper(hopperprog, "Hopper", 'h');

        vector<string> foodProg;
        foodProg.push_back("right");
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species food(foodProg, "Food", 'f');

        Creature testHopper(hopper, 2);
        Creature testFood(food, 2);
        Board testBoard(1, 5);

        testBoard.place(testHopper, 0, 0);
        testBoard.place(testFood, 0, 3);
        testBoard.run(4, false);
        CPPUNIT_ASSERT(testBoard.view(0, 3) == 'h');
        CPPUNIT_ASSERT(testBoard.view(0, 2) == 'h');
    }

    void test_trap_1() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");

        Species hopper(hopperprog, "Hopper", 'h');

        vector<string> trapProg;
        trapProg.push_back("if_enemy 3");
        trapProg.push_back("left");
        trapProg.push_back("go 0");
        trapProg.push_back("infect");
        trapProg.push_back("go 0");
        Species trap(trapProg, "Trapper", 't');

        Creature testHopper(hopper, 1);
        Creature testTrap(trap, 2);

        Board testBoard(10, 10);

        testBoard.place(testHopper, 3, 5);
        testBoard.place(testTrap, 2, 5);

        testBoard.run(4, false);
        CPPUNIT_ASSERT(testBoard.view(2, 5) == 't');
        CPPUNIT_ASSERT(testBoard.view(3, 5) == 't');
    }

    void test_trap_2() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");

        Species hopper(hopperprog, "Hopper", 'h');
        /*
         0: if_enemy 3
         1: left
         2: go 0
         3: infect
         4: go 0
         */
        vector<string> trapProg;
        trapProg.push_back("if_enemy 3");
        trapProg.push_back("left");
        trapProg.push_back("go 0");
        trapProg.push_back("infect");
        trapProg.push_back("go 0");
        Species trap(trapProg, "Trapper", 't');

        Creature testHopper(hopper, 1);
        Creature testHopper2(hopper, 2);
        Creature testHopper3(hopper, 3);
        Creature testHopper4(hopper, 0);

        Creature testTrap(trap, 2);

        Board testBoard(10, 10);

        testBoard.place(testHopper, 5, 5);
        testBoard.place(testTrap, 2, 5);
        testBoard.place(testHopper2, 2, 4);
        testBoard.place(testHopper3, 1, 5);
        testBoard.place(testHopper4, 2, 6);

        testBoard.run(7, false);

        CPPUNIT_ASSERT(testBoard.view(1, 5) == 't');
        CPPUNIT_ASSERT(testBoard.view(2, 4) == 't');
        CPPUNIT_ASSERT(testBoard.view(2, 5) == 't');
        CPPUNIT_ASSERT(testBoard.view(2, 6) == 't');
        CPPUNIT_ASSERT(testBoard.view(3, 5) == 't');
    }

    void test_trap_3() {
        vector<string> hopperprog;
        hopperprog.push_back("hop");
        hopperprog.push_back("go 0");

        Species hopper(hopperprog, "Hopper", 'h');

        vector<string> trapProg;
        trapProg.push_back("if_enemy 3");
        trapProg.push_back("left");
        trapProg.push_back("go 0");
        trapProg.push_back("infect");
        trapProg.push_back("go 0");
        Species trap(trapProg, "Trapper", 't');

        Creature testHopper(hopper, 1);
        Creature testHopper2(hopper, 2);
        Creature testHopper3(hopper, 3);
        Creature testHopper4(hopper, 0);

        Creature testTrap(trap, 2);

        Board testBoard(10, 10);

        testBoard.place(testHopper, 5, 5);
        testBoard.place(testTrap, 2, 5);
        testBoard.place(testHopper2, 1, 5);
        testBoard.place(testHopper3, 2, 4);
        testBoard.place(testHopper4, 2, 6);

        testBoard.run(6, false);

        CPPUNIT_ASSERT(testBoard.view(2, 5) == 't');
        CPPUNIT_ASSERT(testBoard.view(2, 6) == 't');
        CPPUNIT_ASSERT(testBoard.view(3, 5) == 't');
    }

    void test_if_random_1() {
        vector<string> foodProg;
        foodProg.push_back("if_random 2");
        foodProg.push_back("right");
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species hopper(foodProg, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.run(1);
        int dir = testBoard[5][5].direction();
        CPPUNIT_ASSERT(dir == 2 || dir == 0);
    }

    void test_if_random_2() {
        vector<string> foodProg;
        foodProg.push_back("if_random 2");
        foodProg.push_back("hop");
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species hopper(foodProg, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.run(1);

        bool hopped = testBoard.view(4, 5) == 'h';
        int dir;
        if (hopped)
            dir = testBoard[4][5].direction();
        else
            dir = testBoard[5][5].direction();
        CPPUNIT_ASSERT( hopped || dir == 0);
    }

    void test_if_random_3() {
        vector<string> foodProg;
        foodProg.push_back("if_random 3");
        foodProg.push_back("if_empty 2");
        foodProg.push_back("hop");
        foodProg.push_back("left");
        foodProg.push_back("go 0");
        Species hopper(foodProg, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        testBoard.run(1);
        int dir = testBoard[5][5].direction();
        CPPUNIT_ASSERT(dir == 2 || dir == 0);
    }

    void test_go_1() {
        vector<string> hopperProg;
        hopperProg.push_back("if_random 1");
        hopperProg.push_back("go 0");
        Species hopper(hopperProg, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        bool catched = false;
        try {
            testBoard.run(1);
        } catch (invalid_argument& arg) {
            catched = true;
        }
        CPPUNIT_ASSERT(catched);
    }

    void test_go_2() {
        vector<string> hopperProg;
        hopperProg.push_back("go 0");
        Species hopper(hopperProg, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        bool catched = false;
        try {
            testBoard.run(1);
        } catch (invalid_argument& arg) {
            catched = true;
        }
        CPPUNIT_ASSERT(catched);
    }

    void test_go_3() {
        vector<string> hopperProg;
        hopperProg.push_back("go 1");
        hopperProg.push_back("if_random 0");
        Species hopper(hopperProg, "Hopper", 'h');
        Creature testHopper(hopper, 1);
        Board testBoard(10, 10);
        testBoard.place(testHopper, 5, 5);
        bool catched = false;
        try {
            testBoard.run(1);
        } catch (invalid_argument& arg) {
            catched = true;
        }
        CPPUNIT_ASSERT(catched);
    }

    void test_type_1() {
        Species food = Species::food();
        CPPUNIT_ASSERT( food.type() == 'f');
    }
    void test_type_2() {
        CPPUNIT_ASSERT( Species::hopper().type() == 'h');
    }
    void test_type_3() {
        CPPUNIT_ASSERT( Species::rover().type() == 'r');
    }

    void test_inst_1() {
        Species food = Species::food();
        CPPUNIT_ASSERT(food.inst(0) == "left");
        CPPUNIT_ASSERT(food.inst(1) == "go");
    }

    void test_inst_2() {
        Species hopper = Species::hopper();
        CPPUNIT_ASSERT(hopper.inst(0) == "hop");
        CPPUNIT_ASSERT(hopper.inst(1) == "go");
    }

    void test_inst_3() {
        Species trap = Species::trap();
        CPPUNIT_ASSERT(trap.inst(0) == "if_enemy");
        CPPUNIT_ASSERT(trap.inst(1) == "left");
        CPPUNIT_ASSERT(trap.inst(2) == "go");
        CPPUNIT_ASSERT(trap.inst(3) == "infect");
        CPPUNIT_ASSERT(trap.inst(4) == "go");
    }

    void test_num_1() {
        Species trap = Species::trap();
        CPPUNIT_ASSERT(trap.num(0) == 3);
        CPPUNIT_ASSERT(trap.num(2) == 0);
        CPPUNIT_ASSERT(trap.num(4) == 0);
    }

    void test_num_2() {
        Species rover = Species::rover();
        CPPUNIT_ASSERT(rover.num(0) == 9);
        CPPUNIT_ASSERT(rover.num(1) == 7);
        CPPUNIT_ASSERT(rover.num(2) == 5);
        CPPUNIT_ASSERT(rover.num(4) == 0);
    }

    void test_num_3() {
        Species best = Species::best();
        CPPUNIT_ASSERT(best.num(0) == 7);
        CPPUNIT_ASSERT(best.num(1) == 5);
        CPPUNIT_ASSERT(best.num(2) == 3);
        CPPUNIT_ASSERT(best.num(4) == 0);
    }

    void test_prog_size_1(){
        Species food = Species::food();
        CPPUNIT_ASSERT(food.prog_size() == 2);
    }

    void test_prog_size_2(){
        Species rover = Species::rover();
        CPPUNIT_ASSERT(rover.prog_size() == 11);
    }

    void test_prog_size_3(){
        Species best = Species::best();
        CPPUNIT_ASSERT(best.prog_size() == 9);
    }

CPPUNIT_TEST_SUITE(TestDarwin);
        CPPUNIT_TEST( test_blank_board);
        CPPUNIT_TEST( test_species);

        CPPUNIT_TEST( test_place);
        CPPUNIT_TEST( test_place2);
        CPPUNIT_TEST( test_place3);

        CPPUNIT_TEST( test_hop_1);
        CPPUNIT_TEST( test_hop_2);
        CPPUNIT_TEST( test_hop_3);

        CPPUNIT_TEST( test_left_1);
        CPPUNIT_TEST( test_left_2);
        CPPUNIT_TEST( test_left_3);

        CPPUNIT_TEST( test_right_1);
        CPPUNIT_TEST( test_right_left);
        CPPUNIT_TEST( test_right_left_right);

        CPPUNIT_TEST( test_infect_1);
        CPPUNIT_TEST( test_infect_2);
        CPPUNIT_TEST( test_infect_3);

        CPPUNIT_TEST( test_trap_1);
        CPPUNIT_TEST( test_trap_2);
        CPPUNIT_TEST( test_trap_3);

        CPPUNIT_TEST( test_if_wall_1);
        CPPUNIT_TEST( test_if_wall_2);
        CPPUNIT_TEST( test_if_wall_3);

        CPPUNIT_TEST( test_if_empty_1);
        CPPUNIT_TEST( test_if_empty_2);
        CPPUNIT_TEST( test_if_empty_3);

        CPPUNIT_TEST( test_if_enemy_1);
        CPPUNIT_TEST( test_if_enemy_2);
        CPPUNIT_TEST( test_if_enemy_3);

        CPPUNIT_TEST( test_if_random_1);
        CPPUNIT_TEST( test_if_random_2);
        CPPUNIT_TEST( test_if_random_3);

        CPPUNIT_TEST( test_go_1);
        CPPUNIT_TEST( test_go_2);
        CPPUNIT_TEST( test_go_3);

        CPPUNIT_TEST( test_type_1);
        CPPUNIT_TEST( test_type_2);
        CPPUNIT_TEST( test_type_3);
        CPPUNIT_TEST( test_inst_1);
        CPPUNIT_TEST( test_inst_2);
        CPPUNIT_TEST( test_inst_3);
        CPPUNIT_TEST( test_num_1);
        CPPUNIT_TEST( test_num_2);
        CPPUNIT_TEST( test_num_3);
        CPPUNIT_TEST( test_prog_size_1);
        CPPUNIT_TEST( test_prog_size_2);
        CPPUNIT_TEST( test_prog_size_3);
    CPPUNIT_TEST_SUITE_END();
};

int main() {
    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();
    cout << "Done!";
}
