// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind RunDarwin.c++.app > RunDarwin.out

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

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <sstream>  // istringtstream, ostringstream
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

    Species food("f");
    food.add_instruction("left");
    food.add_instruction("go", 0);

    // ------
    // hopper
    // ------

    Species hopper("h");
    hopper.add_instruction("hop");
    hopper.add_instruction("go", 0);

    // -----
    // rover
    // -----

    Species rover("r");
    rover.add_instruction("if_enemy", 9);
    rover.add_instruction("if_empty", 7);
    rover.add_instruction("if_random", 5);
    rover.add_instruction("left");
    rover.add_instruction("go", 0);
    rover.add_instruction("right");
    rover.add_instruction("go", 0);
    rover.add_instruction("hop");
    rover.add_instruction("go", 0);
    rover.add_instruction("infect");
    rover.add_instruction("go", 0);

    // ----
    // trap
    // ----

    Species trap("t");
    trap.add_instruction("if_enemy", 3);
    trap.add_instruction("left");
    trap.add_instruction("go", 0);
    trap.add_instruction("infect");
    trap.add_instruction("go", 0);

    // ----
    // best
    // ----

    Species best("b");
    best.add_instruction("if_enemy", 6);
    best.add_instruction("if_empty", 4);
    best.add_instruction("left");
    best.add_instruction("go", 0);
    best.add_instruction("hop");
    best.add_instruction("go", 0);
    best.add_instruction("infect");
    best.add_instruction("go", 0);
    

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;

        Creature food1(food, 2);
        Creature hopper1(hopper, 1);
        Creature hopper2(hopper, 2);
        Creature hopper3(hopper, 3);
        Creature hopper4(hopper, 0);
        Creature food2(food, 1);
        Grid grid1(8, 8);
        grid1.add_creature(food1, 0, 0);
        grid1.add_creature(hopper1, 3, 3);
        grid1.add_creature(hopper2, 3, 4);
        grid1.add_creature(hopper3, 4, 4);
        grid1.add_creature(hopper4, 4, 3);
        grid1.add_creature(food2, 7, 7);
        cout << grid1.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid1.step();
          cout << grid1.print_grid();
        }
        /*
        8x8 Darwin
        Food,   facing east,  at (0, 0)
        Hopper, facing north, at (3, 3)
        Hopper, facing east,  at (3, 4)
        Hopper, facing south, at (4, 4)
        Hopper, facing west,  at (4, 3)
        Food,   facing north, at (7, 7)
        Simulate 5 moves.
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    try {
        cout << "*** Darwin 7x9 ***" << endl;

        Creature trap1(trap, 3);
        Creature hopper1(hopper, 2);
        Creature rover1(rover, 1);
        Creature trap2(trap, 0);
        Grid grid2(7, 9);
        grid2.add_creature(trap1, 0, 0);
        grid2.add_creature(hopper1, 3, 2);
        grid2.add_creature(rover1, 5, 4);
        grid2.add_creature(trap2, 6, 8);
        cout << grid2.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid2.step();
          cout << grid2.print_grid();
        }
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);

        Grid grid3(72, 72);
        for (int a = 0; a < 10; a++) {
          int pos = rand();
          Creature creature(food, rand() % 4);
          grid3.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int b = 0; b < 10; b++) {
          int pos = rand();
          Creature creature(hopper, rand() % 4);
          grid3.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int c = 0; c < 10; c++) {
          int pos = rand();
          Creature creature(rover, rand() % 4);
          grid3.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int d = 0; d < 10; d++) {
          int pos = rand();
          Creature creature(trap, rand() % 4);
          grid3.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        cout << grid3.print_grid();
        for (int e = 1; e < 1001; ++e) {
          grid3.step();
          if (e % 100 == 0)
            cout << grid3.print_grid();
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        Simulate 1000 moves.
        Print every 100th grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);

        Grid grid4(72, 72);
        for (int a = 0; a < 10; a++) {
          int pos = rand();
          Creature creature(food, rand() % 4);
          grid4.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int b = 0; b < 10; b++) {
          int pos = rand();
          Creature creature(hopper, rand() % 4);
          grid4.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int c = 0; c < 10; c++) {
          int pos = rand();
          Creature creature(rover, rand() % 4);
          grid4.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int d = 0; d < 10; d++) {
          int pos = rand();
          Creature creature(trap, rand() % 4);
          grid4.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        for (int f = 0; f < 10; f++) {
          int pos = rand();
          Creature creature(best, rand() % 4);
          grid4.add_creature(creature, pos % 5184 / 72, pos % 5184 % 72);
        }
        cout << grid4.print_grid();
        for (int e = 1; e < 1001; ++e) {
          grid4.step();
          if (e % 100 == 0)
            cout << grid4.print_grid();
        }
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 5184 (72x72), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        10 Food
        10 Hopper
        10 Rover
        10 Trap
        10 Best
        Simulate 1000 moves.
        Best MUST outnumber ALL other species for the bonus pts.
        Print every 100th grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 1 x 1
    // ------------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);

        Grid grid(1, 1);
        grid.add_creature(Creature(food, 0), 0, 0);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(food, 0), 0, 0);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(hopper, 2), 0, 0);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(hopper, 0), 0, 0);
        grid.add_creature(Creature(hopper, 0), 0, 0);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(hopper, 0), 0, 0);
        grid.add_creature(Creature(food, 0), 1, 0);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(hopper, 0), 0, 0);
        grid.add_creature(Creature(hopper, 2), 1, 1);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(rover, 0), 0, 0);
        grid.add_creature(Creature(hopper, 2), 1, 1);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(rover, 0), 0, 0);
        grid.add_creature(Creature(food, 2), 1, 0);
        grid.add_creature(Creature(food, 2), 0, 1);
        grid.add_creature(Creature(food, 2), 1, 1);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 2 x 2
    // ------------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

        Grid grid(2, 2);
        grid.add_creature(Creature(rover, 0), 0, 0);
        grid.add_creature(Creature(food, 2), 1, 0);
        grid.add_creature(Creature(hopper, 2), 0, 1);
        grid.add_creature(Creature(food, 2), 1, 1);
        cout << grid.print_grid();
        for (int a = 0; a < 5; ++a) {
          grid.step();
          cout << grid.print_grid();
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
