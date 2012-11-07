// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunCollatz.c++ -o RunCollatz.c++.app
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
    Species food("food");
    food.add(LEFT);
    food.add(GO,0);

    // ------
    // hopper
    // ------
    /*
     0: hop
     1: go 0
    */
     Species hopper("hopper");
     hopper.add(HOP);
     hopper.add(GO,0);

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
     Species rover("rover");
     rover.add(IF_ENEMY,9);
     rover.add(IF_EMPTY,7);
     rover.add(IF_RANDOM,5);
     rover.add(LEFT);
     rover.add(GO,0);
     rover.add(RIGHT);
     rover.add(GO,0);
     rover.add(HOP);
     rover.add(GO,0);
     rover.add(INFECT);
     rover.add(GO,0);

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
    Species trap("trap");
    trap.add(IF_ENEMY,3);
    trap.add(LEFT);
    trap.add(GO,0);
    trap.add(INFECT);
    trap.add(GO,0);

    // ----
    // best
    // ----
    /*
    0 if enemy 7
    1 if wall 3
    2 if empty 5
    3 left
    4 go 0
    5 hop
    6 go 0
    7 infect
    8 go 0

     */
    Species best("best");
    best.add(IF_ENEMY,7);
    best.add(IF_WALL,3);
    best.add(IF_EMPTY,5);
    best.add(LEFT);
    best.add(GO,0);
    best.add(HOP);
    best.add(GO,0);
    best.add(INFECT);
    best.add(GO,0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
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
        Darwin d(8,8);
        d.add(  &food,  EAST, 0, 0);
        d.add(&hopper, NORTH, 3, 3);
        d.add(&hopper,  EAST, 3, 4);
        d.add(&hopper, SOUTH, 4, 4);
        d.add(&hopper,  WEST, 4, 3);
        d.add(  &food, NORTH, 7, 7);
        d.run(5);
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
        Darwin d(7,9);
        d.add(  &trap, SOUTH, 0, 0);
        d.add(&hopper,  EAST, 3, 2);
        d.add( &rover, NORTH, 5, 4);
        d.add(  &trap,  WEST, 6, 8);
        d.run(5);
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
        Darwin d(72,72);
        const size_t numToAdd = 10;
        const size_t numTypes = 4;
        const Species* s[] = {&food, &hopper, &rover, &trap};
        for (size_t t = 0; t < numTypes; ++t) {
            for (size_t n = 0; n < numToAdd; ++n) {
                size_t loc = rand() % 5184;
                // size_t dir = rand() % 4;
                d.add(s[t], get_direction(rand() % 4), loc / 72, loc % 72);
            }
        }
        d.run(1000,100);
        d.print_totals();
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
        Darwin d(72,72);
        const size_t numToAdd = 10;
        const size_t numTypes = 5;
        const Species* s[] = {&food, &hopper, &rover, &trap, &best};
        for (size_t t = 0; t < numTypes; ++t) {
            for (size_t n = 0; n < numToAdd; ++n) {
                size_t loc = rand() % 5184;
                // size_t dir = rand() % 4;
                d.add(s[t], get_direction(rand() % 4), loc / 72, loc % 72);
            }
        }
        d.run(1000,100);
        d.print_totals();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 5x1 ***" << endl;
        Darwin d(5,1);
        d.add( &trap, SOUTH, 2, 0);
        d.add(&rover, NORTH, 3, 0);
        d.run();
        d.print_totals();
    } catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 5x1 ***" << endl;
        Darwin d(5,1);
        d.add( &trap, NORTH, 3, 0);
        d.add(&rover, SOUTH, 2, 0);
        d.run();
        d.print_totals();
    } catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 1x5 ***" << endl;
        Darwin d(1,5);
        d.add( &trap, EAST, 0, 2);
        d.add(&rover, WEST, 0, 3);
        d.run();
        d.print_totals();
    } catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 1x5 ***" << endl;
        Darwin d(1,5);
        d.add( &trap, WEST, 0, 3);
        d.add(&rover, EAST, 0, 2);
        d.run();
        d.print_totals();
    } catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        Darwin d(2,2);
        d.add(&rover, SOUTH, 0, 0);
        d.add(&rover, NORTH, 1, 1);
        d.add( &trap,  EAST, 1, 0);
        d.add( &trap,  WEST, 0, 1);
        d.run(5); 
        d.print_totals();
    } catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
