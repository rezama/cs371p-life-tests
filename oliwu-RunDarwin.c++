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

#define private public
#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O


    // ----------
    // darwin 8x8
    // ----------

    try {
        cout << "*** Darwin 8x8 ***" << endl;
        srand(0);
        MASTER.new_game (8, 8); // 8x8 Darwin
        MASTER.spawn_creature (FOOD, EAST, 0, 0); // Food,   facing east,  at (0, 0)
        MASTER.spawn_creature (HOPPER, NORTH, 3, 3); // Hopper, facing north, at (3, 3)
        MASTER.spawn_creature (HOPPER, EAST, 3, 4); // Hopper, facing east,  at (3, 4)
        MASTER.spawn_creature (HOPPER, SOUTH, 4, 4); // Hopper, facing south, at (4, 4)
        MASTER.spawn_creature (HOPPER, WEST, 4, 3); // Hopper, facing west,  at (4, 3)
        MASTER.spawn_creature (FOOD, NORTH, 7, 7); // Food,   facing north, at (7, 7)
        MASTER.gameon(cout, 8); // Simulate 5 moves. Print every grid.
        
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
        MASTER.new_game (7, 9); // 7x9 Darwin
        MASTER.spawn_creature (TRAP, SOUTH, 0, 0); // Trap,   facing south,  at (0, 0)
        MASTER.spawn_creature (HOPPER, EAST, 3, 2); // Hopper, facing east, at (3, 2)
        MASTER.spawn_creature (ROVER, NORTH, 5, 4); // Rover, facing north,  at (5, 4)
        MASTER.spawn_creature (TRAP, WEST, 6, 8); // Trap, facing west, at (6, 8)
        MASTER.gameon(cout, 5); // Simulate 5 moves. Print every grid.
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
        MASTER.new_game (72, 72);
        // 10 Food
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x); 
          MASTER.spawn_creature (FOOD, d, x, y);
        }
        // 10 Hopper
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x);
          MASTER.spawn_creature (HOPPER, d, x, y);
        }
        // 10 Rover
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x); 
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // 10 Trap
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x);
          MASTER.spawn_creature (TRAP, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 1000, 100);          
 
        int count[] = {0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "FOOD = " << count[0] << ", HOPPER = " << count[1] << ", ROVER = " << count[2] << ", TRAP = " << count[3] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
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
        MASTER.new_game (72, 72);
        // 10 Food
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x); 
          MASTER.spawn_creature (FOOD, d, x, y);
        }
        // 10 Hopper
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x);
          MASTER.spawn_creature (HOPPER, d, x, y);
        }
        // 10 Rover
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x); 
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // 10 Trap
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x);
          MASTER.spawn_creature (TRAP, d, x, y);
        }
        // 10 BEST 
        for (int i = 0; i < 10; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x);
          MASTER.spawn_creature (BEST, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 1000, 100);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "FOOD = " << count[0] << ", HOPPER = " << count[1] << ", ROVER = " << count[2] << ", TRAP = " << count[3] << ", BEST = " << count[4] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -------------
    // darwin 72x72
    // best v. rover
    // -------------

    try {
        cout << "*** Darwin 72x72 50 Bests v. 50 Rovers ***" << endl;
       
        srand(0);
        MASTER.new_game (72, 72);
        // 50 Rover
        for (int i = 0; i < 50; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x); 
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // 50 BEST 
        for (int i = 0; i < 50; i++) {
          int location = rand() % 5184;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 72;
          int y = location - (72 * x);
          MASTER.spawn_creature (BEST, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 1000, 1000);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "ROVER = " << count[2] << ", BEST = " << count[4] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -------------
    // darwin 20x20
    // best v. rover
    // -------------

    try {
        cout << "*** Darwin 20x20 12 Bests v. 12 Rovers ***" << endl;
       
        srand(0);
        MASTER.new_game (20, 20);
        // 50 Rover
        for (int i = 0; i < 12; i++) {
          int location = rand() % 400;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 20;
          int y = location - (20 * x); 
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // 50 BEST 
        for (int i = 0; i < 12; i++) {
          int location = rand() % 400;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 20;
          int y = location - (20 * x);
          MASTER.spawn_creature (BEST, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 500, 500);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "ROVER = " << count[2] << ", BEST = " << count[4] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -------------
    // darwin 10x10
    // best v. rover
    // -------------

    try {
        cout << "*** Darwin 10x10 5 Bests v. 5 Rovers ***" << endl;
       
        srand(0);
        MASTER.new_game (20, 20);
        // 5 Rover
        for (int i = 0; i < 5; i++) {
          int location = rand() % 100;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 10;
          int y = location - (10 * x); 
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // 5 BEST 
        for (int i = 0; i < 5; i++) {
          int location = rand() % 100;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 10;
          int y = location - (10 * x);
          MASTER.spawn_creature (BEST, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 500, 500);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "ROVER = " << count[2] << ", BEST = " << count[4] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -------------
    // darwin 20x20
    // rover v. trap 
    // -------------

    try {
        cout << "*** Darwin 20x20 12 Rovers v. 12 Traps ***" << endl;
       
        srand(0);
        MASTER.new_game (20, 20);
        // 12 Trap
        for (int i = 0; i < 12; i++) {
          int location = rand() % 400;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 20;
          int y = location - (20 * x); 
          MASTER.spawn_creature (TRAP, d, x, y);
        }
        // 12 Rover 
        for (int i = 0; i < 12; i++) {
          int location = rand() % 400;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 20;
          int y = location - (20 * x);
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 500, 500);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "TRAP = " << count[3] << ", ROVER = " << count[2] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------
    // darwin 20x20
    // best v. trap 
    // ------------

    try {
        cout << "*** Darwin 20x20 12 Bests v. 12 Traps ***" << endl;
       
        srand(0);
        MASTER.new_game (20, 20);
        // 12 Trap
        for (int i = 0; i < 12; i++) {
          int location = rand() % 400;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 20;
          int y = location - (20 * x); 
          MASTER.spawn_creature (TRAP, d, x, y);
        }
        // 12 BEST 
        for (int i = 0; i < 12; i++) {
          int location = rand() % 400;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 20;
          int y = location - (20 * x);
          MASTER.spawn_creature (BEST, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 500, 500);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "TRAP = " << count[3] << ", BEST = " << count[4] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------
    // darwin 20x20
    // everything 
    // ------------

    try {
        cout << "*** Darwin 25x25 5 of Everything ***" << endl;
       
        srand(0);
        MASTER.new_game (25, 25);
        // 5 Food
        for (int i = 0; i < 5; i++) {
          int location = rand() % 625;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 25;
          int y = location - (25 * x); 
          MASTER.spawn_creature (FOOD, d, x, y);
        }
        // 5 Hopper
        for (int i = 0; i < 5; i++) {
          int location = rand() % 625;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 25;
          int y = location - (25 * x);
          MASTER.spawn_creature (HOPPER, d, x, y);
        }
        // 5 Rover
        for (int i = 0; i < 5; i++) {
          int location = rand() % 625;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 25;
          int y = location - (25 * x); 
          MASTER.spawn_creature (ROVER, d, x, y);
        }
        // 5 Trap
        for (int i = 0; i < 5; i++) {
          int location = rand() % 625;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 25;
          int y = location - (25 * x);
          MASTER.spawn_creature (TRAP, d, x, y);
        }
        // 5 BEST 
        for (int i = 0; i < 5; i++) {
          int location = rand() % 625;
          int direction = rand() % 4;
          directions d = (directions) ((direction + 3) % 4);
          int x = location / 25;
          int y = location - (25 * x);
          MASTER.spawn_creature (BEST, d, x, y);
        }
        // Simulate 1000 moves. Print every 100th grid.
        MASTER.gameon(cout, 500, 500);          


        int count[] = {0,0,0,0,0};
        // FOOD
        for (size_t c = 0; c < MASTER.players.size(); c++) {
          if (MASTER.players[c].type == FOOD) count[0]++; 
          else if (MASTER.players[c].type == HOPPER) count[1]++; 
          else if (MASTER.players[c].type == ROVER) count[2]++; 
          else if (MASTER.players[c].type == TRAP) count[3]++; 
          else if (MASTER.players[c].type == BEST) count[4]++; 
          else
            std::cout << "wtf?" << std::endl;
        }
        std::cout << "***********************RESULTS***********************" << std::endl;
        std::cout << "FOOD = " << count[0] << ", HOPPER = " << count[1] << ", ROVER = " << count[2] << ", TRAP = " << count[3] << ", BEST = " << count[4] << std::endl;
        std::cout << "*****************************************************\n\n" << std::endl;
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
