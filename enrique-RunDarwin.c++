// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin_test.c++ -o RunDarwin_test.c++.app
    % valgrind RunDarwin_test.c++.app > RunDarwin_test.out

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
    // general instructions
    // ----

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
        World temp_world(8,8);

        Instruction left(temp_world, "left", 0); 
        Instruction go_0(temp_world, "go", 0); 
        Instruction hop(temp_world, "hop", 0); 
    
        Species food;
        food.addInstr(left);
        food.addInstr(go_0);
    
        Species hopper;
        hopper.addInstr(hop);
        hopper.addInstr(go_0);

        Creature food_c_e('e', 0, 'f', &food);
        Creature food_c_n('n', 0, 'f', &food);
        Creature hopper_c_n('n', 0, 'h', &hopper);
        Creature hopper_c_e('e', 0, 'h', &hopper);
        Creature hopper_c_s('s', 0, 'h', &hopper);
        Creature hopper_c_w('w', 0, 'h', &hopper);
        temp_world.place_creature(food_c_e, 0, 0); 
        temp_world.place_creature(hopper_c_n, 3, 3); 
        temp_world.place_creature(hopper_c_e, 3, 4); 
        temp_world.place_creature(hopper_c_s, 4, 4); 
        temp_world.place_creature(hopper_c_w, 4, 3); 
        temp_world.place_creature(food_c_n, 7, 7); 
        temp_world.run(5);
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

        World temp_world(7,9);

        Instruction if_enemy_3(temp_world, "if_enemy", 3); 
        Instruction left(temp_world, "left", 0); 
        Instruction right(temp_world, "right", 0); 
        Instruction go_0(temp_world, "go", 0); 
        Instruction hop(temp_world, "hop", 0); 
        Instruction infect(temp_world, "infect", 0); 
        Instruction if_enemy_9(temp_world, "if_enemy", 9); 
        Instruction if_empty_7(temp_world, "if_empty", 7); 
        Instruction if_random_5(temp_world, "if_random", 5); 

        Species trap;
        trap.addInstr(if_enemy_3);
        trap.addInstr(left);
        trap.addInstr(go_0);
        trap.addInstr(infect);
        trap.addInstr(go_0);
    
        Species hopper;
        hopper.addInstr(hop);
        hopper.addInstr(go_0);

        Species rover;
        rover.addInstr(if_enemy_9);
        rover.addInstr(if_empty_7);
        rover.addInstr(if_random_5);
        rover.addInstr(left);
        rover.addInstr(go_0);
        rover.addInstr(right);
        rover.addInstr(go_0);
        rover.addInstr(hop);
        rover.addInstr(go_0);
        rover.addInstr(infect);
        rover.addInstr(go_0);

        Creature t('s', 0, 't', &trap);
        Creature h('e', 0, 'h', &hopper);
        Creature r('n', 0, 'r', &rover);
        Creature t2('w', 0, 't', &trap);

        temp_world.place_creature(t, 0, 0); 
        temp_world.place_creature(h, 3, 2); 
        temp_world.place_creature(r, 5, 4); 
        temp_world.place_creature(t2, 6, 8); 

        temp_world.run(5);

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
        World temp_world(72,72);

        Instruction if_enemy_3(temp_world, "if_enemy", 3); 
        Instruction left(temp_world, "left", 0); 
        Instruction right(temp_world, "right", 0); 
        Instruction go_0(temp_world, "go", 0); 
        Instruction hop(temp_world, "hop", 0); 
        Instruction infect(temp_world, "infect", 0); 
        Instruction if_enemy_9(temp_world, "if_enemy", 9); 
        Instruction if_empty_7(temp_world, "if_empty", 7); 
        Instruction if_random_5(temp_world, "if_random", 5); 

        Species food;
        food.addInstr(left);
        food.addInstr(go_0);

        Species trap;
        trap.addInstr(if_enemy_3);
        trap.addInstr(left);
        trap.addInstr(go_0);
        trap.addInstr(infect);
        trap.addInstr(go_0);
    
        Species hopper;
        hopper.addInstr(hop);
        hopper.addInstr(go_0);

        Species rover;
        rover.addInstr(if_enemy_9);
        rover.addInstr(if_empty_7);
        rover.addInstr(if_random_5);
        rover.addInstr(left);
        rover.addInstr(go_0);
        rover.addInstr(right);
        rover.addInstr(go_0);
        rover.addInstr(hop);
        rover.addInstr(go_0);
        rover.addInstr(infect);
        rover.addInstr(go_0);

 	Creature tw('w', 0, 't', &trap);
 	Creature tn('n', 0, 't', &trap);
 	Creature te('e', 0, 't', &trap);
 	Creature ts('s', 0, 't', &trap);

        Creature hw('w', 0, 'h', &hopper);
        Creature hn('n', 0, 'h', &hopper);
        Creature he('e', 0, 'h', &hopper);
        Creature hs('s', 0, 'h', &hopper);

        Creature rw('w', 0, 'r', &rover);
        Creature rn('n', 0, 'r', &rover);
        Creature re('e', 0, 'r', &rover);
        Creature rs('s', 0, 'r', &rover);

        Creature fw('w', 0, 'f', &food);
        Creature fn('n', 0, 'f', &food);
        Creature fe('e', 0, 'f', &food);
        Creature fs('s', 0, 'f', &food);



//	char names[4] = {'f', 'h', 'r', 't'};
//	Species race[4] = {food, hopper, rover, trap};
	char directions[4] = {'w', 'n', 'e', 's'};


		for(int i = 0; i < 4; i++){
			for(int j = 0; j < 10; j++){
				int random = rand()%5184;
				int theRow = random/72;
				int theCol = random%72;
				int ran2 = rand()%4;
				char direc = directions[ran2];
                               // cout << "theCol: " << theCol;
                               // cout << "theRow: " << theRow;
				if(direc == 'w'){
					if(i == 0){
						temp_world.place_creature(fw, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(hw, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(rw, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(tw, theRow, theCol);
					}
				}
				else if(direc == 'n'){
					if(i == 0){
						temp_world.place_creature(fn, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(hn, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(rn, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(tn, theRow, theCol);
					}
				}
				else if(direc == 'e'){
					if(i == 0){
						temp_world.place_creature(fe, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(he, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(re, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(te, theRow, theCol);
					}
				}
				else if(direc == 's'){
					if(i == 0){
						temp_world.place_creature(fs, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(hs, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(rs, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(ts, theRow, theCol);
					}
				} 
   
			}
		}

		temp_world.run(1000, 100);


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
        World temp_world(72,72);

        Instruction if_enemy_3(temp_world, "if_enemy", 3); 
        Instruction left(temp_world, "left", 0); 
        Instruction right(temp_world, "right", 0); 
        Instruction go_0(temp_world, "go", 0); 
        Instruction hop(temp_world, "hop", 0); 
        Instruction infect(temp_world, "infect", 0); 
        Instruction if_enemy_9(temp_world, "if_enemy", 9); 
        Instruction if_enemy_4(temp_world, "if_enemy", 4); 
        Instruction if_empty_7(temp_world, "if_empty", 7); 
        Instruction if_empty_6(temp_world, "if_empty", 6); 
        Instruction if_random_5(temp_world, "if_random", 5); 

        Species food;
        food.addInstr(left);
        food.addInstr(go_0);

        Species trap;
        trap.addInstr(if_enemy_3);
        trap.addInstr(left);
        trap.addInstr(go_0);
        trap.addInstr(infect);
        trap.addInstr(go_0);
    
        Species hopper;
        hopper.addInstr(hop);
        hopper.addInstr(go_0);

        Species rover;
        rover.addInstr(if_enemy_9);
        rover.addInstr(if_empty_7);
        rover.addInstr(if_random_5);
        rover.addInstr(left);
        rover.addInstr(go_0);
        rover.addInstr(right);
        rover.addInstr(go_0);
        rover.addInstr(hop);
        rover.addInstr(go_0);
        rover.addInstr(infect);
        rover.addInstr(go_0);

        Species best;
        best.addInstr(if_enemy_4);
        best.addInstr(if_empty_6);
        best.addInstr(right);
        best.addInstr(go_0);
        best.addInstr(infect);
        best.addInstr(go_0);
        best.addInstr(hop);
        best.addInstr(go_0);

 	Creature tw('w', 0, 't', &trap);
 	Creature tn('n', 0, 't', &trap);
 	Creature te('e', 0, 't', &trap);
 	Creature ts('s', 0, 't', &trap);

        Creature hw('w', 0, 'h', &hopper);
        Creature hn('n', 0, 'h', &hopper);
        Creature he('e', 0, 'h', &hopper);
        Creature hs('s', 0, 'h', &hopper);

        Creature rw('w', 0, 'r', &rover);
        Creature rn('n', 0, 'r', &rover);
        Creature re('e', 0, 'r', &rover);
        Creature rs('s', 0, 'r', &rover);

        Creature fw('w', 0, 'f', &food);
        Creature fn('n', 0, 'f', &food);
        Creature fe('e', 0, 'f', &food);
        Creature fs('s', 0, 'f', &food);

        Creature bw('w', 0, 'b', &best);
        Creature bn('n', 0, 'b', &best);
        Creature be('e', 0, 'b', &best);
        Creature bs('s', 0, 'b', &best);


//	char names[4] = {'f', 'h', 'r', 't'};
//	Species race[4] = {food, hopper, rover, trap};
	char directions[4] = {'w', 'n', 'e', 's'};


		for(int i = 0; i < 5; i++){
			for(int j = 0; j < 10; j++){
				int random = rand()%5184;
				int theRow = random/72;
				int theCol = random%72;
				int ran2 = rand()%4;
				char direc = directions[ran2];
                               // cout << "theCol: " << theCol;
                               // cout << "theRow: " << theRow;
				if(direc == 'w'){
					if(i == 0){
						temp_world.place_creature(fw, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(hw, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(rw, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(tw, theRow, theCol);
					}
                                 	else if(i == 4){
						temp_world.place_creature(bw, theRow, theCol);
					}

				}
				else if(direc == 'n'){
					if(i == 0){
						temp_world.place_creature(fn, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(hn, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(rn, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(tn, theRow, theCol);
					}
                                 	else if(i == 4){
						temp_world.place_creature(bn, theRow, theCol);
					}

				}
				else if(direc == 'e'){
					if(i == 0){
						temp_world.place_creature(fe, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(he, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(re, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(te, theRow, theCol);
					}
                                 	else if(i == 4){
						temp_world.place_creature(be, theRow, theCol);
					}

				}
				else if(direc == 's'){
					if(i == 0){
						temp_world.place_creature(fs, theRow, theCol);
					}
					else if(i == 1){
						temp_world.place_creature(hs, theRow, theCol);
					}
					else if(i == 2){
						temp_world.place_creature(rs, theRow, theCol);
					}
					else if(i == 3){
						temp_world.place_creature(ts, theRow, theCol);
					}
                                 	else if(i == 4){
						temp_world.place_creature(bs, theRow, theCol);
					}

				} 
   
			}
		}

		temp_world.run(1000, 100);


        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
