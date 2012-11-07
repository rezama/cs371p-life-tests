//---------------------
// TestingDarwin.c++
// Stephen Cook
//---------------------


/*
Run the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.c++.app
% valgrind TestDarwin.c++.app >& TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#define private public
#define protected public
#include "Darwin.h"


// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {
	
	
	void test_add_instruction_1() {
        Species test("test", 't');
        test.addInstruction(turn_left);
        CPPUNIT_ASSERT(test.instructionSet[0].type == turn_left);
	}
	void test_add_instruction_2() {
        Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(turn_right);
        test.addInstruction(go, 0);
        CPPUNIT_ASSERT(test.instructionSet[0].type == turn_left);
        CPPUNIT_ASSERT(test.instructionSet[1].type == turn_right);
        CPPUNIT_ASSERT(test.instructionSet[2].type == go);
        CPPUNIT_ASSERT(test.instructionSet[2].moveToLine == 0);
	}
	void test_add_instruction_3() {
        Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(turn_left);
        test.addInstruction(go, 0);
        test.addInstruction(turn_left);
        test.addInstruction(if_random, 3);
        CPPUNIT_ASSERT(test.instructionSet[0].type == turn_left);
        CPPUNIT_ASSERT(test.instructionSet[1].type == turn_left);
        CPPUNIT_ASSERT(test.instructionSet[2].type == go);
        CPPUNIT_ASSERT(test.instructionSet[2].moveToLine == 0);
        CPPUNIT_ASSERT(test.instructionSet[3].type == turn_left);
        CPPUNIT_ASSERT(test.instructionSet[4].type == if_random);
        CPPUNIT_ASSERT(test.instructionSet[4].moveToLine == 3);
	}
	
	void test_next_instruction_1(){
	    Species test("test", 't');
        test.addInstruction(turn_left);
        CPPUNIT_ASSERT(test.nextInstruction(0).type == turn_left);
	}
	void test_next_instruction_2(){
		Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(turn_right);
        test.addInstruction(go, 0);
        CPPUNIT_ASSERT(test.nextInstruction(0).type == turn_left);
        CPPUNIT_ASSERT(test.nextInstruction(1).type == turn_right);
        CPPUNIT_ASSERT(test.nextInstruction(2).type == go);
        CPPUNIT_ASSERT(test.nextInstruction(2).moveToLine == 0);
	}
	void test_next_instruction_3(){
		Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(turn_left);
        test.addInstruction(go, 0);
        test.addInstruction(turn_left);
        test.addInstruction(if_random, 3);
        CPPUNIT_ASSERT(test.nextInstruction(0).type == turn_left);
        CPPUNIT_ASSERT(test.nextInstruction(1).type == turn_left);
        CPPUNIT_ASSERT(test.nextInstruction(2).type == go);
        CPPUNIT_ASSERT(test.nextInstruction(2).moveToLine == 0);
        CPPUNIT_ASSERT(test.nextInstruction(3).type == turn_left);
        CPPUNIT_ASSERT(test.nextInstruction(4).type == if_random);
        CPPUNIT_ASSERT(test.nextInstruction(4).moveToLine == 3);
	}
	
	void test_species_abbreviation_1(){
		Species food("food", 'f');
		CPPUNIT_ASSERT(food.speciesAbbreviation() == 'f');
	}
	void test_species_abbreviation_2(){
		Species hopper("hopper", 'h');
		CPPUNIT_ASSERT(hopper.speciesAbbreviation() == 'h');
	}
	void test_species_abbreviation_3(){
		Species rover("rover", 'r');
		CPPUNIT_ASSERT(rover.speciesAbbreviation() == 'r');
	}
	
	void test_creature_constructor_1(){
		Grid map(1,1);
		Species testSpecies("testSpecies", 't');
		Grid::Creature test(testSpecies, 'n', map);
		CPPUNIT_ASSERT(test.speciesType.speciesName == testSpecies.speciesName);
		CPPUNIT_ASSERT(test.pc == 0);
		CPPUNIT_ASSERT(test.direction == 'n');
	}
	void test_creature_constructor_2(){
		Grid map(2,2);
		Species testSpecies("stuff", 't');
		Grid::Creature test(testSpecies, 'e', map);
		CPPUNIT_ASSERT(test.speciesType.speciesName == testSpecies.speciesName);
		CPPUNIT_ASSERT(test.pc == 0);
		CPPUNIT_ASSERT(test.direction == 'e');
	}
	void test_creature_constructor_3(){
		Grid map(1,1);
		Species testSpecies("testSpecies", 't');
		Grid::Creature test(testSpecies, 'w', map);
		CPPUNIT_ASSERT(test.speciesType.speciesName == testSpecies.speciesName);
		CPPUNIT_ASSERT(test.pc == 0);
		CPPUNIT_ASSERT(test.direction == 'w');		
	}
	
	void test_creature_run_1(){
		Grid map(1,1);
		Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(go, 0);
        Grid::Creature testCreature(test, 'w', map);
        testCreature.run();
        CPPUNIT_ASSERT(testCreature.pc == 1);
	}
	void test_creature_run_2(){
		Grid map(1,1);
		Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(turn_left);
        test.addInstruction(go, 0);
        Grid::Creature testCreature(test, 'w', map);
        testCreature.run();
        testCreature.run();
        CPPUNIT_ASSERT(testCreature.pc == 2);
	}
	void test_creature_run_3(){
		Grid map(1,1);
		Species test("test", 't');
        test.addInstruction(turn_left);
        test.addInstruction(turn_left);
        test.addInstruction(go, 0);
        Grid::Creature testCreature(test, 'w', map);
        testCreature.run();
        testCreature.run();
        testCreature.run();
        CPPUNIT_ASSERT(testCreature.pc == 1);
	}
	
	void test_creature_hop_1(){
		Grid map(1,2);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).hop();
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).pc == 1);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[0]);
	}
	void test_creature_hop_2(){
		Grid map(1,2);
		Species test("test", 't');
		map.place(test, 'e', 0, 1);

        (*(map.mapGrid[0][1].unitCreature)).hop();
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).pc == 1);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[0]);		
	}
	void test_creature_hop_3(){
		Grid map(1,2);
		Species test("test", 't');
		Species test1("test1", 't');
		map.place(test, 'e', 0, 0);
		map.place(test1, 'e', 0, 1);

        (*(map.mapGrid[0][0].unitCreature)).hop();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);	
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).pc == 0);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[1]);		
	}
	
	void test_creature_left_1(){
		Grid map(1,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).left();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');
	}
	void test_creature_left_2(){
		Grid map(1,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).left();
        (*(map.mapGrid[0][0].unitCreature)).left();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'w');
	}
	void test_creature_left_3(){
		Grid map(1,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).left();
        (*(map.mapGrid[0][0].unitCreature)).left();
        (*(map.mapGrid[0][0].unitCreature)).left();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 3);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');
	}
	
	void test_creature_right_1(){
		Grid map(1,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).right();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');
	}
	void test_creature_right_2(){
		Grid map(1,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).right();
        (*(map.mapGrid[0][0].unitCreature)).right();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'w');
	}
	void test_creature_right_3(){
		Grid map(1,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).right();
        (*(map.mapGrid[0][0].unitCreature)).right();
        (*(map.mapGrid[0][0].unitCreature)).right();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 3);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');
	}
	
	void test_creature_infect_1(){
		Grid map(1,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 'e', 0, 0);
		map.place(test2, 'n', 0, 1);


        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).speciesType.abbreviation == 't');
        (*(map.mapGrid[0][0].unitCreature)).infect();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).pc == 0);
        
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).speciesType.abbreviation == 'o');
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[1]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).direction == 'n');
	}
	void test_creature_infect_2(){
		Grid map(1,2);
		Species test1("test1", 'o');
		map.place(test1, 'e', 0, 0);
		map.place(test1, 'n', 0, 1);

        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).speciesType.abbreviation == 'o');
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).pc == 0);
        
        (*(map.mapGrid[0][1].unitCreature)).hop();
        (*(map.mapGrid[0][0].unitCreature)).infect();
        
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).pc == 1);
        
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).speciesType.abbreviation == 'o');
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[1]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).direction == 'n');		
	}
	void test_creature_infect_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).infect();
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);	
	}
	
	void test_creature_ifempty_1(){
		Grid map(1,2);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		Species test2("test2", 't');
		test2.addInstruction(turn_left);
		test2.addInstruction(turn_right);
		
		map.place(test1, 'e', 0, 0);
		map.place(test2, 'n', 0, 1);

        (*(map.mapGrid[0][0].unitCreature)).if_empty(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');	

	}
	void test_creature_ifempty_2(){
		Grid map(1,2);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);

		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).if_empty(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');			
	}
	void test_creature_ifempty_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).if_empty(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');			
	}
	
	void test_creature_ifwall_1(){
		Grid map(1,2);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		Species test2("test2", 't');
		test2.addInstruction(turn_left);
		test2.addInstruction(turn_right);
		
		map.place(test1, 'e', 0, 0);
		map.place(test2, 'n', 0, 1);

        (*(map.mapGrid[0][0].unitCreature)).if_wall(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');	

	}
	void test_creature_ifwall_2(){
		Grid map(1,2);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);

		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).if_wall(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');			
	}
	void test_creature_ifwall_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).if_wall(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');			
	}
	
	void test_creature_ifenemy_1(){
		Grid map(1,2);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		Species test2("test2", 't');
		test2.addInstruction(turn_left);
		test2.addInstruction(turn_right);
		
		map.place(test1, 'e', 0, 0);
		map.place(test2, 'n', 0, 1);

        (*(map.mapGrid[0][0].unitCreature)).if_enemy(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');	

	}
	void test_creature_ifenemy_2(){
		Grid map(1,2);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);

		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).if_enemy(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');			
	}
	void test_creature_ifenemy_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).if_enemy(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');			
	}
	
	void test_creature_go_1(){
		Grid map(1,1);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		test1.addInstruction(turn_left);
		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).go(0);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 1);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');			
	}
	void test_creature_go_2(){
		Grid map(1,1);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		test1.addInstruction(turn_left);
		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).go(1);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 2);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 's');		
	}
	void test_creature_go_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		test1.addInstruction(turn_left);
		test1.addInstruction(turn_right);
		test1.addInstruction(turn_left);
		
		map.place(test1, 'e', 0, 0);

        (*(map.mapGrid[0][0].unitCreature)).go(2);

        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).pc == 3);
        CPPUNIT_ASSERT((*(map.mapGrid[0][0].unitCreature)).direction == 'n');		
	}
	
	void test_creature_reset_1(){
		Grid map(1,1);
		Species test1("test1", 'o');
		Species test2("test2", 't');
        test1.addInstruction(turn_left);
        test2.addInstruction(turn_left);

        Grid::Creature testCreature1(test1, 'w', map);
        Grid::Creature testCreature2(test2, 'w', map);
        testCreature1.left();
        CPPUNIT_ASSERT(testCreature1.pc == 1);	
        testCreature1.reset(test2);
        
        CPPUNIT_ASSERT(testCreature1.pc == 0);	
        CPPUNIT_ASSERT(testCreature1.speciesType.abbreviation == 't');	
	}
	void test_creature_reset_2(){
		Grid map(1,1);
		Species test1("test1", 'o');
		Species test2("test2", 't');
        test1.addInstruction(turn_left);
        test2.addInstruction(turn_left);

        Grid::Creature testCreature1(test1, 'w', map);
        Grid::Creature testCreature2(test2, 'w', map);
        testCreature1.left();
        CPPUNIT_ASSERT(testCreature1.pc == 1);	
        testCreature1.reset(test1);
        CPPUNIT_ASSERT(testCreature1.speciesType.abbreviation == 'o');			
	}
	void test_creature_reset_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		Species test2("test2", 't');
        test1.addInstruction(turn_left);
        test2.addInstruction(turn_left);

        Grid::Creature testCreature1(test1, 'w', map);
        Grid::Creature testCreature2(test2, 'w', map);
        testCreature1.left();
        CPPUNIT_ASSERT(testCreature1.pc == 1);	
        testCreature1.reset(test2);
        
        CPPUNIT_ASSERT(testCreature1.pc == 0);	
        CPPUNIT_ASSERT(testCreature1.speciesType.abbreviation == 't');	
        CPPUNIT_ASSERT(testCreature1.direction == 's');	
	}
	
	void test_grid_constructor_1(){
		Grid test(1,1);
		CPPUNIT_ASSERT(test.mapGrid.size() == 1);
		CPPUNIT_ASSERT(test.mapGrid[0].size() == 1);
	}
	void test_grid_constructor_2(){
		Grid test(70,70);
		CPPUNIT_ASSERT(test.mapGrid.size() == 70);
		CPPUNIT_ASSERT(test.mapGrid[0].size() == 70);		
	}
	void test_grid_constructor_3(){
		Grid test(256,1);
		CPPUNIT_ASSERT(test.mapGrid.size() == 256);
		CPPUNIT_ASSERT(test.mapGrid[0].size() == 1);		
	}
	
	void test_grid_move_1(){
		Grid map(1,2);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);
        
        CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature == true);
        CPPUNIT_ASSERT(map.mapGrid[0][1].isCreature == false);
        
        map.currentCoord = make_pair(0, 0);
        map.move('e');
        
        CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature == false);
        CPPUNIT_ASSERT(map.mapGrid[0][1].isCreature == true);
		
	}
	void test_grid_move_2(){
		Grid map(2,1);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);
        
        CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature == true);
        
        map.currentCoord = make_pair(0, 0);
        map.move('s');
        
        CPPUNIT_ASSERT(map.mapGrid[1][0].isCreature == true);		
	}
	void test_grid_move_3(){
		Grid map(1,2);
		Species test("test", 't');
		map.place(test, 'e', 0, 0);
		Species test2("test2", 't');
		map.place(test2, 'e', 0, 1);
        
        CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature == true);
        CPPUNIT_ASSERT(map.mapGrid[0][1].isCreature == true);
        
        map.currentCoord = make_pair(0, 0);
        map.move('e');
        
        CPPUNIT_ASSERT(map.mapGrid[0][1].isCreature == true);		
	}
	
	void test_grid_infection_1(){	
        Grid map(1,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 'e', 0, 0);
		map.place(test2, 'n', 0, 1);

        CPPUNIT_ASSERT(map.mapGrid[0][1].unitName == 't');
        
        map.currentCoord = make_pair(0, 0);
        map.infection('e', test2);

        CPPUNIT_ASSERT(map.mapGrid[0][1].unitName == 'o');
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[1]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).direction == 'n');
        
	}
	void test_grid_infection_2(){
        Grid map(1,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 'e', 0, 0);
		map.place(test2, 'n', 0, 1);

        CPPUNIT_ASSERT(map.mapGrid[0][1].unitName == 't');
        
        map.currentCoord = make_pair(0, 0);
        map.infection('e', test1);

        CPPUNIT_ASSERT(map.mapGrid[0][1].unitName == 'o');
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT(map.mapGrid[0][1].unitCreature == &map.creatures[1]);
        CPPUNIT_ASSERT((*(map.mapGrid[0][1].unitCreature)).direction == 'n');		
	}
	void test_grid_infection_3(){
        Grid map(2,1);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test2, 'n', 1, 0);

        CPPUNIT_ASSERT(map.mapGrid[1][0].unitName == 't');
        
        map.currentCoord = make_pair(0, 0);
        map.infection('s', test2);

        CPPUNIT_ASSERT(map.mapGrid[1][0].unitName == 'o');
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitCreature == &map.creatures[0]);
        CPPUNIT_ASSERT(map.mapGrid[1][0].unitCreature == &map.creatures[1]);
        CPPUNIT_ASSERT((*(map.mapGrid[1][0].unitCreature)).direction == 'n');		
	}
	
	void test_grid_iswall_1(){
		Grid map(1,1);
		map.currentCoord = make_pair(0, 0);
		CPPUNIT_ASSERT(map.isWall('s'));
		CPPUNIT_ASSERT(map.isWall('n'));
		CPPUNIT_ASSERT(map.isWall('e'));
		CPPUNIT_ASSERT(map.isWall('w'));
	}
	void test_grid_iswall_2(){
		Grid map(1,2);
		map.currentCoord = make_pair(0, 0);
		CPPUNIT_ASSERT(map.isWall('s'));
		CPPUNIT_ASSERT(map.isWall('n'));
		CPPUNIT_ASSERT(!map.isWall('e'));
		CPPUNIT_ASSERT(map.isWall('w'));
	}
	void test_grid_iswall_3(){
		Grid map(2,2);
		map.currentCoord = make_pair(1, 1);
		CPPUNIT_ASSERT(map.isWall('s'));
		CPPUNIT_ASSERT(!map.isWall('n'));
		CPPUNIT_ASSERT(map.isWall('e'));
		CPPUNIT_ASSERT(!map.isWall('w'));
	}
	
	void test_grid_isenemy_1(){
		Grid map(2,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test2, 'n', 1, 0);
        
        map.currentCoord = make_pair(0, 0);
        CPPUNIT_ASSERT(map.isEnemy('s'));
        CPPUNIT_ASSERT(!map.isEnemy('e'));
	}
	void test_grid_isenemy_2(){
		Grid map(2,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test2, 'n', 0, 1);
        
        map.currentCoord = make_pair(0, 0);
        CPPUNIT_ASSERT(!map.isEnemy('s'));		
        CPPUNIT_ASSERT(map.isEnemy('e'));	
	}
	void test_grid_isenemy_3(){
		Grid map(2,2);
		Species test1("test1", 'o');
		map.place(test1, 's', 0, 0);
		map.place(test1, 'n', 1, 0);
        
        map.currentCoord = make_pair(0, 0);
        CPPUNIT_ASSERT(!map.isEnemy('e'));	
        CPPUNIT_ASSERT(!map.isEnemy('s'));	
	}
	
	void test_grid_isempty_1(){
		Grid map(2,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test2, 'n', 1, 0);
        
        map.currentCoord = make_pair(0, 0);
        CPPUNIT_ASSERT(!map.isEmpty('s'));
        CPPUNIT_ASSERT(map.isEmpty('e'));
        CPPUNIT_ASSERT(!map.isEmpty('n'));
        CPPUNIT_ASSERT(!map.isEmpty('w'));
	}
	void test_grid_isempty_2(){
		Grid map(2,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test2, 'n', 0, 1);
        
        map.currentCoord = make_pair(0, 0);
        CPPUNIT_ASSERT(map.isEmpty('s'));
        CPPUNIT_ASSERT(!map.isEmpty('e'));
        CPPUNIT_ASSERT(!map.isEmpty('n'));
        CPPUNIT_ASSERT(!map.isEmpty('w'));
	}
	void test_grid_isempty_3(){
		Grid map(1,1);
		Species test1("test1", 'o');
		map.place(test1, 's', 0, 0);
        
        map.currentCoord = make_pair(0, 0);
        CPPUNIT_ASSERT(!map.isEmpty('s'));
        CPPUNIT_ASSERT(!map.isEmpty('e'));
        CPPUNIT_ASSERT(!map.isEmpty('n'));
        CPPUNIT_ASSERT(!map.isEmpty('w'));	
	}
	
	void test_grid_newcoordinate_1(){
		Grid map(3,3);
		map.currentCoord = make_pair(1, 1);
		CPPUNIT_ASSERT(map.newCoordinate('n') == make_pair(0, 1));
	}
	void test_grid_newcoordinate_2(){
		Grid map(3,3);
		map.currentCoord = make_pair(1, 1);
		CPPUNIT_ASSERT(map.newCoordinate('s') == make_pair(2, 1));		
	}
	void test_grid_newcoordinate_3(){
		Grid map(3,3);
		map.currentCoord = make_pair(1, 1);
		CPPUNIT_ASSERT(map.newCoordinate('e') == make_pair(1, 2));		
	}
	void test_grid_newcoordinate_4(){
		Grid map(3,3);
		map.currentCoord = make_pair(1, 1);
		CPPUNIT_ASSERT(map.newCoordinate('w') == make_pair(1, 0));		
	}	
	void test_grid_place_1(){
		Grid map(1,1);
		Species test1("test1", 'o');
		map.place(test1, 's', 0, 0);
        
        CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitName == 'o');
	}
	void test_grid_place_2(){
		Grid map(2,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test2, 'n', 1, 0);
		
		CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitName == 'o');
		CPPUNIT_ASSERT(map.mapGrid[1][0].isCreature);
        CPPUNIT_ASSERT(map.mapGrid[1][0].unitName == 't');
        CPPUNIT_ASSERT(!map.mapGrid[0][1].isCreature);
        CPPUNIT_ASSERT(!map.mapGrid[1][1].isCreature);
	}
	void test_grid_place_3(){
		Grid map(2,2);
		Species test1("test1", 'o');
		Species test2("test2", 't');
		map.place(test1, 's', 0, 0);
		map.place(test1, 'n', 1, 0);	
		
		CPPUNIT_ASSERT(map.mapGrid[0][0].isCreature);
        CPPUNIT_ASSERT(map.mapGrid[0][0].unitName == 'o');	
		CPPUNIT_ASSERT(map.mapGrid[1][0].isCreature);
        CPPUNIT_ASSERT(map.mapGrid[1][0].unitName == 'o');
        CPPUNIT_ASSERT(!map.mapGrid[0][1].isCreature);
        CPPUNIT_ASSERT(!map.mapGrid[1][1].isCreature);
        	
	}
	
	void test_print_output_1(){
		Grid(1,1);
		
	}
	void test_print_output_2(){
		
	}
	void test_print_output_3(){
		
	}
	
	
	
	CPPUNIT_TEST_SUITE(TestDarwin);
	CPPUNIT_TEST(test_add_instruction_1);
	CPPUNIT_TEST(test_add_instruction_2);
	CPPUNIT_TEST(test_add_instruction_3);
	CPPUNIT_TEST(test_next_instruction_1);
	CPPUNIT_TEST(test_next_instruction_2);
	CPPUNIT_TEST(test_next_instruction_3);
	CPPUNIT_TEST(test_species_abbreviation_1);
	CPPUNIT_TEST(test_species_abbreviation_2);
	CPPUNIT_TEST(test_species_abbreviation_3);
	CPPUNIT_TEST(test_creature_constructor_1);
	CPPUNIT_TEST(test_creature_constructor_2);
	CPPUNIT_TEST(test_creature_constructor_3);
	CPPUNIT_TEST(test_creature_run_1);
	CPPUNIT_TEST(test_creature_run_2);
	CPPUNIT_TEST(test_creature_run_3);
	CPPUNIT_TEST(test_creature_hop_1);
	CPPUNIT_TEST(test_creature_hop_2);
	CPPUNIT_TEST(test_creature_hop_3);
	CPPUNIT_TEST(test_creature_left_1);
	CPPUNIT_TEST(test_creature_left_2);
	CPPUNIT_TEST(test_creature_left_3);
	CPPUNIT_TEST(test_creature_right_1);
	CPPUNIT_TEST(test_creature_right_2);
	CPPUNIT_TEST(test_creature_right_3);
	CPPUNIT_TEST(test_creature_infect_1);
	CPPUNIT_TEST(test_creature_infect_2);
	CPPUNIT_TEST(test_creature_infect_3);
	CPPUNIT_TEST(test_creature_ifempty_1);
	CPPUNIT_TEST(test_creature_ifempty_2);
	CPPUNIT_TEST(test_creature_ifempty_3);
	CPPUNIT_TEST(test_creature_ifwall_1);
	CPPUNIT_TEST(test_creature_ifwall_2);
	CPPUNIT_TEST(test_creature_ifwall_3);
	CPPUNIT_TEST(test_creature_ifenemy_1);
	CPPUNIT_TEST(test_creature_ifenemy_2);
	CPPUNIT_TEST(test_creature_ifenemy_3);
	CPPUNIT_TEST(test_creature_go_1);
	CPPUNIT_TEST(test_creature_go_2);
	CPPUNIT_TEST(test_creature_go_3);
	CPPUNIT_TEST(test_creature_reset_1);
	CPPUNIT_TEST(test_creature_reset_2);
	CPPUNIT_TEST(test_creature_reset_3);
	CPPUNIT_TEST(test_grid_constructor_1);
	CPPUNIT_TEST(test_grid_constructor_2);
	CPPUNIT_TEST(test_grid_constructor_3);
	CPPUNIT_TEST(test_grid_move_1);
	CPPUNIT_TEST(test_grid_move_2);
	CPPUNIT_TEST(test_grid_move_3);
	CPPUNIT_TEST(test_grid_infection_1);
	CPPUNIT_TEST(test_grid_infection_2);
	CPPUNIT_TEST(test_grid_infection_3);
	CPPUNIT_TEST(test_grid_iswall_1);
	CPPUNIT_TEST(test_grid_iswall_2);
	CPPUNIT_TEST(test_grid_iswall_3);
	CPPUNIT_TEST(test_grid_isenemy_1);
	CPPUNIT_TEST(test_grid_isenemy_2);
	CPPUNIT_TEST(test_grid_isenemy_3);
	CPPUNIT_TEST(test_grid_isempty_1);
	CPPUNIT_TEST(test_grid_isempty_2);
	CPPUNIT_TEST(test_grid_isempty_3);
	CPPUNIT_TEST(test_grid_newcoordinate_1);
	CPPUNIT_TEST(test_grid_newcoordinate_2);
	CPPUNIT_TEST(test_grid_newcoordinate_3);
	CPPUNIT_TEST(test_grid_newcoordinate_4);
	CPPUNIT_TEST(test_grid_place_1);
	CPPUNIT_TEST(test_grid_place_2);
	CPPUNIT_TEST(test_grid_place_3);
	CPPUNIT_TEST_SUITE_END();
};


int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
