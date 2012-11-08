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
typedef DarwinWorld::Creature Creature;
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
        
        DarwinWorld world1(8,8,5,1);
        Creature food1 (0, 0, EAST, FOOD, &world1);
        Creature hopper1 (3, 3, NORTH, HOPPER, &world1);
        Creature hopper2 (3, 4, EAST, HOPPER, &world1);
        Creature hopper3 (4, 4, SOUTH, HOPPER, &world1);
        Creature hopper4 (4, 3, WEST, HOPPER, &world1);
        Creature food2 (7, 7, NORTH, FOOD, &world1);
        
        world1.run();
        
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
        DarwinWorld world1(7,9,5,1);
        Creature trap1 (0, 0, SOUTH, TRAP, &world1);
        Creature hopper1 (3, 2, EAST, HOPPER, &world1);
		  Creature rover1 (5, 4, NORTH, ROVER, &world1);
		  Creature trap2 (6, 8, WEST, TRAP, &world1);
        world1.run();
        

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
		  DarwinWorld world1(72,72,1000, 100);
		  int pos;
		  pos = rand()%5184;
		  Creature food1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;

		  Creature hopper1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);

		  pos = rand()%5184;
		  Creature trap1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);

		  pos = rand()%5184;
		  Creature rover1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);

        world1.run();
        
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
		  DarwinWorld world1(72,72,1000, 100);
		  int pos;
		  pos = rand()%5184;
		  Creature food1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;
		  Creature food10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), FOOD, &world1);
		  pos = rand()%5184;

		  Creature hopper1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);
		  pos = rand()%5184;
		  Creature hopper10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), HOPPER, &world1);

		  pos = rand()%5184;
		  Creature trap1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);
		  pos = rand()%5184;
		  Creature trap10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), TRAP, &world1);

		  pos = rand()%5184;
		  Creature rover1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);
		  pos = rand()%5184;
		  Creature rover10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), ROVER, &world1);

		  pos = rand()%5184;
		  Creature best1(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best2(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%184;
		  Creature best3(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best4(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best5(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best6(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best7(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best8(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best9(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);
		  pos = rand()%5184;
		  Creature best10(pos/72, pos%72, static_cast<compassDirection>(rand()%4), BEST, &world1);


        world1.run();
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