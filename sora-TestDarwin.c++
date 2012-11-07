// ------------------------------
// TestDarwin.c++
// Copyright (C) 2012
// Simon Doty and Ang Li
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

#include <string>
#define private public
#include "Darwin.h"

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {
    // --------
    // test_darwin
    // --------   

    void test_darwin1 () {
        Darwin A(3, 4);
        CPPUNIT_ASSERT(A.num_r == 3);
        CPPUNIT_ASSERT(A.num_c == 4);
    }
    
    void test_darwin2() {
        Darwin B(1, 1);
        CPPUNIT_ASSERT(B.num_r == 1);
        CPPUNIT_ASSERT(B.num_c == 1);
        CPPUNIT_ASSERT(B._world.size() == 1);
        CPPUNIT_ASSERT(B.turn == 0);
    }
    
    void test_darwin3() {
        Darwin C(100, 90);
        CPPUNIT_ASSERT(C.num_r == 100);
        CPPUNIT_ASSERT(C.num_c == 90);
        CPPUNIT_ASSERT(C._world.size() == 100);
        CPPUNIT_ASSERT(C.turn == 0);
    }
    
    //--------------
    // test_in_bound
    //--------------
    
    void test_bounds1 () {
        Darwin A(3, 4);
        bool in_bound = A.in_bound(0, 0);
        CPPUNIT_ASSERT(in_bound == true);    
    }
    
    void test_bounds2 () {
        Darwin B(1, 1);
        bool in_bound = B.in_bound(1, 1);
        CPPUNIT_ASSERT(in_bound == false);    
    }
       
    void test_bounds3 () {
        Darwin C(100, 90);
        bool in_bound = C.in_bound(99, 0);
        CPPUNIT_ASSERT(in_bound == true);    
    }
    
    //-------------
    // set_contents
    //-------------
    
    void test_set_contents1() {
        Darwin A(10, 10);
        species trap("t");
        A.set_contents(6, 8, creature(enums::west, &trap));
        CPPUNIT_ASSERT(A.life_list.size() == 1);
        CPPUNIT_ASSERT(A.life_list[0]._isWall == false);
        CPPUNIT_ASSERT(A.life_list[0].turn_bool == true);
        CPPUNIT_ASSERT((A._world[6][8])->_pc == 0);
    }
    
    void test_set_contents2() {
        Darwin A(10, 10);
        species trap("t");
        species forest("f");
        species wind("w");
        A.set_contents(6, 8, creature(enums::west, &trap));
        A.set_contents(0, 5, creature(enums::east, &wind));
        A.set_contents(4, 3, creature(enums::north, &forest));
        CPPUNIT_ASSERT(A.life_list.size() == 3);
        CPPUNIT_ASSERT(A.life_list[2]._isWall == false);
        CPPUNIT_ASSERT(A.life_list[1].turn_bool == true);
        CPPUNIT_ASSERT( (A._world[6][8])->_pc == 0);
        CPPUNIT_ASSERT( ((A._world[0][5])->_sp)->_name == "w");
        CPPUNIT_ASSERT( ((A._world[4][3])->_sp)->_name == "f");
    }
    
    void test_set_contents3() {
        Darwin A(10, 10);
        species trap("t");
        species sand("sand");                       
        A.set_contents(9, 9, creature(enums::west, &trap));
        A.set_contents(0, 5, creature(enums::east, &sand));        
        CPPUNIT_ASSERT(A.life_list.size() == 2);
        CPPUNIT_ASSERT(A.life_list[0]._isWall == false);
        CPPUNIT_ASSERT(A.life_list[1].turn_bool == true);
        CPPUNIT_ASSERT( (A._world[9][9])->_pc == 0);
        CPPUNIT_ASSERT( ((A._world[0][5])->_sp)->_name == "sand");
        CPPUNIT_ASSERT( ((A._world[9][9])->_sp)->_name == "t");
    }
    
    //-----------------
    // test_print_world
    //-----------------
    
    
    void test_print_world1 () {
    	std::ostringstream w;
        Darwin A(5, 5);
        species trap("t");
        species sand("s");                       
        A.set_contents(4, 4, creature(enums::west, &trap));
        A.set_contents(0, 3, creature(enums::east, &sand)); 
        A.set_contents(0, 0, creature(enums::east, &sand));
        A.set_contents(1, 2, creature(enums::east, &trap));
        std::string board = "Turn = 0.\n  01234\n0 s..s.\n1 ..t..\n2 .....\n3 .....\n4 ....t\n\n";
        A.print_world(w);
        std::cout << "printing board: " << std::endl << board << std::endl;
        std::cout << "printing print world: " << std::endl << w.str() << std::endl;
        CPPUNIT_ASSERT(w.str() == board);            
    }
    
    void test_print_world2 () {
    	std::ostringstream w;
        Darwin A(10, 10);
        species trap("t");
        species sand("s"); 
        species fern("f");                        
        A.set_contents(0, 0, creature(enums::west, &trap));
        A.set_contents(6, 3, creature(enums::east, &sand)); 
        A.set_contents(3, 3, creature(enums::east, &sand));
        A.set_contents(5, 8, creature(enums::east, &trap));
        A.set_contents(2, 9, creature(enums::east, &fern));
        A.set_contents(4, 1, creature(enums::east, &fern));
        std::string board = "Turn = 0.\n  0123456789\n0 t.........\n1 ..........\n2 .........f\n3 ...s......\n4 .f........\n5 ........t.\n6 ...s......\n7 ..........\n8 ..........\n9 ..........\n\n";
        A.print_world(w);
        std::cout << "printing board: " << std::endl << board << std::endl;
        std::cout << "printing print world: " << std::endl << w.str() << std::endl;
        CPPUNIT_ASSERT(w.str() == board);            
    }
    
    void test_print_world3 () {
    	std::ostringstream w;
        Darwin A(20, 20);
        species trap("t");
        species sand("s");
        species wind("w");
        species fire("f");
        species rock("r");                       
        A.set_contents(0, 0, creature(enums::west, &trap));
        A.set_contents(10, 10, creature(enums::east, &trap)); 
        A.set_contents(5, 0, creature(enums::east, &sand));
        A.set_contents(12, 19, creature(enums::east, &sand));
        A.set_contents(10, 19, creature(enums::west, &fire));
        A.set_contents(1, 3, creature(enums::east, &fire)); 
        A.set_contents(9, 7, creature(enums::east, &rock));
        A.set_contents(12, 15, creature(enums::east, &rock));
        A.set_contents(4, 4, creature(enums::west, &wind));
        A.set_contents(0, 8, creature(enums::east, &wind)); 
        
        std::string board = "Turn = 0.\n  01234567890123456789\n0 t.......w...........\n1 ...f................\n2 ....................\n3 ....................\n4 ....w...............\n5 s...................\n6 ....................\n7 ....................\n8 ....................\n9 .......r............\n0 ..........t........f\n1 ....................\n2 ...............r...s\n3 ....................\n4 ....................\n5 ....................\n6 ....................\n7 ....................\n8 ....................\n9 ....................\n\n";
        A.print_world(w);
        std::cout << "printing board: " << std::endl << board << std::endl;
        std::cout << "printing print world: " << std::endl << w.str() << std::endl;
        CPPUNIT_ASSERT(w.str() == board);            
    }
    
    
    //-----------------
	// test_instruction constructor
    //-----------------
    
    void test_instruction1 () {
        instruction A("right", 4);
        CPPUNIT_ASSERT(A._n == 4);
        CPPUNIT_ASSERT(A._action == true);
    }
    
    void test_instruction2() {
        instruction B("hop", 1);
        CPPUNIT_ASSERT(B._n == 1);     
        CPPUNIT_ASSERT(B._action == true);        
    }
    
    void test_instruction3() {
        instruction C("if_empty", 90);
        CPPUNIT_ASSERT(C._n == 90);
        CPPUNIT_ASSERT(C._action == false);        
    }
    
    
    //-----------------
	// test_str_to_opcode
    //-----------------
    
    void test_str_opcode1 () {
        instruction A("right", 4);
       CPPUNIT_ASSERT(A._opcode == enums::right); 
    }
    
    void test_str_opcode2() {
        instruction B("hop", 1);
        CPPUNIT_ASSERT(B._opcode == enums::hop);       
    }
    
    void test_str_opcode3() {
        instruction C("if_empty", 90);
        CPPUNIT_ASSERT(C._opcode == enums::if_empty);       
    }
    
    //-----------------
	// test_species constructor
    //-----------------
    
    void test_species1 () {
       species A("first");
       CPPUNIT_ASSERT(A._name == "first");        
    }
    
    void test_species2 () {
       species B("second");
       CPPUNIT_ASSERT(B._name == "second");        
    }
    
    void test_species3 () {
       species C("third");
       CPPUNIT_ASSERT(C._name == "third");        
    }
    
    //-----------------
	// test_species add inst
    //-----------------
    
    void test_add_inst1 () {
       species A("first");
       A.add_inst("hop", 3);
       
       CPPUNIT_ASSERT(A._program[0]._opcode == enums::hop);        
    }
    
    void test_add_inst2 () {
       species B("first");
       B.add_inst("if_wall", 4);
       
       CPPUNIT_ASSERT(B._program[0]._opcode == enums::if_wall);        
    }
    
    void test_add_inst3 () {
       species C("first");
       C.add_inst("if_random", 1);
       CPPUNIT_ASSERT(C._program[0]._opcode == enums::if_random);        
    }
   
    //-----------------
	// test_inst_at
    //-----------------
    
    void test_inst_at1 () {
       species A("first");
       A.add_inst("hop", 3);
       A.add_inst("if_random", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       instruction* test = A.inst_at(1);
       CPPUNIT_ASSERT(test->_opcode == enums::if_random);        
    }
    
    void test_inst_at2 () {
       species A("first");
       A.add_inst("hop", 3);
       A.add_inst("if_random", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       instruction* test = A.inst_at(3);
       CPPUNIT_ASSERT(test->_opcode == enums::if_wall);        
    }
    
    void test_inst_at3 () {
       species A("first");
       A.add_inst("hop", 3);
       A.add_inst("if_random", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       instruction* test = A.inst_at(0);
       CPPUNIT_ASSERT(test->_opcode == enums::hop);        
    }
    
    //-----------------
	// test_size species
    //-----------------
    
    void test_size_sp1 () {
       species A("first");
       A.add_inst("hop", 3);
       A.add_inst("if_random", 3);  
       size_t test = A.size();
       CPPUNIT_ASSERT(test == 2);
    }
    
    void test_size_sp2 () {
       species A("first");    
       A.add_inst("if_random", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       size_t test = A.size();
       CPPUNIT_ASSERT(test == 3);    
    }
    
    void test_size_sp3 () {
       species A("first");
       A.add_inst("hop", 3);
       A.add_inst("if_random", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       A.add_inst("hop", 3);
       A.add_inst("if_wall", 3);
       size_t test = A.size();
       CPPUNIT_ASSERT(test == 8);        
    }
    
    //-----------------
	// test_creature
    //-----------------
    
    void test_creature1 () {
       creature test;
       CPPUNIT_ASSERT(test._isWall == true);
    }
    
     void test_creature2 () {
       creature test;
       CPPUNIT_ASSERT(test._isWall == true);
    }
    
     void test_creature3 () {
       creature test;
       CPPUNIT_ASSERT(test._isWall == true);
    }
    
    
    //-----------------
	// test_creature_constructor2
    //-----------------
    
    void test_creature_const1 () {
       species a("sp");
       creature test(2, &a);
       CPPUNIT_ASSERT(test._isWall == false);
       CPPUNIT_ASSERT(test._d == 2);
    }
    
     void test_creature_const2() {
       species a("sp2");
       creature test(10, &a);
       CPPUNIT_ASSERT(test._isWall == false);
       CPPUNIT_ASSERT(test._d == 10);
    }
    
     void test_creature_const3 () {
       species a("sp3");
       creature test(100, &a);
       CPPUNIT_ASSERT(test._isWall == false);
       CPPUNIT_ASSERT(test._d == 100);
    }
    
    //-----------------
	// test_creature_isWall
    //-----------------
    
    void test_creature_isWall1 () {
       species a("sp");
       creature test(2, &a);
       CPPUNIT_ASSERT(test.isWall() == false);      
    }
    
    void test_creature_isWall2 () {
       creature test;
       CPPUNIT_ASSERT(test.isWall() == true);
    }
    
    void test_creature_isWall3 () {
       species a("sp3");
       creature test(100, &a);
       CPPUNIT_ASSERT(test.isWall() == false);       
    }
    
    //-----------------
	// test_creature_execute
    //-----------------
    
    void test_creature_execute1 () {
		species food("f");
		food.add_inst("left", 0);
		food.add_inst("go", 0);			
		Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &food));
        executor.set_contents(3, 3, creature(enums::north, &food));        
        size_t result = executor._world[0][0]->execute(executor._world[1][0]);
        
		CPPUNIT_ASSERT(result == enums::nothing);      
    }
    
    void test_creature_execute2 () {
		species trap("t");
		trap.add_inst("if_enemy", 3);
		trap.add_inst("left", 0);
		trap.add_inst("go", 0);
		trap.add_inst("infect", 0);
		trap.add_inst("go", 0);
        species food("f");
		food.add_inst("left", 0);
		food.add_inst("go", 0);		
		Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &trap));
        executor.set_contents(3, 3, creature(enums::north, &trap));     
        executor.set_contents(1, 0, creature(enums::east, &food));
        executor.set_contents(3, 3, creature(enums::north, &food));     
        size_t result = executor._world[0][0]->execute(executor._world[1][0]);
        
		CPPUNIT_ASSERT(result == enums::infect_it);      
    }
    
    void test_creature_execute3 () {
		species trap("t");
		trap.add_inst("if_enemy", 3);
		trap.add_inst("left", 0);
		trap.add_inst("go", 0);
		trap.add_inst("infect", 0);
		trap.add_inst("go", 0);
        species food("f");
		food.add_inst("left", 0);
		food.add_inst("go", 0);		
		Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &trap));
        executor.set_contents(3, 3, creature(enums::north, &trap));     
        executor.set_contents(1, 0, creature(enums::east, &food));
        executor.set_contents(3, 3, creature(enums::north, &food));     
        size_t result = executor._world[3][3]->execute(executor._world[2][3]);        
		CPPUNIT_ASSERT(result == enums::nothing);           
    }
    
    //-----------------
	// test_creature_execute_one	
    //-----------------
    
    
    void test_creature_execute_one1 () {
		species food("f");
		food.add_inst("left", 0);
		food.add_inst("go", 0);			
		Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &food));
        instruction* inst = food.inst_at(0);
        size_t result = executor._world[0][0]->execute_one(executor._world[1][0], inst);        
		CPPUNIT_ASSERT(result == enums::nothing);      
    }
    
    void test_creature_execute_one2() {
		species trap("t");
		trap.add_inst("if_enemy", 3);
		trap.add_inst("left", 0);
		trap.add_inst("go", 0);
		trap.add_inst("infect", 0);
		trap.add_inst("go", 0);	
		Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &trap));
        executor.set_contents(2, 2, creature(enums::east, &trap));
        instruction* inst = trap.inst_at(1);
        size_t result = executor._world[2][2]->execute_one(executor._world[2][3], inst);        
		CPPUNIT_ASSERT(result == enums::nothing);      
    }
    
    void test_creature_execute_one3 () {
		species best("b");
		best.add_inst("if_enemy", 9);
		best.add_inst("if_empty", 7);
		best.add_inst("if_random", 5);
		best.add_inst("left", 0);
		best.add_inst("go", 0);
		best.add_inst("right", 0);
		best.add_inst("go", 0);
		best.add_inst("hop", 0);
		best.add_inst("go", 0);
		best.add_inst("infect", 0);
		best.add_inst("go", 0);		
		Darwin executor(8, 8);
        executor.set_contents(0, 0, creature(enums::east, &best));
        executor.set_contents(1, 3, creature(enums::east, &best));
        executor.set_contents(4, 4, creature(enums::east, &best));
        executor.set_contents(0, 4, creature(enums::east, &best));
        executor.set_contents(5, 7, creature(enums::east, &best));
        
        instruction* inst = best.inst_at(7);
        size_t result = executor._world[1][3]->execute_one(executor._world[1][4], inst);        
		CPPUNIT_ASSERT(result == enums::move_me);      
    }
    
    //-------------------------
	// test_creature_darwin run
    //-------------------------
    
    void test_darwin_run1 () {
		try {
		    species rover("r");
			rover.add_inst("if_enemy", 9);
			rover.add_inst("if_empty", 7);
			rover.add_inst("if_random", 5);
			rover.add_inst("left", 0);
			rover.add_inst("go", 0);
			rover.add_inst("right", 0);
			rover.add_inst("go", 0);
			rover.add_inst("hop", 0);
			rover.add_inst("go", 0);
			rover.add_inst("infect", 0);
			rover.add_inst("go", 0);
			species trap("t");
			trap.add_inst("if_enemy", 3);
			trap.add_inst("left", 0);
			trap.add_inst("go", 0);
			trap.add_inst("infect", 0);
			trap.add_inst("go", 0);
			species food("f");
			food.add_inst("left", 0);
			food.add_inst("go", 0);
		    Darwin executor(4, 4);
		    executor.set_contents(0, 0, creature(enums::south, &food));
		    executor.set_contents(0, 1, creature(enums::south, &trap));
		    executor.set_contents(1, 0, creature(enums::south, &trap));
		    executor.set_contents(1, 1, creature(enums::south, &food));
		    executor.run(4, 1);
		}
		catch (const invalid_argument&) {
		    assert(false);}
		catch (const out_of_range&) {
		    assert(false);}
    }
    
     void test_darwin_run2() {
		try {
			species trap("t");
			trap.add_inst("if_enemy", 3);
			trap.add_inst("left", 0);
			trap.add_inst("go", 0);
			trap.add_inst("infect", 0);
			trap.add_inst("go", 0);
			species food("f");
			food.add_inst("left", 0);
			food.add_inst("go", 0);
			species rover("r");
			rover.add_inst("if_enemy", 9);
			rover.add_inst("if_empty", 7);
			rover.add_inst("if_random", 5);
			rover.add_inst("left", 0);
			rover.add_inst("go", 0);
			rover.add_inst("right", 0);
			rover.add_inst("go", 0);
			rover.add_inst("hop", 0);
			rover.add_inst("go", 0);
			rover.add_inst("infect", 0);
			rover.add_inst("go", 0);
			srand(0);
			Darwin executor(4, 4);
			executor.set_contents(0, 0, creature(enums::south, &rover));
			executor.set_contents(0, 1, creature(enums::south, &food));
			executor.set_contents(1, 0, creature(enums::south, &food));
			executor.set_contents(1, 1, creature(enums::south, &food));
			executor.run(20, 1);
		}
		catch (const invalid_argument&) {
			assert(false);}
		catch (const out_of_range&) {
			assert(false);}
    }
    
     void test_darwin_run3 () {
		try {
		    species rover("r");
			rover.add_inst("if_enemy", 9);
			rover.add_inst("if_empty", 7);
			rover.add_inst("if_random", 5);
			rover.add_inst("left", 0);
			rover.add_inst("go", 0);
			rover.add_inst("right", 0);
			rover.add_inst("go", 0);
			rover.add_inst("hop", 0);
			rover.add_inst("go", 0);
			rover.add_inst("infect", 0);
			rover.add_inst("go", 0);
			species trap("t");
			trap.add_inst("if_enemy", 3);
			trap.add_inst("left", 0);
			trap.add_inst("go", 0);
			trap.add_inst("infect", 0);
			trap.add_inst("go", 0);
			species food("f");
			food.add_inst("left", 0);
			food.add_inst("go", 0);
			species hopper("h");
			hopper.add_inst("hop", 0);
			hopper.add_inst("go", 0);

			srand(0);
			Darwin s(3, 1);
			s.set_contents(0, 0, creature(enums::east, &food));
			s.set_contents(1, 0, creature(enums::east, &hopper));
			s.set_contents(2, 0, creature(enums::east, &rover));
			s.run(5, 1);
		}
		catch (const invalid_argument&) {
			assert(false);}
		catch (const out_of_range&) {
			assert(false);}
    }
    
    
    
    
    
    CPPUNIT_TEST_SUITE(TestDarwin);  
    CPPUNIT_TEST(test_darwin1);
    CPPUNIT_TEST(test_darwin2);
    CPPUNIT_TEST(test_darwin3);
    CPPUNIT_TEST(test_bounds1);
    CPPUNIT_TEST(test_bounds2);
    CPPUNIT_TEST(test_bounds3);
    CPPUNIT_TEST(test_set_contents1);
    CPPUNIT_TEST(test_set_contents2);
    CPPUNIT_TEST(test_set_contents3);
    CPPUNIT_TEST(test_print_world1);
    CPPUNIT_TEST(test_print_world2);
    CPPUNIT_TEST(test_print_world3);
    CPPUNIT_TEST(test_instruction1);
    CPPUNIT_TEST(test_instruction2);
    CPPUNIT_TEST(test_instruction3);
    CPPUNIT_TEST(test_str_opcode1);
    CPPUNIT_TEST(test_str_opcode2);
    CPPUNIT_TEST(test_str_opcode3);    
    CPPUNIT_TEST(test_species1);
    CPPUNIT_TEST(test_species2);
    CPPUNIT_TEST(test_species3);
    CPPUNIT_TEST(test_add_inst1);
    CPPUNIT_TEST(test_add_inst2);
    CPPUNIT_TEST(test_add_inst3);
    CPPUNIT_TEST(test_inst_at1);
    CPPUNIT_TEST(test_inst_at2);
    CPPUNIT_TEST(test_inst_at3);
    CPPUNIT_TEST(test_size_sp1);
    CPPUNIT_TEST(test_size_sp2);
    CPPUNIT_TEST(test_size_sp3);
    CPPUNIT_TEST(test_creature1);
    CPPUNIT_TEST(test_creature2);
    CPPUNIT_TEST(test_creature3);
    CPPUNIT_TEST(test_creature_const1);
    CPPUNIT_TEST(test_creature_const2);
    CPPUNIT_TEST(test_creature_const3);
    CPPUNIT_TEST(test_creature_isWall1);
    CPPUNIT_TEST(test_creature_isWall2);
    CPPUNIT_TEST(test_creature_isWall3);
    CPPUNIT_TEST(test_creature_execute1);
    CPPUNIT_TEST(test_creature_execute2);
    CPPUNIT_TEST(test_creature_execute3);
    CPPUNIT_TEST(test_creature_execute_one1);
    CPPUNIT_TEST(test_creature_execute_one2);
    CPPUNIT_TEST(test_creature_execute_one3);
    CPPUNIT_TEST(test_darwin_run1);
    CPPUNIT_TEST(test_darwin_run2);
    CPPUNIT_TEST(test_darwin_run3);   
    
    CPPUNIT_TEST_SUITE_END();
	};
	
	
// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}


