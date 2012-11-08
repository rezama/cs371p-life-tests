// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
valgrind RunDarwin.c++.app > RunDarwin.out

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

void setupRand(int i[])
{
    int r = rand()%5184;
    int x = r / 72;
    int y = r % 72;
    int dir = rand() % 4;
    
    i[0] = x;
    i[1] = y;
    i[2] = dir;
}

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
    
    Specie food("food");
    food.addAction(LEFT, -1);
    food.addAction(GO, 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    
    Specie hopper("hopper");
    hopper.addAction(HOP, -1);
    hopper.addAction(GO,0);

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
    
    Specie rover("rover");
    rover.addAction(IF_ENEMY, 9);
    rover.addAction(IF_EMPTY, 7);
    rover.addAction(IF_RANDOM, 5);
    rover.addAction(LEFT, -1);
    rover.addAction(GO, 0);
    rover.addAction(RIGHT,-1);
    rover.addAction(GO, 0);
    rover.addAction(HOP, -1);
    rover.addAction(GO, 0);
    rover.addAction(INFECT, -1);
    rover.addAction(GO,0);

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
    
    Specie trap("trap");
    trap.addAction(IF_ENEMY, 3);
    trap.addAction(LEFT,-1);
    trap.addAction(GO, 0);
    trap.addAction(INFECT, -1);
    trap.addAction(GO,0);

    // -----
    // Best
    // -----
    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: left
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    
    Specie best("best");
    best.addAction(IF_ENEMY, 9);
    best.addAction(IF_EMPTY, 7);
    best.addAction(IF_RANDOM, 5);
    best.addAction(LEFT, -1);
    best.addAction(GO, 0);
    best.addAction(LEFT,-1);
    best.addAction(GO, 0);
    best.addAction(HOP, -1);
    best.addAction(GO, 0);
    best.addAction(INFECT, -1);
    best.addAction(GO,0);
            
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
        
        Grid g(8,8);
        
        Creature f1(food, 2);
        Creature h1(hopper, 1);
        Creature h2(hopper, 2);
        Creature h3(hopper, 3);
        Creature h4(hopper, 0);
        Creature f2(food, 1);
        
        g.put(f1, 0, 0);
        g.put(h1, 3, 3);
        g.put(h2, 3, 4);
        g.put(h3, 4, 4);
        g.put(h4, 4, 3);
        g.put(f2, 7, 7);
        
        
        g.simulate(5,1);
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
        
        Grid g(7,9);
        
        Creature t1(trap,3);
        Creature h1(hopper,2);
        Creature r1(rover, 1);
        Creature t2(trap, 0);
        
        g.put(t1,0,0);
        g.put(h1,3,2);
        g.put(r1,5,4);
        g.put(t2,6,8);
        
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
        
        int rand[3];
        
        //food
        setupRand(rand);
        Creature f1(food,rand[2]);
        g.put(f1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f2(food,rand[2]);
        g.put(f2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f3(food,rand[2]);
        g.put(f3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f4(food,rand[2]);
        g.put(f4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f5(food,rand[2]);
        g.put(f5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f6(food,rand[2]);
        g.put(f6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f7(food,rand[2]);
        g.put(f7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f8(food,rand[2]);
        g.put(f8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f9(food,rand[2]);
        g.put(f9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f10(food,rand[2]);
        g.put(f10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h1(hopper,rand[2]);
        g.put(h1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h2(hopper,rand[2]);
        g.put(h2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h3(hopper,rand[2]);
        g.put(h3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h4(hopper,rand[2]);
        g.put(h4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h5(hopper,rand[2]);
        g.put(h5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h6(hopper,rand[2]);
        g.put(h6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h7(hopper,rand[2]);
        g.put(h7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h8(hopper,rand[2]);
        g.put(h8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h9(hopper,rand[2]);
        g.put(h9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h10(hopper,rand[2]);
        g.put(h10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r1(rover,rand[2]);
        g.put(r1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r2(rover,rand[2]);
        g.put(r2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r3(rover,rand[2]);
        g.put(r3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r4(rover,rand[2]);
        g.put(r4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r5(rover,rand[2]);
        g.put(r5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r6(rover,rand[2]);
        g.put(r6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r7(rover,rand[2]);
        g.put(r7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r8(rover,rand[2]);
        g.put(r8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r9(rover,rand[2]);
        g.put(r9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r10(rover,rand[2]);
        g.put(r10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t1(trap,rand[2]);
        g.put(t1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t2(trap,rand[2]);
        g.put(t2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t3(trap,rand[2]);
        g.put(t3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t4(trap,rand[2]);
        g.put(t4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t5(trap,rand[2]);
        g.put(t5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t6(trap,rand[2]);
        g.put(t6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t7(trap,rand[2]);
        g.put(t7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t8(trap,rand[2]);
        g.put(t8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t9(trap,rand[2]);
        g.put(t9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t10(trap,rand[2]);
        g.put(t10,rand[0],rand[1]);
                
        g.simulate(1000,100);
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
        
        Grid g(72,72);
        
        int rand[3];
        
        //food
        setupRand(rand);
        Creature f1(food,rand[2]);
        g.put(f1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f2(food,rand[2]);
        g.put(f2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f3(food,rand[2]);
        g.put(f3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f4(food,rand[2]);
        g.put(f4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f5(food,rand[2]);
        g.put(f5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f6(food,rand[2]);
        g.put(f6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f7(food,rand[2]);
        g.put(f7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f8(food,rand[2]);
        g.put(f8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f9(food,rand[2]);
        g.put(f9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature f10(food,rand[2]);
        g.put(f10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h1(hopper,rand[2]);
        g.put(h1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h2(hopper,rand[2]);
        g.put(h2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h3(hopper,rand[2]);
        g.put(h3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h4(hopper,rand[2]);
        g.put(h4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h5(hopper,rand[2]);
        g.put(h5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h6(hopper,rand[2]);
        g.put(h6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h7(hopper,rand[2]);
        g.put(h7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h8(hopper,rand[2]);
        g.put(h8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h9(hopper,rand[2]);
        g.put(h9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature h10(hopper,rand[2]);
        g.put(h10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r1(rover,rand[2]);
        g.put(r1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r2(rover,rand[2]);
        g.put(r2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r3(rover,rand[2]);
        g.put(r3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r4(rover,rand[2]);
        g.put(r4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r5(rover,rand[2]);
        g.put(r5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r6(rover,rand[2]);
        g.put(r6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r7(rover,rand[2]);
        g.put(r7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r8(rover,rand[2]);
        g.put(r8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r9(rover,rand[2]);
        g.put(r9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature r10(rover,rand[2]);
        g.put(r10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t1(trap,rand[2]);
        g.put(t1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t2(trap,rand[2]);
        g.put(t2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t3(trap,rand[2]);
        g.put(t3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t4(trap,rand[2]);
        g.put(t4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t5(trap,rand[2]);
        g.put(t5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t6(trap,rand[2]);
        g.put(t6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t7(trap,rand[2]);
        g.put(t7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t8(trap,rand[2]);
        g.put(t8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t9(trap,rand[2]);
        g.put(t9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature t10(trap,rand[2]);
        g.put(t10,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b1(best,rand[2]);
        g.put(b1,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b2(best,rand[2]);
        g.put(b2,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b3(best,rand[2]);
        g.put(b3,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b4(best,rand[2]);
        g.put(b4,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b5(best,rand[2]);
        g.put(b5,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b6(best,rand[2]);
        g.put(b6,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b7(best,rand[2]);
        g.put(b7,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b8(best,rand[2]);
        g.put(b8,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b9(best,rand[2]);
        g.put(b9,rand[0],rand[1]);
        
        setupRand(rand);
        Creature b10(best,rand[2]);
        g.put(b10,rand[0],rand[1]);

        g.simulate(1000,100);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // test_rover
    // ----------
    
    try{
        cout << "*** ccheng Rover Darwin***" << endl;
        srand(0);
        Creature r(rover,1);
        Grid g(5,5);
        g.put(r,0,3);
        
        g.simulate(5,1);
        
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // test_infect
    // ----------
    try{   
        cout << "*** ccheng Infect***" << endl;
        Creature t(trap,2);
        Creature f(food,3);
        
        Grid g(5,5);
        g.put(t, 0, 0);
        g.put(f, 0, 1);
        
        g.simulate(5,1);
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    // ----------
    // sora 4x4
    // ----------
    
    try{
        cout << "*** SORA Darwin 4x4 ***" << endl;
        srand(0);
        Grid g(4,4);
        srand(0);       
        Creature r1(rover,3);
        g.put(r1,0,0);
        
        Creature f1(food,3);
        g.put(f1,0,1);
        
        Creature f2(food,3);
        g.put(f2,1,0);
        
        Creature f3(food,3);
        g.put(f3,1,1);
        
        g.simulate(20,1);
        
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // sora 3x9
    // ----------
    
    try{
        cout << "*** SORA Darwin 3x9 ***" << endl;
        srand(0);
        Grid g(3,9);
        srand(0);        
        Creature h1(hopper,3);
        g.put(h1,0,0);
        
        Creature h2(hopper,0);
        g.put(h2,0,1);
        
        Creature h3(hopper,3);
        g.put(h3,0,2);
        
        Creature h4(hopper,0);
        g.put(h4,0,3);
        
        Creature r1(rover,3);
        g.put(r1,1,0);
        
        Creature t1(trap, 0);
        g.put(t1,1,1);
        
        g.simulate(5,1);
        
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // test_trap
    // ----------
    
    try{
    
        cout << "*** ccheng Trap***" << endl;
        Creature t(trap,1);
        Grid g(5,5);
        g.put(t,0,3);
        
        g.simulate(5,1);
        
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // test_1_1
    // ----------
    
    try{
    
        cout << "*** ccheng 1 x 1***" << endl;
        srand(0);
                
        Creature r(rover,1);
        Grid g(1,1);
        g.put(r,0,0);
        
        g.simulate(5,1);
        
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // test_9_9
    // ----------
    
    try{
    
        cout << "*** ccheng 9 x 9***" << endl;

        Grid g(9,9);
        srand(0);
        Creature r1(rover,1);  
        g.put(r1,0,0); 
        Creature r2(rover,1);
        g.put(r2,7,7);
        
        Creature f1(food,1);
        g.put(f1,5,5);
        
        Creature t1(trap, 0);
        g.put(t1, 3,6);
        
        Creature h1(hopper,1);
        g.put(h1,6,6);
        Creature h2(hopper,1);
        g.put(h2,6,7);
        Creature h3(hopper,2);
        g.put(h2,6,5);

        
        g.simulate(5,1);
        
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;
}
