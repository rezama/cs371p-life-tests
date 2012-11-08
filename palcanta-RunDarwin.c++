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
	Species food(FOOD);
	food.addInstruction(Left);
	food.addInstruction(Go, 0);
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
	Species hopper(HOPPER);	
	hopper.addInstruction(Hop);
	hopper.addInstruction(Go, 0);
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
	Species rover(ROVER);
	rover.addInstruction(IfEnemy, 9);
	rover.addInstruction(IfEmpty, 7);
	rover.addInstruction(IfRandom, 5);
	rover.addInstruction(Left);
	rover.addInstruction(Go, 0);
	rover.addInstruction(Right);
	rover.addInstruction(Go, 0);
	rover.addInstruction(Hop);
	rover.addInstruction(Go, 0);
	rover.addInstruction(Infect);
	rover.addInstruction(Go, 0);

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
	Species trap(TRAP);
	trap.addInstruction(IfEnemy, 3);
	trap.addInstruction(Left);
	trap.addInstruction(Go, 0);
	trap.addInstruction(Infect);
	trap.addInstruction(Go, 0);

    // -----
    // best - my best creature is... ROVER!
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
	Species best(BEST);
	best.addInstruction(IfEnemy, 9);
	best.addInstruction(IfEmpty, 7);
	best.addInstruction(IfRandom, 5);
	best.addInstruction(Left);
	best.addInstruction(Go, 0);
	best.addInstruction(Right);
	best.addInstruction(Go, 0);
	best.addInstruction(Hop);
	best.addInstruction(Go, 0);
	best.addInstruction(Infect);
	best.addInstruction(Go, 0);

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
	srand(0);
	Darwin controller(8,8);
	controller.addCreature(food,   0,0, directionT::EAST);
	controller.addCreature(hopper, 3,3, directionT::NORTH);	
	controller.addCreature(hopper, 3,4, directionT::EAST);
	controller.addCreature(hopper, 4,4, directionT::SOUTH);
	controller.addCreature(hopper, 4,3, directionT::WEST);
	controller.addCreature(food,   7,7, directionT::NORTH);
	controller.goDarwin(5, 1);
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
	Darwin controller(7,9);
	controller.addCreature(trap,   0,0, directionT::SOUTH);
	controller.addCreature(hopper, 3,2, directionT::EAST);
	controller.addCreature(rover,  5,4, directionT::NORTH);
	controller.addCreature(trap,   6,8, directionT::WEST);
	controller.goDarwin(5,1);
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
	Darwin controller(72, 72);
	Species creatures[] = {food, hopper, rover, trap};
	for(int i=0;i<4;i++){
		for(int j=0;j<10;j++){
			int location = rand()%5184;
			int direction = rand()%4;
			controller.addCreature(creatures[i], location/72, location%72, direction);	
		}
	}
	controller.goDarwin(1000,100);
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

	Darwin controller(72, 72);
	Species creatures[] = {food, hopper, rover, trap, best};
	for(int i=0;i<5;i++){
		for(int j=0;j<10;j++){
			int location = rand()%5184;
			int direction = rand()%4;
			controller.addCreature(creatures[i], location/72, location%72, direction);	
		}
	}
	controller.goDarwin(1000,100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 1x1 - Corner Test - 1
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
	srand(0);
	Darwin controller(1,1);
	controller.goDarwin(5, 1);
        /*
        1x1 Darwin
        Simulate 5 moves.
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1 - Corner Test - 2
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
	srand(0);
	Darwin controller(1,1);
	controller.addCreature(hopper,   0,0, directionT::EAST);
	controller.goDarwin(5, 1);
        /*
        1x1 Darwin
        Simulate 5 moves.
	hopper at 0,0 facing EAST
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1 - Corner Test - 3
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
	srand(0);
	Darwin controller(1,1);
	controller.addCreature(rover,   0,0, directionT::EAST);
	controller.goDarwin(5, 1);
        /*
        1x1 Darwin
        Simulate 5 moves.
	rover at 0,0 facing EAST
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // darwin 1x1 - Corner Test - 4
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
	srand(0);
	Darwin controller(1,1);
	controller.addCreature(food,   0,0, directionT::EAST);
	controller.goDarwin(5, 1);
        /*
        1x1 Darwin
        Simulate 5 moves.
	food at 0,0 facing EAST
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1 - Corner Test - 5
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
	srand(0);
	Darwin controller(1,1);
	controller.addCreature(best,   0,0, directionT::EAST);
	controller.goDarwin(5, 1);
        /*
        1x1 Darwin
        Simulate 5 moves.
	best at 0,0 facing EAST
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 2x2 - Test - 6
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
	srand(0);
	Darwin controller(2,2);
	controller.addCreature(trap,   0,0, directionT::EAST);
	controller.addCreature(food,   0,1, directionT::EAST);
	controller.addCreature(food,   1,0, directionT::EAST);
	controller.addCreature(food,   1,1, directionT::EAST);
	controller.goDarwin(5, 1);
        /*
        1x1 Darwin
        Simulate 5 moves.
	trap at 0,0 facing EAST
	food at 0,1 facing EAST
	food at 1,0 facing EAST
	food at 1,1 facing EAST
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 3x2 - Test - 7
    // ----------

    try {
        cout << "*** Darwin 3x2 ***" << endl;
	srand(0);
	Darwin controller(3,2);
	controller.addCreature(trap,   1,1, directionT::EAST);
	controller.addCreature(hopper, 2,1, directionT::NORTH);	
	controller.addCreature(hopper, 2,0, directionT::WEST);
	controller.goDarwin(5, 1);
        /*
        3x2 Darwin
        Simulate 5 moves.
	Trap at 1,1 Facing EAST
	hopper at 2,1 facing NORTH
	hopper at 2,0 facing west
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 2x3 - Test 8
    // ----------

    try {
        cout << "*** Darwin 2x3 ***" << endl;
	srand(0);
	Darwin controller(2,3);
	controller.addCreature(best,   1,1, directionT::EAST);
	controller.addCreature(hopper, 0,0, directionT::NORTH);	
	controller.addCreature(trap, 1,0, directionT::WEST);
	controller.goDarwin(5, 1);
        /*
        2x3 Darwin
        Simulate 5 moves.
	best at 1,1 Facing EAST
	hopper at 2,1 facing NORTH
	trap at 2,0 facing west
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10 - Test 9
    // ----------
    try {
        cout << "*** Darwin 10x10 ***" << endl;
	srand(0);
	Darwin controller(10,10);
	controller.addCreature(trap,   0,0, directionT::EAST);
	controller.addCreature(trap,   9,0, directionT::EAST);
	controller.addCreature(trap,   0,9, directionT::EAST);
	controller.addCreature(trap,   9,9, directionT::EAST);
	controller.addCreature(hopper, 0,5, directionT::WEST);	
	controller.addCreature(hopper, 5,0, directionT::SOUTH);
	controller.goDarwin(10, 1);
        /*
        10x10 Darwin
        Simulate 10 moves.
	Trap at 0,0 Facing EAST
	Trap at 9,0 Facing EAST
	Trap at 0,9 Facing EAST
	Trap at 9,9 Facing EAST
	hopper at 0,5 facing WEST
	hopper at 5,0 facing SOUTH
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10 - Test 10
    // ----------
    try {
        cout << "*** Darwin 10x10 ***" << endl;
	srand(0);
	Darwin controller(10,10);
	controller.addCreature(rover,   0,0, directionT::EAST);
	controller.addCreature(rover,   9,0, directionT::EAST);
	controller.addCreature(rover,   0,9, directionT::EAST);
	controller.addCreature(rover,   9,9, directionT::EAST);
	controller.addCreature(hopper, 0,5, directionT::WEST);	
	controller.addCreature(hopper, 5,0, directionT::SOUTH);
	controller.goDarwin(10, 1);
        /*
        10x10 Darwin
        Simulate 10 moves.
	Rover at 0,0 Facing EAST
	Rover at 9,0 Facing EAST
	Rover at 0,9 Facing EAST
	Rover at 9,9 Facing EAST
	hopper at 0,5 facing WEST
	hopper at 5,0 facing SOUTH
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10 - Test 11
    // ----------
    try {
        cout << "*** Darwin 10x10 ***" << endl;
	srand(0);
	Darwin controller(10,10);
	controller.addCreature(best,   0,0, directionT::EAST);
	controller.addCreature(food,   9,0, directionT::EAST);
	controller.addCreature(rover,   0,9, directionT::EAST);
	controller.addCreature(rover,   9,9, directionT::EAST);
	controller.addCreature(trap, 0,5, directionT::WEST);	
	controller.addCreature(hopper, 5,0, directionT::SOUTH);
	controller.goDarwin(10, 1);
        /*
        10x10 Darwin
        Simulate 10 moves.
	Best at 0,0 Facing EAST
	Food at 9,0 Facing EAST
	Rover at 0,9 Facing EAST
	Rover at 9,9 Facing EAST
	trap at 0,5 facing WEST
	hopper at 5,0 facing SOUTH
        Print every grid.
        */
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    return 0;}
