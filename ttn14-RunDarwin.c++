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
#include <vector>

#include "Darwin.h"

// --------
// macros
// --------
#define RAN_GEN(x) (rand() % (x))

using namespace std;

// -----------------
// acceptance tests
// -----------------
void darwin_8_8_without_best();
void darwin_7_9_without_best();
void darwin_10_10_without_best();
void darwin_10_10_with_best();
void darwin_24_24_without_best();
void darwin_36_36_with_best();
void darwin_36_36_without_best();
void darwin_50_10_with_best();
void darwin_72_72_with_best();
void darwin_72_72_without_best();

// ---------------
// Sample species
// ---------------
Species food = Species::food();
Species trap = Species::trap();
Species hopper = Species::hopper();
Species rover = Species::rover();
Species best = Species::best();

// ----
// main
// ----

int main() {  //rename to main
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O

    darwin_8_8_without_best();
    darwin_7_9_without_best();
    darwin_10_10_without_best();
    darwin_10_10_with_best();
    darwin_24_24_without_best();
    darwin_36_36_with_best();
    darwin_36_36_without_best();
    darwin_50_10_with_best();
    darwin_72_72_without_best();
    darwin_72_72_with_best();

    return 0;
}

void darwin_8_8_without_best() {
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
        Board runBoard1(8, 8);
        Creature food1(food, 2);
        runBoard1.place(food1, 0, 0);
        Creature hopper1(hopper, 1);
        runBoard1.place(hopper1, 3, 3);
        Creature hopper2(hopper, 2);
        runBoard1.place(hopper2, 3, 4);
        Creature hopper3(hopper, 3);
        runBoard1.place(hopper3, 4, 4);
        Creature hopper4(hopper, 0);
        runBoard1.place(hopper4, 4, 3);
        Creature food2(food, 1);
        runBoard1.place(food2, 7, 7);
        runBoard1.run(5, true);
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }

}
void darwin_7_9_without_best() {
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
        Board runBoard2(7, 9);
        Creature trapper1(trap, 3);
        runBoard2.place(trapper1, 0, 0);

        Creature hopper1(hopper, 2);
        runBoard2.place(hopper1, 3, 2);

        Creature rover1(rover, 1);
        runBoard2.place(rover1, 5, 4);

        Creature trapper2(trap, 0);
        runBoard2.place(trapper2, 6, 8);

        runBoard2.run(5, true);
    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }
}

void darwin_10_10_with_best() {
    // ------------
    // darwin 10x10
    // with best
    // ------------

    try {
        cout << "*** Darwin 10x10 with Best ***" << endl;
        srand(0);
        Board runBoard3(10, 10);

        Species specs[] = { food, hopper, rover, trap, best };

        for (int i = 0; i < 4; i++)
            for (int sp = 0; sp < 5; ++sp) {
                int row = RAN_GEN( 10 );
                int col = RAN_GEN( 10 );
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(200, true, 100);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

void darwin_10_10_without_best() {
    // ------------
    // darwin 10x10
    // without best
    // ------------

    try {
        cout << "*** Darwin 10x10 without Best ***" << endl;
        srand(0);

        Board runBoard3(10, 10);

        Species specs[] = { food, hopper, rover, trap };

        for (int i = 0; i < 4; i++)
            for (int sp = 0; sp < 4; ++sp) {
                int row = RAN_GEN( 10 );
                int col = RAN_GEN( 10 );
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(200, true, 100);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

void darwin_24_24_without_best() {
    // ------------
    // darwin 24x24
    // without best
    // ------------

    try {
        cout << "*** Darwin 24x24 without Best ***" << endl;
        srand(0);

        Board runBoard3(24, 24);

        Species specs[] = { food, hopper, rover, trap };

        for (int i = 0; i < 10; i++)
            for (int sp = 0; sp < 4; ++sp) {
                int row = RAN_GEN( 24 );
                int col = RAN_GEN( 24 );
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(1000, true, 100);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

void darwin_36_36_without_best() {

    // ------------
    // darwin 36x36
    // without best
    // ------------

    try {
        cout << "*** Darwin 36x36 without Best ***" << endl;
        srand(0);

        Board runBoard3(36, 36);

        Species specs[] = { food, hopper, rover, trap };

        for (int i = 0; i < 500; i++)
            for (int sp = 0; sp < 4; ++sp) {
                int row = RAN_GEN( 36 );
                int col = RAN_GEN( 36 );
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(100, true, 50);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

// ------------
// darwin 36x36
// with best
// ------------

void darwin_36_36_with_best() {
    try {
        cout << "*** Darwin 36x36 with Best ***" << endl;
        srand(0);

        Board runBoard3(36, 36);

        Species specs[] = { food, hopper, rover, trap, best };

        for (int i = 0; i < 400; i++)
            for (int sp = 0; sp < 5; ++sp) {
                int row = RAN_GEN( 36 );
                int col = RAN_GEN( 36 );
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(20, true, 5);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

// ------------
// darwin 50x10
// with best
// ------------

void darwin_50_10_with_best() {
    try {
        cout << "*** Darwin 50x10 with Best ***" << endl;
        srand(0);

        Board runBoard3(50, 10);

        Species specs[] = { food, hopper, rover, trap, best };

        for (int i = 0; i < 50; i++)
            for (int sp = 0; sp < 5; ++sp) {
                int row = RAN_GEN( 50 );
                int col = RAN_GEN( 10 );
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(20, true, 5);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

// ------------
// darwin 72x72
// without best
// ------------

void darwin_72_72_without_best() {

    try {
        cout << "*** Darwin 72x72 without Best ***" << endl;
        srand(0);
        /**
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
        Board runBoard3(72, 72);

        Species specs[] = { food, hopper, rover, trap };

        for (int sp = 0; sp < 4; ++sp)
            for (int i = 0; i < 10; i++) {
                int pos = RAN_GEN( 5184 );
                int row = pos / 72;
                int col = pos % 72;
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(1000, true, 100);

    } catch (const invalid_argument& arg) {
        cout << arg.what() << endl;
        assert(false);
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        assert(false);
    }
}

void darwin_72_72_with_best() {
    // ------------
    // darwin 72x72
    // with best
    // ------------

    try {
        cout << "*** Darwin 72x72 with Best ***" << endl;
        srand(0);
        Board runBoard3(72, 72);

        Species specs[] = { food, hopper, rover, trap, best };

        for (int sp = 0; sp < 5; ++sp)
            for (int i = 0; i < 10; i++) {
                int pos = RAN_GEN( 5184 );
                int row = pos / 72;
                int col = pos % 72;
                int dir = RAN_GEN( 4 );
                Creature cr = Creature(specs[sp], dir);
                runBoard3.place(cr, row, col);
            }
        runBoard3.run(1000, true, 100);
        Creature cr_rover = Creature(rover, 0);
        Creature cr_best = Creature(best, 0);
        int c_r = runBoard3.count(cr_rover);
        int c_b = runBoard3.count(cr_best);
        cout << "Rover Count: " << c_r << endl;
        cout << "Best Count: " << c_b << endl;

    } catch (const invalid_argument&) {
        assert(false);
    } catch (const out_of_range&) {
        assert(false);
    }
}
