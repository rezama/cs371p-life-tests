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
#include "darwin.h"

char direction( int i ){
	if(i == 0){
		return 'w';
	}else if (i == 1){
		return 'n';
	}else if (i == 2){
		return 'e';
	}else if (i == 3){
		return 's';
	}
	return 'a';

}

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ----
    // food
    // ----

	Species food('f');
	food.add_inst("left");
	food.add_inst("go");
	
//	std::cout << food._sInst[0] << " " << food._sInst[1] << std::endl;
//	std::cout << food._iInst[0] << " " << food._iInst[1] << std::endl;
	

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

	Species hopper('h');
	hopper.add_inst("hop");
	hopper.add_inst("go");

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

	Species rover('r');
	rover.add_inst("if_enemy", 9);
	rover.add_inst("if_empty", 7);
	rover.add_inst("if_random", 5);
	rover.add_inst("left");
	rover.add_inst("go");
	rover.add_inst("right");
	rover.add_inst("go");
	rover.add_inst("hop");
	rover.add_inst("go");
	rover.add_inst("infect");
	rover.add_inst("go");

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



	// -----
    // best
    // -----

	Species best('b');
	best.add_inst("if_enemy", 9);
	best.add_inst("if_empty", 7);
	best.add_inst("if_random", 5);
	best.add_inst("right");
	best.add_inst("go");
	best.add_inst("left");
	best.add_inst("go");
	best.add_inst("hop");
	best.add_inst("go");
	best.add_inst("infect");
	best.add_inst("go");

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

	Species trap('t');
	trap.add_inst("if_enemy", 3);
	trap.add_inst("left");
	trap.add_inst("go");
	trap.add_inst("infect");
	trap.add_inst("go");

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
 			srand(0);
			Grid g(8, 8);
			g.place(&food, 'e', 0, 0);
			g.place(&hopper, 'n', 3, 3);
			g.place(&hopper, 'e', 3, 4);
			g.place(&hopper, 's', 4, 4);
			g.place(&hopper, 'w', 4, 3);
			g.place(&food, 'n', 7, 7);
			g.simulate(5);
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

		Grid g(7, 9);
		g.place(&trap, 's', 0, 0);
		g.place(&hopper, 'e', 3, 2);
		g.place(&rover, 'n', 5, 4);
		g.place(&trap, 'w', 5, 7);
		g.simulate(5);
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
        Print every 100th grid
        */
		
		Grid g(72, 72);

		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&food, dir, x, y);	
		}
		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&hopper, dir, x, y);	
		}
		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&rover, dir, x, y);	
		}
		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&trap, dir, x, y);	
		}
		g.simulate(1000, 100);

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
		Grid g(72, 72);

		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&best, dir, x, y);	
		}

		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&food, dir, x, y);	
		}
		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&hopper, dir, x, y);	
		}
		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&rover, dir, x, y);	
		}
		for(unsigned int i = 0; i < 10; i++){
			unsigned int p = rand() % 5184;
			int d = rand() % 4;
			unsigned int x, y, count;
			x = y = count = 0;
			for (int j = 0; j < 72; j++) {
				for (int k = 0; k < 72; k++) {
					if (count++ == p) {
						x = j;
						y = k;
					}
				}
			}
			char dir = direction(d);
			g.place(&trap, dir, x, y);	
		}
		g.simulate(1000, 100);

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
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
			Grid g(1,1);
 			srand(0);
			g.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 2x2 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
			Grid g(2,2);
 			srand(0);
			g.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 4x4 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
			Grid g(4,4);
 			srand(0);
			g.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Trap 2x2 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
			Grid g(2,2);
 			srand(0);
			g.place(&trap, 's', 0, 0);
			g.place(&food, 's', 1, 0);
			g.place(&food, 'n', 0, 1);
			g.place(&trap, 'n', 1, 1);
			g.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	try {
        cout << "*** Trap 5x5 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
		Grid g(5,5);
 		srand(0);
		for(unsigned int x = 0; x < 5; x++){
			g.place(&trap, 'w', 0, x);
			g.place(&hopper, 's', 1, x);
			g.place(&trap, 'n', 2, x);
			g.place(&hopper, 's', 3, x);
			g.place(&trap, 'e', 4, x);
		}
		g.simulate(5);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	try {
        cout << "*** Hopper 5x5 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
		Grid g(5,5);
 		srand(0);
		for(unsigned int x = 0; x < 5; x++){
			g.place(&hopper, 'w', 0, x);
			g.place(&hopper, 's', 1, x);
			g.place(&hopper, 'n', 2, x);
			g.place(&hopper, 's', 3, x);
			g.place(&hopper, 'e', 4, x);
		}
		g.simulate(5);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	try {
        cout << "*** Rover 5x5 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
		Grid g(5,5);
 		srand(0);
		g.place(&rover, 'w', 2, 3);
		g.simulate(5);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


	try {
        cout << "*** Best 5x5 ***" << endl;
       
        /*
        1x1 Grid
        Simulate 5 moves.
        Print every grid.
        */
		Grid g(5,5);
 		srand(0);
		g.place(&best, 'w', 2, 3);
		g.simulate(5);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
