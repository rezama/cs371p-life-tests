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

    Controller controller;
    
    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    vector<vector<int> > foodProgram(2);
    foodProgram[0] = {LEFT, -1};
    foodProgram[1] = {GO, 0};
    const Species food(foodProgram, 'f');

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    vector<vector<int> > hopperProgram(2);
    hopperProgram[0] = {HOP, -1};
    hopperProgram[1] = {GO, 0};
    const Species hopper(hopperProgram, 'h');

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
    vector<vector<int> > roverProgram(11);
      roverProgram[0] = { IF_ENEMY, 9};
      roverProgram[1] = { IF_EMPTY, 7};
      roverProgram[2] = { IF_RANDOM, 5};
      roverProgram[3] = { LEFT, -1};
      roverProgram[4] = { GO, 0};
      roverProgram[5] = { RIGHT, -1};
      roverProgram[6] = { GO, 0};
      roverProgram[7] = { HOP, -1};
      roverProgram[8] = { GO, 0};
      roverProgram[9] = { INFECT, -1};
      roverProgram[10] = { GO, 0};
    const Species rover(roverProgram, 'r');

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
    vector<vector<int> > trapProgram(5);
    trapProgram[0] = { IF_ENEMY, 3};
    trapProgram[1] = { LEFT, -1};
    trapProgram[2] = { GO, 0};
    trapProgram[3] = { INFECT, -1};
    trapProgram[4] = { GO, 0};
    const Species trap(trapProgram, 't');
 
    // ----
    // best
    // ----
    /*
      0)        if enemy 6
      1)        if empty 4
      2)        left
      3)        go 0
      4)        hop
      5)        go 0
      6)        infect
      7)        go 2
    */
    vector<vector<int> > bestProgram(8);
    bestProgram[0] = { IF_ENEMY, 6 };
    bestProgram[1] = { IF_EMPTY, 4 };
    bestProgram[2] = { LEFT, -1 };
    bestProgram[3] = { GO, 0 };
    bestProgram[4] = { HOP, -1 };
    bestProgram[5] = { GO, 0 };
    bestProgram[6] = { INFECT, -1 };
    bestProgram[7] = { GO, 2 };
    const Species best(bestProgram, 'b');

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

        controller.makeGrid(8,8);
        controller.placeCreature(&food, EAST, 0, 0);
        controller.placeCreature(&hopper, NORTH, 3, 3);
        controller.placeCreature(&hopper, EAST, 3, 4);
        controller.placeCreature(&hopper, SOUTH, 4, 4);
        controller.placeCreature(&hopper, WEST, 4, 3);
        controller.placeCreature(&food, NORTH, 7, 7);
        controller.run(5, 1); // 5 moves, print every frame
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
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (3, 2)
        Rover,  facing north, at (5, 4)
        Trap,   facing west,  at (6, 8)
        Simulate 5 moves.
        Print every grid.
        */

        srand(0);
        controller.makeGrid(7,9);
        controller.placeCreature(&trap, SOUTH, 0, 0);
        controller.placeCreature(&hopper, EAST, 3, 2);
        controller.placeCreature(&rover, NORTH, 5, 4);
        controller.placeCreature(&trap, WEST, 6, 8);
        controller.run(5, 1); // 5 moves, print every frame

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
        controller.makeGrid(72, 72);
        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&food, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&hopper, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&rover, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&trap, d, p / 72, p % 72);
        }
        controller.run(1000, 100);
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

        controller.makeGrid(72, 72);
        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&food, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&hopper, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&rover, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&trap, d, p / 72, p % 72);
        }

        for (int i = 0; i < 10; ++i) {
          int p = rand() % 5184;
          Direction d = (Direction) (rand() % 4);
          controller.placeCreature(&best, d, p / 72, p % 72);
        }

        controller.run(1000, 100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
