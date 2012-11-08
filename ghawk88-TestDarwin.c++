/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */


#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#include "Darwin.h"




struct TestDarwin : CppUnit::TestFixture {

	/*************************
	Creature Constructor Tests
	**************************/
	void testCreatureConstrutor(){
		Creature c;

		CPPUNIT_ASSERT(c.currentTurn == 0);
		CPPUNIT_ASSERT(c.programCounter == 0);
		CPPUNIT_ASSERT(c.currentDirection >= 0 && c.currentDirection <= 3);


	}

	void testCreatureConstrutorRandom(){
		Creature c;

		c.currentTurn = 100;
		c.programCounter = 12;
		c.currentDirection = (CreatureFacingDirection)2;

		CPPUNIT_ASSERT(c.currentTurn == 100);
		CPPUNIT_ASSERT(c.programCounter == 12);
		CPPUNIT_ASSERT(c.currentDirection == 2);


	}

	void testCreatureConstrutorNegative(){
		Creature c;

		c.currentTurn = -100;
		c.programCounter = -12;
		c.currentDirection = (CreatureFacingDirection)2;

		CPPUNIT_ASSERT(c.currentTurn == -100);
		CPPUNIT_ASSERT(c.programCounter == -12);
		CPPUNIT_ASSERT(c.currentDirection == 2);


	}

	/*************************
	Execute Instructions Tests
	**************************/
	void testExecuteInstructions(){
		Creature c;
		c.programInstructions.push_back("Hello");

		CPPUNIT_ASSERT(c.programInstructions.size() == 1);
		CPPUNIT_ASSERT(c.getCurrentInstruction().compare("Hello") == 0);

	}

	void testExecuteInstructionsTwice(){
		Creature c;
		c.programInstructions.push_back("Hello");
		c.programInstructions.push_back("World");



		CPPUNIT_ASSERT(c.programInstructions.size() == 2);
		CPPUNIT_ASSERT(c.getCurrentInstruction().compare("Hello") == 0);
		CPPUNIT_ASSERT(c.getCurrentInstruction().compare("World") == 0);
	}

	void testExecuteInstructionsThree(){
		Creature c;
		c.programInstructions.push_back("Hello");
		c.programInstructions.push_back("World");
		c.programInstructions.push_back("!");



		CPPUNIT_ASSERT(c.programInstructions.size() == 3);
		CPPUNIT_ASSERT(c.getCurrentInstruction().compare("Hello") == 0);
		CPPUNIT_ASSERT(c.getCurrentInstruction().compare("World") == 0);
		CPPUNIT_ASSERT(c.getCurrentInstruction().compare("!") == 0);
	}

	/*************************
	Food Constructor Tests
	**************************/

	void testFoodConstructor(){
		Food f;

		CPPUNIT_ASSERT(f.programInstructions[0].compare("left") == 0);
		CPPUNIT_ASSERT(f.programInstructions[1].compare("go 0") == 0);
	}

	void testFoodConstructorName(){
		Food f;

		CPPUNIT_ASSERT(f.name == 'f');
	}

	void testFoodConstructorGetsCreature(){
		Food f;

		CPPUNIT_ASSERT(f.programCounter == 0);
		CPPUNIT_ASSERT(f.currentDirection >= 0 && f.currentDirection <= 3);
		CPPUNIT_ASSERT(f.programInstructions.size() == 2);
		CPPUNIT_ASSERT(f.currentTurn == 0);


	}

	/*************************
	Hopper Constructor Tests
	**************************/

	void testHopperConstructor(){
		Hopper h;

		CPPUNIT_ASSERT(h.programInstructions[0].compare("hop") == 0);
		CPPUNIT_ASSERT(h.programInstructions[1].compare("go 0") == 0);
	}

	void testHopperConstructorName(){
		Hopper h;

		CPPUNIT_ASSERT(h.name == 'h');
	}

	void testHopperConstructorGetsCreature(){
		Hopper h;

		CPPUNIT_ASSERT(h.programCounter == 0);
		CPPUNIT_ASSERT(h.currentDirection >= 0 && h.currentDirection <= 3);
		CPPUNIT_ASSERT(h.programInstructions.size() == 2);
		CPPUNIT_ASSERT(h.currentTurn == 0);


	}

	/*************************
	Trap Constructor Tests
	**************************/

	void testTrapConstructor(){
		Trap t;

		CPPUNIT_ASSERT(t.programInstructions[0].compare("if_enemy 3") == 0);
		CPPUNIT_ASSERT(t.programInstructions[1].compare("left") == 0);
		CPPUNIT_ASSERT(t.programInstructions[2].compare("go 0") == 0);
		CPPUNIT_ASSERT(t.programInstructions[3].compare("infect") == 0);
		CPPUNIT_ASSERT(t.programInstructions[4].compare("go 0") == 0);
	}

	void testTrapConstructorName(){
		Trap t;

		CPPUNIT_ASSERT(t.name == 't');
	}

	void testTrapConstructorGetsCreature(){
		Trap t;

		CPPUNIT_ASSERT(t.programCounter == 0);
		CPPUNIT_ASSERT(t.currentDirection >= 0 && t.currentDirection <= 3);
		CPPUNIT_ASSERT(t.programInstructions.size() == 5);
		CPPUNIT_ASSERT(t.currentTurn == 0);


	}

	/*************************
	Rover Constructor Tests
	**************************/

	void testRoverConstructor(){
		Rover r;

		CPPUNIT_ASSERT(r.programInstructions[0].compare("if_enemy 9") == 0);
		CPPUNIT_ASSERT(r.programInstructions[1].compare("if_empty 7") == 0);
		CPPUNIT_ASSERT(r.programInstructions[2].compare("if_random 5") == 0);
		CPPUNIT_ASSERT(r.programInstructions[3].compare("left") == 0);
		CPPUNIT_ASSERT(r.programInstructions[4].compare("go 0") == 0);
		CPPUNIT_ASSERT(r.programInstructions[5].compare("right") == 0);
		CPPUNIT_ASSERT(r.programInstructions[6].compare("go 0") == 0);
		CPPUNIT_ASSERT(r.programInstructions[7].compare("hop") == 0);
		CPPUNIT_ASSERT(r.programInstructions[8].compare("go 0") == 0);
		CPPUNIT_ASSERT(r.programInstructions[9].compare("infect") == 0);
		CPPUNIT_ASSERT(r.programInstructions[10].compare("go 0") == 0);
	}

	void testRoverConstructorName(){
		Rover r;

		CPPUNIT_ASSERT(r.name == 'r');
	}

	void testRoverConstructorGetsCreature(){
		Rover r;

		CPPUNIT_ASSERT(r.programCounter == 0);
		CPPUNIT_ASSERT(r.currentDirection >= 0 && r.currentDirection <= 3);
		CPPUNIT_ASSERT(r.programInstructions.size() == 11);
		CPPUNIT_ASSERT(r.currentTurn == 0);


	}
	/*************************
	World Constructor Tests
	**************************/

	void testWorldConstructor(){
		World w(12, 12, 12, 12);

		CPPUNIT_ASSERT(w.movesToPrint == 12);
		CPPUNIT_ASSERT(w.board.size() == 12);
		CPPUNIT_ASSERT(w.board[0].size() == 12);
		CPPUNIT_ASSERT(w.totalNumberOfMoves == 12);

	}

	void testWorldConstructorZero(){
		World w(0, 0, 0, 0);

		CPPUNIT_ASSERT(w.movesToPrint == 0);
		CPPUNIT_ASSERT(w.board.size() == 0);
		CPPUNIT_ASSERT(w.totalNumberOfMoves == 0);

	}

	void testWorldConstructorDots(){
		World w(12, 12, 12, 12);

		CPPUNIT_ASSERT(w.board[0][0].name == '.');
		CPPUNIT_ASSERT(w.board[1][7].name == '.');
		CPPUNIT_ASSERT(w.board[8][4].name == '.');


	}

	/*************************
	Spawn Tests
	**************************/

	void testSpawnFood(){
		World w(1,1,1,1);

		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionRandom, 0, 0);

		CPPUNIT_ASSERT(w.board[0][0].name == 'f');

	}

	void testSpawnHopper(){

		World w(1,1,1,1);

		w.spawn(CreatureSpeciesTypeHopper, CreatureFacingDirectionNorth, 0, 0);

		CPPUNIT_ASSERT(w.board[0][0].name == 'h');
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionNorth);
		
	}

	void testSpawnRover(){
		World w(1,1,1,1);

		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionSouth, 0, 0);

		CPPUNIT_ASSERT(w.board[0][0].name == 'r');
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionSouth);
		
	}

	void testSpawnTrap(){
		World w(1,1,1,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionWest, 0, 0);

		CPPUNIT_ASSERT(w.board[0][0].name == 't');
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionWest);
		
	}

	/*************************
	Run Tests
	**************************/

	void testRun(){
		World w(5,5,5,0);
		CPPUNIT_ASSERT(w.currentMoveNumber == 0);
		w.run();

		CPPUNIT_ASSERT(w.totalNumberOfMoves == 5);
		CPPUNIT_ASSERT(w.totalNumberOfMoves == w.currentMoveNumber);

	}

	void testRunBig(){
		World w(5,5,50,0);

		CPPUNIT_ASSERT(w.currentMoveNumber == 0);

		w.run();

		CPPUNIT_ASSERT(w.totalNumberOfMoves == 50);
		CPPUNIT_ASSERT(w.totalNumberOfMoves == w.currentMoveNumber);

	}

	void testRunZero(){
		World w(5,5,0,0);

		CPPUNIT_ASSERT(w.currentMoveNumber == 0);
		
		w.run();

		CPPUNIT_ASSERT(w.totalNumberOfMoves == 0);
		CPPUNIT_ASSERT(w.totalNumberOfMoves == w.currentMoveNumber);

	}

	/*************************
	TravelTheWorld Tests
	**************************/

	void testTravelTheWorld(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 2, 1);

		w.travelTheWorld();

		CPPUNIT_ASSERT(w.board[2][1].currentDirection == CreatureFacingDirectionWest);
		CPPUNIT_ASSERT(w.board[2][1].name == 'f');
		CPPUNIT_ASSERT(w.board[2][1].currentTurn == 1);
		CPPUNIT_ASSERT(w.board[2][1].currentTurn == w.currentMoveNumber + 1);
	}

	void testTravelTheWorldTwoCreatures(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 0, 0);
		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		w.travelTheWorld();

		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionWest);
		CPPUNIT_ASSERT(w.board[0][0].name == 'f');
		CPPUNIT_ASSERT(w.board[0][0].currentTurn == 1);
		CPPUNIT_ASSERT(w.board[0][0].currentTurn == w.currentMoveNumber + 1);

		CPPUNIT_ASSERT(w.board[2][2].currentDirection == CreatureFacingDirectionWest);
		CPPUNIT_ASSERT(w.board[2][2].name == 't');
		CPPUNIT_ASSERT(w.board[2][2].currentTurn == 1);
		CPPUNIT_ASSERT(w.board[2][2].currentTurn == w.currentMoveNumber + 1);
	}

	void testTravelTheWorldMultipleCalls(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 0, 0);
		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		w.travelTheWorld();

		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionWest);
		CPPUNIT_ASSERT(w.board[0][0].name == 'f');
		CPPUNIT_ASSERT(w.board[0][0].currentTurn == 1);
		CPPUNIT_ASSERT(w.board[0][0].currentTurn == w.currentMoveNumber + 1);

		CPPUNIT_ASSERT(w.board[2][2].currentDirection == CreatureFacingDirectionWest);
		CPPUNIT_ASSERT(w.board[2][2].name == 't');
		CPPUNIT_ASSERT(w.board[2][2].currentTurn == 1);
		CPPUNIT_ASSERT(w.board[2][2].currentTurn == w.currentMoveNumber + 1);
		w.currentMoveNumber++;
		
		w.travelTheWorld();

		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionSouth);
		CPPUNIT_ASSERT(w.board[0][0].name == 'f');
		CPPUNIT_ASSERT(w.board[0][0].currentTurn == 2);
		CPPUNIT_ASSERT(w.board[0][0].currentTurn == w.currentMoveNumber + 1);

		CPPUNIT_ASSERT(w.board[2][2].currentDirection == CreatureFacingDirectionSouth);
		CPPUNIT_ASSERT(w.board[2][2].name == 't');
		CPPUNIT_ASSERT(w.board[2][2].currentTurn == 2);
		CPPUNIT_ASSERT(w.board[2][2].currentTurn == w.currentMoveNumber + 1);
	}

	/********************
	Creatures Turn Tests
	********************/

	void testCreaturesTurnFood(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 0, 0);

		bool b = w.creaturesTurn(&w.board[0][0],0,0);

		CPPUNIT_ASSERT(!b);
		CPPUNIT_ASSERT(w.board[0][0].programCounter == 1);
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionWest);



	}

	void testCreaturesTurnRover(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionNorth, 0, 0);

		bool b = w.creaturesTurn(&w.board[0][0],0,0);


		CPPUNIT_ASSERT(b);
		CPPUNIT_ASSERT(w.board[0][0].programCounter == 1);



	}

	void testCreaturesTurnRoverEnemy(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionEast, 0, 0);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 1);

		bool b = w.creaturesTurn(&w.board[0][0],0,0);

		CPPUNIT_ASSERT(w.board[0][0].programCounter == 9);
		CPPUNIT_ASSERT(b);
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionEast);
		CPPUNIT_ASSERT(w.board[0][1].name == 'f');

	}

	void testChangeDirectionLeft(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 0);

		w.changeDirection(&w.board[0][0], "left");
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionNorth);

	}

	void testChangeDirectionRight(){

		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 0);

		w.changeDirection(&w.board[0][0], "right");
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionSouth);
		
	}

	void testChangeDirectionTwice(){

		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 0);

		w.changeDirection(&w.board[0][0], "left");
		w.changeDirection(&w.board[0][0], "left");
		CPPUNIT_ASSERT(w.board[0][0].currentDirection == CreatureFacingDirectionWest);
		
	}

	void testExecuteHopTwice(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 0);

		w.executeHop(&w.board[0][0], 0, 0);
		w.executeHop(&w.board[0][1], 0 , 1);

		CPPUNIT_ASSERT(w.board[0][2].name == 'f');
		CPPUNIT_ASSERT(w.board[0][0].name == '.');
		CPPUNIT_ASSERT(w.board[0][1].name == '.');

	}

	void testExecuteHop(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionEast, 0, 0);

		w.executeHop(&w.board[0][0], 0,0);

		CPPUNIT_ASSERT(w.board[0][1].name == 'f');
		CPPUNIT_ASSERT(w.board[0][0].name == '.');

	}

	void testExecuteHopOutOfBounds(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 0, 0);

		w.executeHop(&w.board[0][0], 0,0);

		CPPUNIT_ASSERT(w.board[0][0].name == 'f');

	}

	void testExecuteInfect(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 1, 2);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		w.executeInfect(&w.board[2][2], 2, 2);
		CPPUNIT_ASSERT(w.board[1][2].name == 't');
		CPPUNIT_ASSERT(w.board[2][2].name == 't');

	}

	void testExecuteInfectNotEnemy(){
		World w(5,5,5,1);
		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 1, 2);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		w.executeInfect(&w.board[2][2], 2, 2);

		CPPUNIT_ASSERT(w.board[1][2].name == 't');
		CPPUNIT_ASSERT(w.board[2][2].name == 't');

	}

	void testExecuteInfectNothing(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		w.executeInfect(&w.board[2][2], 2, 2);

		CPPUNIT_ASSERT(w.board[1][2].name == '.');
		CPPUNIT_ASSERT(w.board[2][2].name == 't');

	}

	void testEnemyCheckEmpty(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		CPPUNIT_ASSERT(w.enemyCheck(&w.board[2][2], 2, 2) == false);

	}

	void testEnemyCheckTrue(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 1, 2);

		CPPUNIT_ASSERT(w.enemyCheck(&w.board[2][2], 2, 2));

	}

	void testEnemyCheckFalse(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);
		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 1, 2);

		CPPUNIT_ASSERT(w.enemyCheck(&w.board[2][2], 2, 2) == false);

	}

	void testEmptyCheckTrue(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);

		CPPUNIT_ASSERT(w.emptyCheck(&w.board[2][2], 2, 2));

	}

	void testEmptyCheckFalse(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);
		w.spawn(CreatureSpeciesTypeFood, CreatureFacingDirectionNorth, 1, 2);

		CPPUNIT_ASSERT(w.emptyCheck(&w.board[2][2], 2, 2) == false);

	}

	void testEmptyCheckSame(){
		World w(5,5,5,1);

		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 2, 2);
		w.spawn(CreatureSpeciesTypeTrap, CreatureFacingDirectionNorth, 1, 2);

		CPPUNIT_ASSERT(w.emptyCheck(&w.board[2][2], 2, 2) == false);

	}

	void testRandomNumber(){

		World w(5,5,5,5);

		int num = w.randomNumber(2);

		CPPUNIT_ASSERT(num>=0 && num <2);

	}

	void testRandomNumberOne(){

		World w(5,5,5,5);

		int num = w.randomNumber(1);

		CPPUNIT_ASSERT(num==0);

	}

	void testRandomNumberMAX(){

		World w(5,5,5,5);

		int num = w.randomNumber(RAND_MAX);

		CPPUNIT_ASSERT(num>=0 && num <RAND_MAX);

	}


////////////////////////////////////////////////////////////////////////////////////

/////////////            wall check

////////////////////////////////////////////////////////////////////////////////////


	void testWallCheckOne(){

		World w(1,1,1,1);

		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionSouth, 0, 0);

		bool wall = w.wallCheck(&w.board[0][0],0,0);

		CPPUNIT_ASSERT(wall);

	}

	void testWallCheckTwo(){

		World w(6,6,1,1);

		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionSouth, 3, 3);

		bool wall = w.wallCheck(&w.board[3][3],3,3);

		CPPUNIT_ASSERT(!wall);

	}

	void testWallCheckThree(){

		World w(2,1,1,1);

		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionEast, 0, 0);

		w.spawn(CreatureSpeciesTypeRover, CreatureFacingDirectionSouth, 0, 1);


		bool wall = w.wallCheck(&w.board[0][0],0,0);

		CPPUNIT_ASSERT(!wall);

	}




	CPPUNIT_TEST_SUITE(TestDarwin);
	/*************************
	Creature Constructor Tests
	**************************/
	CPPUNIT_TEST(testCreatureConstrutor);
	CPPUNIT_TEST(testCreatureConstrutorRandom);
	CPPUNIT_TEST(testCreatureConstrutorNegative);

	/*************************
	Creature getNextInstruction Tests
	**************************/
	CPPUNIT_TEST(testExecuteInstructions);
	CPPUNIT_TEST(testExecuteInstructionsTwice);
	CPPUNIT_TEST(testExecuteInstructionsThree);
	/*************************
	food Constructor tests
	**************************/
	CPPUNIT_TEST(testFoodConstructor);
	CPPUNIT_TEST(testFoodConstructorName);
	CPPUNIT_TEST(testFoodConstructorGetsCreature);
	/*************************
	hopper constructor tests
	**************************/
	CPPUNIT_TEST(testHopperConstructor);
	CPPUNIT_TEST(testHopperConstructorName);
	CPPUNIT_TEST(testHopperConstructorGetsCreature);
	/*************************
	trap constructor tests
	**************************/
	CPPUNIT_TEST(testTrapConstructor);
	CPPUNIT_TEST(testTrapConstructorName);
	CPPUNIT_TEST(testTrapConstructorGetsCreature);
	/*************************
	rover constructor tests
	**************************/
	CPPUNIT_TEST(testRoverConstructor);
	CPPUNIT_TEST(testRoverConstructorName);
	CPPUNIT_TEST(testRoverConstructorGetsCreature);
	/*************************
	World Constructor Tests
	**************************/
	CPPUNIT_TEST(testWorldConstructor);	
	CPPUNIT_TEST(testWorldConstructorZero);	
	CPPUNIT_TEST(testWorldConstructorDots);	
	/************************
	Spawn Tests
	*************************/
	CPPUNIT_TEST(testSpawnFood);
	CPPUNIT_TEST(testSpawnHopper);
	CPPUNIT_TEST(testSpawnRover);
	CPPUNIT_TEST(testSpawnTrap);
	/*************************
	Run Tests
	**************************/
	CPPUNIT_TEST(testRun);
	CPPUNIT_TEST(testRunBig);
	CPPUNIT_TEST(testRunZero);

	CPPUNIT_TEST(testTravelTheWorld);
	CPPUNIT_TEST(testTravelTheWorldTwoCreatures);
	CPPUNIT_TEST(testTravelTheWorldMultipleCalls);

	CPPUNIT_TEST(testCreaturesTurnFood);
	CPPUNIT_TEST(testCreaturesTurnRover);
	CPPUNIT_TEST(testCreaturesTurnRoverEnemy);

	CPPUNIT_TEST(testChangeDirectionLeft);
	CPPUNIT_TEST(testChangeDirectionRight);
	CPPUNIT_TEST(testChangeDirectionTwice);

	CPPUNIT_TEST(testExecuteHop);
	CPPUNIT_TEST(testExecuteHopTwice);
	CPPUNIT_TEST(testExecuteHopOutOfBounds);

	CPPUNIT_TEST(testExecuteInfect);
	CPPUNIT_TEST(testExecuteInfectNothing);
	CPPUNIT_TEST(testExecuteInfectNotEnemy);

	CPPUNIT_TEST(testEnemyCheckEmpty);
	CPPUNIT_TEST(testEnemyCheckTrue);
	CPPUNIT_TEST(testEnemyCheckFalse);

	CPPUNIT_TEST(testEmptyCheckTrue);
	CPPUNIT_TEST(testEmptyCheckFalse);
	CPPUNIT_TEST(testEmptyCheckSame);

	CPPUNIT_TEST(testWallCheckOne);
	CPPUNIT_TEST(testWallCheckTwo);
	CPPUNIT_TEST(testWallCheckThree);

	CPPUNIT_TEST(testRandomNumber);
	CPPUNIT_TEST(testRandomNumberMAX);
	CPPUNIT_TEST(testRandomNumberOne);


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