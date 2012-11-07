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
    species food("f");
    food.add_inst("left", 0);
    food.add_inst("go", 0);
    
    
    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    species hopper("h");
    hopper.add_inst("hop", 0);
    hopper.add_inst("go", 0);

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
    species rover("r");
    rover.add_inst("if_enemy", 9);
    rover.add_inst("if_empty", 7);
    rover.add_inst("if_random", 5);
    rover.add_inst("left", 0);
    rover.add_inst("go", 0);
    rover.add_inst("right", 0);
    rover.add_inst("go", 0);
    rover.add_inst("hop", 0);
    rover.add_inst("go", 0);
    rover.add_inst("infect", 0);
    rover.add_inst("go", 0);
    
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
    species trap("t");
    trap.add_inst("if_enemy", 3);
    trap.add_inst("left", 0);
    trap.add_inst("go", 0);
    trap.add_inst("infect", 0);
    trap.add_inst("go", 0);
    
    // -----
    // best
    // -----
    
    /*
     0: if_enemy 12
     1: if_empty 10
     2: left
     3: if_wall 7
     4: hop
     5: left
     6: go 0
     7: left
     8: left
     9: go 0
     10: hop
     11: go 0
     12: infect
     13: go 0
     */
    species best("b");
    best.add_inst("if_enemy", 9);
    best.add_inst("if_empty", 7);
    best.add_inst("if_random", 5);
    best.add_inst("left", 0);
    best.add_inst("go", 0);
    best.add_inst("right", 0);
    best.add_inst("go", 0);
    best.add_inst("hop", 0);
    best.add_inst("go", 0);
    best.add_inst("infect", 0);
    best.add_inst("go", 0);

    // ----------
    // #1 darwin 8x8
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
        Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &food));
        executor.set_contents(3, 3, creature(enums::north, &hopper));
        executor.set_contents(3, 4, creature(enums::east, &hopper));
        executor.set_contents(4, 4, creature(enums::south, &hopper));
        executor.set_contents(4, 3, creature(enums::west, &hopper));
        executor.set_contents(7, 7, creature(enums::north, &food));
        //executor.print_world();
        executor.run(5, 1);
    }
    catch (const invalid_argument& e) {
        assert(false);}
    catch (const out_of_range& e) {
        assert(false);}

    // ----------
    // #2 darwin 7x9
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
        Darwin executor(7, 9);
        executor.set_contents(0, 0, creature(enums::south, &trap));
        executor.set_contents(3, 2, creature(enums::east, &hopper));
        executor.set_contents(5, 4, creature(enums::north, &rover));
        executor.set_contents(6, 8, creature(enums::west, &trap));
        executor.run(5, 1);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ------------
    // #3 darwin 72x72
    // ------------

    species* spec_array[] = { &food, &hopper, &rover, &trap, &best };
    
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
        Darwin executor(72, 72);
        for (int i=0; i<4; ++i) {
            for (int j=0; j<10; ++j) {
                int pos = rand() % 5184;
                executor.set_contents(pos/72, pos%72, creature(rand()%4, spec_array[i]));
            }
        }
        executor.run(5, 1);
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // #4 darwin 72x72
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
        Darwin executor(72, 72);
        for (int i=0; i<5; ++i) {
            for (int j=0; j<10; ++j) {
                int pos = rand() % 5184;
                executor.set_contents(pos/72, pos%72, creature(rand()%4, spec_array[i]));
            }
        }
        executor.run(1000, 100);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range& e) {
        cerr << e.what();
        assert(false);}
 
    // ----------
    // #5 darwin 1x1
    // ----------
    
    try {
        cout << "*** Darwin 1x1 ***" << endl;
        Darwin executor(1, 1);
        executor.run(4, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    
    // ----------
    // #6 darwin 1x1
    // ----------
    
    try {
        cout << "*** Darwin 1x1 ***" << endl;
        Darwin executor(1, 1);
        executor.set_contents(0, 0, creature(enums::south, &trap));
        executor.run(4, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // #7 darwin 4x4
    // ----------
    
    try {
        cout << "*** Darwin 4x4 ***" << endl;
        Darwin executor(4, 4);
        executor.set_contents(0, 0, creature(enums::south, &food));
        executor.set_contents(0, 1, creature(enums::south, &trap));
        executor.set_contents(1, 0, creature(enums::south, &trap));
        executor.set_contents(1, 1, creature(enums::south, &food));
        executor.run(4, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    // ----------
    // #8 darwin 4x4
    // ----------
    
    try {
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);
        Darwin executor(4, 4);
        executor.set_contents(0, 0, creature(enums::south, &rover));
        executor.set_contents(0, 1, creature(enums::south, &food));
        executor.set_contents(1, 0, creature(enums::south, &food));
        executor.set_contents(1, 1, creature(enums::south, &food));
        executor.run(20, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    // ----------
    // #9 darwin 2x2
    // ----------
    
    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);
        Darwin executor(2, 2);
        executor.set_contents(0, 0, creature(enums::south, &hopper));
        executor.set_contents(0, 1, creature(enums::south, &food));
        executor.set_contents(1, 0, creature(enums::south, &food));
        executor.set_contents(1, 1, creature(enums::south, &food));
        executor.run(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    // ----------
    // #10 darwin 1x10
    // ----------
    
    try {
        cout << "*** Darwin 1x10 ***" << endl;
        srand(0);
        Darwin executor(1, 10);
        executor.set_contents(0, 0, creature(enums::south, &rover));
        executor.set_contents(0, 5, creature(enums::south, &food));
        executor.set_contents(0, 9, creature(enums::south, &trap));
        executor.run(20, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    
    
    
    // -----------------
    // #11 darwin 3x1
    // -----------------
    try {
        cout << "*** Darwin 3x1 ***" << endl;
        srand(0);
        Darwin s(3, 1);
        s.set_contents(0, 0, creature(enums::east, &food));
        s.set_contents(1, 0, creature(enums::east, &hopper));
        s.set_contents(2, 0, creature(enums::east, &rover));
        s.run(10, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    
    // -----------------
    // #12 darwin 3x9
    // -----------------
    try {
        cout << "*** Darwin 3x9 ***" << endl;
        srand(0);
        Darwin s(3, 9);
        s.set_contents(0, 0, creature(enums::south, &hopper));
        s.set_contents(0, 1, creature(enums::west, &hopper));
        s.set_contents(0, 2, creature(enums::south, &hopper));
        s.set_contents(0, 3, creature(enums::west, &hopper));
        s.set_contents(1, 0, creature(enums::south, &rover));
        s.set_contents(1, 1, creature(enums::west, &trap));
        s.run(5, 1);
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    return 0;}
