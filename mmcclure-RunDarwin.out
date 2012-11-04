// -----------------------------
// Modeled after
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
//
// Modified for the purpose of CS371P Project #5
// Matthew McClure
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin
    % valgrind RunDarwin.c++ > RunDarwin.out

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

    // -----------------
    // #1 darwin 1x1
    // -----------------
    try {
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);
        Grid s = Grid(1, 1);
        s.place(FOOD, 'e', 0, 0);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #2 darwin 3x1
    // -----------------
    try {
        cout << "*** Darwin 3x1 ***" << endl;
        srand(0);
        Grid s = Grid(3, 1);
        s.place(FOOD,  'e', 0, 0);
        s.place(HOPPER,'e', 1, 0);
        s.place(ROVER, 'e', 2, 0);        
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #3 darwin 2x2
    // -----------------
    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);
        Grid s = Grid(2, 2);
        s.place(ROVER,  'n', 0, 0);
        s.place(ROVER,  's', 1, 1);
        s.place(HOPPER, 'w', 0, 1);
        s.place(FOOD,   's', 1, 0);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #4 darwin 2x2
    // -----------------
    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);
        Grid s = Grid(2, 2);
        s.place(ROVER,  's', 0, 0);
        s.place(HOPPER, 'e', 1, 0);
        s.place(FOOD,   'e', 1, 1);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // -----------------
    // #5 darwin 2x2 AVOIDANCE
    // -----------------
    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);
        Grid s = Grid(2, 2);
        s.place(ROVER,  's', 0, 1);
        s.place(HOPPER, 'w', 1, 1);
        s.place(HOPPER, 'n', 1, 0);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // -----------------
    // #6 darwin 256x256
    // -----------------
    try {
        cout << "*** Darwin 256x256 ***" << endl;
        srand(0);
        Grid s = Grid(256, 256);
        s.place(HOPPER, 's', 0, 0);
        s.place(ROVER,  'n', 1, 0);
        s.place(TRAP,   'w', 1, 1);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #7 darwin 3x9
    // -----------------
    try {
        cout << "*** Darwin 3x9 ***" << endl;
        srand(0);
        Grid s = Grid(3, 9);
        s.place(HOPPER, 's', 0, 0);
        s.place(HOPPER, 'w', 0, 1);
        s.place(HOPPER, 's', 0, 2);
        s.place(HOPPER, 'w', 0, 3);
        s.place(ROVER,  's', 1, 0);
        s.place(TRAP,   'w', 1, 1);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #8 darwin 4x4
    // -----------------
    try {
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);
        Grid s = Grid(4, 4);
        s.place(FOOD,   's', 2, 0);
        s.place(FOOD,   'w', 2, 1);
        s.place(HOPPER, 's', 0, 2);
        s.place(HOPPER, 'w', 0, 3);
        s.place(ROVER,  's', 1, 0);
        s.place(TRAP,   'w', 1, 1);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // -----------------
    // #9 darwin 7x7
    // -----------------
    try {
        cout << "*** Darwin 7x7 ***" << endl;
        srand(0);
        Grid s = Grid(7, 7);
        s.place(FOOD,   's', 2, 0);
        s.place(FOOD,   'w', 2, 1);
        s.place(HOPPER, 's', 0, 2);
        s.place(HOPPER, 'w', 0, 3);
        s.place(ROVER,  's', 1, 0);
        s.place(TRAP,   'w', 1, 1);
        s.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #10 darwin 5x5
    // -----------------
    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        Grid s = Grid(5, 5);
        s.randPlace(FOOD, 23);
        s.randPlace(ROVER, 1);
        s.randPlace(TRAP, 1);
        s.simulate(25, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------------
    // #11 darwin 15x14
    // -----------------
    try {
        cout << "*** Darwin 15x14 ***" << endl;
        srand(0);
        Grid s = Grid(15, 14);
        s.randPlace(FOOD, 48);
        s.randPlace(ROVER, 1);
        s.simulate(49, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

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
        Grid s = Grid(8, 8);
        
        s.place(FOOD,   'e', 0, 0);
        s.place(HOPPER, 'n', 3, 3);
        s.place(HOPPER, 'e', 3, 4);
        s.place(HOPPER, 's', 4, 4);
        s.place(HOPPER, 'w', 4, 3);
        s.place(FOOD,   'n', 7, 7);
        s.simulate(5, 1);
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
        Grid s = Grid(7, 9);

        s.place(TRAP,   's', 0, 0);
        s.place(HOPPER, 'e', 3, 2);
        s.place(ROVER,  'n', 5, 4);
        s.place(TRAP,   'w', 6, 8);
        
        s.simulate(5, 1);
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
        Grid s = Grid(72, 72);

        s.randPlace(FOOD, 10);
		s.randPlace(HOPPER, 10);
		s.randPlace(ROVER, 10);
		s.randPlace(TRAP, 10);
        
        s.simulate(1000, 100);
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
        Grid s = Grid(72, 72);
        
		s.randPlace(FOOD, 10);
		s.randPlace(HOPPER, 10);
		s.randPlace(ROVER, 10);
		s.randPlace(TRAP, 10);
		s.randPlace(BEST, 10);
        
        s.simulate(1000, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
