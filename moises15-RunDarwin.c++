// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind RunDarwin.c++.app >& RunDarwin.out

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
    */try {
        cout << "*** Darwin 9x7 ***" << endl;
        srand(0);
        Grid grid(9, 7);
        grid.place("trap", EAST, 1, 1);
        grid.place("hop", NORTH, 2, 2);
        grid.place("rover", NORTH, 4, 4);
        grid.place("trap", WEST, 2, 5);
        grid.place("food", WEST, 0, 0);
        grid.place("rover", EAST, 6, 5);
        grid.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

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
        Grid grid(8,8);
        grid.place("food",EAST,0,0);
        grid.place("hop",NORTH,3,3);
        grid.place("hop",EAST,3,4);
        grid.place("hop",SOUTH,4,4);
        grid.place("hop",WEST,4,3);
        grid.place("food",NORTH,7,7);
        grid.simulate(5,1);
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
        srand(0);
        Grid grid(7,9);
        grid.place("trap",SOUTH,0,0);
        grid.place("hop",EAST,3,2);
        grid.place("rover",NORTH,5,4);
        grid.place("trap",WEST,6,8);
        grid.simulate(5,1);
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
    
    try {
        cout << "*** Darwin 9x7 ***" << endl;
        srand(0);
        Grid grid(9, 7);
        grid.place("trap", EAST, 1, 1);
        grid.place("hop", NORTH, 2, 2);
        grid.place("rover", NORTH, 4, 4);
        grid.place("trap", WEST, 2, 5);
        grid.place("food", WEST, 0, 0);
        grid.place("rover", EAST, 6, 5);
        grid.simulate(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    try {
        cout << "*** Darwin 5x5 ***" << endl;
        srand(0);
        Grid grid(5, 5);
        grid.place("trap", EAST, 0, 0);
        grid.place("hop", NORTH, 0, 4);

        grid.simulate(5, 1);
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
        Grid grid(72,72);
        string to_place[4] = {"food","hop","rover","trap"};
        for(int x=0;x<4;x++)
        {    
            for(int amount=0;amount<10;amount++)
            {
                int row = rand()%72;
                int col = rand()%72;
                int direction = rand()%4;
                while(!grid.place(to_place[x],direction,row,col))
                {
                    row = rand()%72;
                    col = rand()%72;
                    direction = rand()%4;
                }
            }
        }
        grid.simulate(1000,100);
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
        Grid grid(72,72);
        string to_place[5] = {"food","hop","rover","trap","best"};
        for(int x=0;x<5;x++)
        {    
            for(int amount=0;amount<10;amount++)
            {
                int row = rand()%72;
                int col = rand()%72;
                int direction = rand()%4;
                while(!grid.place(to_place[x],direction,row,col))
                {
                    row = rand()%72;
                    col = rand()%72;
                    direction = rand()%4;
                }
            }
        }
        grid.simulate(1000,100);
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

    return 0;}
