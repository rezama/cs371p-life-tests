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
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <cstdlib>   // rand, srand
#include <ctime>
#include "./Darwin.h"
#include "./Darwin.h"

// ----
// main
// ----

Species makeFood() {
    // ----
    // food
    // ----
    /*
     0: left
     1: go 0
     */
    Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");

    return food;
}

Species makeHopper() {
    // ------
    // hopper
    // ------
    /*
     0: hop
     1: go 0
     */
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

    return hopper;
}

Species makeTrap() {
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
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    return trap;
}

Species makeRover() {
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
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop ");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");

    return rover;
}

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O

    // ----
    // food
    // ----
    /*
     0: left
     1: go 0
     */
    Species food("food");
    food.addInstruction("left");
    food.addInstruction("go 0");

    // ------
    // hopper
    // ------
    /*
     0: hop
     1: go 0
     */
    Species hopper("hopper");
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");

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
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop ");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");

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
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    Species* spec_array[] = { &food, &hopper, &rover, &trap };
//    Species* spec_array[] = { &food, &hopper, &rover, &trap, &best };

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

        World w(8, 8);
        w.addCreature( { 0, 0 }, Creature(food, EAST));
        w.addCreature( { 3, 3 }, Creature(hopper, NORTH));
        w.addCreature( { 3, 4 }, Creature(hopper, EAST));
        w.addCreature( { 4, 4 }, Creature(hopper, SOUTH));
        w.addCreature( { 4, 3 }, Creature(hopper, WEST));
        w.addCreature( { 7, 7 }, Creature(food, NORTH));

        w.display(cout);
        for (int i = 0; i < 5; ++i) {  // display next 5 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // --------------
    // darwin 8x8 (2)
    // --------------

    try {
        cout << "*** Darwin 8x8 (2) ***" << endl;
        /*
         8x8 Darwin
         Trap,   facing south, at (1, 1)
         Trap,   facing north, at (3, 1)
         Trap,   facing east, at (5, 1)
         Trap,   facing west, at (7, 1)
         Rover,  facing west, at (1, 6)
         Rover,  facing west, at (3, 6)
         Rover,  facing west, at (5, 6)
         Rover,  facing west, at (7, 6)

         Simulate 5 moves.
         Print every grid.
         */

        World w(8, 8);
        w.addCreature( { 1, 1 }, Creature(trap, SOUTH));
        w.addCreature( { 3, 1 }, Creature(trap, NORTH));
        w.addCreature( { 5, 1 }, Creature(trap, EAST));
        w.addCreature( { 7, 1 }, Creature(trap, WEST));
        w.addCreature( { 1, 6 }, Creature(rover, WEST));
        w.addCreature( { 3, 6 }, Creature(rover, WEST));
        w.addCreature( { 5, 6 }, Creature(rover, WEST));
        w.addCreature( { 7, 6 }, Creature(rover, WEST));

        w.display(cout);
        for (int i = 0; i < 5; ++i) {  // display next 5 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // --------------
    // darwin 8x8 (3)
    // --------------

    try {
        cout << "*** Darwin 8x8 (3) ***" << endl;
        /*
         8x8 Darwin
         Trap,   facing south, at (1, 6)
         Trap,   facing north, at (3, 6)
         Trap,   facing east, at (5, 6)
         Trap,   facing west, at (7, 6)
         Rover,  facing east, at (1, 1)
         Rover,  facing east, at (3, 1)
         Rover,  facing east, at (5, 1)
         Rover,  facing east, at (7, 1)

         Simulate 4 moves.
         Print every grid.
         */

        World w(8, 8);
        w.addCreature( { 1, 6 }, Creature(trap, SOUTH));
        w.addCreature( { 3, 6 }, Creature(trap, NORTH));
        w.addCreature( { 5, 6 }, Creature(trap, EAST));
        w.addCreature( { 7, 6 }, Creature(trap, WEST));
        w.addCreature( { 1, 1 }, Creature(rover, EAST));
        w.addCreature( { 3, 1 }, Creature(rover, EAST));
        w.addCreature( { 5, 1 }, Creature(rover, EAST));
        w.addCreature( { 7, 1 }, Creature(rover, EAST));

        w.display(cout);
        for (int i = 0; i < 4; ++i) {  // display next 4 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

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

        World w(7, 9);
        w.addCreature( { 0, 0 }, Creature(trap, SOUTH));
        w.addCreature( { 3, 2 }, Creature(hopper, EAST));
        w.addCreature( { 5, 4 }, Creature(rover, NORTH));
        w.addCreature( { 6, 8 }, Creature(trap, WEST));

        w.display(cout);
        for (int i = 0; i < 5; ++i) {  // display next 5 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ----------
    // darwin 3x3
    // ----------

    try {
        cout << "*** Darwin 3x3 ***" << endl;
        /*
         3x3 Darwin
         Rover,  facing east, at (0, 0)

         Simulate 10 moves.
         Print every grid.
         */

        World w(3, 3);
        w.addCreature( { 0, 0 }, Creature(rover, EAST));

        w.display(cout);
        for (int i = 0; i < 10; ++i) {  // display next 10 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // --------------
    // darwin 3x3 (2)
    // --------------

    try {
        cout << "*** Darwin 3x3 (2) ***" << endl;
        /*
         3x3 Darwin
         Trap,  facing east, at (1, 1)
         Food,  facing east, at (1, 0)
         Food,  facing east, at (1, 2)
         Food,  facing east, at (0, 1)
         Food,  facing east, at (2, 1)

         Simulate 7 moves.
         Print every grid.
         */

        World w(3, 3);
        w.addCreature( { 1, 1 }, Creature(trap, EAST));
        w.addCreature( { 1, 0 }, Creature(food, EAST));
        w.addCreature( { 1, 2 }, Creature(food, EAST));
        w.addCreature( { 0, 1 }, Creature(food, EAST));
        w.addCreature( { 2, 1 }, Creature(food, EAST));

        w.display(cout);
        for (int i = 0; i < 7; ++i) {  // display next 7 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ----------
    // darwin 5x5
    // ----------

    try {
        cout << "*** Darwin 5x5 ***" << endl;
        /*
         5x5 Darwin
         Trap,  facing east, at (2, 2)
         Hopper,  facing east, at (2, 0)
         Hopper,  facing west, at (2, 4)
         Hopper,  facing south, at (0, 2)
         Hopper,  facing north, at (4, 2)


         Simulate 8 moves.
         Print every grid.
         */

        World w(5, 5);
        w.addCreature( { 2, 2 }, Creature(trap, EAST));
        w.addCreature( { 2, 0 }, Creature(hopper, EAST));
        w.addCreature( { 2, 4 }, Creature(hopper, WEST));
        w.addCreature( { 0, 2 }, Creature(hopper, SOUTH));
        w.addCreature( { 4, 2 }, Creature(hopper, NORTH));

        w.display(cout);
        for (int i = 0; i < 8; ++i) {  // display next 8 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ------------
    // darwin 10x10
    // ------------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
        /*
         10x10 Darwin
         Hopper,  facing east, at (0, 0)
         Hopper,  facing east, at (1, 0)
         Hopper,  facing east, at (2, 0)
         Hopper,  facing east, at (3, 0)
         Hopper,  facing east, at (4, 0)
         Hopper,  facing south, at (0, 5)
         Hopper,  facing south, at (0, 6)
         Hopper,  facing south, at (0, 7)
         Hopper,  facing south, at (0, 8)
         Hopper,  facing south, at (0, 9)

         Simulate 10 moves.
         Print every grid.
         */

        World w(10, 10);
        w.addCreature( { 0, 0 }, Creature(hopper, EAST));
        w.addCreature( { 1, 0 }, Creature(hopper, EAST));
        w.addCreature( { 2, 0 }, Creature(hopper, EAST));
        w.addCreature( { 3, 0 }, Creature(hopper, EAST));
        w.addCreature( { 4, 0 }, Creature(hopper, EAST));
        w.addCreature( { 0, 5 }, Creature(hopper, SOUTH));
        w.addCreature( { 0, 6 }, Creature(hopper, SOUTH));
        w.addCreature( { 0, 7 }, Creature(hopper, SOUTH));
        w.addCreature( { 0, 8 }, Creature(hopper, SOUTH));
        w.addCreature( { 0, 9 }, Creature(hopper, SOUTH));

        w.display(cout);
        for (int i = 0; i < 10; ++i) {  // display next 10 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ----------
    // darwin 4x4
    // ----------

    try {
        cout << "*** Darwin 4x4 ***" << endl;
        /*
         4x4 Darwin



         Simulate 5 moves.
         Print every grid.
         */

        World w(4, 4);
        w.addCreature( { 3, 3 }, Creature(rover, WEST));
        w.addCreature( { 3, 1 }, Creature(food, SOUTH));
        w.addCreature( { 3, 0 }, Creature(trap, NORTH));
        w.addCreature( { 0, 1 }, Creature(trap, SOUTH));

        w.display(cout);
        for (int i = 0; i < 5; ++i) {  // display next 5 steps
            w.execute();
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ------------
    // darwin 72x72
    // without best
    // ------------

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
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
        srand(0);
        World w(72, 72);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 10; ++j) {
                int pos = rand() % (72 * 72);
                w.addCreature(Coordinate(pos / 72, pos % 72),
                              Creature(*(spec_array[i]), rand() % 4));
            }
        }

        w.display(cout);
        for (int i = 0; i < 1000; i += 100) {
            w.execute(100);
            w.display(cout);
        }
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
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
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

    return 0;
}
