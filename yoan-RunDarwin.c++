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

	Direction table[] = {DIR_WEST, DIR_NORTH, DIR_EAST, DIR_SOUTH};
	
    // ----
    // food
    // ----
    /*
     0: left
     1: go 0
    */
    
	char foodActions[] = {
		OP_LEFT, 0,
		OP_GO, 0
	};
	Species food('f', foodActions, sizeof foodActions);
	
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    
    char hopperActions[] = {
		OP_HOP, 0,
		OP_GO, 0
	};
	Species hopper('h', hopperActions, sizeof hopperActions);

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
    
    char roverActions[] = {
		OP_IF_ENEMY, 9,
		OP_IF_EMPTY, 7,
		OP_IF_RANDOM, 5,
		OP_LEFT, 0,
		OP_GO, 0,
		OP_RIGHT, 0,
		OP_GO, 0,
		OP_HOP, 0,
		OP_GO, 0,
		OP_INFECT, 0,
		OP_GO, 0
	};
	Species rover('r', roverActions, sizeof roverActions);

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
    
    char trapActions[] = {
		OP_IF_ENEMY, 3,
		OP_LEFT, 0,
		OP_GO, 0,
		OP_INFECT, 0,
		OP_GO, 0
	};
	Species trap('t', trapActions, sizeof trapActions);

	// ----
	// best
	// ----
    
	char bestActions[] = {
		OP_IF_RANDOM, 3,	// best at 3 or 19
		OP_IF_RANDOM, 3,
		OP_IF_RANDOM, 19,
		OP_IF_ENEMY, 12,
		OP_IF_EMPTY, 10,
		OP_IF_RANDOM, 8,
		OP_LEFT, 0,
		OP_GO, 3,
		OP_RIGHT, 0,
		OP_GO, 3,
		OP_HOP, 0,
		OP_GO, 3,
		OP_INFECT, 0,
		OP_GO, 3,
		OP_IF_ENEMY, 18,
		OP_LEFT, 0,
		OP_GO, 15,
		OP_INFECT, 0,
		OP_GO, 15,
		OP_IF_ENEMY, 5,
		OP_IF_EMPTY, 7,
		OP_IF_WALL, 10,
		OP_LEFT, 0,
		OP_GO, 0,
		OP_INFECT, 0,
		OP_GO, 0,
		OP_IF_RANDOM, 15,
		OP_IF_RANDOM, 15,
		OP_IF_RANDOM, 13,
		OP_IF_RANDOM, 13,
		OP_LEFT, 0,
		OP_GO, 0,
		OP_RIGHT, 0,
		OP_GO, 0,
		OP_HOP, 0,
		OP_GO, 0
	};
	Species best('b', bestActions, sizeof bestActions);

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
		    
		    Simulation simulation(8,8);
		    
		    simulation.spawn(&food, DIR_EAST, 0, 0);
		    simulation.spawn(&hopper, DIR_NORTH, 3, 3);
		    simulation.spawn(&hopper, DIR_EAST, 3, 4);
		    simulation.spawn(&hopper, DIR_SOUTH, 4, 4);
		    simulation.spawn(&hopper, DIR_WEST, 4, 3);
		    simulation.spawn(&food, DIR_NORTH, 7, 7);
		    
		    for (int i = 0; i <= 5; i++) {
				simulation.print(cout);
		    	simulation.run(1);
		    }
		    
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
		    Simulation simulation(7,9);
		    
		    simulation.spawn(&trap, DIR_SOUTH, 0, 0);
		    simulation.spawn(&hopper, DIR_EAST, 3, 2);
		    simulation.spawn(&rover, DIR_NORTH, 5, 4);
		    simulation.spawn(&trap, DIR_WEST, 6, 8);

		    for (int i = 0; i <= 5; i++) {
				simulation.print(cout);
		    	simulation.run(1);
		    }

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

		    Simulation simulation(72,72);
		    
		    for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&food, table[dir], pos/72, pos%72);
			}

			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&hopper, table[dir], pos/72, pos%72);
			}
			
			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&rover, table[dir], pos/72, pos%72);
			}
			
			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&trap, table[dir], pos/72, pos%72);
			}
		    
		    for (int i = 0; i <= 10; i++) {
				simulation.print(cout);
		    	simulation.run(100);
		    }
		    
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

		    Simulation simulation(72,72);
		    
			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&food, table[dir], pos/72, pos%72);
			}

			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&hopper, table[dir], pos/72, pos%72);
			}
			
			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&rover, table[dir], pos/72, pos%72);
			}
			
			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&trap, table[dir], pos/72, pos%72);
			}
			
			for (int i=0; i < 10; i++) {
				int pos = rand()%5184;
				int dir = rand()%4;
				simulation.spawn(&best, table[dir], pos/72, pos%72);
			}
			
		    for (int i = 0; i <= 10; i++) {
				simulation.print(cout);
		    	simulation.run(100);
		    }
		}
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 4x4
    // ----------

    try {
		    cout << "*** Darwin 4x4 ***" << endl;
		    /*
		    4x4 Darwin
		    Hopper, facing north, at (3, 2)
		    Hopper, facing east,  at (2, 0)
		    Hopper, facing south, at (0, 1)
		    Hopper, facing west,  at (1, 3)
		    Simulate 5 moves.
		    Print every grid.
		    */
		    
		    Simulation simulation(4,4);
		    
		    simulation.spawn(&hopper, DIR_NORTH, 3, 2);
		    simulation.spawn(&hopper, DIR_EAST, 2, 0);
		    simulation.spawn(&hopper, DIR_SOUTH, 0, 1);
		    simulation.spawn(&hopper, DIR_WEST, 1, 3);
		    
		    for (int i = 0; i <= 5; i++) {
				simulation.print(cout);
		    	simulation.run(1);
		    }		    
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 2x2
    // ----------

    try {
		    cout << "*** Darwin 2x2 ***" << endl;
		    /*
		    2x2 Darwin
		    Hopper, facing north, at (0, 1)
		    Hopper, facing east,  at (1, 1)
		    Hopper, facing south, at (1, 0)
		    Hopper, facing west,  at (0, 0)
		    Simulate 5 moves.
		    Print every grid.
		    */
		    
		    Simulation simulation(2,2);
		    
		    simulation.spawn(&hopper, DIR_NORTH, 0, 1);
		    simulation.spawn(&hopper, DIR_EAST, 1, 1);
		    simulation.spawn(&hopper, DIR_SOUTH, 1, 0);
		    simulation.spawn(&hopper, DIR_WEST, 0, 0);
		    
		    for (int i = 0; i <= 5; i++) {
				simulation.print(cout);
		    	simulation.run(1);
		    }	    
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
		    /*
		    1x1 Darwin
		    Rover, facing north, at (0, 0)
		    Simulate 5 moves.
		    Print every grid.
		    */
		    
		    Simulation simulation(1,1);
		    
		    simulation.spawn(&rover, DIR_NORTH, 0, 0);
		    
		    for (int i = 0; i <= 5; i++) {
				simulation.print(cout);
		    	simulation.run(1);
		    }		    
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -----------
    // darwin 1x10
    // -----------

    try {
		    cout << "*** Darwin 1x10 ***" << endl;
		    /*
		    1x10 Darwin
		    Rover, facing north, at (0, 0)
		    Simulate 30 moves.
		    Print every 5th grid.
		    */
		    
		    Simulation simulation(1,10);
		    
		    simulation.spawn(&rover, DIR_NORTH, 0, 0);
		    
		    for (int i = 0; i <= 6; i++) {
				simulation.print(cout);
		    	simulation.run(5);
		    }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x3
    // ----------

    try {
		    cout << "*** Darwin 3x3 ***" << endl;
		    /*
		    3x3 Darwin
		    Trap, facing north, at (1, 1)
		    Food, facing north, at (0, 1)
		    Food, facing east,  at (1, 2)
		    Food, facing south, at (2, 1)
		    Food, facing west,  at (1, 0)
		    Simulate 15 moves.
		    Print every 3rd grid.
		    */
		    
		    Simulation simulation(3,3);
		    
		    simulation.spawn(&trap, DIR_NORTH, 1, 1);
		    simulation.spawn(&food, DIR_NORTH, 0, 1);
		    simulation.spawn(&food, DIR_EAST, 1, 2);
		    simulation.spawn(&food, DIR_SOUTH, 2, 1);
		    simulation.spawn(&food, DIR_WEST, 1, 0);
		    
		    for (int i = 0; i <= 5; i++) {
				simulation.print(cout);
		    	simulation.run(3);
		    }		    
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 25x25
    // ------------

    try {
		    cout << "*** Darwin 25x25 ***" << endl;
		    /*
		    25x25 Darwin
		    Trap, facing north, at (12, 12)
		    Food, facing north, everywhere else
		    Simulate 30 moves.
		    Print every 3rd grid.
		    */
		    
		    Simulation simulation(25,25);
			
		    for (unsigned int r = 0; r < 25; r++) {
				for (unsigned int c = 0; c < 25; c++) {
					simulation.spawn(&food, DIR_NORTH, r, c);
				}
			}
		    simulation.spawn(&trap, DIR_NORTH, 12, 12);

		    for (int i = 0; i <= 10; i++) {
				simulation.print(cout);
		    	simulation.run(3);
		    }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
    
