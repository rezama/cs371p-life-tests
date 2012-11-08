// ------------------------------
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

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Darwin.h"

using namespace std;

struct TestDarwin : CppUnit::TestFixture {

    void test_print(){
      cout << "test" << endl;
      World x(5, 5);
      x.print();
    }
				
    void test_place_creature(){
    	cout << "test place_creature" << endl;
	    World x(13, 13);
      Species specie;
     	Creature f('n', 0, 'F', &specie);
	    x.place_creature(f, 3, 4);
      x.print();
    }
    
    void test_isEmpty(){
    	cout << "test isEmpty" << endl;
    	World x(7, 7);
    	bool test;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isEmpty('n');
    	CPPUNIT_ASSERT(test == false);
    }

    void test_isEmpty_2(){
    	cout << "test isEmpty2" << endl;
    	World x(7, 7);
    	bool test;
    	x.curr_row = 2;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isEmpty('n');
    	CPPUNIT_ASSERT(test == true);
    }

    void test_isEmpty_3(){
    	cout << "test isEmpty3" << endl;
    	World x(7, 7);
    	bool test;
      Species specie;
    	Creature f('n', 0, 'X', &specie);
    	x.place_creature(f, 1, 3);
    	x.curr_row = 2;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isEmpty('n');
     	CPPUNIT_ASSERT(test == false);
    }

    void test_isWall(){
    	cout << "test isWall" << endl;
    	World x(7, 7);
    	bool test;
    	x.curr_row = 2;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isWall('n');
    	CPPUNIT_ASSERT(test == false);
    }

    void test_isWall_2(){
    	cout << "test isWall2" << endl;
    	World x(7, 7);
    	bool test;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isWall('n');
    	CPPUNIT_ASSERT(test == true);
    }

    void test_isWall_3(){
    	cout << "test isWall3" << endl;
    	World x(7, 7);
    	bool test;
      Species specie;
    	Creature f('n', 0, 'X', &specie);
    	x.place_creature(f, 1, 3);
    	x.curr_row = 2;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isWall('n');
    	CPPUNIT_ASSERT(test == false);
    }

    void test_isCreature(){
    	cout << "test isCreature" << endl;
    	World x(7, 7);
    	bool test;
        Species specie;
    	Creature f('n', 0, 'X', &specie);
    	x.place_creature(f, 1, 3);
    	x.curr_row = 2;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isCreature('n');
    	CPPUNIT_ASSERT(test == true);
    }

    void test_isCreature_2(){
    	cout << "test isCreature2" << endl;
    	World x(7, 7);
    	bool test;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isCreature('n');
    	CPPUNIT_ASSERT(test == false);
    }
     void test_isCreature_3(){
    	cout << "test isCreature3" << endl;
    	World x(7, 7);
    	bool test;
    	x.curr_row = 2;
    	x.curr_column = 3;
    	Instruction first(x, "andy", 0);
    	test = first.isCreature('n');
    	CPPUNIT_ASSERT(test == false);
    }



     void test_hop(){
    	cout << "test hop" << endl;

      // create world and a hop instruction
    	World world(7, 7);
    	Instruction instrOne(world, "hop", 1);

      // create righty specie (always goes right)
      	Species simpleHopper;
     	simpleHopper.addInstr(instrOne);
	

      	Creature creature('s', 0, 'h', &simpleHopper);
      	world.place_creature(creature, 0, 0);
      	world.print();
      	int progC = 0;
      	char direction = 'e';
	//im concerned about a safety issue here
	//by this implementation, we can move a hopper
	//regardless of its initial direction
	
	//we need safe access to a creatures direction		
      	instrOne.execute(progC, direction);
      	world.print();
    }





    void test_hop_1(){
    	cout << "test hop1" << endl;

      // create world and a hop instruction
    	World world(7, 7);
    	Instruction instrOne(world, "hop", 0);

      // create simple hopper
      Species simpleHopper;
      simpleHopper.addInstr(instrOne);
      
      Creature creature('s', 0, 'h', &simpleHopper);
      world.place_creature(creature, 0, 0);
      world.print();
      int progC = 0;
      char direction = 's';
      instrOne.execute(progC, direction);
      world.print();
    }

    void test_hop_evolve(){
    	cout << "test hop evolve" << endl;

      // create world and instructions
    	World world(7, 7);
    	Instruction instrOne(world, "hop", 0);
    	Instruction instrTwo(world, "go", 0);

      // create simple hopper
      Species simpleHopper;
      simpleHopper.addInstr(instrOne);
      simpleHopper.addInstr(instrTwo);
      
      Creature creature('e', 0, 'h', &simpleHopper);
      world.place_creature(creature, 0, 0);
      world.print();
      int progC = 0;
      char direction = 's';

      //hop once going south
      simpleHopper.evolve(progC, direction);
      CPPUNIT_ASSERT(progC == 1);
      CPPUNIT_ASSERT(direction == 's');
      world.print();

      //update world manually
      int row = 0;
      int col = 0;
      instrOne.getNextPos(direction, row, col);
      CPPUNIT_ASSERT(row == 1);
      CPPUNIT_ASSERT(col == 0);

      world.curr_row = row;
      world.curr_column = col;

      //hop once more going south
      simpleHopper.evolve(progC, direction);
      CPPUNIT_ASSERT(progC == 1);
      CPPUNIT_ASSERT(direction == 's');
      world.print();
    }

     void test_world_run_hopper(){
    	cout << "test world run hopper" << endl;

      // create world and a hop instruction
    	World world(7, 7);
    	Instruction hop (world, "hop", 0);
    	Instruction right(world, "right", 0);
    	Instruction left(world, "left", 0);
    	Instruction go(world, "go", 0);

      // create righty specie (always goes right)
      Species simpleHopper;
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(right);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(left);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(right);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(go);
      
      Creature creature('e', 0, 'h', &simpleHopper);
      world.place_creature(creature, 0, 0);
	//from the assertion below we know the creature faces its initial direction
//      CPPUNIT_ASSERT(creature.direction == 'n');
      world.run(7);
    }
void test_world_run_hopper2(){
    	cout << "test world run hopper" << endl;

      // create world and a hop instruction
    	World world(7, 7);
    	Instruction hop (world, "hop", 0);
    	Instruction right(world, "right", 0);
    	Instruction left(world, "left", 0);
    	Instruction go(world, "go", 0);

      // create righty specie (always goes right)
      Species simpleHopper;
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(left);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(right);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(left);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(go);
      
      Creature creature('w', 0, 'h', &simpleHopper);
      world.place_creature(creature, 0, 6);
	//from the assertion below we know the creature faces its initial direction
//      CPPUNIT_ASSERT(creature.direction == 'n');
      world.run(7);
    }
void test_world_run_hopper3(){
    	cout << "test world run hopper" << endl;

      // create world and a hop instruction
    	World world(7, 7);
    	Instruction hop (world, "hop", 0);
    	Instruction right(world, "right", 0);
    	Instruction left(world, "left", 0);
    	Instruction go(world, "go", 0);

      // create righty specie (always goes right)
      Species simpleHopper;
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(left);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(right);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(left);
      simpleHopper.addInstr(hop);
      simpleHopper.addInstr(go);
      
      Creature creature('e', 0, 'h', &simpleHopper);
      world.place_creature(creature, 6, 0);
	//from the assertion below we know the creature faces its initial direction
//      CPPUNIT_ASSERT(creature.direction == 'n');
      world.run(7);
    }

    void test_ifEmpty(){
	cout << "test is_empty instruction" << endl;
	
	World world(7, 7);
	Instruction hop(world, "hop", 0);
	Instruction isEmpty(world, "if_empty", 0);
	Instruction right(world, "right", 0);
	Instruction left(world, "left" , 0);
	Instruction go(world, "go", 0);
	Species beta;	
	Species alpha;
	alpha.addInstr(hop);
	alpha.addInstr(isEmpty);
	alpha.addInstr(right);
	alpha.addInstr(go);
	beta.addInstr(left);
	beta.addInstr(go);
	Creature y('s', 0, 'y', &beta);
	Creature x('e', 0, 'x', &alpha);
	world.place_creature(x, 0, 0);
	world.place_creature(y, 0, 4);
	world.run(20);
    }
	
 void test_ifEmpty2(){
	cout << "test is_empty instruction" << endl;
	
	World world(7, 7);
	Instruction hop(world, "hop", 0);
	Instruction isEmpty(world, "if_empty", 0);
	Instruction right(world, "right", 0);
	Instruction go(world, "go", 0);
	Species alpha;
	alpha.addInstr(hop);
	alpha.addInstr(isEmpty);
	alpha.addInstr(right);
	alpha.addInstr(go);
	Creature y('s', 0, 'y', &alpha);
	Creature x('e', 0, 'x', &alpha);
	world.place_creature(x, 0, 0);
	world.place_creature(y, 0, 4);
	world.run(20);
    }
 void test_ifWall(){
	cout << "test if_wall instruction" << endl;
	
	World world(7, 7);
	Instruction hop(world, "hop", 0);
	Instruction ifWall(world, "if_wall", 3);
	Instruction left(world, "left", 0);
	Instruction go(world, "go", 0);
	Species alpha;

	alpha.addInstr(ifWall);
	alpha.addInstr(hop);
	alpha.addInstr(go);
	alpha.addInstr(left);
	alpha.addInstr(left);
	alpha.addInstr(go);
	Creature x('e', 0, 'x', &alpha);
	world.place_creature(x, 0, 0);
	world.run(20);
    }
 void test_ifEnemy(){
	cout << "test if_enemy instruction" << endl;
	
	World world(7, 7);
	Instruction hop(world, "hop", 0);
	Instruction ifEnemy(world, "if_enemy", 3);
	Instruction left(world, "left", 0);
	Instruction go(world, "go", 0);
	Species alpha;
	Species beta;
	alpha.addInstr(ifEnemy);
	alpha.addInstr(hop);
	alpha.addInstr(go);
	alpha.addInstr(left);
	alpha.addInstr(go);
	beta.addInstr(left);
	beta.addInstr(go);

	Creature x('e', 0, 'x', &alpha);
	Creature y('n', 0, 'y', &beta);
	world.place_creature(x, 4, 0);
	world.place_creature(y, 4, 4);
	world.run(6);
    }
 void test_infect(){
	cout << "test if_enemy instruction" << endl;
	
	World world(7, 7);
	Instruction hop(world, "hop", 0);
	Instruction ifEnemy(world, "if_enemy", 3);
	Instruction infect(world, "infect", 0);
	Instruction left(world, "left", 0);
	Instruction go(world, "go", 0);
	Instruction right(world, "right", 0);
	Instruction go2(world, "go", 5);

	Species alpha;
	Species beta;
	alpha.addInstr(ifEnemy);
	alpha.addInstr(hop);
	alpha.addInstr(go);
	alpha.addInstr(infect);
	alpha.addInstr(go2);
	alpha.addInstr(left);
	alpha.addInstr(go);

	beta.addInstr(right);
	beta.addInstr(go);

	Creature x('e', 0, 'x', &alpha);
	Creature y('n', 0, 'y', &beta);
	world.place_creature(x, 4, 0);
	world.place_creature(y, 4, 4);
	world.run(6);
    }

    void test_left(){
	cout << "test left" << endl;

	World world (7,7);
	Instruction left(world, "left", 0);

	Species lefty;
	lefty.addInstr(left);

	Creature x('e', 0, 'h', &lefty);
	world.place_creature(x, 0, 0);

	CPPUNIT_ASSERT(x.direction == 'e');
	int progC = 0;

	left.execute(progC, x.direction);

	CPPUNIT_ASSERT(x.direction == 'n');

	
    }

    void test_food(){
    	cout << "test food" << endl;

      // create world and instructions
    	World world(7, 7);
    	Instruction instrOne(world, "left", 0);
    	Instruction instrTwo(world, "go", 0);

      // create righty specie (always goes right)
      Species food;
      food.addInstr(instrOne);
      food.addInstr(instrTwo);
      
      Creature creature('e', 0, 'f', &food);
      world.place_creature(creature, 0, 0);
      int progC = 0;
      char direction = 's';
      instrOne.execute(progC, direction);
    	CPPUNIT_ASSERT(progC == 1);
    	CPPUNIT_ASSERT(direction == 's');
    }


    void test_infect2(){
    	cout << "test infect" << endl;

      // create world and instructions

      // create any specie
      Species master;
      Species weak_specie;
      
      Creature master_creature('e', 0, 'm', &master);
      Creature weak_creature('e', 0, 'w', &weak_specie);
    	CPPUNIT_ASSERT(master_creature.name == 'm');
    	CPPUNIT_ASSERT(weak_creature.name == 'w');

      // infect weak creature
      weak_creature.infect(&master, 'm');
    	CPPUNIT_ASSERT(master_creature.name == 'm');
    	CPPUNIT_ASSERT(weak_creature.name == 'm');

    }
    void test_world_run_infect(){
    	cout << "test world run infect" << endl;

      // create world and a hop instruction
    	World world(7, 7);
    	Instruction infectorOne(world, "infect", 0);
    	Instruction infectorTwo(world, "go", 0);
    	Instruction foodOne(world, "left", 0);
    	Instruction foodTwo(world, "go", 0);

      // create righty specie (always goes right)
      Species infector;
      infector.addInstr(infectorOne);
      infector.addInstr(infectorTwo);
      
      Species food;
      infector.addInstr(foodOne);
      infector.addInstr(foodTwo);

      Creature i_creature('e', 0, 'i', &infector);
      world.place_creature(i_creature, 0, 0);
      Creature f_creature('e', 0, 'f', &food);
      world.place_creature(f_creature, 0, 1);
      world.print();
      world.run(1);


    }


    CPPUNIT_TEST_SUITE(TestDarwin);
//    CPPUNIT_TEST(test_print);
  	CPPUNIT_TEST(test_place_creature);
  	CPPUNIT_TEST(test_isEmpty);
  	CPPUNIT_TEST(test_isEmpty_2);
  	CPPUNIT_TEST(test_isEmpty_3);
  	CPPUNIT_TEST(test_isWall);
  	CPPUNIT_TEST(test_isWall_2);
  	CPPUNIT_TEST(test_isWall_3);
  	CPPUNIT_TEST(test_isCreature);
  	CPPUNIT_TEST(test_isCreature_2);
  	CPPUNIT_TEST(test_isCreature_3);
  	CPPUNIT_TEST(test_hop);
  	CPPUNIT_TEST(test_hop_1);
  	CPPUNIT_TEST(test_hop_evolve);
  	CPPUNIT_TEST(test_world_run_hopper);
 	CPPUNIT_TEST(test_world_run_hopper2);
	CPPUNIT_TEST(test_world_run_hopper3);
	CPPUNIT_TEST(test_ifEmpty);
	CPPUNIT_TEST(test_ifEmpty2);
	CPPUNIT_TEST(test_ifWall);
	CPPUNIT_TEST(test_ifEnemy);
	CPPUNIT_TEST(test_left);
  	CPPUNIT_TEST(test_food);
  	CPPUNIT_TEST(test_infect);
	CPPUNIT_TEST(test_infect2);
  	CPPUNIT_TEST(test_world_run_infect);
    CPPUNIT_TEST_SUITE_END();};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}

