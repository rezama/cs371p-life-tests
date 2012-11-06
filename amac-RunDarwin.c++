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

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

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
        Controller c(8, 8);
        c.place(SpeciesType::FOOD  , 2, 0, 0);
        c.place(SpeciesType::HOPPER, 1, 3, 3);
        c.place(SpeciesType::HOPPER, 2, 3, 4);
        c.place(SpeciesType::HOPPER, 3, 4, 4);
        c.place(SpeciesType::HOPPER, 0, 4, 3);
        c.place(SpeciesType::FOOD  , 1, 7, 7);

        c.start(5, 1);
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

        Controller c(7, 9);
        c.place(SpeciesType::TRAP  , 3, 0, 0);
        c.place(SpeciesType::HOPPER, 2, 3, 2);
        c.place(SpeciesType::ROVER, 1, 5, 4);
        c.place(SpeciesType::TRAP, 0, 6, 8);

        c.start(5, 1);
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
        Controller c(72, 72);
        c.place(SpeciesType::FOOD, 10);
        c.place(SpeciesType::HOPPER, 10);
        c.place(SpeciesType::ROVER, 10);
        c.place(SpeciesType::TRAP, 10);

        c.start(1000, 100);
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
        Controller c(72, 72);
        c.place(SpeciesType::FOOD, 10);
        c.place(SpeciesType::HOPPER, 10);
        c.place(SpeciesType::ROVER, 10);
        c.place(SpeciesType::TRAP, 10);
        c.place(SpeciesType::BEST, 10);

        c.start(1000, 100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 9x7 ***" << endl;
        srand(0);
        Controller c(9, 7);
        c.place(SpeciesType::TRAP  , 3, 1, 1);
        c.place(SpeciesType::HOPPER, 1, 2, 2);
        c.place(SpeciesType::ROVER, 1, 4, 4);
        c.place(SpeciesType::TRAP, 0, 2, 5);
        c.place(SpeciesType::FOOD, 0, 0, 0);
        c.place(SpeciesType::ROVER, 2, 6, 5);

        c.start(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 10x10 ***" << endl;
        srand(0);
        Controller c(10, 10);
        c.place(SpeciesType::FOOD, 4);
        c.place(SpeciesType::HOPPER, 3);
        c.place(SpeciesType::ROVER, 2);
        c.place(SpeciesType::TRAP, 2);
        c.place(SpeciesType::BEST, 2);

        c.start(100, 20);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        Controller c(5, 5);
        c.place(SpeciesType::TRAP, 3, 0, 0);
        c.place(SpeciesType::TRAP, 0, 4, 4);
        c.place(SpeciesType::HOPPER, 2, 3, 2);
        c.place(SpeciesType::BEST, 2, 4, 4);
        c.place(SpeciesType::FOOD, 2, 2, 2);

        c.start(10, 2);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        Controller c(5, 5);
        c.place(SpeciesType::TRAP, 3, 0, 0);
        c.place(SpeciesType::HOPPER, 0, 0, 4);

        c.start(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 50x50 ***" << endl;
        srand(0);
        Controller c(50, 50);
        c.place(SpeciesType::FOOD, 20);
        c.place(SpeciesType::HOPPER, 20);
        c.place(SpeciesType::BEST, 5);
        c.place(SpeciesType::TRAP, 10);

        c.start(1000, 200);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 20x5 ***" << endl;
        srand(0);
        Controller c(20, 5);
        c.place(SpeciesType::FOOD, 5);
        c.place(SpeciesType::HOPPER, 7);
        c.place(SpeciesType::BEST, 2);
        c.place(SpeciesType::TRAP, 4);

        c.start(100, 25);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}