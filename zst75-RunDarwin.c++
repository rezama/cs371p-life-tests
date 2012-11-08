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

    Species food("food", 'f');
    food.addInstruction(turn_left);
    food.addInstruction(go, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species hopper("hopper", 'h');
    hopper.addInstruction(hop);
    hopper.addInstruction(go, 0);    
    

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
    
    Species rover("rover", 'r');
    rover.addInstruction(if_enemy, 9);
    rover.addInstruction(if_empty, 7);
    rover.addInstruction(if_random, 5);
    rover.addInstruction(turn_left);
    rover.addInstruction(go, 0);
    rover.addInstruction(turn_right);
    rover.addInstruction(go, 0);
    rover.addInstruction(hop);
    rover.addInstruction(go, 0);
    rover.addInstruction(infect);
    rover.addInstruction(go, 0);
     
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

    Species trap("trap", 't');
    trap.addInstruction(if_enemy, 3);
    trap.addInstruction(turn_left);
    trap.addInstruction(go, 0);
    trap.addInstruction(infect);
    trap.addInstruction(go, 0);

    // ----
    // best
    // ----


    // REMOVED BEST FOR TEST REPO
    
    
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
        Grid g(8, 8);
        g.place(food , 'e', 0, 0);
        g.place(hopper, 'n', 3, 3);
        g.place(hopper, 'e', 3, 4);
        g.place(hopper, 's', 4, 4);
        g.place(hopper, 'w', 4, 3);
        g.place(food , 'n', 7, 7);

        g.simulate(5, 1);
        
        
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
	Grid g(7, 9);
        g.place(trap , 's', 0, 0);
        g.place(hopper, 'e', 3, 2);
        g.place(rover, 'n', 5, 4);
        g.place(trap, 'w', 6, 8);

	g.simulate(5,1);

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
	Grid g(72,72);

	for(int i = 0; i < 10; ++i){
		int random = rand()%5184;
		int y = random/72;
		int x = random%72;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(food, direct, y, x);
	}
	for(int i = 0; i < 10; ++i){
		int random = rand()%5184;
		int y = random/72;
		int x = random%72;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(hopper, direct, y, x);
	}
	for(int i = 0; i < 10; ++i){
		int random = rand()%5184;
		int y = random/72;
		int x = random%72;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(rover, direct, y, x);
	}
	for(int i = 0; i < 10; ++i){
		int random = rand()%5184;
		int y = random/72;
		int x = random%72;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(trap, direct, y, x);
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
	Grid g(1, 1);
        g.place(trap , 's', 0, 0);

	g.simulate(5,1);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10
    // ----------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
	Grid g(10, 10);
        g.place(trap , 's', 0, 0);
        g.place(rover , 's', 1, 1);
        g.place(rover , 's', 2, 2);
        g.place(rover , 's', 3, 3);
        g.place(rover , 's', 4, 4);

	g.simulate(10,2);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // darwin 4x20
    // ----------

    try {
        cout << "*** Darwin 4x20 ***" << endl;
	Grid g(4, 20);
        g.place(hopper , 's', 3, 2);
        g.place(hopper , 's', 3, 1);
        g.place(hopper , 's', 2, 3);
        g.place(hopper , 's', 0, 1);
        g.place(hopper , 's', 3, 6);
        g.place(hopper , 's', 2, 7);
        g.place(hopper , 's', 3, 8);
        g.place(hopper , 's', 2, 5);
        g.place(hopper , 's', 3, 9);
        g.place(hopper , 's', 1, 3);

	g.simulate(5,1);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 500x500
    // ----------

    try {
        cout << "*** Darwin 500x500 ***" << endl;
	Grid g(500, 500);
    for(int i = 0; i < 100; ++i){
		int random = rand()%250000;
		int y = random/500;
		int x = random%500;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(hopper, direct, y, x);
	}

	g.simulate(100,20);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // darwin 50x50
    // ----------

    try {
        cout << "*** Darwin 50x50 ***" << endl;
	Grid g(50, 50);
    for(int i = 0; i < 5; ++i){
		int random = rand()%2500;
		int y = random/50;
		int x = random%50;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(hopper, direct, y, x);
	}
	
    for(int i = 0; i < 5; ++i){
		int random = rand()%2500;
		int y = random/50;
		int x = random%50;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(trap, direct, y, x);
	}

	g.simulate(40,10);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 10x10
    // ----------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
	Grid g(10, 10);
    for(int i = 0; i < 5; ++i){
		int random = rand()%100;
		int y = random/10;
		int x = random%10;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(hopper, direct, y, x);
	}

	g.simulate(100,20);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
        
    // ----------
    // darwin 500x500
    // ----------

    try {
        cout << "*** Darwin 500x500 ***" << endl;
	Grid g(500, 500);
    for(int i = 0; i < 100; ++i){
		int random = rand()%250000;
		int y = random/500;
		int x = random%500;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(rover, direct, y, x);
	}
	    for(int i = 0; i < 10; ++i){
		int random = rand()%250000;
		int y = random/500;
		int x = random%500;
		int dir = rand()%4;
		char direct;
		if(dir == 0)
			direct = 'w';
		else if(dir == 1)
			direct = 'n';
		else if(dir == 2)
			direct = 'e';
		else if(dir == 3)
			direct = 's';
		g.place(rover, direct, y, x);
	}

	g.simulate(1000,100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
    return 0;}
