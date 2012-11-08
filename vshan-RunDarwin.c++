// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind ./RunDarwin.c++.app > RunDarwin.out

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

    Species food("f");
    food.add(Instruction("left"));
    food.add(Instruction("go", 0));

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper("h");
    hopper.add(Instruction("hop"));
    hopper.add(Instruction("go",0));

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

    Species rover("r");
    rover.add(Instruction("if_enemy", 9));
    rover.add(Instruction("if_empty", 7));
    rover.add(Instruction("if_random", 5));
    rover.add(Instruction("left"));
    rover.add(Instruction("go", 0));
    rover.add(Instruction("right"));
    rover.add(Instruction("go", 0));
    rover.add(Instruction("hop"));
    rover.add(Instruction("go", 0));
    rover.add(Instruction("infect"));
    rover.add(Instruction("go", 0));

    // -----
    // best
    // -----





    /*
     if enemy 3
     if wall 4
     hop
     go 1

     infect
     go 0

    */
    Species best("b");
    best.add(Instruction("if_enemy", 9)); //infect1
    best.add(Instruction("if_empty", 11)); //hop1
    best.add(Instruction("left")); //WALL/FRIEND HIT, TURN LEFT
    best.add(Instruction("if_enemy", 13)); //infect3
    best.add(Instruction("left")); //ALTERNATE LEFT/RIGHT and INFECT
    best.add(Instruction("if_enemy", 15)); //infect4
    best.add(Instruction("right"));
    best.add(Instruction("if_enemy", 17)); //infect5, go back to alternate
    best.add(Instruction("go", 3));
    best.add(Instruction("infect")); //infect1
    best.add(Instruction("go", 0));
    best.add(Instruction("hop")); //hop1
    best.add(Instruction("go", 0));
    best.add(Instruction("infect")); //infect3
    best.add(Instruction("go", 3));
    best.add(Instruction("infect")); //infect4
    best.add(Instruction("go", 5));
    best.add(Instruction("infect")); //infect5
    best.add(Instruction("go", 3));

//    best.add(Instruction("if_enemy", 12)); //infect1
//    best.add(Instruction("if_empty", 14)); //hop1
//    best.add(Instruction("left")); //WALL/FRIEND HIT, TURN LEFT
//    best.add(Instruction("if_enemy", 16)); //infect2
//    best.add(Instruction("if_empty", 18)); //hop2
//    best.add(Instruction("left")); //CORNER HIT
//    best.add(Instruction("if_enemy", 20)); //infect3
//    best.add(Instruction("left")); //ALTERNATE LEFT/RIGHT and INFECT
//    best.add(Instruction("if_enemy", 22)); //infect4
//    best.add(Instruction("right"));
//    best.add(Instruction("if_enemy", 24)); //infect5, go back to alternate
//    best.add(Instruction("go", 7));
//    best.add(Instruction("infect")); //infect1
//    best.add(Instruction("go", 0));
//    best.add(Instruction("hop")); //hop1
//    best.add(Instruction("go", 0));
//    best.add(Instruction("infect")); //infect2
//    best.add(Instruction("go", 3));
//    best.add(Instruction("hop")); //hop2
//    best.add(Instruction("go", 3));
//    best.add(Instruction("infect")); //infect3
//    best.add(Instruction("go", 6));
//    best.add(Instruction("infect")); //infect4
//    best.add(Instruction("go", 8));
//    best.add(Instruction("infect")); //infect5
//    best.add(Instruction("go", 6));


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

    Species trap("t");
    trap.add(Instruction("if_enemy", 3));
    trap.add(Instruction("left"));
    trap.add(Instruction("go", 0));
    trap.add(Instruction("infect"));
    trap.add(Instruction("go", 0));

    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
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
        World w(8,8);
        Creature f(&food, E);
        Creature h(&hopper, N);
        Creature h1(&hopper, E);
        Creature h2(&hopper, S);
        Creature h3(&hopper, W);
        Creature f1(&food, N);
        w.add(&f,0,0);
        w.add(&h,3,3);
        w.add(&h1,3,4);
        w.add(&h2,4,4);
        w.add(&h3,4,3);
        w.add(&f1,7,7);
        for(int i = 0; i <= 5; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
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
        World w(7,9);
        Creature t(&trap, S);
        Creature h(&hopper, E);
        Creature r(&rover, N);
        Creature t1(&trap, W);
        w.add(&t,0,0);
        w.add(&h,3,2);
        w.add(&r,5,4);
        w.add(&t1,6,8);
        for(int i = 0; i <= 5; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
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
        World w(72, 72);

        vector<Creature> foods(10, Creature(&food, 0));
        vector<Creature> hoppers(10, Creature(&hopper, 0));
        vector<Creature> rovers(10, Creature(&rover, 0));
        vector<Creature> traps(10, Creature(&trap, 0));

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	foods[j] = Creature(&food, dir);
        	w.add(&foods[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	hoppers[j] = Creature(&hopper, dir);
        	w.add(&hoppers[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	rovers[j] = Creature(&rover, dir);
        	w.add(&rovers[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	traps[j] = Creature(&trap, dir);
        	w.add(&traps[j], r, c);
        }

//        for(int i = 0; i <= 10; i++){
//        	cout << "Turn = " << i << "." << endl;
//        	w.print();
//        	w.execute();
//        }

        for(int i = 0; i <= 1000; i++){
        	if(i%100 == 0){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	}
        	w.execute();
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

        World w(72, 72);

        vector<Creature> foods(10, Creature(&food, 0));
        vector<Creature> hoppers(10, Creature(&hopper, 0));
        vector<Creature> rovers(10, Creature(&rover, 0));
        vector<Creature> traps(10, Creature(&trap, 0));
        vector<Creature> bests(10, Creature(&trap, 0));

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	foods[j] = Creature(&food, dir);
        	w.add(&foods[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	hoppers[j] = Creature(&hopper, dir);
        	w.add(&hoppers[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	rovers[j] = Creature(&rover, dir);
        	w.add(&rovers[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	traps[j] = Creature(&trap, dir);
        	w.add(&traps[j], r, c);
        }

        for(int j = 0; j < 10; j++) {
        	int random = rand() % 5184;
        	int r = random/72;
        	int c = random-(72*r);
        	int dir = rand()%4;
        	bests[j] = Creature(&best, dir);
        	w.add(&bests[j], r, c);
        }

//        for(int i = 0; i <= 100; i++){
//        	cout << "Turn = " << i << "." << endl;
//        	w.print();
//        	w.execute();
//        }
//
        for(int i = 0; i <= 1000; i++){
        	if(i%100 == 0){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	}
        	w.execute();
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
        World w(1,1);
        Creature h(&hopper, N);
        w.add(&h,0,0);
        for(int i = 0; i <= 5; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
        }
    }
    catch (const invalid_argument&) {
    	assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 0x0
    // ----------

    try {
        cout << "*** Darwin 0x0 ***" << endl;
        World w(0,0);
        for(int i = 0; i <= 1; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
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
        World w(4,4);
        Creature r(&rover, S);
        Creature r1(&rover, N);
        Creature t(&trap, E);
        Creature t1(&trap, W);
    	w.add(&r, 0, 0);
    	w.add(&r1, 3, 3);
    	w.add(&t, 1, 2);
    	w.add(&t, 2, 1);
        for(int i = 0; i <= 5; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
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
        World w(2,2);
        Creature f(&food, N);
        Creature f1(&food, N);
        Creature h(&hopper, E);
        Creature h1(&hopper, W);
        w.add(&h,0,0);
        w.add(&f,0,1);
        w.add(&h1,1,1);
        w.add(&f1,1,0);
        for(int i = 0; i <= 2; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
        }
    }
    catch (const invalid_argument&) {
    	assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 5x1
    // ----------

    try {
        cout << "*** Darwin 5x1 ***" << endl;
        World w(5,1);
        Creature r(&rover, S);
        Creature r1(&rover, N);
        w.add(&r,0,0);
        w.add(&r1,4,0);
        for(int i = 0; i <= 5; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
        }
    }
    catch (const invalid_argument&) {
    	assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        cout << "*** Darwin 7x7 ***" << endl;
        srand(0);
        World w(7,7);
        Creature b(&best, N);
        Creature b1(&best, E);
        Creature b2(&best, S);
        w.add(&b,2,2);
        w.add(&b1,3,3);
        w.add(&b2,4,4);
        for(int i = 0; i <= 10; i++){
        	cout << "Turn = " << i << "." << endl;
        	w.print();
        	w.execute();
        }
    }
    catch (const invalid_argument& e) {
    	cout << e.what() << endl;
    	assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
