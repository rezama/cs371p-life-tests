// -----------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
// -----------------------------

/*
To run the program:
    % g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
    % valgrind TestDarwin.c++.app > TestDarwin.out

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

#define private public
#define protected public
#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

// ----
// main
// ----


struct TestDarwin : CppUnit::TestFixture {
    void test_instruction_1 () {
	Instruction testInstruction(Hop);
	testInstruction._address = 12;
        CPPUNIT_ASSERT(testInstruction.getOp() == 0);
        CPPUNIT_ASSERT(testInstruction.getAddress() == 12);
    }

    void test_instruction_2 () {
	Instruction testInstruction(IfEmpty, 21);
        CPPUNIT_ASSERT(testInstruction.getOp() == IfEmpty);
        CPPUNIT_ASSERT(testInstruction.getAddress() == 21);
    }
    void test_instruction_3 () {
	Instruction testInstruction(Go, 0);
        CPPUNIT_ASSERT(testInstruction.getOp() == Go);
        CPPUNIT_ASSERT(testInstruction.getAddress() == 0);
    }

    void test_species_1(){
	Species test(FOOD);
	test.addInstruction(IfEmpty,2);
	test.addInstruction(Hop);
	test.addInstruction(Left);
	test.addInstruction(Go, 0);
	CPPUNIT_ASSERT(test.getName() == "food");
	int pc = 0;
	int action = test.getNextInstruction(pc, false, false, false);
	CPPUNIT_ASSERT(action == Hop);
	
    }

    void test_species_2(){
	Species test(HOPPER);
	test.addInstruction(IfEmpty,2);
	test.addInstruction(Hop);
	test.addInstruction(Left);
	test.addInstruction(Go, 0);
	CPPUNIT_ASSERT(test.getName() == "hopper");
	int pc = 0;
	int action = test.getNextInstruction(pc, false, false, true);
	CPPUNIT_ASSERT(action == Left);
	
    }

    void test_species_3(){
	Species test(FOOD);
	test.addInstruction(IfEmpty,2);
	test.addInstruction(Hop);
	test.addInstruction(Left);
	test.addInstruction(Go, 0);
	CPPUNIT_ASSERT(test.getName() == "food");
	int pc = 54;
	int action = test.getNextInstruction(pc, false, false, false);
	CPPUNIT_ASSERT(action == -1);
	
    }

    void test_creature_1(){
	Creature myCreature = Creature();
	myCreature._programCounter = 5;
	CPPUNIT_ASSERT(myCreature.getDirection() == 0);
	CPPUNIT_ASSERT(myCreature.getRepresentation() == '.');
	CPPUNIT_ASSERT(!myCreature.isEnemy(&myCreature));
	int row = 0;
	int col = 0;
	Creature myEmpty = Creature();
	myCreature.act(row, col, &myEmpty, 2, 2);
	myCreature.endTurn();
	CPPUNIT_ASSERT(myCreature._hasMoved = true);
	Species mySpecies(FOOD);
	myCreature.changeSpecies(&mySpecies);
	CPPUNIT_ASSERT(myCreature._programCounter == 0);
	myCreature.endTurn();
	CPPUNIT_ASSERT(myCreature._hasMoved == false);
	
    }

    void test_creature_2(){
	Species mySpecies(BEST);
	mySpecies.addInstruction(IfEmpty,2);
	mySpecies.addInstruction(Left);
	mySpecies.addInstruction(Hop);
	mySpecies.addInstruction(Go, 0);
	Creature myCreature(&mySpecies, 0,0,3);
	CPPUNIT_ASSERT(myCreature.getDirection() == SOUTH);
	CPPUNIT_ASSERT(myCreature.getRepresentation() == 'b');
	int row = 0;
	int col = 0;
	Creature myEmpty = Creature();
	myCreature.act(row, col, &myEmpty, 5, 5);
	CPPUNIT_ASSERT(myCreature._programCounter = 3);
	CPPUNIT_ASSERT(row == 1);
	CPPUNIT_ASSERT(col == 0);
	myCreature.changeSpecies(NULL);
	CPPUNIT_ASSERT(myCreature._programCounter == 0);
	CPPUNIT_ASSERT(myCreature._mySpecies == NULL);
	myCreature.endTurn();
	CPPUNIT_ASSERT(myCreature._hasMoved);		
    }

    void test_creature_3(){
	Species mySpecies(FOOD);
	mySpecies.addInstruction(Left);
	mySpecies.addInstruction(Go, 0);
	Creature myCreature(&mySpecies, 0, 0, 2);
	CPPUNIT_ASSERT(myCreature.getDirection() == EAST);
	CPPUNIT_ASSERT(myCreature.getRepresentation() == 'f');
	int row = 0;
	int col = 0;
	Creature myEmpty = Creature();
	myCreature.act(row, col, &myEmpty, 5,5);
	CPPUNIT_ASSERT(myCreature.getDirection() == NORTH);
	myCreature.changeSpecies(NULL);	
	CPPUNIT_ASSERT(myCreature._programCounter == 0);
	CPPUNIT_ASSERT(myCreature._mySpecies == NULL);
	myCreature.endTurn();
	CPPUNIT_ASSERT(myCreature._hasMoved);		
    }

    void test_board_1(){
	Species mySpecies(FOOD);
	mySpecies.addInstruction(Left);
	mySpecies.addInstruction(Go, 0);
	Board myBoard(1,1);
	myBoard.addCreature(&mySpecies, 0,0,2);
	myBoard.runTurn();
	CPPUNIT_ASSERT(myBoard._board[0][0].getDirection() == NORTH);	
    }

    void test_board_2(){
	Species mySpecies(HOPPER);
	mySpecies.addInstruction(Hop);
	mySpecies.addInstruction(Go, 0);
	Board myBoard(2,2);
	myBoard.addCreature(&mySpecies, 0,0,2);
	myBoard.runTurn();
	CPPUNIT_ASSERT(myBoard._board[0][1].getRepresentation() == 'h');	
    }

    void test_board_3(){
	Species mySpecies(HOPPER);
	mySpecies.addInstruction(Hop);
	mySpecies.addInstruction(Go, 0);
	Board myBoard(2,2);
	myBoard.addCreature(&mySpecies, 0,0,3);
	myBoard.runTurn();
	CPPUNIT_ASSERT(myBoard._board[1][0].getRepresentation() == 'h');	
    }

    void test_darwin_1(){
	Darwin myDarwin(1,5);	
	Species mySpecies(HOPPER);
	mySpecies.addInstruction(Hop);
	mySpecies.addInstruction(Go, 0);
	myDarwin.addCreature(mySpecies, 0,0,0);
	CPPUNIT_ASSERT(myDarwin._board._board[0][0].getDirection() == WEST);
    }
	
    void test_darwin_2(){
	Darwin myDarwin(0,0);	
	Species mySpecies(HOPPER);
	mySpecies.addInstruction(Hop);
	mySpecies.addInstruction(Go, 0);
	CPPUNIT_ASSERT(!myDarwin.addCreature(mySpecies, 0,0,0));
    }
    void test_darwin_3(){
	Darwin myDarwin(1,5);	
	Species mySpecies(HOPPER);
	mySpecies.addInstruction(Hop);
	mySpecies.addInstruction(Go, 0);
	CPPUNIT_ASSERT(!myDarwin.addCreature(mySpecies, 5,5,0));
    }
    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_instruction_1);
    CPPUNIT_TEST(test_instruction_2);
    CPPUNIT_TEST(test_instruction_3);

    CPPUNIT_TEST(test_species_1);
    CPPUNIT_TEST(test_species_2);
    CPPUNIT_TEST(test_species_3);


    CPPUNIT_TEST(test_creature_1);
    CPPUNIT_TEST(test_creature_2);
    CPPUNIT_TEST(test_creature_3);

	
    CPPUNIT_TEST(test_board_1);
    CPPUNIT_TEST(test_board_2);
    CPPUNIT_TEST(test_board_3);

    CPPUNIT_TEST(test_darwin_1); 
    CPPUNIT_TEST(test_darwin_2); 
    CPPUNIT_TEST(test_darwin_3); 
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
