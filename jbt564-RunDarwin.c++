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

    Species food("food");
    food.addInstruction( instruction(LEFT));
    food.addInstruction( instruction(GO,0));
    
    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------
    
    Species hopper("hopper");
    hopper.addInstruction( instruction(HOP));
    hopper.addInstruction( instruction(GO,0));

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    Species rover("rover");
    rover.addInstruction( instruction(IF_ENEMY,9)  );
    rover.addInstruction( instruction(IF_EMPTY,7)  );
    rover.addInstruction( instruction(IF_RANDOM,5) );
    rover.addInstruction( instruction(LEFT)        );
    rover.addInstruction( instruction(GO,0)        );
    rover.addInstruction( instruction(RIGHT)       );
    rover.addInstruction( instruction(GO,0)        );
    rover.addInstruction( instruction(HOP)         );
    rover.addInstruction( instruction(GO,0)        ); 
    rover.addInstruction( instruction(INFECT)      );
    rover.addInstruction( instruction(GO,0)        );
    
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
     
    Species trap("trap");
    trap.addInstruction( instruction(IF_ENEMY,3) );
    trap.addInstruction( instruction(LEFT)       );
    trap.addInstruction( instruction(GO,0)       );
    trap.addInstruction( instruction(INFECT)     );
    trap.addInstruction( instruction(GO,0)       );
    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    Species best("best");
    best.addInstruction( instruction(IF_ENEMY,4)  );   //0
    best.addInstruction( instruction(IF_EMPTY,6)  );   //1
    best.addInstruction( instruction(LEFT)	  );   //2
    best.addInstruction( instruction(GO,0)        );   //3
    best.addInstruction( instruction(INFECT)      );   //4
    best.addInstruction( instruction(GO,0)	  );   //5
    best.addInstruction( instruction(HOP)	  );   //6
    best.addInstruction( instruction(GO,0)        );   //7


    //insane species
	
    Species insane("insane");
    insane.addInstruction( instruction(IF_ENEMY,5) ); //0
    insane.addInstruction( instruction(IF_RANDOM,7)); //1
    insane.addInstruction( instruction(IF_RANDOM,9)); //2
    insane.addInstruction( instruction(LEFT)	   ); //3
    insane.addInstruction( instruction(GO,0)	   ); //4
    insane.addInstruction( instruction(INFECT)     ); //5
    insane.addInstruction( instruction(GO,0)       ); //6
    insane.addInstruction( instruction(HOP)	   ); //7
    insane.addInstruction( instruction(GO,0)       ); //8
    insane.addInstruction( instruction(RIGHT)      ); //9
    insane.addInstruction( instruction(GO,0)       ); //10

    //back forth species

    Species backforth("backforth");
    backforth.addInstruction( instruction(IF_EMPTY,4) ); //0
    backforth.addInstruction( instruction(LEFT)       ); //1
    backforth.addInstruction( instruction(LEFT)       ); //2
    backforth.addInstruction( instruction(GO,0)       ); //3
    backforth.addInstruction( instruction(HOP)        ); //4
    backforth.addInstruction( instruction(GO,0)	      ); //5

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
        
        Darwin <Creature> world(8,8);
        Creature c1(EAST, food)    ;
        Creature c2(NORTH,hopper)  ;
        Creature c3(EAST, hopper)  ;
        Creature c4(SOUTH,hopper)  ;
        Creature c5(WEST, hopper)  ;
        Creature c6(NORTH,food)    ;
        
        world.placeObject( 0 , 0 , c1 );
        world.placeObject( 3 , 3 , c2 );
        world.placeObject( 4 , 3 , c3 );
        world.placeObject( 4 , 4 , c4 );
        world.placeObject( 3 , 4 , c5 );
        world.placeObject( 7 , 7 , c6 );
        
        world.outputWorld(std::cout);
        
        for(int i = 0; i < 5; i++){
        	world.step();
        	world.outputWorld(std::cout);
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
        
        Darwin <Creature> world(9 , 7);
        Creature c1(SOUTH, trap);
        Creature c2(EAST, hopper);
        Creature c3(NORTH, rover);
        Creature c4(WEST, trap);
        
        world.placeObject( 0 , 0 , c1);
        world.placeObject( 2 , 3 , c2);
        world.placeObject( 4 , 5 , c3);
        world.placeObject( 8 , 6 , c4);
        
        world.outputWorld(std::cout);
        
        for(int i = 0; i < 5; i++){
        	world.step();
          	world.outputWorld(std::cout);
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
        Darwin <Creature> world(72,72);
        
	Creature a[50];	


	unsigned int pos;
	unsigned int x;
        unsigned int y;		
        unsigned int direction;


	for(int i = 0; i < 10; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,food);
		world.placeObject(y,x,a[i]);
	}


	for(int i = 10; i < 20; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,hopper);
		world.placeObject(y,x,a[i]);
	}

	for(int i = 20; i < 30; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,rover);
		world.placeObject(y,x,a[i]);
	}


	for(int i = 30; i < 40; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,trap); 
		world.placeObject(y,x,a[i]);
	}

	string stuff = "";
	
        		
        world.outputWorld(std::cout);
        
        for(int i = 1; i <= 1000; i++){
        	world.step();
        	if(i % 100 == 0){
        		world.outputWorld(std::cout);
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
	Darwin <Creature> world(72,72);
	Creature a[50];	

	//food
	unsigned int pos;
	unsigned int x;
        unsigned int y;
        unsigned int direction;


	for(int i = 0; i < 10; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,food);
		world.placeObject(y,x,a[i]);
	}


	for(int i = 10; i < 20; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,hopper);
		world.placeObject(y,x,a[i]);
	}

	for(int i = 20; i < 30; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,rover);
		world.placeObject(y,x,a[i]);
	}


	for(int i = 30; i < 40; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,trap); 
		world.placeObject(y,x,a[i]);
	}

	for(int i = 40; i < 50; i++){
		pos = rand() % 5184;
		x = pos / 72;
		y = pos % 72;
		direction = rand() % 4;
		a[i] = Creature(direction,best); 
		world.placeObject(y,x,a[i]);
	}


	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 1000; i++){
        	world.step();
        	if(i % 100 == 0)
        		world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    //------------------------------
    //  2x2 World Traps and Hoppers
    //------------------------------
	try {
        cout << "*** Darwin 2x2: Traps and Hoppers ***" << endl;
        srand(0);
        
	Darwin <Creature> world(2,2);
	Creature a[4];	

	a[0] = Creature(NORTH, hopper);
	a[1] = Creature(SOUTH, hopper);
	a[2] = Creature(EAST, trap);
	a[3] = Creature(WEST, trap);

	world.placeObject(0,0,a[0]);
	world.placeObject(1,1,a[1]);
	world.placeObject(0,1,a[2]);
	world.placeObject(1,0,a[3]);

	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 3; i++){
        	world.step();
        	world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


   //--------------------
   // 3x3 Trap and Food
   //--------------------
 	try {
        cout << "*** Darwin 3x3 Trap and Food ***" << endl;
        srand(0);
        
	Darwin <Creature> world(3,3);
	Creature a[4];	

	a[0] = Creature(NORTH, food);
	a[1] = Creature(SOUTH, trap);
	a[2] = Creature(EAST, trap);


	world.placeObject(0,0,a[0]);
	world.placeObject(1,1,a[1]);
	world.placeObject(2,2,a[2]);


	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 2; i++){
        	world.step();
        	world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------
    // darwin 100x10
    // Traps, Rovers
    // ------------

	try {
        cout << "*** Darwin 100x100 Trap and Rovers ***" << endl;
        srand(0);
        
	Darwin <Creature> world(100,100);
	Creature a[100];	

	for(int i = 0; i < 50; i++){
	    a[i] = Creature(rand()%4, trap);
	    int pos = rand() % 10000;
	    int x = pos / 100;
	    int y = pos % 100;
	    world.placeObject(x,y,a[i]);
	}

	for(int i = 50; i < 100; i++){
	    a[i] = Creature(rand()%4, rover);
	    int pos = rand() % 10000;
	    int x = pos / 100;
	    int y = pos % 100;
	    world.placeObject(x,y,a[i]);
	}


	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 1000; i++){
        	world.step();
		if(i % 100 == 0)
        	world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

   //--------------------
   // 5x5 Insane and Food
   //--------------------
 	try {
        cout << "*** Darwin 8x8 Insane and Food ***" << endl;
        srand(0);
        
	Darwin <Creature> world(8,8);
	Creature a[20];	

	for(int i = 0; i < 5; i++){
	   a[i] = Creature(rand() % 4, insane);
	   int pos = rand() % 64;
	   int x = pos % 8;
           int y = pos / 8;
	   world.placeObject(x,y,a[i]);
        }

	for(int i = 5; i < 20; i++){
	   a[i] = Creature(rand() % 4, food);
	   int pos = rand() % 64;
	   int x = pos % 8;
           int y = pos / 8;
	   world.placeObject(x,y,a[i]);
        }
	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 100; i++){
        	world.step();
		if(i%10 == 0)
        	world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

   //--------------------
   // 7x4 Back Forth
   //--------------------
 	try {
        cout << "*** Darwin 7x4 Back Forth ***" << endl;
        srand(0);
        
	Darwin <Creature> world(7,4);
	Creature a[6];	

	a[0] = Creature(WEST,backforth);
	a[1] = Creature(EAST,backforth);
	a[2] = Creature(WEST,backforth);
	a[3] = Creature(EAST,backforth);
	a[4] = Creature(NORTH,backforth);
	a[5] = Creature(SOUTH,backforth);

	world.placeObject(0,0,a[2]);
	world.placeObject(0,2,a[3]);
	world.placeObject(6,1,a[0]);
	world.placeObject(6,3,a[1]);
	world.placeObject(3,3,a[4]);
	world.placeObject(5,3,a[5]);
		
	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 10; i++){
        	world.step();
        	world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
 
    //------------
    // 50x50 All
    //------------

	try {
        cout << "*** Darwin 50x50 All ***" << endl;
        srand(0);
        
	Darwin <Creature> world(50,50);
	Creature a[70];	

	for(int i = 0; i < 10; i++){
	  a[i] = Creature(rand()%4,food);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}

	for(int i = 10; i < 20; i++){
	  a[i] = Creature(rand()%4,hopper);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}

	for(int i =20; i < 30; i++){
	  a[i] = Creature(rand()%4,trap);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}

	for(int i = 30; i < 40; i++){
	  a[i] = Creature(rand()%4,rover);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}

	for(int i = 40; i < 50; i++){
	  a[i] = Creature(rand()%4,best);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}

	for(int i = 50; i < 60; i++){
	  a[i] = Creature(rand()%4,insane);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}

	for(int i = 60; i < 70; i++){
	  a[i] = Creature(rand()%4,backforth);
	  int pos = rand() % 2500;
	  int x = pos / 50;
          int y = pos % 50;
          world.placeObject(x,y,a[i]);
	}
	
	world.outputWorld(std::cout);
        
        for(int i = 1; i <= 1000; i++){
        	world.step();
		if(i%100 == 0)
        	world.outputWorld(std::cout);
        } 

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
