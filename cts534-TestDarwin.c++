/*
To test the program:
    % ls /usr/include/cppunit/
    ...
    HelperMacros.h
    ...
    % locate libcppunit.a
    /usr/lib/libcppunit.a
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.c++.app
    % valgrind TestDarwin.c++.app >& TestDarwin.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <cstdlib>   // rand, srand

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public

#include "Darwin.h"

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {

	// ----
    // line
    // ----
	
	void line_one () {
		vector<string> program(6);
		program[0] = "0: if_wall 3";
		program[1] = "1: if_enemy 4";
		program[2] = "2: left";
		program[3] = "3: go 0";
		program[4] = "4: infect";
		program[5] = "5: go 0";
		Species species(program);
		string realOutput = species.line(2);
		string desiredOutput = "2: left";
		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
	void line_two () {
		vector<string> program(6);
		program[0] = "0: if_wall 3";
		program[1] = "1: if_enemy 4";
		program[2] = "2: left";
		program[3] = "3: go 0";
		program[4] = "4: infect";
		program[5] = "5: go 0";
		Species species(program);
		string realOutput = species.line(5);
		string desiredOutput = "5: go 0";
		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
	void line_three () {
		vector<string> program(6);
		program[0] = "0: if_wall 3";
		program[1] = "1: if_enemy 4";
		program[2] = "2: left";
		program[3] = "3: go 0";
		program[4] = "4: infect";
		program[5] = "5: go 0";
		Species species(program);
		string realOutput = species.line(0);
		string desiredOutput = "0: if_wall 3";
		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
    // ----
    // evalControlLine
    // ----
	
    void evalControlLine_one () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, NORTH);
		vector<string> currentLine(3);
		currentLine[0] = "1:";
		currentLine[1] = "if_empty";
		currentLine[2] = "7";
		creature.evalControlLine(currentLine, EMPTY);	
        CPPUNIT_ASSERT(creature._programCounter == 7);
		CPPUNIT_ASSERT(creature._myDirection == NORTH);	
	}
	
	void evalControlLine_two () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, WEST);
		vector<string> currentLine(3);
		currentLine[0] = "23:";
		currentLine[1] = "if_wall";
		currentLine[2] = "9";
		creature.evalControlLine(currentLine, WALL);	
        CPPUNIT_ASSERT(creature._programCounter == 9);
		CPPUNIT_ASSERT(creature._myDirection == WEST);	
	}
	
	void evalControlLine_three () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, SOUTH);
		vector<string> currentLine(3);
		currentLine[0] = "89:";
		currentLine[1] = "if_enemy";
		currentLine[2] = "19";
		creature.evalControlLine(currentLine, ENEMY);	
        CPPUNIT_ASSERT(creature._programCounter == 19);
		CPPUNIT_ASSERT(creature._myDirection == SOUTH);			
	}
	
	void evalControlLine_four () {
		srand(0);
		vector<string> program(0);
		Species species(program);
		Creature creature(species, SOUTH);
		vector<string> currentLine(3);
		currentLine[0] = "12:";
		currentLine[1] = "if_random";
		currentLine[2] = "19";
		creature.evalControlLine(currentLine, ENEMY);	
        CPPUNIT_ASSERT(creature._programCounter == 19);
		CPPUNIT_ASSERT(creature._myDirection == SOUTH);	
	}
	
	void evalControlLine_five () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, SOUTH);
		creature._programCounter = 89;
		vector<string> currentLine(3);
		currentLine[0] = "89:";
		currentLine[1] = "if_enemy";
		currentLine[2] = "19";
		creature.evalControlLine(currentLine, EMPTY);	
        CPPUNIT_ASSERT(creature._programCounter == 90);
		CPPUNIT_ASSERT(creature._myDirection == SOUTH);			
	}
	
    // ----
    // splitCurrentLine
    // ----

    void splitCurrentLine_one () {
		string input = "Don't count on me";
		vector<string> desiredOutput (4);
		desiredOutput[0] = "Don't";
		desiredOutput[1] = "count";
		desiredOutput[2] = "on";
		desiredOutput[3] = "me";
		vector<string> realOutput = Creature::splitCurrentLine(input);
        CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
	
    void splitCurrentLine_two () {
		string input = "Dream";
		vector<string> desiredOutput (1);
		desiredOutput[0] = "Dream";
		vector<string> realOutput = Creature::splitCurrentLine(input);
        CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
	
    void splitCurrentLine_three () {
		string input = "Double  space";
		vector<string> desiredOutput (2);
		desiredOutput[0] = "Double";
		desiredOutput[1] = "space";
		vector<string> realOutput = Creature::splitCurrentLine(input);
        CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
	// ----
    // processTurn
    // ----

    void processTurn_one () {
		vector<string> program(3);
		program[0] = "0: if_enemy 2";
		program[1] = "1: left";
		program[2] = "2: go 0";
		Species species(program);
		Creature creature(species, NORTH);
		string realOutput = creature.processTurn(WALL);
		string desiredOutput = "left";
		CPPUNIT_ASSERT(desiredOutput == realOutput);
		CPPUNIT_ASSERT(creature._programCounter == 2);
	}
	
	void processTurn_two () {
		vector<string> program(6);
		program[0] = "0: if_wall 3";
		program[1] = "1: if_enemy 4";
		program[2] = "2: left";
		program[3] = "3: go 0";
		program[4] = "4: infect";
		program[5] = "5: go 0";
		Species species(program);
		Creature creature(species, NORTH);
		string realOutput = creature.processTurn(ENEMY);
		string desiredOutput = "infect";
		CPPUNIT_ASSERT(desiredOutput == realOutput);
		CPPUNIT_ASSERT(creature._programCounter == 5);
	}
	
	void processTurn_three () {
		vector<string> program(6);
		program[0] = "0: hop";
		program[1] = "1: go 0";

		Species species(program);
		Creature creature(species, NORTH);
		creature._programCounter = 1;
		string realOutput = creature.processTurn(ENEMY);
		string desiredOutput = "hop";
		CPPUNIT_ASSERT(desiredOutput == realOutput);
		CPPUNIT_ASSERT(creature._programCounter == 1);
	}
	
	// ----
    // turnLeft
    // ----

    void turnLeft_one () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, SOUTH);
		creature._programCounter = 89;
		creature.turnLeft();
		CPPUNIT_ASSERT(creature._myDirection == EAST);
	}
	
	void turnLeft_two () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, NORTH);
		creature._programCounter = 89;
		creature.turnLeft();
		creature.turnLeft();
		CPPUNIT_ASSERT(creature._myDirection == SOUTH);
	}
	
	void turnLeft_three () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, WEST);
		creature._programCounter = 89;
		creature.turnLeft();
		creature.turnLeft();
		creature.turnLeft();
		creature.turnLeft();
		CPPUNIT_ASSERT(creature._myDirection == WEST);
	}
	
	// ----
    // turnRight
    // ----

    void turnRight_one () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, SOUTH);
		creature._programCounter = 89;
		creature.turnRight();
		CPPUNIT_ASSERT(creature._myDirection == WEST);
	}
	
	void turnRight_two () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, NORTH);
		creature._programCounter = 89;
		creature.turnRight();
		creature.turnRight();
		CPPUNIT_ASSERT(creature._myDirection == SOUTH);
	}
	
	void turnRight_three () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, WEST);
		creature._programCounter = 89;
		creature.turnRight();
		creature.turnRight();
		creature.turnRight();
		creature.turnRight();
		CPPUNIT_ASSERT(creature._myDirection == WEST);
	}	
	
	// ----
    // infect
    // ----

    void infect_one () {
		vector<string> programA(13);
		vector<string> programB(50);
		Species speciesA(programA);
		Species speciesB(programA);
		Creature creatureA(speciesA, NORTH);
		creatureA._programCounter = 93;
		Creature creatureB(speciesB, SOUTH);
		creatureB._programCounter = 89;
		creatureA.infect(creatureB);
		
		CPPUNIT_ASSERT(creatureB._myDirection == SOUTH);
		CPPUNIT_ASSERT(creatureB._programCounter == 0);
		CPPUNIT_ASSERT(creatureB._mySpecies._myProgram == speciesA._myProgram);
	}
	
	void infect_two () {
		vector<string> programA(13);
		vector<string> programB(50);
		Species speciesA(programA);
		Species speciesB(programA);
		Creature creatureA(speciesA, NORTH);
		creatureA._programCounter = 93;
		Creature creatureB(speciesB, SOUTH);
		creatureB._programCounter = 89;
		creatureB.infect(creatureA);
		
		CPPUNIT_ASSERT(creatureA._myDirection == NORTH);
		CPPUNIT_ASSERT(creatureA._programCounter == 0);
		CPPUNIT_ASSERT(creatureA._mySpecies._myProgram == speciesB._myProgram);
	}
	
	void infect_three () {
		vector<string> programA(13);
		vector<string> programB(50);
		vector<string> programC(32);
		Species speciesA(programA);
		Species speciesB(programB);
		Species speciesC(programC);
		Creature creatureA(speciesA, NORTH);
		creatureA._programCounter = 93;	
		Creature creatureB(speciesB, SOUTH);
		creatureB._programCounter = 89;
		Creature creatureC(speciesC, SOUTH);
		creatureC._programCounter = 1;
		
		creatureA.infect(creatureC);
		creatureB.infect(creatureC);
		
		
		CPPUNIT_ASSERT(creatureC._myDirection == SOUTH);
		CPPUNIT_ASSERT(creatureC._programCounter == 0);
		CPPUNIT_ASSERT(creatureC._mySpecies._myProgram == speciesB._myProgram);
		CPPUNIT_ASSERT(creatureB._myDirection == SOUTH);
		CPPUNIT_ASSERT(creatureB._programCounter == 89);
		CPPUNIT_ASSERT(creatureB._mySpecies._myProgram == speciesB._myProgram);
		CPPUNIT_ASSERT(creatureA._myDirection == NORTH);
		CPPUNIT_ASSERT(creatureA._programCounter == 93);
		CPPUNIT_ASSERT(creatureA._mySpecies._myProgram == speciesA._myProgram);
	}	
	
	// ----
    // getDirection
    // ----

    void getDirection_one () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, SOUTH);
		Direction currDir = creature.getDirection();
		CPPUNIT_ASSERT(currDir == SOUTH);
	}
	
	void getDirection_two () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, WEST);
		Direction currDir = creature.getDirection();
		CPPUNIT_ASSERT(currDir == WEST);
	}
	
	void getDirection_three () {
		vector<string> program(0);
		Species species(program);
		Creature creature(species, NORTH);
		Direction currDir = creature.getDirection();
		currDir = creature.getDirection();
		CPPUNIT_ASSERT(currDir == NORTH);
	}
	
	// ----
    // populateCreatureQueue
    // ----

    void populateCreatureQueue_one () {
	
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		
		controller.populateCreatureQueue();
		
		CPPUNIT_ASSERT(controller._creatureTurnQueue.size() == 0);
	}
	
    void populateCreatureQueue_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		Creature creature(noSpecies, NORTH);
		CreatureContainer creatureContainer = { creature, 0, 0, 'f' };		
		
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = creatureContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		
		controller.populateCreatureQueue();
		
		CPPUNIT_ASSERT(controller._creatureTurnQueue.size() == 1);
		CPPUNIT_ASSERT((*controller._creatureTurnQueue.front()).mySymbol == 'f');
		
	}

    void populateCreatureQueue_three () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		Creature creatureA(noSpecies, NORTH);
		CreatureContainer creatureContainerA = { creatureA, 0, 0, 'f' };
		
		Creature creatureB(noSpecies, NORTH);
		CreatureContainer creatureContainerB = { creatureB, 0, 0, 'h' };		
		
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = creatureContainerA;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = creatureContainerB;
		
		controller.populateCreatureQueue();
		
		CPPUNIT_ASSERT(controller._creatureTurnQueue.size() == 2);
		CPPUNIT_ASSERT((*controller._creatureTurnQueue.front()).mySymbol == 'f');
		CPPUNIT_ASSERT((*controller._creatureTurnQueue.back()).mySymbol == 'h');
	}
	
	// ----
    // processAction
    // ----	
	
    void processAction_one () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: hop";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
		Creature creature(hopper, SOUTH);
		CreatureContainer creatureContainer = { creature, 0, 1, 'h' };		
		
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = creatureContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		
		controller.processAction(controller._gameBoard[0][1], "hop");
		
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == 'h');
	}
	
    void processAction_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: left";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
		Creature creature(hopper, SOUTH);
		CreatureContainer creatureContainer = { creature, 0, 1, 'h' };		
		
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = creatureContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		
		controller.processAction(controller._gameBoard[0][1], "left");
		
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == 'h');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].myCreature._myDirection == EAST);
	}
	
    void processAction_three () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: right";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
		Creature creature(hopper, SOUTH);
		CreatureContainer creatureContainer = { creature, 0, 1, 'h' };		
		
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = creatureContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		
		controller.processAction(controller._gameBoard[0][1], "right");
		
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == 'h');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].myCreature._myDirection == WEST);
	}	
	
    void processAction_four () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> infectProgram(2);
		infectProgram[0] = "0: infect";
		infectProgram[1] = "1: go 0";
		Species infector(infectProgram);
		Creature creatureA(infector, SOUTH);
		CreatureContainer creatureContainerA = { creatureA, 0, 0, 'i' };
		
		vector<string> foodProgram(2);
		foodProgram[0] = "0: left";
		foodProgram[1] = "1: go 0";
		Species food(foodProgram);
		Creature creatureB(food, SOUTH);
		CreatureContainer creatureContainerB = { creatureB, 1, 0, 'f' };	
		creatureContainerB.myCreature._programCounter = 1;
		
		Controller controller(2, 2);
		
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[1][0] = creatureContainerB;
		controller._gameBoard[1][1] = emptyContainer;
		
		controller.processAction(controller._gameBoard[0][0], "infect");
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == 'i');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == 'i');
		CPPUNIT_ASSERT(controller._gameBoard[0][0].myCreature._myDirection == SOUTH);
		CPPUNIT_ASSERT(controller._gameBoard[1][0].myCreature._programCounter == 0);
	}	
	
	// ----
    // hopCreature
    // ----	
	
	void hopCreature_one () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: hop";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
		
		Creature hopperA(hopper, SOUTH);
		CreatureContainer creatureContainerA = { hopperA, 0, 0, '1' };
		
		Creature hopperB(hopper, NORTH);
		CreatureContainer creatureContainerB = { hopperB, 1, 2, '2' };	
		creatureContainerB.myCreature._programCounter = 1;
		
		Controller controller(3, 3);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[1][2] = creatureContainerB;
		
		controller.hopCreature(controller._gameBoard[0][0]);
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == '1');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][2].mySymbol == '2');
		CPPUNIT_ASSERT(controller._gameBoard[2][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][2].mySymbol == '.');
		
		CPPUNIT_ASSERT(controller._gameBoard[1][0].myCreature._myDirection == SOUTH);
		CPPUNIT_ASSERT(controller._gameBoard[1][2].myCreature._myDirection == NORTH);
	}
	
    void hopCreature_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: hop";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
		
		Creature hopperA(hopper, SOUTH);
		CreatureContainer creatureContainerA = { hopperA, 0, 0, '1' };
		
		Creature hopperB(hopper, NORTH);
		CreatureContainer creatureContainerB = { hopperB, 1, 2, '2' };	
		creatureContainerB.myCreature._programCounter = 1;
		
		Controller controller(3, 3);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[1][2] = creatureContainerB;
		
		controller.hopCreature(controller._gameBoard[1][2]);

		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == '1');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][2].mySymbol == '2');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][2].mySymbol == '.');
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].myCreature._myDirection == SOUTH);
		CPPUNIT_ASSERT(controller._gameBoard[0][2].myCreature._myDirection == NORTH);
	}
	
    void hopCreature_three () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };
		
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: hop";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
		
		Creature hopperA(hopper, EAST);
		CreatureContainer creatureContainerA = { hopperA, 0, 0, '1' };
		
		Creature hopperB(hopper, WEST);
		CreatureContainer creatureContainerB = { hopperB, 0, 2, '2' };	
		creatureContainerB.myCreature._programCounter = 0;
		
		Controller controller(3, 3);
		
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[0][2] = creatureContainerB;

		controller.hopCreature(controller._gameBoard[0][0]);
		controller.hopCreature(controller._gameBoard[0][2]);
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '1');
		CPPUNIT_ASSERT(controller._gameBoard[0][2].mySymbol == '2');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][2].mySymbol == '.');
	}
	
	// ----
    // findWhatIsInFront
    // ----	
	
	void findWhatIsInFront_one () {
	
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,3);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		Creature creature(noSpecies, SOUTH);
		CreatureContainer creatureContainer = { creature, 2, 0, 'h' };
		controller._gameBoard[2][0] = creatureContainer;
		
		InFront desiredOutput = WALL;
		InFront realOutput = controller.findWhatIsInFront(controller._gameBoard[2][0]);

		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
    void findWhatIsInFront_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,3);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		Creature creature(noSpecies, NORTH);
		CreatureContainer creatureContainer = { creature, 2, 0, 'h' };
		controller._gameBoard[2][0] = creatureContainer;
		
		InFront desiredOutput = EMPTY;
		InFront realOutput = controller.findWhatIsInFront(controller._gameBoard[2][0]);
		
		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
    void findWhatIsInFront_three () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,3);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		Creature creatureA(noSpecies, NORTH);
		CreatureContainer creatureContainerA = { creatureA, 2, 0, 'h' };
		controller._gameBoard[2][0] = creatureContainerA;
		
		Creature creatureB(noSpecies, SOUTH);
		CreatureContainer creatureContainerB = { creatureB, 1, 0, 'f' };
		controller._gameBoard[1][0] = creatureContainerB;
		
		InFront desiredOutput = ENEMY;
		InFront realOutput = controller.findWhatIsInFront(controller._gameBoard[2][0]);
		
		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}
	
    void findWhatIsInFront_four () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,3);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		Creature creatureA(noSpecies, EAST);
		CreatureContainer creatureContainerA = { creatureA, 2, 0, 'h' };
		controller._gameBoard[2][0] = creatureContainerA;
		
		Creature creatureB(noSpecies, SOUTH);
		CreatureContainer creatureContainerB = { creatureB, 2, 1, 'h' };
		controller._gameBoard[2][1] = creatureContainerB;
		
		InFront desiredOutput = OTHER;
		InFront realOutput = controller.findWhatIsInFront(controller._gameBoard[2][0]);
		controller.printGameBoard();
		CPPUNIT_ASSERT(desiredOutput == realOutput);
	}	
	
	// ----
    // Controller
    // ----	
	
	void Controller_one () {
		Controller controller(5,9);
		CPPUNIT_ASSERT(controller._gameBoard.size() == 5);
		CPPUNIT_ASSERT(controller._gameBoard[0].size() == 9);
		CPPUNIT_ASSERT(controller._turnNumber == 0);
		for (int i = 0; i < (int)controller._gameBoard.size(); i++){
			for (int j = 0 ; j < (int)controller._gameBoard[0].size(); j++){
				CPPUNIT_ASSERT(controller._gameBoard[i][j].mySymbol == '.');
			}
		}
	}

	void Controller_two () {
		Controller controller(9,5);
		CPPUNIT_ASSERT(controller._gameBoard.size() == 9);
		CPPUNIT_ASSERT(controller._gameBoard[0].size() == 5);
		CPPUNIT_ASSERT(controller._turnNumber == 0);
		for (int i = 0; i < (int)controller._gameBoard.size(); i++){
			for (int j = 0 ; j < (int)controller._gameBoard[0].size(); j++){
				CPPUNIT_ASSERT(controller._gameBoard[i][j].mySymbol == '.');
			}
		}
	}
	
	void Controller_three () {
		Controller controller(72,72);
		CPPUNIT_ASSERT(controller._gameBoard.size() == 72);
		CPPUNIT_ASSERT(controller._gameBoard[0].size() == 72);
		CPPUNIT_ASSERT(controller._turnNumber == 0);
		for (int i = 0; i < (int)controller._gameBoard.size(); i++){
			for (int j = 0 ; j < (int)controller._gameBoard[0].size(); j++){
				CPPUNIT_ASSERT(controller._gameBoard[i][j].mySymbol == '.');
			}
		}
	}	
	
	// ----
    // placeCreatureOnBoard
    // ----	
	
	void placeCreatureOnBoard_one () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,3);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		
		controller.placeCreatureOnBoard(creatureA, 3, 'a');
		controller.placeCreatureOnBoard(creatureB, 7, 'b');
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == 'a');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][1].mySymbol == 'b');
		CPPUNIT_ASSERT(controller._gameBoard[2][2].mySymbol == '.');
	}

	void placeCreatureOnBoard_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,4);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[1][3] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = emptyContainer;
		
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		
		controller.placeCreatureOnBoard(creatureA, 3, 'a');
		controller.placeCreatureOnBoard(creatureB, 7, 'b');
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][3].mySymbol == 'a');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][3].mySymbol == 'b');
		CPPUNIT_ASSERT(controller._gameBoard[2][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][3].mySymbol == '.');
	}
	
	void placeCreatureOnBoard_three () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Controller controller(3,4);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[1][3] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = emptyContainer;
		
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);

		controller.placeCreatureOnBoard(creatureA, 0, 'a');
		controller.placeCreatureOnBoard(creatureB, 11, 'b');
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == 'a');
		CPPUNIT_ASSERT(controller._gameBoard[0][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[0][3].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[1][3].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][0].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][1].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][2].mySymbol == '.');
		CPPUNIT_ASSERT(controller._gameBoard[2][3].mySymbol == 'b');
	}	
	
	// ----
    // printGameBoard
    // ----	
	
	void printGameBoard_one () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
		
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		CreatureContainer ccA = {creatureA, 0, 0, 'a'};
		CreatureContainer ccB = {creatureB, 2, 3, 'b'};

		Controller controller(3,4);
		controller._gameBoard[0][0] = ccA;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[1][3] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = ccB;
		
		string desiredOutut = "Turn = 0.\n  0123\n0 a...\n1 ....\n2 ...b\n";		
		string realOutput = controller.printGameBoard();
		
		CPPUNIT_ASSERT(desiredOutut == realOutput);
	}

	void printGameBoard_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };

		Controller controller(3,4);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = emptyContainer;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[1][3] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = emptyContainer;
		
		string desiredOutut = "Turn = 0.\n  0123\n0 ....\n1 ....\n2 ....\n";		
		string realOutput = controller.printGameBoard();
		
		CPPUNIT_ASSERT(desiredOutut == realOutput);
	}
	
	void printGameBoard_three () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };

		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		CreatureContainer ccA = {creatureA, 0, 0, 'a'};
		CreatureContainer ccB = {creatureB, 2, 3, 'b'};

		Controller controller(3,3);
		controller._gameBoard[0][0] = emptyContainer;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = ccA;
		controller._gameBoard[1][0] = ccB;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = emptyContainer;
		controller._gameBoard[2][0] = emptyContainer;
		controller._gameBoard[2][1] = emptyContainer;
		controller._gameBoard[2][2] = emptyContainer;
		
		string desiredOutut = "Turn = 0.\n  012\n0 ..a\n1 b..\n2 ...\n";		
		string realOutput = controller.printGameBoard();
		
		CPPUNIT_ASSERT(desiredOutut == realOutput);
	}	
	
	// ----
    // completeOneTurn
    // ----	
	
	void completeOneTurn_one () {
		vector<string> foodProgram(2);
		foodProgram[0] = "0: left";
		foodProgram[1] = "1: go 0";
		Species food(foodProgram);
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: hop";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);

		Controller controller(8, 8);

		Creature food1(food, EAST);
		controller.placeCreatureOnBoard(food1, 0, 'f');
		Creature food2(food, NORTH);
		controller.placeCreatureOnBoard(food2, 63, 'f');

		Creature hopper1(hopper,NORTH);
		controller.placeCreatureOnBoard(hopper1, 27, 'h');
        Creature hopper2(hopper,EAST);
		controller.placeCreatureOnBoard(hopper2, 28, 'h');
		Creature hopper3(hopper,SOUTH);
		controller.placeCreatureOnBoard(hopper3, 36, 'h');
        Creature hopper4(hopper,WEST);
		controller.placeCreatureOnBoard(hopper4, 35, 'h');
		
		controller.completeOneTurn();
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == 'f');
		CPPUNIT_ASSERT(controller._gameBoard[7][7].mySymbol == 'f');
		CPPUNIT_ASSERT(controller._gameBoard[4][2].mySymbol == 'h');
		CPPUNIT_ASSERT(controller._gameBoard[2][3].mySymbol == 'h');
		CPPUNIT_ASSERT(controller._gameBoard[3][5].mySymbol == 'h');
		CPPUNIT_ASSERT(controller._gameBoard[5][4].mySymbol == 'h');
	}

	void completeOneTurn_two () {
		vector<string> hopperProgram(2);
		hopperProgram[0] = "0: hop";
		hopperProgram[1] = "1: go 0";
		Species hopper(hopperProgram);
	
		vector<string> trapProgram(5);
		trapProgram[0] = "0: if_enemy 3";
		trapProgram[1] = "1: left";
		trapProgram[2] = "2: go 0";
		trapProgram[3] = "3: infect";
		trapProgram[4] = "4: go 0";
		Species trap(trapProgram);

		vector<string> roverProgram(11);
		roverProgram[0] = "0: if_enemy 9";
		roverProgram[1] = "1: if_empty 7";
		roverProgram[2] = "2: if_random 5";
		roverProgram[3] = "3: left";
		roverProgram[4] = "4: go 0";
		roverProgram[5] = "5: right";
		roverProgram[6] = "6: go 0";
		roverProgram[7] = "7: hop";
		roverProgram[8] = "8: go 0";
		roverProgram[9] = "9: infect";
		roverProgram[10] = "10: go 0";
		Species rover(roverProgram);

		Controller controller(7, 9);

		Creature trap1(trap, EAST);
		controller.placeCreatureOnBoard(trap1, 0, 't');

		Creature hopper1(hopper, EAST);
		controller.placeCreatureOnBoard(hopper1, 29, 'h');

		Creature rover1(rover, NORTH);
		controller.placeCreatureOnBoard(rover1, 49, 'r');

		Creature trap2(trap, WEST);
		controller.placeCreatureOnBoard(trap2, 62, 't');
		
		controller.completeOneTurn();
		
		CPPUNIT_ASSERT(controller._gameBoard[0][0].mySymbol == 't');
		CPPUNIT_ASSERT(controller._gameBoard[3][3].mySymbol == 'h');
		CPPUNIT_ASSERT(controller._gameBoard[4][4].mySymbol == 'r');
		CPPUNIT_ASSERT(controller._gameBoard[6][8].mySymbol == 't');
	}
	
	void completeOneTurn_three () {
		Controller controller(3, 3);
		controller.completeOneTurn();
		for (int i = 0; i < (int)controller._gameBoard.size(); i++){
			for (int j = 0 ; j < (int)controller._gameBoard[0].size(); j++){
				CPPUNIT_ASSERT(controller._gameBoard[i][j].mySymbol == '.');
			}
		}
		
	}	
		
	
	
	void symbolCount_one () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
				
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		
		CreatureContainer creatureContainerA = { creatureA, 0, 0, 'a' };
		CreatureContainer creatureContainerB = { creatureA, 0, 0, 'b' };
				
		Controller controller(3,4);
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = creatureContainerA;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = creatureContainerB;
		controller._gameBoard[1][3] = creatureContainerA;
		controller._gameBoard[2][0] = creatureContainerB;
		controller._gameBoard[2][1] = creatureContainerA;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = creatureContainerA;
	
		int symbolCountA = controller.symbolCount('a');
		CPPUNIT_ASSERT(symbolCountA == 5);

	}
	
	void symbolCount_two () {
		vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
				
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		
		CreatureContainer creatureContainerA = { creatureA, 0, 0, 'c' };
		CreatureContainer creatureContainerB = { creatureA, 0, 0, 'b' };
				
		Controller controller(3,4);
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = creatureContainerA;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = creatureContainerB;
		controller._gameBoard[1][3] = creatureContainerA;
		controller._gameBoard[2][0] = creatureContainerB;
		controller._gameBoard[2][1] = creatureContainerA;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = creatureContainerA;
	
		int symbolCountA = controller.symbolCount('a');
		CPPUNIT_ASSERT(symbolCountA == 0);
	}
	
	void symbolCount_three () {
				vector<string> noProgram(0);
		Species noSpecies(noProgram);
		Creature noCreature(noSpecies, NORTH);
		CreatureContainer emptyContainer = { noCreature, 0, 0, '.' };		
				
		Creature creatureA(noSpecies, EAST);
		Creature creatureB(noSpecies, EAST);
		
		CreatureContainer creatureContainerA = { creatureA, 0, 0, 'a' };
		CreatureContainer creatureContainerB = { creatureA, 0, 0, 'a' };
				
		Controller controller(3,4);
		controller._gameBoard[0][0] = creatureContainerA;
		controller._gameBoard[0][1] = emptyContainer;
		controller._gameBoard[0][2] = emptyContainer;
		controller._gameBoard[0][3] = emptyContainer;
		controller._gameBoard[1][0] = creatureContainerA;
		controller._gameBoard[1][1] = emptyContainer;
		controller._gameBoard[1][2] = creatureContainerB;
		controller._gameBoard[1][3] = creatureContainerA;
		controller._gameBoard[2][0] = creatureContainerB;
		controller._gameBoard[2][1] = creatureContainerA;
		controller._gameBoard[2][2] = emptyContainer;
		controller._gameBoard[2][3] = creatureContainerA;
	
		int symbolCountA = controller.symbolCount('a');
		CPPUNIT_ASSERT(symbolCountA == 7);
	}
	
	
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
			
	CPPUNIT_TEST(line_one);
	CPPUNIT_TEST(line_two);
	CPPUNIT_TEST(line_three);	
		
	CPPUNIT_TEST(evalControlLine_one);
	CPPUNIT_TEST(evalControlLine_two);
	CPPUNIT_TEST(evalControlLine_three);
	CPPUNIT_TEST(evalControlLine_four);
	CPPUNIT_TEST(evalControlLine_five);	
	
    CPPUNIT_TEST(splitCurrentLine_one);
	CPPUNIT_TEST(splitCurrentLine_two);
	CPPUNIT_TEST(splitCurrentLine_three);

	CPPUNIT_TEST(processTurn_one);
	CPPUNIT_TEST(processTurn_two);
	CPPUNIT_TEST(processTurn_three);

	CPPUNIT_TEST(turnLeft_one);
	CPPUNIT_TEST(turnLeft_two);
	CPPUNIT_TEST(turnLeft_three);
	
	CPPUNIT_TEST(turnRight_one);
	CPPUNIT_TEST(turnRight_two);
	CPPUNIT_TEST(turnRight_three);
	
	CPPUNIT_TEST(infect_one);
	CPPUNIT_TEST(infect_two);
	CPPUNIT_TEST(infect_three);
	
	CPPUNIT_TEST(getDirection_one);
	CPPUNIT_TEST(getDirection_two);
	CPPUNIT_TEST(getDirection_three);

	CPPUNIT_TEST(populateCreatureQueue_one);
	CPPUNIT_TEST(populateCreatureQueue_two);
	CPPUNIT_TEST(populateCreatureQueue_three);
	
	CPPUNIT_TEST(processAction_one);
	CPPUNIT_TEST(processAction_two);
	CPPUNIT_TEST(processAction_three);	
	CPPUNIT_TEST(processAction_four);	

	CPPUNIT_TEST(hopCreature_one);
	CPPUNIT_TEST(hopCreature_two);
	CPPUNIT_TEST(hopCreature_three);	
	
	CPPUNIT_TEST(findWhatIsInFront_one);
	CPPUNIT_TEST(findWhatIsInFront_two);
	CPPUNIT_TEST(findWhatIsInFront_three);	
	CPPUNIT_TEST(findWhatIsInFront_four);	

	CPPUNIT_TEST(Controller_one);
	CPPUNIT_TEST(Controller_two);
	CPPUNIT_TEST(Controller_three);	
	
	CPPUNIT_TEST(placeCreatureOnBoard_one);
	CPPUNIT_TEST(placeCreatureOnBoard_two);
	CPPUNIT_TEST(placeCreatureOnBoard_three);
	
	CPPUNIT_TEST(printGameBoard_one);
	CPPUNIT_TEST(printGameBoard_two);
	CPPUNIT_TEST(printGameBoard_three);
	
	CPPUNIT_TEST(completeOneTurn_one);
	CPPUNIT_TEST(completeOneTurn_two);
	CPPUNIT_TEST(completeOneTurn_three);
	
	CPPUNIT_TEST(symbolCount_one);
	CPPUNIT_TEST(symbolCount_two);
	CPPUNIT_TEST(symbolCount_three);
	
	
	
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
