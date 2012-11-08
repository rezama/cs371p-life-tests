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
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
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
        Board game(8, 8);
        game.addCreature(FOOD, RIGHT, 0, 0);
        game.addCreature(HOPPER, UP, 3, 3);
        game.addCreature(HOPPER, RIGHT, 3, 4);
        game.addCreature(HOPPER, DOWN, 4, 4);
        game.addCreature(HOPPER, LEFT, 4, 3);
        game.addCreature(FOOD, UP, 7, 7);
        game.simulate(5);
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
        srand(0);
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */
        Board game(7, 9);
        game.addCreature(TRAP, DOWN, 0, 0);
        game.addCreature(HOPPER, RIGHT, 3, 2);
        game.addCreature(ROVER, UP, 5, 4);
        game.addCreature(TRAP, LEFT, 6, 8);
        game.simulate(5);
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
        Board game(72, 72);

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(FOOD, LEFT, row, col);
            else if (randdir == 1) game.addCreature(FOOD, UP, row, col);
            else if (randdir == 2) game.addCreature(FOOD, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(FOOD, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(HOPPER, LEFT, row, col);
            else if (randdir == 1) game.addCreature(HOPPER, UP, row, col);
            else if (randdir == 2) game.addCreature(HOPPER, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(HOPPER, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(ROVER, LEFT, row, col);
            else if (randdir == 1) game.addCreature(ROVER, UP, row, col);
            else if (randdir == 2) game.addCreature(ROVER, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(ROVER, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(TRAP, LEFT, row, col);
            else if (randdir == 1) game.addCreature(TRAP, UP, row, col);
            else if (randdir == 2) game.addCreature(TRAP, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(TRAP, DOWN, row, col);
        }

        game.simulate(1000, 100);

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
        Board game(72, 72);

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(FOOD, LEFT, row, col);
            else if (randdir == 1) game.addCreature(FOOD, UP, row, col);
            else if (randdir == 2) game.addCreature(FOOD, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(FOOD, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(HOPPER, LEFT, row, col);
            else if (randdir == 1) game.addCreature(HOPPER, UP, row, col);
            else if (randdir == 2) game.addCreature(HOPPER, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(HOPPER, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(ROVER, LEFT, row, col);
            else if (randdir == 1) game.addCreature(ROVER, UP, row, col);
            else if (randdir == 2) game.addCreature(ROVER, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(ROVER, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(TRAP, LEFT, row, col);
            else if (randdir == 1) game.addCreature(TRAP, UP, row, col);
            else if (randdir == 2) game.addCreature(TRAP, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(TRAP, DOWN, row, col);
        }

        for (int i=0; i<10; ++i) {
            int randpos = rand()%5184;
            int row = randpos/72, col = randpos%72;
            int randdir = rand()%4;
            if (randdir == 0) game.addCreature(BEST, LEFT, row, col);
            else if (randdir == 1) game.addCreature(BEST, UP, row, col);
            else if (randdir == 2) game.addCreature(BEST, RIGHT, row, col);
            else if (randdir == 3) game.addCreature(BEST, DOWN, row, col);
        }

        game.simulate(1000, 100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);
        Board game(1, 1);
        game.simulate(3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x10
    // ----------

    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);
        Board game(1, 10);
        game.simulate(3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 11x1
    // ----------

    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);
        Board game(11, 1);
        game.simulate(3);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 4x5 Long Game
    // ----------

    try {
        cout << "*** Darwin 4x5 Long Game ***" << endl;
        srand(0);
        Board game(4, 5);
        game.addCreature(FOOD, RIGHT, 0, 0);
        game.addCreature(HOPPER, UP, 3, 3);
        game.simulate(500, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3 Rover Food
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);
        Board game(3, 3);
        game.addCreature(FOOD, UP, 0, 0);
        game.addCreature(FOOD, UP, 1, 0);
        game.addCreature(ROVER, LEFT, 2, 2);
        game.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3 Best Food
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        srand(0);
        Board game(3, 3);
        game.addCreature(FOOD, UP, 0, 0);
        game.addCreature(FOOD, UP, 1, 0);
        game.addCreature(BEST, LEFT, 2, 2);
        game.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}