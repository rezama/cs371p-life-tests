// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/**
* Stephen Cook
* stc493
*/

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
    // 1. darwin 8x8
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
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(8,8);
		gr.place_creature(0,0, Grid::EAST, &food);
		gr.place_creature(3,3, Grid::NORTH, &hopper);
		gr.place_creature(3,4, Grid::EAST, &hopper);
		gr.place_creature(4,4, Grid::SOUTH, &hopper);
		gr.place_creature(4,3, Grid::WEST, &hopper);
		gr.place_creature(7,7, Grid::NORTH, &food);

		gr.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // 2. darwin 7x9
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
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(7,9);
		gr.place_creature(0,0, Grid::SOUTH, &trap);
		gr.place_creature(3,2, Grid::EAST, &hopper);
		gr.place_creature(5,4, Grid::NORTH, &rover);
		gr.place_creature(6,8, Grid::WEST, &trap);

		gr.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // 3. darwin 72x72
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

		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(72,72);

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&food);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&hopper);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&rover);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&trap);
		}
		
		gr.simulate(1000, 100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // 4. darwin 72x72
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
	
		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Species best('b');
		best.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		best.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		best.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		best.add_instruction(Instruction::RIGHT);
		best.add_instruction(Instruction(Instruction::GO, 0));
		best.add_instruction(Instruction::LEFT);
		best.add_instruction(Instruction(Instruction::GO, 0));
		best.add_instruction(Instruction::HOP);
		best.add_instruction(Instruction(Instruction::GO, 0));
		best.add_instruction(Instruction::INFECT);
		best.add_instruction(Instruction(Instruction::GO, 0));


		Grid gr(72,72);

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&food);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&hopper);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&rover);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&trap);
		}

		for(int i=0; i<10; i++)
		{
			gr.randomly_place_creature(&best);
		}
		
		gr.simulate(1000, 100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------
    // 5. darwin 1x1
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Simulate 5 moves.
        Print every grid.
        */
		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(1,1);
		gr.place_creature(0,0, Grid::SOUTH, &trap);
		gr.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


	// ----------
    // 6. darwin 2x2
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        /*
        7x9 Darwin
        Trap,   facing south, at (0, 0)
        Hopper, facing east,  at (1, 1)
        Food,  facing north, at (0, 1)
        Simulate 5 moves.
        Print every grid.
        */
		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(2,2);
		gr.place_creature(0,0, Grid::SOUTH, &trap);
		gr.place_creature(1,1, Grid::EAST, &hopper);
		gr.place_creature(0,1, Grid::NORTH, &food);

		gr.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


	// ----------
    // 7. darwin 2x2
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        /*
        7x9 Darwin
        Rover,   facing south, at (0, 0)
        Rover, facing east,  at (1, 1)
        Hopper,  facing north, at (0, 1)
        Simulate 5 moves.
        Print every grid.
        */
		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(2,2);
		gr.place_creature(0,0, Grid::SOUTH, &rover);
		gr.place_creature(1,1, Grid::EAST, &rover);
		gr.place_creature(0,1, Grid::NORTH, &hopper);

		gr.simulate(5);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


	// ----------
    // 8. darwin 10x10
    // ----------

    try {
        cout << "*** Darwin 10x10 ***" << endl;
		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
        /*
        10x10 Darwin
        Trap,   facing south, at (2, 2)
        Food,   facing west, at (3, 8)
        Hopper,   facing north, at (9, 9)
        Hopper,   facing east, at (5, 5)
        Hopper, facing east,  at (1, 7)
        Food,  facing north, at (5, 3)
        Rover,   facing south, at (2, 8)
        Rover,   facing west, at (6, 6)
        Simulate 10 moves.
        Print every grid.
        */
		Grid gr(10,10);
		gr.place_creature(2,2, Grid::SOUTH, &trap);
		gr.place_creature(3,8, Grid::WEST, &food);
		gr.place_creature(9,9, Grid::NORTH, &hopper);
		gr.place_creature(5,5, Grid::EAST, &hopper);
		gr.place_creature(1,7, Grid::EAST, &hopper);
		gr.place_creature(5,3, Grid::NORTH, &food);
		gr.place_creature(2,8, Grid::SOUTH, &rover);
		gr.place_creature(6,6, Grid::WEST, &rover);

		gr.simulate(10);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

	// ----------
    // 9. darwin 15x15
    // ----------

    try {
        cout << "*** Darwin 15x15 ***" << endl;
		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
        /*
        15x15 Darwin
	3 randomly placed food, rovers, hoppers, traps.
        Simulate 10 moves.
        Print every grid.
        */
		Grid gr(15,15);
		gr.randomly_place_creature(&food);
		gr.randomly_place_creature(&food);
		gr.randomly_place_creature(&food);
		gr.randomly_place_creature(&rover);
		gr.randomly_place_creature(&rover);
		gr.randomly_place_creature(&rover);
		gr.randomly_place_creature(&hopper);
		gr.randomly_place_creature(&hopper);
		gr.randomly_place_creature(&hopper);
		gr.randomly_place_creature(&trap);
		gr.randomly_place_creature(&trap);
		gr.randomly_place_creature(&trap);

		gr.simulate(10);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

// ------------
    // 3. darwin 100x100
    // without best
    // ------------

    try {
        cout << "*** Darwin 100x100 without Best ***" << endl;
        srand(0);
        /*
        Randomly place the following creatures facing randomly.
        Call rand(), mod it with 10000 (100x100), and use that for the position
        in a row-major order grid.
        Call rand() again, mod it with 4 and use that for it's direction with
        the ordering: west, north, east, south.
        Do that for each kind of creature.
        15 Food
        15 Hopper
        15 Rover
        15 Trap
        Simulate 1500 moves.
        Print every 100th grid.
        */

		srand(0);
	
		Species hopper('h');
		hopper.add_instruction(Instruction::HOP);
		hopper.add_instruction(Instruction(Instruction::GO, 0));

		Species food('f');
		food.add_instruction(Instruction::LEFT);
		food.add_instruction(Instruction(Instruction::GO, 0));
		
		Species trap('t');
		trap.add_instruction(Instruction(Instruction::IF_ENEMY, 3));
		trap.add_instruction(Instruction::LEFT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));
		trap.add_instruction(Instruction::INFECT);	
		trap.add_instruction(Instruction(Instruction::GO, 0));

		Species rover('r');
		rover.add_instruction(Instruction(Instruction::IF_ENEMY, 9));
		rover.add_instruction(Instruction(Instruction::IF_EMPTY, 7));
		rover.add_instruction(Instruction(Instruction::IF_RANDOM, 5));
		rover.add_instruction(Instruction::LEFT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::RIGHT);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::HOP);
		rover.add_instruction(Instruction(Instruction::GO, 0));
		rover.add_instruction(Instruction::INFECT);
		rover.add_instruction(Instruction(Instruction::GO, 0));

		Grid gr(100,100);

		for(int i=0; i<15; i++)
		{
			gr.randomly_place_creature(&food);
		}

		for(int i=0; i<15; i++)
		{
			gr.randomly_place_creature(&hopper);
		}

		for(int i=0; i<15; i++)
		{
			gr.randomly_place_creature(&rover);
		}

		for(int i=0; i<15; i++)
		{
			gr.randomly_place_creature(&trap);
		}
		
		gr.simulate(1500, 100);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}




    return 0;}
