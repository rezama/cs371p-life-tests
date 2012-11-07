// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2012
// Christopher J. Boerner
// ------------------------------

/**
 * To test the program:
 *     g++ -std=c++0x -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#include "Darwin.h"

// ---------
// TestWorld
// ---------
struct TestWorld : CppUnit::TestFixture {
    // -----------
    // constructor
    // -----------
    void test_constructor_1_1 () {
    	World A(1,1);
    	CPPUNIT_ASSERT(1 == A._rows);
    	CPPUNIT_ASSERT(1 == A._columns);
    }

    void test_constructor_100_100 () {
    	World A(100,100);
    	CPPUNIT_ASSERT(100 == A._rows);
    	CPPUNIT_ASSERT(100 == A._columns);
    }

    void test_constructor_1_100 () {
    	World A(1,100);
    	CPPUNIT_ASSERT(1   == A._rows);
    	CPPUNIT_ASSERT(100 == A._columns);
    }

    void test_constructor_100_1 () {
    	World A(100,1);
    	CPPUNIT_ASSERT(100 == A._rows);
    	CPPUNIT_ASSERT(1   == A._columns);
    }

    void test_constructor_0_1 () {
    	try {
    		World A(0,1);
    		CPPUNIT_ASSERT(false);
    	} catch (std::invalid_argument&) {
    		/*nothing to be done*/
    	}
    }

    void test_constructor_1_0 () {
    	try {
    		World A(1,0);
    		CPPUNIT_ASSERT(false);
    	} catch (std::invalid_argument&) {
    		/*nothing to be done*/
    	}
    }

    void test_constructor_0_0 () {
    	try {
    		World A(0,0);
    		CPPUNIT_ASSERT(false);
    	} catch (std::invalid_argument&) {
    		/*nothing to be done*/
    	}
    }

    // -------------
    // find_adjacent
    // -------------
    void test_find_adjacent_1 () {
    	World A(1,1);
    	coordinate_t c = {3,5};
    	coordinate_t c_new = A.find_adjacent(c, NORTH);
    	CPPUNIT_ASSERT(2 == c_new.r);
    	CPPUNIT_ASSERT(5 == c_new.c);
        // coordinate_t r = {2,5};
        // CPPUNIT_ASSERT(c_new == r);
    }

    void test_find_adjacent_2 () {
    	World A(1,1);
    	coordinate_t c = {3,5};
    	coordinate_t c_new = A.find_adjacent(c, WEST);
    	CPPUNIT_ASSERT(3 == c_new.r);
    	CPPUNIT_ASSERT(4 == c_new.c);
    }

    void test_find_adjacent_3 () {
    	World A(1,1);
    	coordinate_t c = {3,5};
    	coordinate_t c_new = A.find_adjacent(c, SOUTH);
    	CPPUNIT_ASSERT(4 == c_new.r);
    	CPPUNIT_ASSERT(5 == c_new.c);
    }

    void test_find_adjacent_4 () {
    	World A(1,1);
    	coordinate_t c = {3,5};
    	coordinate_t c_new = A.find_adjacent(c, EAST);
    	CPPUNIT_ASSERT(3 == c_new.r);
    	CPPUNIT_ASSERT(6 == c_new.c);
    }

    // ------------
    // is_in_bounds
    // ------------
    void test_is_in_bounds_1 () {
        World A(10,6);
        coordinate_t c = {0,0};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_2 () {
        World A(10,6);
        coordinate_t c = {9,0};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_3 () {
        World A(10,6);
        coordinate_t c = {0,5};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_4 () {
        World A(10,6);
        coordinate_t c = {9,5};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_5 () {
        World A(10,6);
        coordinate_t c = {3,2};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_1 () {
        World A(5,9);
        coordinate_t c = {-1,0};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_2 () {
        World A(5,9);
        coordinate_t c = {0,-1};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_3 () {
        World A(5,9);
        coordinate_t c = {-1,-1};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_4 () {
        World A(5,9);
        coordinate_t c = {5,0};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_5 () {
        World A(5,9);
        coordinate_t c = {0,9};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_6 () {
        World A(5,9);
        coordinate_t c = {5,9};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_7 () {
        World A(5,9);
        coordinate_t c = {14,18};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    // -----
    // print
    // -----
    void test_print_blank_1 () {
        std::string r("  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n");
        World A(8,8);
        std::ostringstream w;
        A.print(w);
        CPPUNIT_ASSERT(r == w.str());
    }

    CPPUNIT_TEST_SUITE(TestWorld);
	CPPUNIT_TEST(test_constructor_1_1);
	CPPUNIT_TEST(test_constructor_100_100);
	CPPUNIT_TEST(test_constructor_1_100);
	CPPUNIT_TEST(test_constructor_100_1);
	CPPUNIT_TEST(test_constructor_0_1);
	CPPUNIT_TEST(test_constructor_1_0);
	CPPUNIT_TEST(test_constructor_0_0);

	CPPUNIT_TEST(test_find_adjacent_1);
	CPPUNIT_TEST(test_find_adjacent_2);
	CPPUNIT_TEST(test_find_adjacent_3);
	CPPUNIT_TEST(test_find_adjacent_4);

    CPPUNIT_TEST(test_is_in_bounds_1);
    CPPUNIT_TEST(test_is_in_bounds_2);
    CPPUNIT_TEST(test_is_in_bounds_3);
    CPPUNIT_TEST(test_is_in_bounds_4);
    CPPUNIT_TEST(test_is_in_bounds_5);

    CPPUNIT_TEST(test_is_not_in_bounds_1);
    CPPUNIT_TEST(test_is_not_in_bounds_2);
    CPPUNIT_TEST(test_is_not_in_bounds_3);
    CPPUNIT_TEST(test_is_not_in_bounds_4);
    CPPUNIT_TEST(test_is_not_in_bounds_5);
    CPPUNIT_TEST(test_is_not_in_bounds_6);
    CPPUNIT_TEST(test_is_not_in_bounds_7);

    CPPUNIT_TEST(test_print_blank_1);
    CPPUNIT_TEST_SUITE_END();
};

// ------------
// TestSpecies
// ------------
struct TestSpecies : CppUnit::TestFixture {
    // -----------
    // constructor
    // -----------
    void test_constructor_easy () {
        Species test("test");
        CPPUNIT_ASSERT(test._name == "test");
    }

    void test_constructor_blank () {
        try {
            Species test("");
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }

    // --------------------
    // get_num_instructions
    // --------------------
    void test_get_num_instructions_easy () {
        Species t("test");
        CPPUNIT_ASSERT(0 == t.get_num_instructions());
    }

    void test_get_num_instructions_1 () {
        Species t("test");
        instruction_t i = {HOP};
        t._instructions = std::vector<instruction_t>(10,i);
        CPPUNIT_ASSERT(10 == t.get_num_instructions());
    }

    void test_get_num_instructions_2 () {
        Species t("test");
        instruction_t i = {LEFT};
        t._instructions = std::vector<instruction_t>(100,i);
        CPPUNIT_ASSERT(100 == t.get_num_instructions());
    }

    // ---
    // add
    // ---
    void test_add_easy () {
        Species test("test");
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "test");
        CPPUNIT_ASSERT(1 == test.get_num_instructions());
    }

    void test_add_food () {
        Species test("food");
        test.add(LEFT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "food");
        CPPUNIT_ASSERT(2 == test.get_num_instructions());
    }
 
    void test_add_hopper () {
        Species test("hopper");
        test.add(HOP);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "hopper");
        CPPUNIT_ASSERT(2 == test.get_num_instructions());
    }
 
    void test_add_rover () {
        Species test("rover");
        test.add(IF_ENEMY,9);
        test.add(IF_EMPTY,7);
        test.add(IF_RANDOM,5);
        test.add(LEFT);
        test.add(GO,0);
        test.add(RIGHT);
        test.add(GO,0);
        test.add(HOP);
        test.add(GO,0);
        test.add(INFECT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "rover");
        CPPUNIT_ASSERT(11 == test.get_num_instructions());
    }
 
    void test_add_trap () {
        Species test("trap");
        test.add(IF_ENEMY,3);
        test.add(LEFT);
        test.add(GO,0);
        test.add(INFECT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "trap");
        CPPUNIT_ASSERT(5 == test.get_num_instructions());
    }

    // -----------
    // operator <<
    // -----------
    void test_operator_ll_1 () {
        const std::string r("t");
        Species s("trap");
        std::ostringstream w;
        w << s;
        CPPUNIT_ASSERT(r == w.str());
    }

    void test_operator_ll_2 () {
        const std::string r("f");
        Species s("food");
        std::ostringstream w;
        w << s;
        CPPUNIT_ASSERT(r == w.str());
    }

    void test_operator_ll_3 () {
        const std::string r("r");
        Species s("rover");
        std::ostringstream w;
        w << s;
        CPPUNIT_ASSERT(r == w.str());
    }

    void test_operator_ll_4 () {
        const std::string r("h");
        Species s("hopper");
        std::ostringstream w;
        w << s;
        CPPUNIT_ASSERT(r == w.str());
    }

    // -----
    // clear
    // -----
    void test_clear_easy () {
        Species test("test");
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "test");
        CPPUNIT_ASSERT(1 == test.get_num_instructions());
        test.clear();
        CPPUNIT_ASSERT(0 == test.get_num_instructions());
    }

    void test_clear_food () {
        Species test("food");
        test.add(LEFT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "food");
        CPPUNIT_ASSERT(2 == test.get_num_instructions());
        test.clear();
        CPPUNIT_ASSERT(0 == test.get_num_instructions());
    }
 
    void test_clear_hopper () {
        Species test("hopper");
        test.add(HOP);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "hopper");
        CPPUNIT_ASSERT(2 == test.get_num_instructions());
        test.clear();
        CPPUNIT_ASSERT(0 == test.get_num_instructions());
    }
 
    void test_clear_rover () {
        Species test("rover");
        test.add(IF_ENEMY,9);
        test.add(IF_EMPTY,7);
        test.add(IF_RANDOM,5);
        test.add(LEFT);
        test.add(GO,0);
        test.add(RIGHT);
        test.add(GO,0);
        test.add(HOP);
        test.add(GO,0);
        test.add(INFECT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "rover");
        CPPUNIT_ASSERT(11 == test.get_num_instructions());
        test.clear();
        CPPUNIT_ASSERT(0 == test.get_num_instructions());
    }
 
    void test_clear_trap () {
        Species test("trap");
        test.add(IF_ENEMY,3);
        test.add(LEFT);
        test.add(GO,0);
        test.add(INFECT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "trap");
        CPPUNIT_ASSERT(5 == test.get_num_instructions());
        test.clear();
        CPPUNIT_ASSERT(0 == test.get_num_instructions());
    }

    // ---------------
    // get_instruction
    // ---------------
    void test_get_instruction_food () {
        Species test("food");
        test.add(LEFT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "food");
        CPPUNIT_ASSERT(2 == test.get_num_instructions());

        unsigned int c = 0;
        instruction_t i = test.get_instruction(c);
        instruction_t r = {LEFT};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
    }
 
    void test_get_instruction_hopper () {
        Species test("hopper");
        test.add(HOP);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "hopper");
        CPPUNIT_ASSERT(2 == test.get_num_instructions());

        unsigned int c = 0;
        instruction_t i = test.get_instruction(c);
        instruction_t r = {HOP};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
    }
 
    void test_get_instruction_rover () {
        Species test("rover");
        test.add(IF_ENEMY,9);
        test.add(IF_EMPTY,7);
        test.add(IF_RANDOM,5);
        test.add(LEFT);
        test.add(GO,0);
        test.add(RIGHT);
        test.add(GO,0);
        test.add(HOP);
        test.add(GO,0);
        test.add(INFECT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "rover");
        CPPUNIT_ASSERT(11 == test.get_num_instructions());

        unsigned int c = 0;
        instruction_t i = test.get_instruction(c);
        instruction_t r = {IF_ENEMY,9};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {IF_EMPTY,7};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {IF_RANDOM,5};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {LEFT};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {RIGHT};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {HOP};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {INFECT};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
    }
 
    void test_get_instruction_trap () {
        Species test("trap");
        test.add(IF_ENEMY,3);
        test.add(LEFT);
        test.add(GO,0);
        test.add(INFECT);
        test.add(GO,0);
        CPPUNIT_ASSERT(test._name == "trap");
        CPPUNIT_ASSERT(5 == test.get_num_instructions());

        unsigned int c = 0;
        instruction_t i = test.get_instruction(c);
        instruction_t r = {IF_ENEMY,3};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {LEFT};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {INFECT};
        CPPUNIT_ASSERT(r == i);
        ++c;
        i = test.get_instruction(c);
        r = {GO,0};
        CPPUNIT_ASSERT(r == i);
        ++c;
    }
 
    CPPUNIT_TEST_SUITE(TestSpecies);
    CPPUNIT_TEST(test_constructor_easy);
    CPPUNIT_TEST(test_constructor_blank);

    CPPUNIT_TEST(test_get_num_instructions_easy);
    CPPUNIT_TEST(test_get_num_instructions_1);
    CPPUNIT_TEST(test_get_num_instructions_2);
    
    CPPUNIT_TEST(test_add_easy);
    CPPUNIT_TEST(test_add_food);
    CPPUNIT_TEST(test_add_hopper);
    CPPUNIT_TEST(test_add_rover);
    CPPUNIT_TEST(test_add_trap);
    
    CPPUNIT_TEST(test_operator_ll_1);
    CPPUNIT_TEST(test_operator_ll_2);
    CPPUNIT_TEST(test_operator_ll_3);
    CPPUNIT_TEST(test_operator_ll_4);
    
    CPPUNIT_TEST(test_clear_easy);
    CPPUNIT_TEST(test_clear_food);
    CPPUNIT_TEST(test_clear_hopper);
    CPPUNIT_TEST(test_clear_rover);
    CPPUNIT_TEST(test_clear_trap);
    
    CPPUNIT_TEST(test_get_instruction_food);
    CPPUNIT_TEST(test_get_instruction_hopper);
    CPPUNIT_TEST(test_get_instruction_rover);
    CPPUNIT_TEST(test_get_instruction_trap);
    CPPUNIT_TEST_SUITE_END();  
};

// ------------
// TestCreature
// ------------
struct TestCreature : CppUnit::TestFixture {
    World *world;
    Species *food,*hopper,*rover,*trap;

    void setUp () {
        world  = new World(10,10);
        food   = new Species("food");
        food->add(LEFT);
        food->add(GO,0);

        hopper = new Species("hopper");
        hopper->add(HOP);
        hopper->add(GO,0);

        rover  = new Species("rover");
        rover->add(IF_ENEMY,9);
        rover->add(IF_EMPTY,7);
        rover->add(IF_RANDOM,5);
        rover->add(LEFT);
        rover->add(GO,0);
        rover->add(RIGHT);
        rover->add(GO,0);
        rover->add(HOP);
        rover->add(GO,0);
        rover->add(INFECT);
        rover->add(GO,0);

        trap   = new Species("trap");
        trap->add(IF_ENEMY,3);
        trap->add(LEFT);
        trap->add(GO,0);
        trap->add(INFECT);
        trap->add(GO,0);
    }

    void tearDown () {
        delete trap;
        delete rover;
        delete hopper;
        delete food;
        delete world;
    }

    // -----------
    // constructor
    // -----------
    void test_constructor_1 () {
        Creature c(*world, food, NORTH);
        CPPUNIT_ASSERT(c._species == const_cast<const Species*>(food));
        CPPUNIT_ASSERT(0 == c._programCounter);
        CPPUNIT_ASSERT(NORTH == c._direction);
    }
 
    void test_constructor_2 () {
        Creature c(*world, hopper, WEST);
        CPPUNIT_ASSERT(c._species == const_cast<const Species*>(hopper));
        CPPUNIT_ASSERT(0 == c._programCounter);
        CPPUNIT_ASSERT(WEST == c._direction);
    }
 
    void test_constructor_3 () {
        Creature c(*world, rover, EAST);
        CPPUNIT_ASSERT(c._species == const_cast<const Species*>(rover));
        CPPUNIT_ASSERT(0 == c._programCounter);
        CPPUNIT_ASSERT(EAST == c._direction);
    }
 
    void test_constructor_4 () {
    	Creature c(*world, trap, SOUTH);
        CPPUNIT_ASSERT(c._species == const_cast<const Species*>(trap));
        CPPUNIT_ASSERT(0 == c._programCounter);
        CPPUNIT_ASSERT(SOUTH == c._direction);
    }
 
    // -----------
    // operator <<
    // -----------
    void test_operator_ll_1 () {
        const std::string r("t");
        Creature c(*world, trap, SOUTH);
        std::ostringstream w;
        w << c;
        CPPUNIT_ASSERT(r == w.str());
    }

    void test_operator_ll_2 () {
        const std::string r("f");
        Creature c(*world, food, NORTH);
        std::ostringstream w;
        w << c;
        CPPUNIT_ASSERT(r == w.str());
    }

    void test_operator_ll_3 () {
        const std::string r("r");
        Creature c(*world, rover, WEST);
        std::ostringstream w;
        w << c;
        CPPUNIT_ASSERT(r == w.str());
    }

    void test_operator_ll_4 () {
        const std::string r("h");
        Creature c(*world, hopper, EAST);
        std::ostringstream w;
        w << c;
        CPPUNIT_ASSERT(r == w.str());
    }

    // -----------
    // operator ==
    // -----------
    void test_operator_eq_food_1 () {
        Creature a(*world, food, NORTH);
        Creature b(*world, food, NORTH);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }
 
    void test_operator_eq_food_2 () {
        Creature a(*world, food, NORTH);
        Creature b(*world, food, SOUTH);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }
 
    void test_operator_eq_trap_1 () {
        Creature a(*world, trap, SOUTH);
        Creature b(*world, trap, SOUTH);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }
 
    void test_operator_eq_trap_2 () {
        Creature a(*world, trap, SOUTH);
        Creature b(*world, trap, WEST);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }
 
    void test_operator_eq_rover_1 () {
        Creature a(*world, rover, WEST);
        Creature b(*world, rover, WEST);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
  }
 
    void test_operator_eq_rover_2 () {
        Creature a(*world, rover, NORTH);
        Creature b(*world, rover, WEST);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }
 
    void test_operator_eq_hopper_1 () {
        Creature a(*world, hopper, EAST);
        Creature b(*world, hopper, EAST);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }
 
    void test_operator_eq_hopper_2 () {
    	Creature a(*world, hopper, EAST);
        Creature b(*world, hopper, SOUTH);
        CPPUNIT_ASSERT(a == b);
        CPPUNIT_ASSERT(b == a);
    }

    // -----------
    // operator !=
    // -----------
    void test_operator_neq_1 () {
        Creature a(*world, trap, NORTH);
        Creature b(*world, food, SOUTH);
        CPPUNIT_ASSERT(a != b);
        CPPUNIT_ASSERT(b != a);
    }
 
    void test_operator_neq_2 () {
        Creature a(*world, trap, NORTH);
        Creature b(*world, food, NORTH);
        CPPUNIT_ASSERT(a != b);
        CPPUNIT_ASSERT(b != a);
    }
 
    void test_operator_neq_3 () {
        Creature a(*world, trap, WEST);
        Creature b(*world, food, WEST);
        Creature c(*world, hopper, WEST);
        Creature d(*world, rover, WEST);
        CPPUNIT_ASSERT(a != b);
        CPPUNIT_ASSERT(b != c);
        CPPUNIT_ASSERT(c != d);
        CPPUNIT_ASSERT(a != d);
        CPPUNIT_ASSERT(a != c);
        CPPUNIT_ASSERT(b != d);
    }
 
    // ----
    // left
    // ----
    void test_left () {
        Creature c(*world, rover,NORTH);
        unsigned int p = 0;
        CPPUNIT_ASSERT(c._direction == NORTH);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.left();
        ++p;
        CPPUNIT_ASSERT(c._direction == WEST);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.left();
        ++p;
        CPPUNIT_ASSERT(c._direction == SOUTH);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.left();
        ++p;
        CPPUNIT_ASSERT(c._direction == EAST);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.left();
        ++p;
        CPPUNIT_ASSERT(c._direction == NORTH);
        CPPUNIT_ASSERT(c._programCounter == p);

    }

    // -----
    // right
    // -----
    void test_right () {
        Creature c(*world, trap,SOUTH);
        unsigned int p = 0;
        CPPUNIT_ASSERT(c._direction == SOUTH);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.right();
        ++p;
        CPPUNIT_ASSERT(c._direction == WEST);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.right();
        ++p;
        CPPUNIT_ASSERT(c._direction == NORTH);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.right();
        ++p;
        CPPUNIT_ASSERT(c._direction == EAST);
        CPPUNIT_ASSERT(c._programCounter == p);
        c.right();
        ++p;
        CPPUNIT_ASSERT(c._direction == SOUTH);
        CPPUNIT_ASSERT(c._programCounter == p);
    }

    // --
    // go
    // --
    void test_go_1 () {
    	Creature c(*world, hopper, NORTH);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.go(1);
        CPPUNIT_ASSERT(1 == c._programCounter);
    }

    void test_go_2 () {
        Creature c(*world, rover, SOUTH);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.go(7);
        CPPUNIT_ASSERT(7 == c._programCounter);
    }

    void test_go_3 () {
        Creature c(*world, rover, SOUTH);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.go(10);
        CPPUNIT_ASSERT(10 == c._programCounter);
    }

    // ---------
    // if_random
    // ---------
    void test_if_random_1 () {
        unsigned int n = 100;
        unsigned int p = 2;

        srand(n);
        Creature c(*world, trap, WEST);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.if_random(p);

        srand(n);
        if (!(rand() & 1)) {
            p = 1;
        }
        CPPUNIT_ASSERT(p == c._programCounter);
    }

    void test_if_random_2 () {
        unsigned int n = 0;
        unsigned int p = 0;

        srand(n);
        Creature c(*world, food, EAST);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.if_random(p);

        srand(n);
        if (!(rand() & 1)) {
            p = 1;
        }
        CPPUNIT_ASSERT(p == c._programCounter);
    }

    void test_if_random_3 () {
        unsigned int n = 69420;
        unsigned int p = 0;

        srand(n);
        Creature c(*world, hopper, NORTH);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.if_random(p);

        srand(n);
        if (!(rand() & 1)) {
            p = 1;
        }
        CPPUNIT_ASSERT(p == c._programCounter);
    }

    void test_if_random_4 () {
        unsigned int n = 2813308004;
        unsigned int p = 7;

        srand(n);
        Creature c(*world, rover, SOUTH);
        CPPUNIT_ASSERT(0 == c._programCounter);
        c.if_random(p);

        srand(n);
        if (!(rand() & 1)) {
            p = 1;
        }
        CPPUNIT_ASSERT(p == c._programCounter);
    }

    CPPUNIT_TEST_SUITE(TestCreature);
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);

    CPPUNIT_TEST(test_operator_eq_food_1);
    CPPUNIT_TEST(test_operator_eq_food_2);
    CPPUNIT_TEST(test_operator_eq_trap_1);
    CPPUNIT_TEST(test_operator_eq_trap_2);
    CPPUNIT_TEST(test_operator_eq_rover_1);
    CPPUNIT_TEST(test_operator_eq_rover_2);
    CPPUNIT_TEST(test_operator_eq_hopper_1);
    CPPUNIT_TEST(test_operator_eq_hopper_2);

    CPPUNIT_TEST(test_operator_neq_1);
    CPPUNIT_TEST(test_operator_neq_2);
    CPPUNIT_TEST(test_operator_neq_3);

    CPPUNIT_TEST(test_left);
    CPPUNIT_TEST(test_right);
    CPPUNIT_TEST_SUITE_END();
};

// ----------
// TestDarwin
// ----------
struct TestDarwin : CppUnit::TestFixture {
    World *world;
    Darwin *darwin;
    Species *food,*hopper,*rover,*trap;

    void setUp () {
        world  = new World(10,10);
        darwin = new Darwin(*world);
        food   = new Species("food");
        food->add(LEFT);
        food->add(GO,0);

        hopper = new Species("hopper");
        hopper->add(HOP);
        hopper->add(GO,0);

        rover  = new Species("rover");
        rover->add(IF_ENEMY,9);
        rover->add(IF_EMPTY,7);
        rover->add(IF_RANDOM,5);
        rover->add(LEFT);
        rover->add(GO,0);
        rover->add(RIGHT);
        rover->add(GO,0);
        rover->add(HOP);
        rover->add(GO,0);
        rover->add(INFECT);
        rover->add(GO,0);

        trap   = new Species("trap");
        trap->add(IF_ENEMY,3);
        trap->add(LEFT);
        trap->add(GO,0);
        trap->add(INFECT);
        trap->add(GO,0);
    }

    void tearDown () {
        delete trap;
        delete rover;
        delete hopper;
        delete food;
        delete darwin;
        delete world;
    }

    // ------------------
    // test_get_direction
    // ------------------
    void test_get_direction_1 () {
        direction_t a = NORTH;
        direction_t b = get_direction((unsigned int) a);
        CPPUNIT_ASSERT(a == b);
    }

    void test_get_direction_2 () {
        direction_t a = EAST;
        direction_t b = get_direction((unsigned int) a);
        CPPUNIT_ASSERT(a == b);
    }

    void test_get_direction_3 () {
        direction_t a = SOUTH;
        direction_t b = get_direction((unsigned int) a);
        CPPUNIT_ASSERT(a == b);
    }

    void test_get_direction_4 () {
        direction_t a = WEST;
        direction_t b = get_direction((unsigned int) a);
        CPPUNIT_ASSERT(a == b);
    }

    // --------------------------
    // test_coordinate_operator_l
    // --------------------------
    void test_coordinate_operator_l_1 () {
        coordinate_t a = {4,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a < b));
    }

    void test_coordinate_operator_l_2 () {
        coordinate_t a = {3,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a < b);
    }

    void test_coordinate_operator_l_3 () {
        coordinate_t a = {4,4};
        coordinate_t b = {3,4};
        CPPUNIT_ASSERT(!(a < b));
    }

    void test_coordinate_operator_l_4 () {
        coordinate_t a = {4,3};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a < b);
    }

    void test_coordinate_operator_l_5 () {
        coordinate_t a = {4,5};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a < b));
    }

    // --------------------------
    // test_coordinate_operator_g
    // --------------------------
    void test_coordinate_operator_g_1 () {
        coordinate_t a = {4,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a > b));
    }

    void test_coordinate_operator_g_2 () {
        coordinate_t a = {3,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a > b));
    }

    void test_coordinate_operator_g_3 () {
        coordinate_t a = {4,4};
        coordinate_t b = {3,4};
        CPPUNIT_ASSERT(a > b);
    }

    void test_coordinate_operator_g_4 () {
        coordinate_t a = {4,3};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a > b));
    }

    void test_coordinate_operator_g_5 () {
        coordinate_t a = {4,5};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a > b);
    }

    // ---------------------------
    // test_coordinate_operator_le
    // ---------------------------
    void test_coordinate_operator_le_1 () {
        coordinate_t a = {4,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a <= b);
    }

    void test_coordinate_operator_le_2 () {
        coordinate_t a = {3,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a <= b);
    }

    void test_coordinate_operator_le_3 () {
        coordinate_t a = {4,4};
        coordinate_t b = {3,4};
        CPPUNIT_ASSERT(!(a <= b));
    }

    void test_coordinate_operator_le_4 () {
        coordinate_t a = {4,3};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a <= b);
    }

    void test_coordinate_operator_le_5 () {
        coordinate_t a = {4,5};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a <= b));
    }

    // ---------------------------
    // test_coordinate_operator_ge
    // ---------------------------
    void test_coordinate_operator_ge_1 () {
        coordinate_t a = {4,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a >= b);
    }

    void test_coordinate_operator_ge_2 () {
        coordinate_t a = {3,4};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a >= b));
    }

    void test_coordinate_operator_ge_3 () {
        coordinate_t a = {4,4};
        coordinate_t b = {3,4};
        CPPUNIT_ASSERT(a >= b);
    }

    void test_coordinate_operator_ge_4 () {
        coordinate_t a = {4,3};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(!(a >= b));
    }

    void test_coordinate_operator_ge_5 () {
        coordinate_t a = {4,5};
        coordinate_t b = {4,4};
        CPPUNIT_ASSERT(a >= b);
    }

    // ----------
    // World::put
    // ----------
    void test_put_1 () {
        Creature crt(*world, hopper, SOUTH);
        world->put(&crt, 0, 0);
        CPPUNIT_ASSERT(*world->_grid[0][0] == crt);
    }
    
    void test_put_2 () {
        Creature crt(*world, trap, NORTH);
        world->put(&crt, 9, 0);
        CPPUNIT_ASSERT(*world->_grid[9][0] == crt);
    }
    
    void test_put_3 () {
        Creature crt(*world, rover, EAST);
        world->put(&crt, 0, 9);
        CPPUNIT_ASSERT(*world->_grid[0][9] == crt);
    }
    
    void test_put_4 () {
        Creature crt(*world, food, WEST);
        world->put(&crt, 9, 9);
        CPPUNIT_ASSERT(*world->_grid[9][9] == crt);
    }

    void test_except_put_1 () {
        Creature crt(*world, hopper, SOUTH);
        world->put(&crt, 0, 0);
        try {
            world->put(&crt, 0, 0);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }
    
    void test_except_put_2 () {
        Creature crt(*world, trap, NORTH);
        world->put(&crt, 9, 0);
        try {
            world->put(&crt, 9, 0);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }
    
    void test_except_put_3 () {
        Creature crt(*world, rover, EAST);
        world->put(&crt, 0, 9);
        try {
            world->put(&crt, 0, 9);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }
    
    void test_except_put_4 () {
        Creature crt(*world, food, WEST);
        world->put(&crt, 9, 9);
        try {
            world->put(&crt, 9, 9);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }  

    void test_except_put_5 () {
        Creature crt(*world, food, WEST);
        try {
            world->put(&crt, 9, 10);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }

    void test_except_put_6 () {
        Creature crt(*world, food, WEST);
        try {
            world->put(&crt, 10, 9);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }

    void test_except_put_7 () {
        Creature crt(*world, food, WEST);
        try {
            world->put(&crt, 10, 10);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }

    void test_except_put_8 () {
        Creature crt(*world, food, WEST);
        try {
            world->put(&crt, 11, 10);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) {
            /*nothing to be done*/
        }
    }

    // ----------
    // World::get
    // ----------
    void test_get_1 () {
        Creature crt(*world, hopper, SOUTH);
        world->put(&crt, 0, 0);
        Creature crt2(*world, food, NORTH);
        world->put(&crt2, 1, 0);
        CPPUNIT_ASSERT(*world->get(&crt, SOUTH) == crt2);
    }
    
    void test_get_2 () {
        Creature crt(*world, trap, EAST);
        world->put(&crt, 9, 0);
        Creature crt2(*world, hopper, NORTH);
        world->put(&crt2, 9, 1);
        CPPUNIT_ASSERT(*world->get(&crt, EAST) == crt2);
    }
    
    void test_get_3 () {
        Creature crt(*world, rover, WEST);
        world->put(&crt, 0, 9);
        Creature crt2(*world, trap, NORTH);
        world->put(&crt2, 0, 8);
        CPPUNIT_ASSERT(*world->get(&crt, WEST) == crt2);
    }
    
    void test_get_4 () {
        Creature crt(*world, food, NORTH);
        world->put(&crt, 9, 9);
        Creature crt2(*world, rover, NORTH);
        world->put(&crt2, 8, 9);
        CPPUNIT_ASSERT(*world->get(&crt, NORTH) == crt2);
    }
        
    // --------------
    // World::at_wall
    // --------------
    void test_at_wall_1 () {
        Creature crt(*world, hopper, SOUTH);
        world->put(&crt, 0, 0);
        CPPUNIT_ASSERT(!(world->at_wall(&crt, SOUTH)));
        CPPUNIT_ASSERT(!(world->at_wall(&crt, EAST)));
        CPPUNIT_ASSERT(world->at_wall(&crt, NORTH));
        CPPUNIT_ASSERT(world->at_wall(&crt, WEST));
    }
    
    void test_at_wall_2 () {
        Creature crt(*world, trap, EAST);
        world->put(&crt, 9, 0);
        CPPUNIT_ASSERT(!(world->at_wall(&crt, NORTH)));
        CPPUNIT_ASSERT(!(world->at_wall(&crt, EAST)));
        CPPUNIT_ASSERT(world->at_wall(&crt, SOUTH));
        CPPUNIT_ASSERT(world->at_wall(&crt, WEST));
    }
    
    void test_at_wall_3 () {
        Creature crt(*world, rover, WEST);
        world->put(&crt, 0, 9);
        CPPUNIT_ASSERT(!(world->at_wall(&crt, SOUTH)));
        CPPUNIT_ASSERT(!(world->at_wall(&crt, WEST)));
        CPPUNIT_ASSERT(world->at_wall(&crt, NORTH));
        CPPUNIT_ASSERT(world->at_wall(&crt, EAST));
    }
    
    void test_at_wall_4 () {
        Creature crt(*world, food, NORTH);
        world->put(&crt, 9, 9);
        CPPUNIT_ASSERT(!(world->at_wall(&crt, NORTH)));
        CPPUNIT_ASSERT(!(world->at_wall(&crt, WEST)));
        CPPUNIT_ASSERT(world->at_wall(&crt, SOUTH));
        CPPUNIT_ASSERT(world->at_wall(&crt, EAST));
    }
        
    // --------------------
    // World::move_adjacent
    // --------------------
    void test_move_adjacent_1 () {
        Creature crt(*world, hopper, SOUTH);
        world->put(&crt, 0, 0);
        CPPUNIT_ASSERT(*world->_grid[0][0] == crt);
        world->move_adjacent(&crt, crt._direction);
        CPPUNIT_ASSERT(world->_grid[0][0] == 0);
        CPPUNIT_ASSERT(*world->_grid[1][0] == crt);
    }
    
    void test_move_adjacent_2 () {
        Creature crt(*world, trap, EAST);
        world->put(&crt, 9, 0);
        CPPUNIT_ASSERT(*world->_grid[9][0] == crt);
        world->move_adjacent(&crt, crt._direction);
        CPPUNIT_ASSERT(world->_grid[9][0] == 0);
        CPPUNIT_ASSERT(*world->_grid[9][1] == crt);
    }
    
    void test_move_adjacent_3 () {
        Creature crt(*world, rover, WEST);
        world->put(&crt, 0, 9);
        CPPUNIT_ASSERT(*world->_grid[0][9] == crt);
        world->move_adjacent(&crt, crt._direction);
        CPPUNIT_ASSERT(world->_grid[0][9] == 0);
        CPPUNIT_ASSERT(*world->_grid[0][8] == crt);
    }
    
    void test_move_adjacent_4 () {
        Creature crt(*world, food, NORTH);
        world->put(&crt, 9, 9);
        CPPUNIT_ASSERT(*world->_grid[9][9] == crt);
        world->move_adjacent(&crt, crt._direction);
        CPPUNIT_ASSERT(world->_grid[9][9] == 0);
        CPPUNIT_ASSERT(*world->_grid[8][9] == crt);
    }
        
    void test_move_adjacent_5 () {
        Creature  crt(*world, food, NORTH);
        Creature crt2(*world, trap, WEST);
        world->put(&crt, 9, 9);
        world->put(&crt2,8, 9);
        CPPUNIT_ASSERT(*world->_grid[9][9] == crt);
        CPPUNIT_ASSERT(*world->_grid[8][9] == crt2);
        world->move_adjacent(&crt, crt._direction);
        CPPUNIT_ASSERT(*world->_grid[9][9] == crt);
        CPPUNIT_ASSERT(*world->_grid[8][9] == crt2);
    }
        
    void test_move_adjacent_6 () {
        Creature crt(*world, food, SOUTH);
        world->put(&crt, 9, 9);
        CPPUNIT_ASSERT(*world->_grid[9][9] == crt);
        world->move_adjacent(&crt, crt._direction);
        CPPUNIT_ASSERT(*world->_grid[9][9] == crt);
    }
    
    // ------------
    // World::print
    // ------------
    void test_world_print_1 () {
        const std::string r("  0123456789\n0 f.........\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
        std::ostringstream w;
        Creature crt(*world, food, NORTH);

        world->put(&crt, 0, 0);
        world->print(w);

        CPPUNIT_ASSERT(r == w.str());
    }

    void test_world_print_2 () {
        const std::string r("  0123456789\n0 f........h\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 ..........\n");
        std::ostringstream w;
        Creature  crt(*world, food, NORTH);
        Creature crt2(*world, hopper, NORTH);

        world->put( &crt, 0, 0);
        world->put(&crt2, 0, 9);
        world->print(w);

        CPPUNIT_ASSERT(r == w.str());
    }

    void test_world_print_3 () {
        const std::string r("  0123456789\n0 f........h\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 .........t\n");
        std::ostringstream w;
        Creature  crt(*world, food, NORTH);
        Creature crt2(*world, hopper, NORTH);
        Creature crt3(*world, trap, NORTH);

        world->put( &crt, 0, 0);
        world->put(&crt2, 0, 9);
        world->put(&crt3, 9, 9);
        world->print(w);

        CPPUNIT_ASSERT(r == w.str());
    }

    void test_world_print_4 () {
        const std::string r("  0123456789\n0 f........h\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 r........t\n");
        std::ostringstream w;
        Creature  crt(*world, food, NORTH);
        Creature crt2(*world, hopper, NORTH);
        Creature crt3(*world, trap, NORTH);
        Creature crt4(*world, rover, NORTH);

        world->put( &crt, 0, 0);
        world->put(&crt2, 0, 9);
        world->put(&crt3, 9, 9);
        world->put(&crt4, 9, 0);
        world->print(w);

        CPPUNIT_ASSERT(r == w.str());
    }

    void test_world_print_5 () {
        const std::string r("  0123456789\n0 f........h\n1 ..........\n2 ..........\n3 ..........\n4 ..........\n5 ..r.......\n6 ..........\n7 ..........\n8 ..........\n9 r........t\n");
        std::ostringstream w;
        Creature  crt(*world, food, NORTH);
        Creature crt2(*world, hopper, NORTH);
        Creature crt3(*world, trap, NORTH);
        Creature crt4(*world, rover, NORTH);
        Creature crt5(*world, rover, NORTH);

        world->put( &crt, 0, 0);
        world->put(&crt2, 0, 9);
        world->put(&crt3, 9, 9);
        world->put(&crt4, 9, 0);
        world->put(&crt5, 5, 2);
        world->print(w);

        CPPUNIT_ASSERT(r == w.str());
    }
    
    // --------------
    // Creature::next
    // --------------
    void test_next_food () {
        Creature crt(*world, food, SOUTH);
        world->put(&crt, 0, 0);
        CPPUNIT_ASSERT(SOUTH == crt._direction);
        CPPUNIT_ASSERT(0 == crt._programCounter);

        crt.next();
        CPPUNIT_ASSERT(EAST == crt._direction);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(NORTH == crt._direction);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(WEST == crt._direction);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(SOUTH == crt._direction);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }

    void test_next_hopper () {
        Creature crt(*world, hopper, SOUTH);
        world->put(&crt, 0, 0);
        CPPUNIT_ASSERT(SOUTH == crt._direction);
        CPPUNIT_ASSERT(0 == crt._programCounter);
        CPPUNIT_ASSERT(world->_grid[0][0] == &crt);

        crt.next();
        CPPUNIT_ASSERT(world->_grid[1][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[2][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[3][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[4][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[5][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[6][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[7][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[8][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[9][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(world->_grid[9][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }
    
    void test_next_trap () {
        Creature crt(*world, trap, SOUTH);
        Creature crt2(*world, food, WEST);
        Creature crt3(*world, trap, EAST);
        world->put(&crt, 1, 1);
        world->put(&crt2, 0, 1); // north
        world->put(&crt3, 1, 0); // west
        CPPUNIT_ASSERT(SOUTH == crt._direction);
        CPPUNIT_ASSERT(0 == crt._programCounter);
        CPPUNIT_ASSERT(WEST == crt2._direction);
        CPPUNIT_ASSERT(0 == crt2._programCounter);
        CPPUNIT_ASSERT(EAST == crt3._direction);
        CPPUNIT_ASSERT(0 == crt3._programCounter);
        crt3.next();
        CPPUNIT_ASSERT(2 == crt3._programCounter);
        CPPUNIT_ASSERT(NORTH == crt3._direction);
        crt2.next();
        CPPUNIT_ASSERT(1 == crt2._programCounter);
        CPPUNIT_ASSERT(SOUTH == crt2._direction);

        crt.next();
        CPPUNIT_ASSERT(EAST == crt._direction);
        CPPUNIT_ASSERT(2 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(NORTH == crt._direction);
        CPPUNIT_ASSERT(2 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(NORTH == crt._direction);
        CPPUNIT_ASSERT(4 == crt._programCounter);
        CPPUNIT_ASSERT(SOUTH == crt2._direction);
        CPPUNIT_ASSERT(0 == crt2._programCounter);
        CPPUNIT_ASSERT(crt2 == crt);
        crt.next();
        CPPUNIT_ASSERT(WEST == crt._direction);
        CPPUNIT_ASSERT(2 == crt._programCounter);
        crt.next();
        CPPUNIT_ASSERT(SOUTH == crt._direction);
        CPPUNIT_ASSERT(2 == crt._programCounter);
    }

    void test_next_rover () {
        // nope
    }
    // -------------
    // Creature::hop
    // -------------
    void test_hop_1 () {
        Creature  crt(*world, hopper, EAST);
        world->put( &crt,5,5);
        CPPUNIT_ASSERT(world->_grid[5][5] == &crt);
        CPPUNIT_ASSERT(0 == crt._programCounter);
        crt.hop();
        CPPUNIT_ASSERT(world->_grid[5][5] == 0);
        CPPUNIT_ASSERT(world->_grid[5][6] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }

    void test_hop_2 () {
        Creature  crt(*world, hopper, WEST);
        world->put( &crt,5,0);
        CPPUNIT_ASSERT(world->_grid[5][0] == &crt);
        CPPUNIT_ASSERT(0 == crt._programCounter);
        crt.hop();
        CPPUNIT_ASSERT(world->_grid[5][0] == &crt);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }

    void test_hop_3 () {
        Creature  crt(*world, rover, SOUTH);
        Creature crt2(*world,   trap,  WEST);
        world->put( &crt,0,0);
        world->put(&crt2,5,0);

        for (size_t i = 0; i < 5; ++i) {
            CPPUNIT_ASSERT(world->_grid[i][0] == &crt);
            CPPUNIT_ASSERT(crt._programCounter == i);
            crt.hop();
        }
        CPPUNIT_ASSERT(world->_grid[4][0] == &crt);
        CPPUNIT_ASSERT(world->_grid[5][0] == &crt2);
        crt.hop();
        CPPUNIT_ASSERT(world->_grid[4][0] == &crt);
        CPPUNIT_ASSERT(world->_grid[5][0] == &crt2);
        crt.hop();
        CPPUNIT_ASSERT(world->_grid[4][0] == &crt);
        CPPUNIT_ASSERT(world->_grid[5][0] == &crt2);
    }
    
    // ----------------
    // Creature::infect
    // ----------------
    void test_infect_1 () {
        Creature crt1(*world, rover, NORTH);
        world->put(&crt1,0,0);

        // wall
        CPPUNIT_ASSERT(0 == crt1._programCounter);
        crt1.infect();
        CPPUNIT_ASSERT(1 == crt1._programCounter);

        // wall
        crt1.left();
        CPPUNIT_ASSERT(2 == crt1._programCounter);
        crt1.infect();
        CPPUNIT_ASSERT(3 == crt1._programCounter);

        // empty
        crt1.left();
        CPPUNIT_ASSERT(4 == crt1._programCounter);
        crt1.infect();
        CPPUNIT_ASSERT(5 == crt1._programCounter);

        // empty
        crt1.left();
        CPPUNIT_ASSERT(6 == crt1._programCounter);
        crt1.infect();
        CPPUNIT_ASSERT(7 == crt1._programCounter);

    }

    void test_infect_2 () {
        Creature crt1(*world, rover, SOUTH);
        Creature crt2(*world, food,   WEST);
        world->put(&crt1,0,0);
        world->put(&crt2,1,0);
        CPPUNIT_ASSERT(0 == crt2._programCounter);

        CPPUNIT_ASSERT(0 == crt1._programCounter);
        crt1.infect();
        CPPUNIT_ASSERT(1 == crt1._programCounter);
        CPPUNIT_ASSERT(0 == crt2._programCounter);
        CPPUNIT_ASSERT(WEST == crt2._direction);
        CPPUNIT_ASSERT(crt2._species == rover);
    }

    void test_infect_3 () {
        Creature crt1(*world, rover, EAST);
        Creature crt3(*world, trap,  SOUTH);
        world->put(&crt1,0,0);
        world->put(&crt3,0,1);
        CPPUNIT_ASSERT(0 == crt3._programCounter);

        CPPUNIT_ASSERT(0 == crt1._programCounter);
        crt1.infect();
        CPPUNIT_ASSERT(1 == crt1._programCounter);
        CPPUNIT_ASSERT(0 == crt3._programCounter);
        CPPUNIT_ASSERT(SOUTH == crt3._direction);
        CPPUNIT_ASSERT(crt3._species == rover);
    }
    
    // ------------------
    // Creature::if_empty
    // ------------------
    void test_if_empty_1 () {
        Creature crt1(*world, rover, SOUTH);
        world->put(&crt1,2,2);
        CPPUNIT_ASSERT(0 == crt1._programCounter);

        crt1.if_empty(5);
        CPPUNIT_ASSERT(5 == crt1._programCounter);
    }

    void test_if_empty_2 () {
        Creature crt1(*world, rover, NORTH);
        world->put(&crt1,0,0);
        CPPUNIT_ASSERT(0 == crt1._programCounter);

        crt1.if_empty(5);
        CPPUNIT_ASSERT(1 == crt1._programCounter);
    }

    void test_if_empty_3 () {
        Creature crt1(*world, rover, SOUTH);
        Creature crt2(*world,  trap,  EAST);
        world->put(&crt1,2,2);
        world->put(&crt2,3,2);

        crt1.if_empty(5);
        CPPUNIT_ASSERT(1 == crt1._programCounter);
    }
    
    void test_if_empty_4 () {
        Creature crt1(*world, rover, SOUTH);
        Creature crt2(*world, rover,  EAST);
        world->put(&crt1,2,2);
        world->put(&crt2,3,2);

        crt1.if_empty(5);
        CPPUNIT_ASSERT(1 == crt1._programCounter);
    }
    
    // -----------------
    // Creature::if_wall
    // -----------------
    void test_if_wall_1 () {
        Creature crt(*world, trap, NORTH);
        world->put(&crt, 0, 0);
        crt.if_wall(3);
        CPPUNIT_ASSERT(3 == crt._programCounter);
    }

    void test_if_wall_2 () {
        Creature crt(*world, trap, WEST);
        world->put(&crt, 0, 0);
        crt.if_wall(3);
        CPPUNIT_ASSERT(3 == crt._programCounter);
    }

    void test_if_wall_3 () {
        Creature crt(*world, trap, EAST);
        world->put(&crt, 0, 0);
        crt.if_wall(3);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }
    
    void test_if_wall_4 () {
        Creature crt(*world, trap, SOUTH);
        world->put(&crt, 0, 0);
        crt.if_wall(3);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }
    
    void test_if_wall_5 () {
        Creature crt1(*world, trap, SOUTH);
        Creature crt2(*world, food, NORTH);
        world->put(&crt1, 0, 0);
        world->put(&crt2, 1, 0);
        crt1.if_wall(3);
        CPPUNIT_ASSERT(1 == crt1._programCounter);
    }
    
    // ------------------
    // Creature::if_enemy
    // ------------------
    void test_if_enemy_1 () {
        Creature crt(*world, trap, NORTH);
        world->put(&crt, 0, 0);
        crt.if_enemy(3);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }

    void test_if_enemy_2 () {
        Creature crt(*world, trap, WEST);
        world->put(&crt, 0, 0);
        crt.if_enemy(3);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }

    void test_if_enemy_3 () {
        Creature crt(*world, trap, EAST);
        world->put(&crt, 0, 0);
        crt.if_enemy(3);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }
    
    void test_if_enemy_4 () {
        Creature crt(*world, trap, SOUTH);
        world->put(&crt, 0, 0);
        crt.if_enemy(3);
        CPPUNIT_ASSERT(1 == crt._programCounter);
    }
    
    void test_if_enemy_5 () {
        Creature crt1(*world, trap, SOUTH);
        Creature crt2(*world, food, NORTH);
        world->put(&crt1, 0, 0);
        world->put(&crt2, 1, 0);
        crt1.if_enemy(3);
        CPPUNIT_ASSERT(3 == crt1._programCounter);
    }

    void test_if_enemy_6 () {
        Creature crt1(*world, trap, EAST);
        Creature crt2(*world, trap, WEST);
        world->put(&crt1, 0, 0);
        world->put(&crt2, 0, 1);
        crt1.if_enemy(3);
        CPPUNIT_ASSERT(1 == crt1._programCounter);
    }
        
    // -----------
    // Darwin::add
    // -----------
    void test_add_1 () {
        size_t r = 0;
        size_t c = 0;
        direction_t d = NORTH;
        Creature crt(darwin->_world, hopper, d);
        darwin->add(hopper, d, r, c);
        CPPUNIT_ASSERT(*darwin->_world._grid[r][c] == crt);
        CPPUNIT_ASSERT(darwin->_world._grid[r][c]->_direction == d);
    }

    void test_add_2 () {
        size_t r = 9;
        size_t c = 0;
        direction_t d = SOUTH;
        Creature crt(darwin->_world, trap, d);
        darwin->add(trap, d, r, c);
        CPPUNIT_ASSERT(*darwin->_world._grid[r][c] == crt);
        CPPUNIT_ASSERT(darwin->_world._grid[r][c]->_direction == d);
    }

    void test_add_3 () {
        size_t r = 0;
        size_t c = 9;
        direction_t d = EAST;
        Creature crt(darwin->_world, rover, d);
        darwin->add(rover, d, r, c);
        CPPUNIT_ASSERT(*darwin->_world._grid[r][c] == crt);
        CPPUNIT_ASSERT(darwin->_world._grid[r][c]->_direction == d);
    }

    void test_add_4 () {
        size_t r = 9;
        size_t c = 9;
        direction_t d = WEST;
        Creature crt(darwin->_world, food, d);
        darwin->add(food, d, r, c);
        CPPUNIT_ASSERT(*darwin->_world._grid[r][c] == crt);
        CPPUNIT_ASSERT(darwin->_world._grid[r][c]->_direction == d);
    }
    
    // ----------- 
    // Darwin::run
    // -----------
    void test_run_1 () {
        Creature crt(darwin->_world, hopper, SOUTH);
        darwin->add(hopper, SOUTH, 0, 0);
    }
     
    // ------------- 
    // Darwin::print
    // -------------
    void test_darwin_print () {
        const std::string r("Turn = 0.\n  012\n0 ...\n1 ...\n");
        std::ostringstream w;
        Darwin d(2,3,w);
        d.print();
        CPPUNIT_ASSERT(r == w.str());
    }
     
    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_get_direction_1);
    CPPUNIT_TEST(test_get_direction_2);
    CPPUNIT_TEST(test_get_direction_3);
    CPPUNIT_TEST(test_get_direction_4);

    CPPUNIT_TEST(test_coordinate_operator_l_1);
    CPPUNIT_TEST(test_coordinate_operator_l_2);
    CPPUNIT_TEST(test_coordinate_operator_l_3);
    CPPUNIT_TEST(test_coordinate_operator_l_4);
    CPPUNIT_TEST(test_coordinate_operator_l_5);

    CPPUNIT_TEST(test_coordinate_operator_g_1);
    CPPUNIT_TEST(test_coordinate_operator_g_2);
    CPPUNIT_TEST(test_coordinate_operator_g_3);
    CPPUNIT_TEST(test_coordinate_operator_g_4);
    CPPUNIT_TEST(test_coordinate_operator_g_5);

    CPPUNIT_TEST(test_coordinate_operator_le_1);
    CPPUNIT_TEST(test_coordinate_operator_le_2);
    CPPUNIT_TEST(test_coordinate_operator_le_3);
    CPPUNIT_TEST(test_coordinate_operator_le_4);
    CPPUNIT_TEST(test_coordinate_operator_le_5);

    CPPUNIT_TEST(test_coordinate_operator_ge_1);
    CPPUNIT_TEST(test_coordinate_operator_ge_2);
    CPPUNIT_TEST(test_coordinate_operator_ge_3);
    CPPUNIT_TEST(test_coordinate_operator_ge_4);
    CPPUNIT_TEST(test_coordinate_operator_ge_5);

    CPPUNIT_TEST(test_put_1);
    CPPUNIT_TEST(test_put_2);
    CPPUNIT_TEST(test_put_3);
    CPPUNIT_TEST(test_put_4);
    CPPUNIT_TEST(test_except_put_1);
    CPPUNIT_TEST(test_except_put_2);
    CPPUNIT_TEST(test_except_put_3);
    CPPUNIT_TEST(test_except_put_4);
    CPPUNIT_TEST(test_except_put_5);
    CPPUNIT_TEST(test_except_put_6);
    CPPUNIT_TEST(test_except_put_7);
    CPPUNIT_TEST(test_except_put_8);

    CPPUNIT_TEST(test_get_1);
    CPPUNIT_TEST(test_get_2);
    CPPUNIT_TEST(test_get_3);
    CPPUNIT_TEST(test_get_4);
    
    CPPUNIT_TEST(test_at_wall_1);
    CPPUNIT_TEST(test_at_wall_2);
    CPPUNIT_TEST(test_at_wall_3);
    CPPUNIT_TEST(test_at_wall_4);
    
    CPPUNIT_TEST(test_move_adjacent_1);
    CPPUNIT_TEST(test_move_adjacent_2);
    CPPUNIT_TEST(test_move_adjacent_3);
    CPPUNIT_TEST(test_move_adjacent_4);
    CPPUNIT_TEST(test_move_adjacent_5);
    CPPUNIT_TEST(test_move_adjacent_6);
    
    CPPUNIT_TEST(test_world_print_1);
    CPPUNIT_TEST(test_world_print_2);
    CPPUNIT_TEST(test_world_print_3);
    CPPUNIT_TEST(test_world_print_4);
    CPPUNIT_TEST(test_world_print_5);

    CPPUNIT_TEST(test_next_food);
    CPPUNIT_TEST(test_next_hopper);
    CPPUNIT_TEST(test_next_trap);

    CPPUNIT_TEST(test_hop_1);
    CPPUNIT_TEST(test_hop_2);
    CPPUNIT_TEST(test_hop_3);

    CPPUNIT_TEST(test_infect_1);
    CPPUNIT_TEST(test_infect_2);
    CPPUNIT_TEST(test_infect_3);

    CPPUNIT_TEST(test_if_empty_1);
    CPPUNIT_TEST(test_if_empty_2);
    CPPUNIT_TEST(test_if_empty_3);
    CPPUNIT_TEST(test_if_empty_4);

    CPPUNIT_TEST(test_if_wall_1);
    CPPUNIT_TEST(test_if_wall_2);
    CPPUNIT_TEST(test_if_wall_3);
    CPPUNIT_TEST(test_if_wall_4);
    CPPUNIT_TEST(test_if_wall_5);
    
    CPPUNIT_TEST(test_if_enemy_1);
    CPPUNIT_TEST(test_if_enemy_2);
    CPPUNIT_TEST(test_if_enemy_3);
    CPPUNIT_TEST(test_if_enemy_4);
    CPPUNIT_TEST(test_if_enemy_5);
    CPPUNIT_TEST(test_if_enemy_6);

    CPPUNIT_TEST(test_add_1);
    CPPUNIT_TEST(test_add_2);
    CPPUNIT_TEST(test_add_3);
    CPPUNIT_TEST(test_add_4);

    CPPUNIT_TEST(test_darwin_print);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    cout << "\nTestWorld::suite()" << endl;
    CppUnit::TextTestRunner tworld;
    tworld.addTest(TestWorld::suite());
    tworld.run();

    cout << "\nTestSpecies::suite()" << endl;
    CppUnit::TextTestRunner tspecies;
    tspecies.addTest(TestSpecies::suite());
    tspecies.run();

    cout << "\nTestCreature::suite()" << endl;
    CppUnit::TextTestRunner tcreature;
    tcreature.addTest(TestCreature::suite());
    tcreature.run();

    cout << "\nTestDarwin::suite()" << endl;
	CppUnit::TextTestRunner tdarwin;
    tdarwin.addTest(TestDarwin::suite());
    tdarwin.run();

    cout << "Done." << endl;
    return 0;}
