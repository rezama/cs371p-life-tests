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
#include <vector>    // vector
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
    
	vector<string> foodProgram(2);
	foodProgram[0] = "0: left";
	foodProgram[1] = "1: go 0";
	Species food(foodProgram);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    
	vector<string> hopperProgram(2);
	hopperProgram[0] = "0: hop";
	hopperProgram[1] = "1: go 0";
	Species hopper(hopperProgram);

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
    
	vector<string> roverProgram(11);
	roverProgram[0] = "0: if_enemy 9";
	roverProgram[1] = "1: if_empty 7";
	roverProgram[2] = "2: if_random 5";
	roverProgram[3] = "3: left";
	roverProgram[4] = "4: go 0";
	roverProgram[5] = "5: right";
	roverProgram[6] = "6: go 0";
	roverProgram[7] = "7: hop";
	roverProgram[8] = "8: go 0";
	roverProgram[9] = "9: infect";
	roverProgram[10] = "10: go 0";
	Species rover(roverProgram);


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
    
	vector<string> trapProgram(5);
	trapProgram[0] = "0: if_enemy 3";
	trapProgram[1] = "1: left";
	trapProgram[2] = "2: go 0";
	trapProgram[3] = "3: infect";
	trapProgram[4] = "4: go 0";
	Species trap(trapProgram);
	
	// -----
    // best
    // -----

	vector<string> bestProgram(19);
	bestProgram[0] = "0: if_enemy 9";
	bestProgram[1] = "1: if_empty 7";
	bestProgram[2] = "2: if_random 5";
	bestProgram[3] = "3: right";
	bestProgram[4] = "4: go 0";
	bestProgram[5] = "5: right";
	bestProgram[6] = "6: go 0";
	bestProgram[7] = "7: hop";
	bestProgram[8] = "8: go 0";
	bestProgram[9] = "9: infect";
	bestProgram[10] = "10: go 0";		
	Species best(bestProgram);


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

		Controller controller(8, 8);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		Creature food2(food, Direction::NORTH);
		controller.placeCreatureOnBoard(food2, 63, 'f');

		Creature hopper1(hopper,Direction::NORTH);
		controller.placeCreatureOnBoard(hopper1, 27, 'h');
        Creature hopper2(hopper,Direction::EAST);
		controller.placeCreatureOnBoard(hopper2, 28, 'h');
		Creature hopper3(hopper,Direction::SOUTH);
		controller.placeCreatureOnBoard(hopper3, 36, 'h');
        Creature hopper4(hopper,Direction::WEST);
		controller.placeCreatureOnBoard(hopper4, 35, 'h');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
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

		Controller controller(7, 9);

		Creature trap1(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trap1, 0, 't');

		Creature hopper1(hopper, Direction::EAST);
		controller.placeCreatureOnBoard(hopper1, 29, 'h');

		Creature rover1(rover, Direction::NORTH);
		controller.placeCreatureOnBoard(rover1, 49, 'r');

		Creature trap2(trap, Direction::WEST);
		controller.placeCreatureOnBoard(trap2, 62, 't');

		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
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

		Controller controller(72, 72);
		
		// Food
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature foodCreature(food, (Direction) randDirection);
			controller.placeCreatureOnBoard(foodCreature, randPosition, 'f');
		}

		// Hopper
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature hopperCreature(hopper, (Direction) randDirection);
			controller.placeCreatureOnBoard(hopperCreature, randPosition, 'h');
		}

		// Rover
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature roverCreature(rover, (Direction) randDirection);
			controller.placeCreatureOnBoard(roverCreature, randPosition, 'r');
		}

		// Trap
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature trapCreature(trap, (Direction) randDirection);
			controller.placeCreatureOnBoard(trapCreature, randPosition, 't');
		}


		cout << controller.printGameBoard() << endl;
		for(int i = 1; i < 1001; ++i){
			controller.completeOneTurn();
			if(i % 100 == 0){
				cout << controller.printGameBoard() << endl;
			}
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

		Controller controller(72, 72);
		
		// Food
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature foodCreature(food, (Direction) randDirection);
			controller.placeCreatureOnBoard(foodCreature, randPosition, 'f');
		}

		// Hopper
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature hopperCreature(hopper, (Direction) randDirection);
			controller.placeCreatureOnBoard(hopperCreature, randPosition, 'h');
		}

		// Rover
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature roverCreature(rover, (Direction) randDirection);
			controller.placeCreatureOnBoard(roverCreature, randPosition, 'r');
		}

		// Trap
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature trapCreature(trap, (Direction) randDirection);
			controller.placeCreatureOnBoard(trapCreature, randPosition, 't');
		}
		
		// Best
		for(int i = 0; i < 10; ++i){
			int randPosition = rand() % 5184;
			int randDirection = rand() % 4;
			Creature bestCreature(best, (Direction) randDirection);
			controller.placeCreatureOnBoard(bestCreature, randPosition, 'b');
		}

		cout << controller.printGameBoard() << endl;
		for(int i = 1; i < 1001; ++i){
			controller.completeOneTurn();
			if(i % 100 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}
		
		 // uncomment this block to see the final creature count
		cout << "f: " << controller.symbolCount('f') << endl;
		cout << "h: " << controller.symbolCount('h') << endl;
		cout << "r: " << controller.symbolCount('r') << endl;
		cout << "t: " << controller.symbolCount('t') << endl;
		cout << "b: " << controller.symbolCount('b') << endl;
		
		
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 1x1 (acceptance 1)
    // ----------

    try {
        cout << "*** Darwin 1x1 ***" << endl;
        srand(0);

		Controller controller(1, 1);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // darwin 8x4 (acceptance 2)
    // ----------

    try {
        cout << "*** Darwin 8x4 ***" << endl;
        srand(0);

		Controller controller(4, 8);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		Creature food2(food, Direction::NORTH);
		controller.placeCreatureOnBoard(food2, 13, 'f');

		Creature hopper1(hopper,Direction::NORTH);
		controller.placeCreatureOnBoard(hopper1, 7, 'h');
        Creature hopper2(hopper,Direction::EAST);
		controller.placeCreatureOnBoard(hopper2, 18, 'h');
		Creature hopper3(hopper,Direction::SOUTH);
		controller.placeCreatureOnBoard(hopper3, 3, 'h');
        Creature hopper4(hopper,Direction::WEST);
		controller.placeCreatureOnBoard(hopper4, 6, 'h');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // darwin 4x8 (acceptance 3)
    // ----------

    try {
        cout << "*** Darwin 4x8 ***" << endl;
        srand(0);

		Controller controller(8, 4);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		
		Creature rover1(rover, Direction::NORTH);
		controller.placeCreatureOnBoard(rover1, 13, 'r');

		Creature hopper1(hopper,Direction::NORTH);
		controller.placeCreatureOnBoard(hopper1, 7, 'h');
        Creature hopper2(hopper,Direction::EAST);
		controller.placeCreatureOnBoard(hopper2, 18, 'h');
		Creature hopper3(hopper,Direction::SOUTH);
		controller.placeCreatureOnBoard(hopper3, 3, 'h');
        Creature hopper4(hopper,Direction::WEST);
		controller.placeCreatureOnBoard(hopper4, 6, 'h');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // darwin 30x1 (acceptance 4)
    // ----------

    try {
        cout << "*** Darwin 30x1 ***" << endl;
        srand(0);

		Controller controller(1, 30);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 13, 'b');

		Creature hopper1(hopper,Direction::EAST);
		controller.placeCreatureOnBoard(hopper1, 7, 'h');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 10; ++i){			
			controller.completeOneTurn();
			if (i%2 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // darwin 9x9 (acceptance 5)
    // ----------

    try {
        cout << "*** Darwin 9x9 ***" << endl;
        srand(0);

		Controller controller(9, 9);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 1, 'b');
		Creature best2(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best2, 2, 'b');
		Creature best3(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best3, 3, 'b');
		Creature best4(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best4, 4, 'b');
		Creature best5(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best5, 5, 'b');
		Creature best6(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best6, 6, 'b');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 20; ++i){			
			controller.completeOneTurn();
			if (i%3 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}        
        
    // ----------
    // darwin 9x9 (acceptance 6)
    // ----------

    try {
        cout << "*** Darwin 9x9 ***" << endl;
        srand(0);

		Controller controller(9, 9);

		Creature food1(food, Direction::EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		
		Creature trapCreature1(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature1, 16, 't');
		Creature trapCreature2(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature2, 17, 't');
		Creature trapCreature3(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature3, 9, 't');
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 1, 'b');
		Creature best2(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best2, 2, 'b');
		Creature best3(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best3, 3, 'b');
		Creature best4(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best4, 4, 'b');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 20; ++i){			
			controller.completeOneTurn();
			if (i%3 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}      
            
    // ----------
    // darwin 2x2 (acceptance 7)
    // ----------

    try {
        cout << "*** Darwin 2x2 ***" << endl;
        srand(0);

		Controller controller(2, 2);
		
		Creature trapCreature1(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature1, 0, 't');
		Creature trapCreature2(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature2, 3, 't');
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 1, 'b');
		Creature best2(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best2, 2, 'b');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){			
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
        
	// ----------
    // darwin 4x4 (acceptance 8)
    // ----------

    try {
        cout << "*** Darwin 4x4 ***" << endl;
        srand(0);

		Controller controller(4, 4);
		
		Creature trapCreature1(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature1, 0, 't');
		Creature trapCreature2(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature2, 1, 't');
		Creature trapCreature3(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature3, 2, 't');
		Creature trapCreature4(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature4, 3, 't');
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 10, 'b');
		Creature best2(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best2, 11, 'b');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 20; ++i){			
			controller.completeOneTurn();
			if (i%3 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
    
	// ----------
    // darwin 8*8 (acceptance 9)
    // ----------

    try {
		srand(0);
		
        cout << "*** Darwin 8*8 ***" << endl;
        srand(0);

		Controller controller(8, 8);
		
		Creature trapCreature1(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature1, 0, 't');
		Creature trapCreature2(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature2, 1, 't');
		Creature trapCreature3(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature3, 2, 't');
		Creature trapCreature4(trap, Direction::EAST);
		controller.placeCreatureOnBoard(trapCreature4, 3, 't');
		
		Creature rover1(rover, Direction::SOUTH);
		controller.placeCreatureOnBoard(rover1, 10, 'r');
		Creature rover2(rover, Direction::SOUTH);
		controller.placeCreatureOnBoard(rover2, 11, 'r');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 30; ++i){			
			controller.completeOneTurn();
			if (i%5 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
        
	// ----------
    // darwin 4*4 (acceptance 10)
    // ----------

    try {
		srand(0);
		
        cout << "*** Darwin 4*4 ***" << endl;
        srand(0);

		Controller controller(4, 4);
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 1, 'b');
		Creature best2(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best2, 2, 'b');
		
		Creature rover1(rover, Direction::SOUTH);
		controller.placeCreatureOnBoard(rover1, 14, 'r');
		Creature rover2(rover, Direction::SOUTH);
		controller.placeCreatureOnBoard(rover2, 15, 'r');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 50; ++i){			
			controller.completeOneTurn();
			if (i%8 == 0){
				cout << controller.printGameBoard() << endl;
			}
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
        
	// ----------
    // darwin 4*4 (acceptance 11)
    // ----------

    try {
		srand(0);
		
        cout << "*** Darwin 4*4 ***" << endl;
        srand(0);

		Controller controller(4, 4);
		
		Creature best1(best, Direction::SOUTH);
		controller.placeCreatureOnBoard(best1, 1, 'b');
		
		Creature rover1(rover, Direction::SOUTH);
		controller.placeCreatureOnBoard(rover1, 14, 'r');
		
		cout << controller.printGameBoard() << endl;
		for(int i = 0; i < 5; ++i){			
			controller.completeOneTurn();
			cout << controller.printGameBoard() << endl;
		}

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
	
    return 0;}
