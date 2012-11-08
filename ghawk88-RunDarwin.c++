// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunDarwin.c++ -o RunDarwin.c++.app
    % valgrind RunDarwin.c++.app &> RunDarwin.out

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

        World w(8,8,5,1);

        w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 0);
        w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionNorth, 3, 3);
        w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionEast, 3, 4);
        w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionSouth, 4, 4);
        w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionWest, 4, 3);
        w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 7, 7);

        w.run();


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


        World w(9,7,5,1);

        w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionSouth, 0, 0);
        w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionEast, 3, 2);
        w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionNorth, 5, 4);
        w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionWest, 6, 8);

        w.run();
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

        World w(72,72,1000,100);
        

        int randomX;
        int randomY;
        int position;
        
        //spawn 10 food
        int foodPlaced = 0;
        while(foodPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place food if spot is empty
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionRandom, randomX, randomY);
                foodPlaced++;
            }
        }
        //place 10 hopper 
        int hopperPlaced = 0;
        while(hopperPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place hopper if spot is empty
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionRandom, randomX, randomY);
                hopperPlaced++;
            }
        }

        //place 10 rover
        int roverPlaced = 0;
        while(roverPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place rover if spot available
            if (w.getNameAtLocation(randomX,randomY) == '.'){
                w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionRandom, randomX, randomY);
                roverPlaced++;
            }

        }
        //place 10 rover
        int trapPlaced = 0;
        while(trapPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place rover if spot available 
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionRandom, randomX, randomY);
                trapPlaced++;
            }
        }
        //run the world
        w.run();
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
        World w(72,72,1000,100);

        int randomX;
        int randomY;
        int position;
        
        //spawn 10 food
        int foodPlaced = 0;
        while(foodPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place food if spot is empty
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionRandom, randomX, randomY);
                foodPlaced++;
            }
        }
        //place 10 hopper 
        int hopperPlaced = 0;
        while(hopperPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place hopper if spot is empty
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionRandom, randomX, randomY);
                hopperPlaced++;
            }
        }

        //place 10 rover
        int roverPlaced = 0;
        while(roverPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place rover if spot available
            if (w.getNameAtLocation(randomX,randomY) == '.'){
                w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionRandom, randomX, randomY);
                roverPlaced++;
            }

        }
        //place 10 traps
        int trapPlaced = 0;
        while(trapPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place rover if spot available 
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionRandom, randomX, randomY);
                trapPlaced++;
            }
        }

        //place 10 Best
        int bestPlaced = 0;
        while(bestPlaced < 10){
            position = rand()%5184;
            randomX = position / 72;
            randomY = position % 72;
            //place rover if spot available 
            if (w.getNameAtLocation(randomX,randomY) == '.')
            {
                w.spawn(CreatureSpeciesTypeBest, CreatureFacingDirectionRandom, randomX, randomY);
                bestPlaced++;
            }
        }
        //run the world
        w.run();
        
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
	srand(0);        

        World w(2,2,2,1);


        w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionEast, 0, 0);

        w.run();


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
		srand(0);

        World w(1,1,1,1);

        w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionSouth, 0, 0);


        w.run();
    }
    catch (const invalid_argument&) {
        assert(false);}
        catch (const out_of_range&) {
            assert(false);}


            return 0;}
