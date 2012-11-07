// ------------------------------
// projects/Darwin/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind ./TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include "Darwin.h"

#define CONTROL 0
#define ACTION 1

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {
    // --------
    // Instruction tests
    // --------

    void test_instruction_1 () {
        Instruction x("hop");
        CPPUNIT_ASSERT(x.type() == ACTION);
    }

    void test_instruction_2 () {
        Instruction x("go", 2);
        CPPUNIT_ASSERT(x.type() == CONTROL);
    }

    void test_instruction_3 () {
        Instruction x("if_wall", 5);
        CPPUNIT_ASSERT(x.type() == CONTROL);
        CPPUNIT_ASSERT(x.instruction() == "if_wall");
        CPPUNIT_ASSERT(x.line() == 5);
    }

    // --------
    // Species tests
    // --------

    void test_species_1 () {
        Species x("x");
        x.add(Instruction("go",1));
        CPPUNIT_ASSERT(x.id() == 1);
        CPPUNIT_ASSERT(x.getInstruction(0).instruction() == "go");
        CPPUNIT_ASSERT(x.getInstruction(0).line() == 1);
        CPPUNIT_ASSERT(x.getInstruction(0).type() == CONTROL);
    }

    void test_species_2 () {
        Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("go",0));
        CPPUNIT_ASSERT(x.id() == 2);
        CPPUNIT_ASSERT(x.getInstruction(0).instruction() == "go");
        CPPUNIT_ASSERT(x.getInstruction(0).line() == 1);
        CPPUNIT_ASSERT(x.getInstruction(0).type() == CONTROL);
        CPPUNIT_ASSERT(x.getInstruction(1).instruction() == "go");
        CPPUNIT_ASSERT(x.getInstruction(1).line() == 0);
        CPPUNIT_ASSERT(x.getInstruction(1).type() == CONTROL);
    }

    void test_species_3 () {
        Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("hop"));
        CPPUNIT_ASSERT(x.id() == 3);
        CPPUNIT_ASSERT(x.getInstruction(0).instruction() == "go");
        CPPUNIT_ASSERT(x.getInstruction(0).line() == 1);
        CPPUNIT_ASSERT(x.getInstruction(0).type() == CONTROL);
        CPPUNIT_ASSERT(x.getInstruction(1).instruction() == "hop");
        CPPUNIT_ASSERT(x.getInstruction(1).type() == ACTION);
    }

    // --------
    // Creature tests
    // --------

    void test_creature_1 () {
    	Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("go",0));
        Creature y(x, 0);
        CPPUNIT_ASSERT(x.id() == y.species_id());
        Instruction n = y.next();
        CPPUNIT_ASSERT(n.instruction() == "go");
        CPPUNIT_ASSERT(n.line() == 1);
        y.increment();
        n = y.next();
        CPPUNIT_ASSERT(n.instruction() == "go");
        CPPUNIT_ASSERT(n.line() == 0);
        try {
        	y.increment();
        	CPPUNIT_ASSERT(false);
        }
        catch(exception& e) {
        	CPPUNIT_ASSERT(true);
        }

        Species z("z");
        z.add(Instruction("hop"));
        y.setSpecies(z);
        CPPUNIT_ASSERT(y.next().instruction() == "hop");
        CPPUNIT_ASSERT(z.id() == y.species_id());
    }

    void test_jump_1 () {
    	Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("go",0));
        Creature y(x, 0);
        try {
        	y.jump(3);
        	CPPUNIT_ASSERT(false);
        }
        catch(exception& e) {
        	CPPUNIT_ASSERT(true);
        }
    }

    void test_jump_2 () {
    	Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("go",0));
        Creature y(x, 0);
        y.jump(1);
        Instruction n = y.next();
        CPPUNIT_ASSERT(n.instruction() == "go");
        CPPUNIT_ASSERT(n.line() == 0);
        y.jump(0);
        n = y.next();
        CPPUNIT_ASSERT(n.instruction() == "go");
        CPPUNIT_ASSERT(n.line() == 1);
    }

    void test_jump_3 () {
    	Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("go",0));
        Creature y(x, 0);
        try {
        	y.jump(-1);
        	CPPUNIT_ASSERT(false);
        }
        catch(exception& e) {
        	CPPUNIT_ASSERT(true);
        }
    }

    void test_creature_3 () {
    	Species x("x");
        x.add(Instruction("go",1));
        x.add(Instruction("go",0));
        Creature y(x, 0);
        Instruction n = y.next();
        CPPUNIT_ASSERT(n.instruction() == "go");
        CPPUNIT_ASSERT(n.line() == 1);
        y.increment();
        n = y.next();
        CPPUNIT_ASSERT(n.instruction() == "go");
        CPPUNIT_ASSERT(n.line() == 0);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_instruction_1);
    CPPUNIT_TEST(test_instruction_2);
    CPPUNIT_TEST(test_instruction_3);
    CPPUNIT_TEST(test_species_1);
    CPPUNIT_TEST(test_species_2);
    CPPUNIT_TEST(test_species_3);
    CPPUNIT_TEST(test_creature_1);
    CPPUNIT_TEST(test_jump_1);
    CPPUNIT_TEST(test_jump_2);
    CPPUNIT_TEST(test_jump_3);
    CPPUNIT_TEST_SUITE_END();};

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
