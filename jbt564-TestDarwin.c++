// ------------------------------
// projects/matlab/TestMatrix.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------

#include <sstream>
#include <string>
#include <iostream>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Darwin.h"

// ----------
// TestDarwin
// ----------
//enum op_code { HOP, LEFT, RIGHT, INFECT, IF_EMPTY, IF_WALL, IF_RANDOM, IF_ENEMY, GO  };
//enum direction { NORTH, SOUTH, EAST, WEST };

struct TestDarwin : CppUnit::TestFixture { 

	//------------------
	// Instruction Tests
	//------------------
	
	
	void test_instruction_1(){
		instruction i1(HOP);
		instruction i2(LEFT);
		instruction i3(IF_EMPTY,4);
		instruction i4(GO, 5);
	   
		CPPUNIT_ASSERT(i1.isAction());
		CPPUNIT_ASSERT(i2.isAction());
	   	CPPUNIT_ASSERT(!i3.isAction());
		CPPUNIT_ASSERT(!i4.isAction());

		CPPUNIT_ASSERT(i3.getDestination() == 4);
		CPPUNIT_ASSERT(i4.getDestination() == 5);

		int x = 3;
		int y = 3;
	
		CPPUNIT_ASSERT(i1.newPosition(x,y,NORTH));
		CPPUNIT_ASSERT( (x == 3) && (y == 2) );
		CPPUNIT_ASSERT(i2.newPosition(x,y,NORTH)); 
		CPPUNIT_ASSERT( (x == 3) && (y == 2) );
	}

    void test_instruction_2(){
        instruction i1(HOP);

        CPPUNIT_ASSERT(i1.isAction());

        int x = 3;
        int y = 3;

        CPPUNIT_ASSERT(i1.newPosition(x,y,NORTH));
        CPPUNIT_ASSERT( (x == 3) && (y == 2) );
        CPPUNIT_ASSERT(i1.newPosition(x,y,SOUTH));
        CPPUNIT_ASSERT( (x == 3) && (y == 3) );
		CPPUNIT_ASSERT(i1.newPosition(x,y,EAST));
		CPPUNIT_ASSERT( (x == 4) && (y == 3) );
		CPPUNIT_ASSERT(i1.newPosition(x,y,WEST));
		CPPUNIT_ASSERT( (x == 3) && (y == 3) );
        }

   void test_instruction_3(){
        instruction i1(HOP);
        instruction i2(LEFT);
        instruction i3(RIGHT);
        instruction i4(INFECT);

        CPPUNIT_ASSERT(i1.isAction());
        CPPUNIT_ASSERT(i2.isAction());
        CPPUNIT_ASSERT(i3.isAction());
        CPPUNIT_ASSERT(i4.isAction());
        }
   
   void test_instruction_4(){
	   instruction i1(IF_EMPTY);
	   instruction i2(IF_ENEMY);
	   instruction i3(IF_RANDOM);
	   instruction i4(IF_WALL);
	   instruction i5(GO);
	   
	   CPPUNIT_ASSERT(!i1.isAction());
	   CPPUNIT_ASSERT(!i2.isAction());
	   CPPUNIT_ASSERT(!i3.isAction());
	   CPPUNIT_ASSERT(!i4.isAction());
	   CPPUNIT_ASSERT(!i5.isAction());	   
   }

    //-------------
   	// Specie Tests
   	//-------------
   
	void test_specie_1(){
		Species s1("frog");

		CPPUNIT_ASSERT(s1.programSize() == 0);

		s1.addInstruction( instruction(HOP)   );
		s1.addInstruction( instruction(GO, 2) );

		CPPUNIT_ASSERT(s1.programSize() == 2);
		CPPUNIT_ASSERT(s1.isSameSpecie(string("frog")));
		CPPUNIT_ASSERT(!s1.isSameSpecie(string("cat")));
		CPPUNIT_ASSERT((s1.getInstructionLine(0)).isAction());
		CPPUNIT_ASSERT((s1.getInstructionLine(1)).getDestination() == 2);
		CPPUNIT_ASSERT(s1.getPrefix() == 'f');
	}

	void test_specie_2(){
		Species s1("frog");
		Species s2("frog");

		s1.addInstruction( instruction(IF_ENEMY,5));
		s2.addInstruction( instruction(GO, 6)     );
	
		CPPUNIT_ASSERT(s1.programSize() == 1);
		CPPUNIT_ASSERT(s2.programSize() == 1);
		CPPUNIT_ASSERT(s1.isSameSpecie(s2.getName()));
		CPPUNIT_ASSERT(s1.getPrefix() == 'f');
		CPPUNIT_ASSERT(s2.getPrefix() == 'f');
	}

	void test_specie_3(){
		Species s1("puppy");
		
		s1.addInstruction( instruction(HOP)   );
		s1.addInstruction( instruction(LEFT)  );
		s1.addInstruction( instruction(RIGHT) );
		s1.addInstruction( instruction(INFECT));

		CPPUNIT_ASSERT(s1.programSize() == 4);
		CPPUNIT_ASSERT(s1.getPrefix() == 'p');
		CPPUNIT_ASSERT(s1.isSameSpecie(s1.getName()));
		CPPUNIT_ASSERT((s1.getInstructionLine(0)).isAction());
        CPPUNIT_ASSERT((s1.getInstructionLine(1)).isAction());
        CPPUNIT_ASSERT((s1.getInstructionLine(2)).isAction());
        CPPUNIT_ASSERT((s1.getInstructionLine(3)).isAction());
	}
	
	//---------------------------
	// Creature Constructor Tests
	//---------------------------

	void test_creature_construct_1(){
		Species s1("retarded frog");
		
		s1.addInstruction( instruction(HOP)   );
		s1.addInstruction( instruction(LEFT)  );
				
		Creature frog1(NORTH, s1);
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
		CPPUNIT_ASSERT(&s1 == &frog1.getSpecie());
	}
	
	void test_creature_construct_2(){
		Species s1("really stupid frog");
		
		s1.addInstruction( instruction(HOP) );
		s1.addInstruction( instruction(LEFT));
		s1.addInstruction( instruction(RIGHT));
		
		Creature frog1(NORTH, s1);
		Creature frog2(SOUTH, s1);
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
		CPPUNIT_ASSERT(&s1 == &frog1.getSpecie());
		CPPUNIT_ASSERT(frog2.getDirection() == SOUTH);
		CPPUNIT_ASSERT(frog2.hasActed(0) == false);
		CPPUNIT_ASSERT(&s1 == &frog2.getSpecie());
		CPPUNIT_ASSERT(&frog2.getSpecie() == &frog1.getSpecie());
	}
	
	void test_creature_construct_3(){
		Species s1("stupid frog");
		Species s2("not so stupid frog");
		
		s1.addInstruction( instruction(LEFT) );
		s1.addInstruction( instruction(RIGHT));
		
		s2.addInstruction( instruction(LEFT) );
		s2.addInstruction( instruction(HOP)  );
		s2.addInstruction( instruction(RIGHT));
		s2.addInstruction( instruction(HOP)  );
		s2.addInstruction( instruction(GO,0) );
		
		Creature frog1(NORTH,s1);
		Creature frog2(SOUTH,s2);
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
		CPPUNIT_ASSERT(&s1 == &frog1.getSpecie());
		CPPUNIT_ASSERT(frog2.getDirection() == SOUTH);
		CPPUNIT_ASSERT(frog2.hasActed(0) == false);
		CPPUNIT_ASSERT(&s2 == &frog2.getSpecie());
		CPPUNIT_ASSERT(&frog1.getSpecie() != &frog2.getSpecie());		
	}
	
	//---------------------------
	// Creature Turn Switch Tests
	//---------------------------
	
	void test_creature_switch_turn_1(){
		Species s1("frog");
		
		Creature frog1(NORTH,s1);
		
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
		
		frog1.switchTurn();
		
		CPPUNIT_ASSERT(frog1.hasActed(0) == true);
	}	
	
	void test_creature_switch_turn_2(){
		Species s1("frog");
		
		Creature frog1(NORTH,s1);
		
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
		
		frog1.switchTurn();
		frog1.switchTurn();
		
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
	}	
	
	void test_creature_switch_turn_3(){
		Species s1("frog");
		
		Creature frog1(NORTH,s1);
		
		CPPUNIT_ASSERT(frog1.hasActed(0) == false);
		
		frog1.switchTurn();
		frog1.switchTurn();
		
		CPPUNIT_ASSERT(frog1.hasActed(1) == true);
	}

	//-----------------------------------
	// Creature Jump PC / Take Turn Tests
	//-----------------------------------
	
	void test_creature_jump_turn_1(){
		Species s1("frog");
		
		s1.addInstruction( instruction(HOP) );
		
		Creature frog1(NORTH, s1);
		
		CPPUNIT_ASSERT(frog1.getSpecie().programSize() == 1);
		
		s1.addInstruction( instruction(GO,0) );
		
		CPPUNIT_ASSERT(frog1.getSpecie().programSize() == 2);		
		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == 0);		
		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == 8);
		
		frog1.resetPC();
		
		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == 0);
		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == 8);
		
		frog1.jumpPC(0);
		
		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == 0);
	}
	
	void test_creature_jump_turn_2(){
		Species s1("frog");
		Species s2("cat");
		
		s1.addInstruction( instruction(HOP) );
		s1.addInstruction( instruction(GO,0));
		
		s2.addInstruction( instruction(LEFT));
		s2.addInstruction( instruction(GO,0));
		
		Creature frog(NORTH, s1);
		Creature cat(SOUTH, s2);
		
		CPPUNIT_ASSERT(frog.takeTurn().getOp() == 0);
		CPPUNIT_ASSERT(cat.takeTurn().getOp() == 1);
		
		CPPUNIT_ASSERT(frog.takeTurn().getOp() == cat.takeTurn().getOp());
		
		frog.resetPC();
		cat.resetPC();
		
		CPPUNIT_ASSERT(frog.takeTurn().getOp() != cat.takeTurn().getOp());
	}
	
	void test_creature_jump_turn_3(){
		Species s1("frog");
		
		s1.addInstruction( instruction(HOP) );
		s1.addInstruction( instruction(GO,0));
		
		Creature frog1(NORTH, s1);
		Creature frog2(SOUTH, s1);
		
		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == frog2.takeTurn().getOp());
		
		frog1.jumpPC( frog1.takeTurn().getDestination() );
		frog2.jumpPC( frog2.takeTurn().getDestination() );

		CPPUNIT_ASSERT(frog1.takeTurn().getOp() == frog2.takeTurn().getOp());
	}
	
	//------------------------
	// Turn Left / Right Tests
	//------------------------
	
	void test_creature_left_right_1(){
		Species s1("frog");
		
		Creature frog1(NORTH, s1);
		
		frog1.turnLeft();
		CPPUNIT_ASSERT(frog1.getDirection() == WEST);
		frog1.turnRight();
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
	}
	
	void test_creature_left_right_2(){
		Species s1("frog");
		
		Creature frog1(NORTH, s1);
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
		
		frog1.turnLeft();
		frog1.turnLeft();
		frog1.turnLeft();
		frog1.turnLeft();
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
		
		frog1.turnRight();
		frog1.turnRight();
		frog1.turnRight();
		frog1.turnRight();
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
	}
	
	void test_creature_left_right_3(){
		Species s1("frog");
		
		Creature frog1(NORTH, s1);
		Creature frog2(SOUTH, s1);
		
		CPPUNIT_ASSERT(frog1.getDirection() == NORTH);
		CPPUNIT_ASSERT(frog2.getDirection() == SOUTH);
		
		frog1.turnRight();
		frog2.turnLeft();
		
		CPPUNIT_ASSERT(frog1.getDirection() == frog2.getDirection());
		
		frog1.turnRight();
		frog2.turnRight();
		
		CPPUNIT_ASSERT(frog1.getDirection() == frog2.getDirection());
		
		frog1.turnRight();
		frog1.turnRight();
		frog2.turnLeft();
		frog2.turnLeft();
		
		CPPUNIT_ASSERT(frog1.getDirection() == frog2.getDirection());
	}
	
	//-----------------
	// Same Specie Test
	//-----------------
	
	void test_creature_same_specie_1(){
		Species s1("frog");
		Creature frog1(NORTH, s1);
		Creature frog2(SOUTH, s1);
		
		CPPUNIT_ASSERT(frog1.isSameSpecie(frog2));		
	}
	
	void test_creature_same_specie_2(){
		Species s1("frog");
		Species s2("cat");
		Creature frog(NORTH, s1);
		Creature cat(SOUTH, s2);
		
		CPPUNIT_ASSERT(!frog.isSameSpecie(cat));		
	}
	
	void test_creature_same_specie_3(){
		Species s1("frog");
		Species s2("cat");
		Species s3("frog cat");
		Creature frog(NORTH, s1);
		Creature cat(SOUTH, s2);
		Creature frogcat(EAST, s3);
		
		CPPUNIT_ASSERT(!frog.isSameSpecie(cat));
		CPPUNIT_ASSERT(!frog.isSameSpecie(frogcat));
		CPPUNIT_ASSERT(!cat.isSameSpecie(frogcat));
	}
	
	//-------------
	// Infect Tests
	//-------------
	
	void test_creature_infect_1(){
		Species s1("frog");
		Species s2("cat");
		
		s1.addInstruction( instruction(HOP) );		
		s2.addInstruction( instruction(LEFT));
		
		Creature frog(NORTH,s1);
		CPPUNIT_ASSERT(frog.takeTurn().getOp() == 0);
		CPPUNIT_ASSERT(&frog.getSpecie() == &s1);		
		frog.infect(s2);		
		CPPUNIT_ASSERT(&frog.getSpecie() == &s2);	
		CPPUNIT_ASSERT(frog.takeTurn().getOp() == 1);
	}
	
	void test_creature_infect_2(){
		Species s1("frog");
		Species s2("cat");
		
		s1.addInstruction( instruction(HOP) );		
		s2.addInstruction( instruction(LEFT));
				
		Creature frog(NORTH, s1);
		Creature cat(NORTH, s2);
		
		CPPUNIT_ASSERT(!frog.isSameSpecie(cat));
		CPPUNIT_ASSERT(frog.takeTurn().getOp() == 0);
		CPPUNIT_ASSERT(cat.takeTurn().getOp() == 1);
		
		frog.infect( cat.getSpecie() );
		
		CPPUNIT_ASSERT(frog.isSameSpecie(cat));
		CPPUNIT_ASSERT(frog.takeTurn().getOp() == 1);
	}
	
	void test_creature_infect_3(){
		Species s1("frog");
		Species s2("cat");
		
		s1.addInstruction( instruction(HOP) );
		s2.addInstruction( instruction(LEFT));
		
		Creature frog(NORTH, s1);
		Creature cat (NORTH, s2);
		
		CPPUNIT_ASSERT(!frog.isSameSpecie(cat));
		CPPUNIT_ASSERT(cat.takeTurn().getOp() == 1);
		
		frog.infect( cat.getSpecie() );
		cat.infect( frog.getSpecie() );
		
		CPPUNIT_ASSERT(cat.takeTurn().getOp() == 1);
		CPPUNIT_ASSERT(frog.isSameSpecie(cat));
	}
	
	//----------------------------------
	// Test Darwin Constructor / In Grid
	//----------------------------------
	
	void test_darwin_constructor_grid_1(){
		Darwin <Creature> world(0,0);
		
		CPPUNIT_ASSERT(!world.inGrid(1,1));
		CPPUNIT_ASSERT(!world.inGrid(2,2));
		CPPUNIT_ASSERT(!world.inGrid(0,0));
	}
	
	void test_darwin_constructor_grid_2(){
		Darwin <Creature> world(2,2);
		
		CPPUNIT_ASSERT(world.inGrid(1,1));
		CPPUNIT_ASSERT(world.inGrid(0,0));
		CPPUNIT_ASSERT(!world.inGrid(5,1));
		CPPUNIT_ASSERT(!world.inGrid(1,5));		
	}
	
	void test_darwin_constructor_grid_3(){
		Darwin <Creature> world(0,5);
		
		CPPUNIT_ASSERT(!world.inGrid(1,1));
		CPPUNIT_ASSERT(!world.inGrid(0,0));
		CPPUNIT_ASSERT(!world.inGrid(5,0));
		CPPUNIT_ASSERT(!world.inGrid(0,5));			
	}
	
	void test_darwin_constructor_grid_4(){
		Darwin <Creature> world(1,5);
			
		CPPUNIT_ASSERT(!world.inGrid(1,1));
		CPPUNIT_ASSERT(world.inGrid(0,0));
		CPPUNIT_ASSERT(!world.inGrid(5,0));
		CPPUNIT_ASSERT(world.inGrid(0,3));			
	}
	
	//------------------------------------------------
	// Test Darwin Object Placement / Object Detection
	//------------------------------------------------
	
	void test_darwin_object_placement_1(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");
		Creature c1(NORTH,s1);
		
		CPPUNIT_ASSERT(world.placeObject(3,3,c1));
		CPPUNIT_ASSERT(!world.placeObject(10,4,c1));
		CPPUNIT_ASSERT(world.objectAtPoint(3,3));
	}
	
	void test_darwin_object_placement_2(){
			Darwin <Creature> world(5,5);
			
			Species s1("frog");
			Creature c1(NORTH,s1);
			Creature c2(SOUTH,s1);
			
			CPPUNIT_ASSERT(world.placeObject(3,3,c1));
			CPPUNIT_ASSERT(world.placeObject(1,1,c2));
			CPPUNIT_ASSERT(!world.placeObject(10,4,c1));
			CPPUNIT_ASSERT(world.objectAtPoint(3,3));
			CPPUNIT_ASSERT(world.objectAtPoint(1,1));
			CPPUNIT_ASSERT(!world.objectAtPoint(2,2));
			CPPUNIT_ASSERT(!world.objectAtPoint(4,2));
			CPPUNIT_ASSERT(!world.objectAtPoint(100,100));
	}
	
	void test_darwin_object_placement_3(){
			Darwin <Creature> world(5,5);
			
			Species s1("frog");
			Species s2("cat");
			Creature c1(NORTH,s1);
			Creature c2(NORTH,s2);
				
			CPPUNIT_ASSERT(world.placeObject(3,3,c1));
			CPPUNIT_ASSERT(world.placeObject(2,2,c2));
			CPPUNIT_ASSERT(!world.placeObject(10,4,c1));
			CPPUNIT_ASSERT(world.objectAtPoint(3,3));
			CPPUNIT_ASSERT(world.objectAtPoint(2,2));
	}
	
	//------------------------
	// Darwin Test Move Object
	//------------------------

	void test_darwin_move_object_1(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");		
		Creature c1(NORTH,s1);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,c1));
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));
		CPPUNIT_ASSERT(!world.objectAtPoint(2,1));
		
		CPPUNIT_ASSERT(world.moveObject(2,2,c1.getDirection()));
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));
		CPPUNIT_ASSERT(!world.objectAtPoint(2,2));
		
		CPPUNIT_ASSERT(!world.moveObject(0,0,NORTH));
		CPPUNIT_ASSERT(!world.moveObject(3,3,NORTH));
		CPPUNIT_ASSERT(!world.moveObject(1,0,NORTH));
	}
	
	void test_darwin_move_object_2(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");		
		Creature c1(NORTH,s1);
		Creature c2(WEST, s1);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,c1));
		CPPUNIT_ASSERT(world.placeObject(2,1,c2));
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));
		
		CPPUNIT_ASSERT(world.moveObject(2,2,c1.getDirection()));
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));
		
		CPPUNIT_ASSERT(world.moveObject(2,1,c2.getDirection()));
		CPPUNIT_ASSERT(world.moveObject(2,2,c1.getDirection()));
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));
		CPPUNIT_ASSERT(world.objectAtPoint(1,1));
		CPPUNIT_ASSERT(!world.objectAtPoint(2,2));
	}
	
	void test_darwin_move_object_3(){
		Darwin <Creature> world(4,4);
		
		Species s1("frog");
		Creature c1(NORTH, s1);
		Creature c2(EAST, s1);
		Creature c3(SOUTH, s1);
		Creature c4(WEST, s1);
		
		CPPUNIT_ASSERT(world.placeObject(1,1,c4));
		CPPUNIT_ASSERT(world.placeObject(1,2,c3));
		CPPUNIT_ASSERT(world.placeObject(2,2,c2));
		CPPUNIT_ASSERT(world.placeObject(2,1,c1));
		
		CPPUNIT_ASSERT(world.objectAtPoint(1,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(0,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,0));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,3));
		
		CPPUNIT_ASSERT(world.moveObject(1,1,WEST));
		CPPUNIT_ASSERT(world.moveObject(1,2,SOUTH));
		CPPUNIT_ASSERT(world.moveObject(2,2,EAST));
		CPPUNIT_ASSERT(world.moveObject(2,1,NORTH));
		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(0,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,0));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(1,3));
	}
	
	//----------------------------------
	// Darwin Determine Instruction Jump
	//----------------------------------
	
	void test_darwin_instruct_jump_1(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");
		Creature c1(NORTH, s1);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,c1));
		
		CPPUNIT_ASSERT(world.determineJump( instruction(GO,5)       , c1 , 2 , 2 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_WALL,5)  , c1 , 2 , 2 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_EMPTY,5) , c1 , 2 , 2 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_ENEMY,5) , c1 , 2 , 2 ) == -1);
		
		int random = world.determineJump( instruction(IF_RANDOM,5) , c1 , 2 , 2 );
		
		CPPUNIT_ASSERT(random == -1 || random == 5);
	}
	
	void test_darwin_instruct_jump_2(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");
		Species s2("cat");
		
		Creature frog(NORTH, s1);
		Creature cat(EAST, s2);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,frog));
		CPPUNIT_ASSERT(world.placeObject(2,1,cat));
		
		CPPUNIT_ASSERT(world.determineJump( instruction(GO,5)       , frog , 2 , 2 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_WALL,5)  , frog , 2 , 2 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_EMPTY,5) , frog , 2 , 2 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_ENEMY,5) , frog , 2 , 2 ) ==  5);
		
		CPPUNIT_ASSERT(world.determineJump( instruction(GO,5)       , cat , 2 , 1 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_WALL,5)  , cat , 2 , 1 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_EMPTY,5) , cat , 2 , 1 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_ENEMY,5) , cat , 2 , 1 ) == -1);
	}
	
	void test_darwin_instruct_jump_3(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");
		Species s2("cat");
		
		Creature frog(NORTH, s1);
		Creature frog2(NORTH, s1);
		Creature cat(EAST, s2);
		Creature cat2(NORTH, s2);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,frog));
		CPPUNIT_ASSERT(world.placeObject(0,0,frog2));
		CPPUNIT_ASSERT(world.placeObject(2,1,cat));
		CPPUNIT_ASSERT(world.placeObject(3,1,cat2));
		
		CPPUNIT_ASSERT(world.determineJump( instruction(GO,5)       , frog , 2 , 2 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_WALL,5)  , frog , 2 , 2 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_EMPTY,5) , frog , 2 , 2 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_ENEMY,5) , frog , 2 , 2 ) ==  5);
			
		CPPUNIT_ASSERT(world.determineJump( instruction(GO,5)       , cat , 2 , 1 ) ==  5);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_WALL,5)  , cat , 2 , 1 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_EMPTY,5) , cat , 2 , 1 ) == -1);
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_ENEMY,5) , cat , 2 , 1 ) == -1);
		
		CPPUNIT_ASSERT(world.determineJump( instruction(IF_WALL,5)  , frog2 , 0 , 0) == 5);
	}
	
	//-----------------------
	// Darwin Infect Creature
	//-----------------------
	
	void test_darwin_infect_1(){
		Darwin <Creature> world(5,5);
		
		Species s1("frog");
		
		Creature frog1(NORTH,s1);
		Creature frog2(NORTH,s1);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,frog1));
		CPPUNIT_ASSERT(world.placeObject(2,1,frog2));
		
		CPPUNIT_ASSERT(!world.infectCreature(frog1,2,2));
	}
	
	void test_darwin_infect_2(){
		Darwin <Creature> world(5,5);
		
		Species frog("frog");
		Species cat("cat");
		
		Creature f(NORTH,frog);
		Creature c(NORTH,cat);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,f));
		CPPUNIT_ASSERT(world.placeObject(2,1,c));
		
		CPPUNIT_ASSERT(!f.isSameSpecie(c));
		CPPUNIT_ASSERT(world.infectCreature(f,2,2));
		CPPUNIT_ASSERT(f.isSameSpecie(c));
		
	}
	
	void test_darwin_infect_3(){
		Darwin <Creature> world(5,5);
		
		Species frog("frog");
		Species cat("cat");
		Species frogcat("frogcat");
		
		Creature f (NORTH, frog);
		Creature c (NORTH, cat);
		Creature fc(NORTH, frogcat);
		
		CPPUNIT_ASSERT(world.placeObject(2,2,f));
		CPPUNIT_ASSERT(world.placeObject(2,1,c));
		CPPUNIT_ASSERT(world.placeObject(2,0,fc));
		
		CPPUNIT_ASSERT(!f.isSameSpecie(c));
		CPPUNIT_ASSERT(!f.isSameSpecie(fc));
		CPPUNIT_ASSERT(!c.isSameSpecie(fc));
		
		CPPUNIT_ASSERT(world.infectCreature(c,2,1));
	
		CPPUNIT_ASSERT(!f.isSameSpecie(c));
		CPPUNIT_ASSERT(!f.isSameSpecie(fc));
		CPPUNIT_ASSERT(c.isSameSpecie(fc));
		
		CPPUNIT_ASSERT(world.infectCreature(f,2,2));
		CPPUNIT_ASSERT(world.infectCreature(c,2,1));
		
		CPPUNIT_ASSERT(f.isSameSpecie(c));
		CPPUNIT_ASSERT(f.isSameSpecie(fc));
		CPPUNIT_ASSERT(c.isSameSpecie(fc));
	}
	
	//------------------------------------------
	// Darwin Step (Essentially Acceptance Test)
	//------------------------------------------
	
	void test_darwin_step_1(){
		Darwin <Creature> world(4,4);
				
		Species s1("frog");
		s1.addInstruction( instruction(HOP) );
		s1.addInstruction( instruction(GO,0));
		Creature c1(NORTH, s1);
		Creature c2(EAST, s1);
		Creature c3(SOUTH, s1);
		Creature c4(WEST, s1);
				
		CPPUNIT_ASSERT(world.placeObject(1,1,c4));
		CPPUNIT_ASSERT(world.placeObject(1,2,c3));
		CPPUNIT_ASSERT(world.placeObject(2,2,c2));
		CPPUNIT_ASSERT(world.placeObject(2,1,c1));
		
		
		CPPUNIT_ASSERT(world.objectAtPoint(1,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(0,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,0));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,3));
		
		CPPUNIT_ASSERT(world.step() == 1);
		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(0,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,0));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(1,3));
		
		CPPUNIT_ASSERT(world.step() == 2);
		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(0,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,0));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(1,3));
	}
	
	void test_darwin_step_2(){
		Darwin <Creature> world(6,6);
				
		Species s1("frog");
		s1.addInstruction( instruction(HOP) );
		s1.addInstruction( instruction(GO,0));
		Creature c1(NORTH, s1);
		Creature c2(EAST, s1);
		Creature c3(SOUTH, s1);
		Creature c4(WEST, s1);
				
		CPPUNIT_ASSERT(world.placeObject(2,2,c4));
		CPPUNIT_ASSERT(world.placeObject(2,3,c3));
		CPPUNIT_ASSERT(world.placeObject(3,3,c2));
		CPPUNIT_ASSERT(world.placeObject(3,2,c1));
		
		
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,3));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,3));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,4));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(4,3));
		
		CPPUNIT_ASSERT(world.step() == 1);
		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,3));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,3));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,4));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,1));		
		CPPUNIT_ASSERT(world.objectAtPoint(4,3));
		CPPUNIT_ASSERT(!world.objectAtPoint(0,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,0));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,5));		
		CPPUNIT_ASSERT(!world.objectAtPoint(5,3));
		
		CPPUNIT_ASSERT(world.step() == 2);
		
		CPPUNIT_ASSERT(!world.objectAtPoint(1,2));		
		CPPUNIT_ASSERT(!world.objectAtPoint(2,4));		
		CPPUNIT_ASSERT(!world.objectAtPoint(3,1));		
		CPPUNIT_ASSERT(!world.objectAtPoint(4,3));		
		CPPUNIT_ASSERT(world.objectAtPoint(0,2));		
		CPPUNIT_ASSERT(world.objectAtPoint(3,0));		
		CPPUNIT_ASSERT(world.objectAtPoint(2,5));		
		CPPUNIT_ASSERT(world.objectAtPoint(5,3));
	}
	
	void test_darwin_step_3(){
		Darwin <Creature> world(4,4);
		
		Species circle_frog("frog");
		Creature froggy(NORTH,circle_frog);
		
		circle_frog.addInstruction( instruction(HOP) );
		circle_frog.addInstruction( instruction(LEFT));
		circle_frog.addInstruction( instruction(GO,0));
		
		CPPUNIT_ASSERT(world.placeObject(2,2,froggy));
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));
		
		CPPUNIT_ASSERT(world.step() == 1);
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));
		CPPUNIT_ASSERT(world.step() == 2);
		CPPUNIT_ASSERT(world.objectAtPoint(2,1));
		CPPUNIT_ASSERT(world.step() == 3);
		CPPUNIT_ASSERT(world.objectAtPoint(1,1));
		CPPUNIT_ASSERT(world.step() == 4);
		CPPUNIT_ASSERT(world.objectAtPoint(1,1));
		CPPUNIT_ASSERT(world.step() == 5);
		CPPUNIT_ASSERT(world.objectAtPoint(1,2));
		CPPUNIT_ASSERT(world.step() == 6);
		CPPUNIT_ASSERT(world.objectAtPoint(1,2));
		CPPUNIT_ASSERT(world.step() == 7);
		CPPUNIT_ASSERT(world.objectAtPoint(2,2));
	}
	
	//-------------------
	// Test Darwin Output
	//-------------------
	
	void test_darwin_output_1(){
		Darwin <Creature> world(2,2);
		std::ostringstream w;
		world.outputWorld(w);		
		CPPUNIT_ASSERT(w.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
	}
	
	void test_darwin_output_2(){
		Darwin <Creature> world(2,2);
		std::ostringstream w;
		world.outputWorld(w);		
		CPPUNIT_ASSERT(w.str() ==  "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
		
		Species frog("frog");
		Creature f(NORTH,frog);
		CPPUNIT_ASSERT(world.placeObject(1,1,f));
		
		std::ostringstream w2;
		world.outputWorld(w2);
		CPPUNIT_ASSERT(w2.str() == "Turn = 0.\n  01\n0 ..\n1 .f\n\n");
	}
	
	void test_darwin_output_3(){
		Darwin <Creature> world(2,2);
		std::ostringstream w;
		world.outputWorld(w);		
		CPPUNIT_ASSERT(w.str() ==  "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
		
		Species frog("frog");
		Creature f(NORTH,frog);
		CPPUNIT_ASSERT(world.placeObject(1,1,f));
		frog.addInstruction( instruction(HOP) );
		
		std::ostringstream w2;
		world.outputWorld(w2);
		CPPUNIT_ASSERT(w2.str() == "Turn = 0.\n  01\n0 ..\n1 .f\n\n");
			
		CPPUNIT_ASSERT(world.step() == 1);
			
		std::ostringstream w3;
		world.outputWorld(w3);
		CPPUNIT_ASSERT(w3.str() == "Turn = 1.\n  01\n0 .f\n1 ..\n\n");
	}



	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(test_instruction_1);
	CPPUNIT_TEST(test_instruction_2);
	CPPUNIT_TEST(test_instruction_3);
	CPPUNIT_TEST(test_instruction_4);
	CPPUNIT_TEST(test_specie_1);
	CPPUNIT_TEST(test_specie_2);
	CPPUNIT_TEST(test_specie_3);
	CPPUNIT_TEST(test_creature_construct_1);
	CPPUNIT_TEST(test_creature_construct_2);
	CPPUNIT_TEST(test_creature_construct_3);
	CPPUNIT_TEST(test_creature_switch_turn_1);
	CPPUNIT_TEST(test_creature_switch_turn_2);
	CPPUNIT_TEST(test_creature_switch_turn_3);
	CPPUNIT_TEST(test_creature_jump_turn_1);
	CPPUNIT_TEST(test_creature_jump_turn_2);
	CPPUNIT_TEST(test_creature_jump_turn_3);
	CPPUNIT_TEST(test_creature_left_right_1);
	CPPUNIT_TEST(test_creature_left_right_2);
	CPPUNIT_TEST(test_creature_left_right_3);
	CPPUNIT_TEST(test_creature_same_specie_1);
	CPPUNIT_TEST(test_creature_same_specie_2);
	CPPUNIT_TEST(test_creature_same_specie_3);
	CPPUNIT_TEST(test_creature_infect_1);
	CPPUNIT_TEST(test_creature_infect_2);
	CPPUNIT_TEST(test_creature_infect_3);
	CPPUNIT_TEST(test_darwin_constructor_grid_1);
	CPPUNIT_TEST(test_darwin_constructor_grid_2);
	CPPUNIT_TEST(test_darwin_constructor_grid_3);
	CPPUNIT_TEST(test_darwin_constructor_grid_4);
	CPPUNIT_TEST(test_darwin_object_placement_1);
	CPPUNIT_TEST(test_darwin_object_placement_2);
	CPPUNIT_TEST(test_darwin_object_placement_3);
	CPPUNIT_TEST(test_darwin_move_object_1);
	CPPUNIT_TEST(test_darwin_move_object_2);
	CPPUNIT_TEST(test_darwin_move_object_3);
	CPPUNIT_TEST(test_darwin_instruct_jump_1);
	CPPUNIT_TEST(test_darwin_instruct_jump_2);
	CPPUNIT_TEST(test_darwin_instruct_jump_3);
	CPPUNIT_TEST(test_darwin_infect_1);
	CPPUNIT_TEST(test_darwin_infect_2);
	CPPUNIT_TEST(test_darwin_infect_3);
	CPPUNIT_TEST(test_darwin_step_1);
	CPPUNIT_TEST(test_darwin_step_2);
	CPPUNIT_TEST(test_darwin_step_3);
	CPPUNIT_TEST(test_darwin_output_1);
	CPPUNIT_TEST(test_darwin_output_2);
	CPPUNIT_TEST(test_darwin_output_3);
	CPPUNIT_TEST_SUITE_END();
};

int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);
	cout << "TestDarwin.c++" << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDarwin::suite());
	tr.run();

	cout << "Done." << endl;
	return 0;
}
