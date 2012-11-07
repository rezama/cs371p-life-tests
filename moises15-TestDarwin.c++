// ------------------------------
// projects/Darwin/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
* To test the program:
* g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
* valgrind TestDarwin.app >& TestDarwin.out
*/

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" //CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner
#define private public
#define protected public
#define class struct
#include "Darwin.h"
#include <cstdlib>

using namespace std;

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture 
{
    
    // -----
    // Species Struct
    // -----
    void test_species_construct_1()
    {
        Species test("food");
        vector<string> instructions;
        instructions.push_back("left");
		instructions.push_back("go 0");
		CPPUNIT_ASSERT(instructions==test.instructions);
    }
    
    void test_species_construct_2()
    {
        Species test("trap");
        vector<string> instructions;
        instructions.push_back("if_enemy 3");
 		instructions.push_back("left");
		instructions.push_back("go 0");
 		instructions.push_back("infect");
		instructions.push_back("go 0");
		CPPUNIT_ASSERT(instructions==test.instructions);
    }
    
    void test_species_construct_3()
    {
        Species test("rover");
        vector<string> instructions;
        instructions.push_back("if_enemy 9");
		instructions.push_back("if_empty 7");
 		instructions.push_back("if_random 5");
 		instructions.push_back("left");
 		instructions.push_back("go 0");
 		instructions.push_back("right");
 		instructions.push_back("go 0");
 		instructions.push_back("hop");
 		instructions.push_back("go 0");
 		instructions.push_back("infect");
		instructions.push_back("go 0");
		CPPUNIT_ASSERT(instructions==test.instructions);
    }
    
    void test_species_instruction_at_1()
    {
        Species test("food");
		CPPUNIT_ASSERT(test.instruction_at(1).compare("go 0")==0);
    }
    
    void test_species_instruction_at_2()
    {
        Species test("trap");
		CPPUNIT_ASSERT(test.instruction_at(3).compare("infect")==0);
    }
    
    void test_species_instruction_at_3()
    {
        Species test("rover");
		CPPUNIT_ASSERT(test.instruction_at(9).compare("infect")==0);
    }
    
    // -----
    // Creature Struct
    // -----
    
    void test_creature_construct_1()
    {
        Creature test("food", NORTH, 45);
        CPPUNIT_ASSERT(test.direction==NORTH);
        CPPUNIT_ASSERT(test.location==45);
        CPPUNIT_ASSERT(test.species.name.compare("food")==0);
        CPPUNIT_ASSERT(test.program_counter==0);
    }
    
    void test_creature_construct_2()
    {
        Creature test("rover", WEST, 100);
        CPPUNIT_ASSERT(test.direction==WEST);
        CPPUNIT_ASSERT(test.location==100);
        CPPUNIT_ASSERT(test.species.name.compare("rover")==0);
        CPPUNIT_ASSERT(test.program_counter==0);
    }
    
    void test_creature_construct_3()
    {
        Creature test("hop", EAST, 85);
        CPPUNIT_ASSERT(test.direction==EAST);
        CPPUNIT_ASSERT(test.location==85);
        CPPUNIT_ASSERT(test.species.name.compare("hop")==0);
        CPPUNIT_ASSERT(test.program_counter==0);
    }
    
    void test_creature_is_located_at_1()
    {
        Creature test("food", NORTH, 45);
        CPPUNIT_ASSERT(test.is_located_at(45));
    }
    
    void test_creature_is_located_at_2()
    {
        Creature test("rover", WEST, 100);
        CPPUNIT_ASSERT(!test.is_located_at(45));
    }
    
    void test_creature_is_located_at_3()
    {
        Creature test("hop", EAST, 85);
        CPPUNIT_ASSERT(test.is_located_at(85));
    }
    
    void test_creature_located_at_1()
    {
        Creature test("food", NORTH, 45);
        CPPUNIT_ASSERT(test.located_at()==45);
    }
    
    void test_creature_located_at_2()
    {
        Creature test("rover", WEST, 100);
        CPPUNIT_ASSERT(test.located_at()!=45);
    }
    
    void test_creature_located_at_3()
    {
        Creature test("hop", EAST, 85);
        CPPUNIT_ASSERT(test.located_at()==85);
    }
    
    void test_creature_directed_towards_1()
    {
        Creature test("food", NORTH, 45);
        CPPUNIT_ASSERT(test.directed_towards()==NORTH);
    }
    
    void test_creature_directed_towards_2()
    {
        Creature test("rover", WEST, 100);
        CPPUNIT_ASSERT(test.directed_towards()!=SOUTH);
    }
    
    void test_creature_directed_towards_3()
    {
        Creature test("hop", EAST, 85);
        CPPUNIT_ASSERT(test.directed_towards()==EAST);
    }
    
    void test_creature_next_instruction_1()
    {
        Creature test("food", NORTH, 45);
        CPPUNIT_ASSERT(test.next_instruction().compare("left")==0);
    }
    
    void test_creature_next_instruction_2()
    {
        Creature test("hop", WEST, 100);
        test.next_instruction();
        CPPUNIT_ASSERT(test.next_instruction().compare("go 0")==0);
    }
    
    void test_creature_next_instruction_3()
    {
        Creature test("rover", EAST, 85);
        test.next_instruction();
        test.next_instruction();
        CPPUNIT_ASSERT(test.next_instruction().compare("if_random 5")==0);
    }
    
    void test_creature_exectute_flow_instruction_1()
    {
        Creature test("rover", EAST, 85);
        test.exectute_flow_instruction("if_empty 7",true);
        CPPUNIT_ASSERT(test.program_counter==7);
    }
    
    void test_creature_exectute_flow_instruction_2()
    {
        Creature test("rover", EAST, 85);
        int pc = test.program_counter;
        test.exectute_flow_instruction("if_enemy 9",false);
        CPPUNIT_ASSERT(test.program_counter==pc);
    }
    
    void test_creature_exectute_flow_instruction_3()
    {
        Creature test("rover", EAST, 85);
        test.exectute_flow_instruction("if_random 5",true);
        CPPUNIT_ASSERT(test.program_counter==5);
    }
    
    void test_creature_exectute_action_instruction_1()
    {
        Creature test("rover", SOUTH, 0);
        test.exectute_action_instruction("hop",100,10);
        CPPUNIT_ASSERT(test.location==10);
    }
    
    void test_creature_exectute_action_instruction_2()
    {
        Creature test("rover", EAST, 85);
        test.exectute_action_instruction("left",100,10);
        CPPUNIT_ASSERT(test.direction==NORTH);
    }
    
    void test_creature_exectute_action_instruction_3()
    {
        Creature test("rover", EAST, 85);
        test.exectute_action_instruction("right",100,10);
        CPPUNIT_ASSERT(test.direction==SOUTH);
    }
    // -----
    // Grid Struct
    // -----
    
    void test_grid_construct_1()
    {
        Grid test(10,10);
        CPPUNIT_ASSERT(test.dimension==100);
        CPPUNIT_ASSERT(test.rows==10);
        CPPUNIT_ASSERT(test.turn==0);
    }
    
    void test_grid_construct_2()
    {
        Grid test(9,8);
        CPPUNIT_ASSERT(test.dimension==72);
        CPPUNIT_ASSERT(test.rows==9);
        CPPUNIT_ASSERT(test.turn==0);
    }
    
    void test_grid_construct_3()
    {
        Grid test(10,12);
        CPPUNIT_ASSERT(test.dimension==120);
        CPPUNIT_ASSERT(test.rows==10);
        CPPUNIT_ASSERT(test.turn==0);
    }
    
    void test_grid_place_1()
    {
        Grid test(10,10);
        bool success = test.place("food",NORTH,5,5);
        CPPUNIT_ASSERT(success);
        CPPUNIT_ASSERT(test.creatures.size()==1);
        CPPUNIT_ASSERT(test.creatures[0].species.name.compare("food")==0);
    }
    
    void test_grid_place_2()
    {
        Grid test(10,10);
        bool success = test.place("food",NORTH,5,5);
        bool success2 = test.place("rover",NORTH,5,5);
        CPPUNIT_ASSERT(success);
        CPPUNIT_ASSERT(!success2);
        CPPUNIT_ASSERT(test.creatures.size()==1);
        CPPUNIT_ASSERT(test.creatures[0].species.name.compare("food")==0);
    }
    
    void test_grid_place_3()
    {
        Grid test(10,10);
        bool success = test.place("food",NORTH,5,5);
        bool success2 = test.place("rover",NORTH,2,5);
        CPPUNIT_ASSERT(success);
        CPPUNIT_ASSERT(success2);
        CPPUNIT_ASSERT(test.creatures.size()==2);
        CPPUNIT_ASSERT(test.creatures[0].species.name.compare("food")==0);
        CPPUNIT_ASSERT(test.creatures[1].species.name.compare("rover")==0);
    }
    
    void test_grid_creature_at_1()
    {
        Grid test(10,10);
        test.place("food",NORTH,5,5);
        Creature* c = test.creature_at(5,5);
        CPPUNIT_ASSERT((*c).species.name.compare("food")==0);
    }
    
    void test_grid_creature_at_2()
    {
        Grid test(10,10);
        test.place("food",NORTH,5,5);
        Creature* c = test.creature_at(0,0);
        CPPUNIT_ASSERT(c==NULL);
    }
    
    void test_grid_creature_at_3()
    {
        Grid test(10,10);
        test.place("food",NORTH,5,5);
        test.place("rover",NORTH,2,5);
        Creature* c = test.creature_at(2,5);
        CPPUNIT_ASSERT((*c).species.name.compare("rover")==0);
    }
    
    void test_evaluate_flow_instruction_1()
    {
        Grid test(10,10);
        bool result = test.evaluate_flow_instruction("if_wall 3",EAST,100,"hop");
        CPPUNIT_ASSERT(result);
    }
    
    void test_evaluate_flow_instruction_2()
    {
        Grid test(10,10);
        bool result = test.evaluate_flow_instruction("if_wall 3",EAST,25,"hop");
        CPPUNIT_ASSERT(!result);
    }
    
    void test_evaluate_flow_instruction_3()
    {
        Grid test(10,10);
        bool result = test.evaluate_flow_instruction("if_empty 3",EAST,20,"hop");
        CPPUNIT_ASSERT(result);
    }
    
    void test_action_is_valid_1()
    {
        Grid test(10,10);
        bool result = test.action_is_valid("hop",WEST,25,"hop");
        CPPUNIT_ASSERT(result);
    }
    
    void test_action_is_valid_2()
    {
        Grid test(10,10);
        bool result = test.action_is_valid("hop",EAST,100,"hop");
        CPPUNIT_ASSERT(!result);
    }
    
    void test_action_is_valid_3()
    {
        Grid test(10,10);
        bool result = test.action_is_valid("infect",WEST,100,"hop");
        CPPUNIT_ASSERT(!result);
    }
    
    
    
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_species_construct_1);
    CPPUNIT_TEST(test_species_construct_2);
    CPPUNIT_TEST(test_species_construct_3);
    CPPUNIT_TEST(test_species_instruction_at_1);
    CPPUNIT_TEST(test_species_instruction_at_2);
    CPPUNIT_TEST(test_species_instruction_at_3);
    CPPUNIT_TEST(test_creature_construct_1);
    CPPUNIT_TEST(test_creature_construct_2);
    CPPUNIT_TEST(test_creature_construct_3 );
    CPPUNIT_TEST(test_creature_is_located_at_1);
    CPPUNIT_TEST(test_creature_is_located_at_2);
    CPPUNIT_TEST(test_creature_is_located_at_3);
    CPPUNIT_TEST(test_creature_located_at_1);
    CPPUNIT_TEST(test_creature_located_at_2);
    CPPUNIT_TEST(test_creature_located_at_3);
    CPPUNIT_TEST(test_creature_directed_towards_1);
    CPPUNIT_TEST(test_creature_directed_towards_2);
    CPPUNIT_TEST(test_creature_directed_towards_3);
    CPPUNIT_TEST(test_creature_next_instruction_1);
    CPPUNIT_TEST(test_creature_next_instruction_2);
    CPPUNIT_TEST(test_creature_next_instruction_3);
    CPPUNIT_TEST(test_creature_exectute_flow_instruction_1);
    CPPUNIT_TEST(test_creature_exectute_flow_instruction_2);
    CPPUNIT_TEST(test_creature_exectute_flow_instruction_3);
    CPPUNIT_TEST(test_creature_exectute_action_instruction_1);
    CPPUNIT_TEST(test_creature_exectute_action_instruction_2);
    CPPUNIT_TEST(test_creature_exectute_action_instruction_3);
    CPPUNIT_TEST(test_grid_construct_1);
    CPPUNIT_TEST(test_grid_construct_2);
    CPPUNIT_TEST(test_grid_construct_3);
    CPPUNIT_TEST(test_grid_place_1);
    CPPUNIT_TEST(test_grid_place_2);
    CPPUNIT_TEST(test_grid_place_3);
    CPPUNIT_TEST(test_grid_creature_at_1);
    CPPUNIT_TEST(test_grid_creature_at_2);
    CPPUNIT_TEST(test_grid_creature_at_3);
    CPPUNIT_TEST(test_evaluate_flow_instruction_1);
    CPPUNIT_TEST(test_evaluate_flow_instruction_2);
    CPPUNIT_TEST(test_evaluate_flow_instruction_3);
    CPPUNIT_TEST(test_action_is_valid_1);
    CPPUNIT_TEST(test_action_is_valid_2);
    CPPUNIT_TEST(test_action_is_valid_3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () 
{
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}


 
