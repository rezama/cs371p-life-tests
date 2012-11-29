/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind TestLife.app >& TestLife.out
 */


#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public
#include "Life.h"
#include "FredkinCell.h"
#include "ConwayCell.h"




struct TestLife : CppUnit::TestFixture {

    ///////////////////////////////////
    // FredkinCell Constructor Tests //
    //////////////////////////////////
    void testFredkinConstructor(){
        FredkinCell f;

        CPPUNIT_ASSERT(f.age == 0);

    }

    void testFredkinConstructorTwice(){
        FredkinCell f;
        FredkinCell f2;

        CPPUNIT_ASSERT(&f != & f2);
        CPPUNIT_ASSERT(f.age == f2.age);
        CPPUNIT_ASSERT(f.isAlive == f2.isAlive);
    }

    void testFredkinConstructorMakesDead(){
        FredkinCell f;

        CPPUNIT_ASSERT(f.isAlive == false);

    }

    ///////////////////////////////////
    // FredkinCell toString Tests   //
    //////////////////////////////////

    void testFredkinCellToStringDead(){
        FredkinCell f;

        CPPUNIT_ASSERT(f.str() == "-");

    }

    void testFredkinCellToStringAlive(){
        FredkinCell f;
        f.isAlive = true;

        CPPUNIT_ASSERT(f.str() == "0");
        
    }

    void testFredkinCellToStringGreaterThan10(){
        FredkinCell f;
        f.isAlive = true;
        f.age = 10;

        CPPUNIT_ASSERT(f.str() == "+");
        
    }
    ////////////////////////////////////
    // FredkinCell makeAlive Tests //
    ///////////////////////////////////
    void testFredkinCellMakeAliveFromDead(){
        FredkinCell f;
        f.isAlive = false;
        f.makeAlive();

        CPPUNIT_ASSERT(f.isAlive);
        CPPUNIT_ASSERT(f.age == 0);
    }

    void testFredkinCellMakeAliveFromAlive(){
        FredkinCell f;
        f.isAlive = true;
        f.makeAlive();

        CPPUNIT_ASSERT(f.isAlive);
        CPPUNIT_ASSERT(f.age == 1);
    }

    void testFredkinCellMakeAliveFromConstruction(){
        FredkinCell f;
        f.makeAlive();

        CPPUNIT_ASSERT(f.isAlive);
        CPPUNIT_ASSERT(f.age == 0);
    }

    ////////////////////////////////////
    // FredkinCell kill Tests //
    ///////////////////////////////////
    void testFredkinCellKillFromDead(){
        FredkinCell f;
        f.isAlive = false;
        f.kill();

        CPPUNIT_ASSERT(f.isAlive == false);
    }

    void testFredkinCellKillFromAlive(){
        FredkinCell f;
        f.isAlive = true;
        f.kill();

        CPPUNIT_ASSERT(f.isAlive == false);
    }

    void testFredkinCellKillFromConstruction(){
        FredkinCell f;
        f.kill();

        CPPUNIT_ASSERT(f.isAlive == false);
    }

    ////////////////////////////////////
    // FredkinCell incrementAge Tests //
    ///////////////////////////////////

    void testFredkinCellIncrementAgeInitial(){
        FredkinCell f;
        f.makeAlive();

        f.incrementAge();
        CPPUNIT_ASSERT(f.age == 1);
    }

    void testFredkinCellIncrementAgeDead(){
        FredkinCell f;
        f.age = 900;
        f.kill();

        f.incrementAge();
        CPPUNIT_ASSERT(f.age == 900);
    }

    void testFredkinCellIncrementAgeGreaterThan9(){
        FredkinCell f;
        f.makeAlive();
        f.age = 90;

        f.incrementAge();
        CPPUNIT_ASSERT(f.age == 91);
    }

    ////////////////////////////////////
    // FredkinCell << operator Tests //
    ///////////////////////////////////

    void testFredkinCellGreaterThanGreaterThanOperatorInitial(){
        FredkinCell f;
        std::stringstream s;

        s << f;
        CPPUNIT_ASSERT(s.str() == "-");
    }

    void testFredkinCellGreaterThanGreaterThanOperatorDead(){
        FredkinCell f;
        f.age = 900;
        f.kill();
        std::stringstream s;
        s << f;
        CPPUNIT_ASSERT(s.str() == "-");
    }

    void testFredkinCellGreaterThanGreaterThanOperatorAlive(){
        FredkinCell f;
        f.makeAlive();
        f.age = 90;
        std::stringstream s;
        s << f;
        CPPUNIT_ASSERT(s.str() == "+");
    }

    //////////////////////////////
    // FredkinCell clone Tests //
    ////////////////////////////

    void testFredkinCellClone(){
        FredkinCell f;
        FredkinCell* g = f.clone();

        CPPUNIT_ASSERT(g->isAlive == false);
        CPPUNIT_ASSERT(g->age == 0);
        CPPUNIT_ASSERT(g != &f);

        delete g;

    }

    void testFredkinCellCloneAlive(){
        FredkinCell f;
        f.isAlive = true;
        FredkinCell* g = f.clone();

        CPPUNIT_ASSERT(f.isAlive);
        CPPUNIT_ASSERT(g->isAlive == false);
        CPPUNIT_ASSERT(g->age == 0);
        CPPUNIT_ASSERT(g != &f);

        delete g;

    }

    void testFredkinCellCloneOld(){
        FredkinCell f;
        f.isAlive = true;
        f.incrementAge();
        f.incrementAge();
        f.incrementAge();
        FredkinCell* g = f.clone();

        CPPUNIT_ASSERT(g->isAlive == false);
        CPPUNIT_ASSERT(f.age == 3);
        CPPUNIT_ASSERT(g->age == 0);
        CPPUNIT_ASSERT(g != &f);

        delete g;

    }

    //////////////////////////////////
    // FredkinCell shouldLive Tests //
    ////////////////////////////////
    void testFredkinCellShouldLiveTrue(){
        FredkinCell c;
        CPPUNIT_ASSERT(c.shouldLive(3) == true);

    }

    void testFredkinCellShouldLiveFalse(){
        FredkinCell c;
        CPPUNIT_ASSERT(c.shouldLive(4) == false);
    }

    void testFredkinCellShouldLiveAlreadyAlive(){
        FredkinCell c;
        c.isAlive = true;
        CPPUNIT_ASSERT(c.shouldLive(4) == true);
    }

    //////////////////////////////////
    // FredkinCell shouldDie Tests //
    ////////////////////////////////

    void testFredkinCellShouldDieTrue(){
        FredkinCell c;
        c.isAlive = true;
        CPPUNIT_ASSERT(c.shouldDie(2) == true);

    }

    void testFredkinCellShouldDieFalse(){
        FredkinCell c;
        CPPUNIT_ASSERT(c.shouldDie(3) == false);
    }

    void testFredkinCellShouldDieEdge(){
        FredkinCell c;
        c.isAlive = false;
        CPPUNIT_ASSERT(c.shouldLive(3) == true);
    }

    ///////////////////////////////////
    // ConwayCell Constructor Tests //
    //////////////////////////////////
    void testConwayConstructor(){
        ConwayCell f;

        CPPUNIT_ASSERT(f.isAlive == false);

    }

    void testConwayConstructorTwice(){
        ConwayCell f;
        ConwayCell f2;

        CPPUNIT_ASSERT(&f != &f2);
        CPPUNIT_ASSERT(f.isAlive == f2.isAlive);
        CPPUNIT_ASSERT(f.isAlive == false);
    }

    void testConwayConstructorMakesDead(){
        ConwayCell f;

        CPPUNIT_ASSERT(f.isAlive == false);

    }

    ///////////////////////////////////
    // ConwayCell toString Tests   //
    //////////////////////////////////

    void testConwayCellToStringDead(){
        ConwayCell f;
        CPPUNIT_ASSERT(f.str() == ".");

    }

    void testConwayCellToStringAlive(){
        ConwayCell f;
        f.isAlive = true;

        CPPUNIT_ASSERT(f.str() == "*");
        
    }

    void testConwayCellToStringAliveThenDead(){
        ConwayCell f;
        CPPUNIT_ASSERT(f.str() == ".");
        f.isAlive = true;

        CPPUNIT_ASSERT(f.str() == "*");
        
    }

    ////////////////////////////////////
    // ConwayCell makeAlive Tests //
    ///////////////////////////////////
    void testConwayCellMakeAliveFromDead(){
        ConwayCell f;
        f.isAlive = false;
        f.makeAlive();

        CPPUNIT_ASSERT(f.isAlive);
    }

    void testConwayCellMakeAliveFromAlive(){
        ConwayCell f;
        f.isAlive = true;
        f.makeAlive();

        CPPUNIT_ASSERT(f.isAlive);
    }

    void testConwayCellMakeAliveFromConstruction(){
        ConwayCell f;
        f.makeAlive();

        CPPUNIT_ASSERT(f.isAlive);
    }

    //////////////////////////
    // ConwayCell kill Tests//
    //////////////////////////
    void testConwayCellKillFromDead(){
        ConwayCell f;
        f.isAlive = false;
        f.kill();

        CPPUNIT_ASSERT(f.isAlive == false);
    }

    void testConwayCellKillFromAlive(){
        ConwayCell f;
        f.isAlive = true;
        f.kill();

        CPPUNIT_ASSERT(f.isAlive == false);
    }

    void testConwayCellKillFromConstruction(){
        ConwayCell f;
        f.kill();

        CPPUNIT_ASSERT(f.isAlive == false);
    }

    ////////////////////////////////////
    // ConwayCell << operator Tests //
    ///////////////////////////////////

    void testConwayCellGreaterThanGreaterThanOperatorInitial(){
        ConwayCell f;
        std::stringstream s;

        s << f;
        CPPUNIT_ASSERT(s.str() == ".");
    }

    void testConwayCellGreaterThanGreaterThanOperatorDead(){
        ConwayCell f;
        f.kill();
        std::stringstream s;
        s << f;
        CPPUNIT_ASSERT(s.str() == ".");
    }

    void testConwayCellGreaterThanGreaterThanOperatorAlive(){
        ConwayCell f;
        f.makeAlive();
        std::stringstream s;
        s << f;
        CPPUNIT_ASSERT(s.str() == "*");
    }

    /////////////////////////////
    // ConwayCell clone Tests //
    ///////////////////////////

    void testConwayCellClone(){
        ConwayCell* f = new ConwayCell();
        ConwayCell* g = f->clone();

        CPPUNIT_ASSERT(g->isAlive == false);
        CPPUNIT_ASSERT(g != f);

        delete g;
        delete f;

    }

    void testConwayCellCloneAlive(){
        ConwayCell* f = new ConwayCell();
        f->isAlive = true;
        ConwayCell* g = f->clone();

        CPPUNIT_ASSERT(f->isAlive);
        CPPUNIT_ASSERT(g->isAlive == false);
        CPPUNIT_ASSERT(g != f);

        delete g;
        delete f;

    }

    void testConwayCellCloneMakeAlive(){
        ConwayCell* f = new ConwayCell();
        ConwayCell* g = f->clone();
        g->makeAlive();

        CPPUNIT_ASSERT(g->isAlive);
        CPPUNIT_ASSERT(g != f);

        delete g;
        delete f;

    }

    //////////////////////////////////
    // ConwayCell shouldLive Tests //
    ////////////////////////////////

    void testConwayCellShouldLiveTrue(){
        ConwayCell c;
        CPPUNIT_ASSERT(c.shouldLive(3) == true);

    }

    void testConwayCellShouldLiveFalse(){
        ConwayCell c;
        CPPUNIT_ASSERT(c.shouldLive(4) == false);
    }

    void testConwayCellShouldLiveEdge(){
        ConwayCell c;
        c.isAlive = true;
        CPPUNIT_ASSERT(c.shouldLive(8) == true);
    }

    //////////////////////////////////
    // ConwayCell shouldDie Tests //
    ////////////////////////////////

    void testConwayCellShouldDieTrue(){
        ConwayCell c;
        c.isAlive = true;
        CPPUNIT_ASSERT(c.shouldDie(1) == true);

    }

    void testConwayCellShouldDieFalse(){
        ConwayCell c;
        CPPUNIT_ASSERT(c.shouldDie(3) == false);
    }

    void testConwayCellShouldDieEdge(){
        ConwayCell c;
        c.isAlive = false;
        CPPUNIT_ASSERT(c.shouldLive(8) == true);
    }

    /////////////////////////////
    // Cell Constructor Tests //
    ///////////////////////////

    void testCellConstructor(){
        Cell c(new ConwayCell());
        Cell c2(new ConwayCell());

        CPPUNIT_ASSERT(&c != &c2);
        CPPUNIT_ASSERT( &(c.abstractCell) != &(c2.abstractCell) );

    }

    void testCellConstructorSamePointer(){
        ConwayCell* pointerC = new ConwayCell();
        Cell c(pointerC);
        Cell c2(pointerC);

        CPPUNIT_ASSERT(&c != &c2);
        CPPUNIT_ASSERT( &(c.abstractCell) != &(c2.abstractCell) );

    }

    void testCellConstructorIsDynamic(){
        Cell c(new ConwayCell());
        Cell f(new FredkinCell());

        CPPUNIT_ASSERT(&c != &f);
        CPPUNIT_ASSERT( &(c.abstractCell) != &(f.abstractCell) );
        CPPUNIT_ASSERT(c.abstractCell->isAlive == false);
        CPPUNIT_ASSERT(c.abstractCell->str() == ".");
        CPPUNIT_ASSERT(f.abstractCell->str() == "-");

    }

    //////////////////////////////////
    // Cell Copy Constructor Tests //
    ////////////////////////////////

    void testCellCopyConstructor(){
        Cell c(new ConwayCell());
        Cell c2(c);

        CPPUNIT_ASSERT(&c != &c2);
        CPPUNIT_ASSERT( &(c.abstractCell) != &(c2.abstractCell) );

    }

    void testCellCopyConstructorConwayIsConway(){
        Cell c(new ConwayCell());
        Cell c2(c);

        CPPUNIT_ASSERT(&c != &c2);
        CPPUNIT_ASSERT( &(c.abstractCell) != &(c2.abstractCell) );
        CPPUNIT_ASSERT(c.abstractCell->str() == ".");
        CPPUNIT_ASSERT(c2.abstractCell->str() == ".");

    }

    void testCellCopyConstructorFredkinIsFredkin(){
        Cell c(new FredkinCell());
        Cell c2(c);

        CPPUNIT_ASSERT(&c != &c2);
        CPPUNIT_ASSERT( &(c.abstractCell) != &(c2.abstractCell) );
        CPPUNIT_ASSERT(c.abstractCell->str() == "-");
        CPPUNIT_ASSERT(c2.abstractCell->str() == "-");

    }

    /////////////////
    // Life Tests //
    ////////////////

    void testLifeConstructor(){
        Life<FredkinCell> l(4, 4);

        CPPUNIT_ASSERT(l.cellGrid.size() == 4);
        CPPUNIT_ASSERT(l.cellGrid[0].size() == 4);
    }

    void testLifeConstructorDynamicFredkin(){
        Life<FredkinCell> l(4, 4);
        l.cellGrid[0][0].makeAlive();
        CPPUNIT_ASSERT(l.cellGrid[0][0].str() == "0");
    }

    void testLifeConstructorDynamicConway(){
        Life<ConwayCell> l(4, 4);
        l.cellGrid[0][0].makeAlive();
        CPPUNIT_ASSERT(l.cellGrid[0][0].isAlive);
        CPPUNIT_ASSERT(l.cellGrid[0][0].str() == "*");
    }

    /////////////////////////////////////
    // Life livingOrDeadCellFrom Tests //
    /////////////////////////////////////

    void testLifeLivingOrDeadCellFromWithDeadFredkin(){
        Life<FredkinCell> l(4, 4);
        l.livingOrDeadCellFrom(0,0,'-');
        CPPUNIT_ASSERT(l.cellGrid[0][0].isAlive == false);
        CPPUNIT_ASSERT(l.cellGrid[0][0].str() == "-");
    }
    void testLifeLivingOrDeadCellFromWithLivingFredkin(){
        Life<FredkinCell> l(4, 4);
        l.livingOrDeadCellFrom(0,0,'0');

        CPPUNIT_ASSERT(l.cellGrid[0][0].isAlive == true);
        CPPUNIT_ASSERT(l.cellGrid[0][0].str() == "0");

    }
    void testLifeLivingOrDeadCellFromWithDeadConway(){
        Life<ConwayCell> l(4, 4);
        l.livingOrDeadCellFrom(0,0,'*');

        CPPUNIT_ASSERT(l.cellGrid[0][0].isAlive == true);
        CPPUNIT_ASSERT(l.cellGrid[0][0].str() == "*");

    }
    void testLifeLivingOrDeadCellFromWithLivingConway(){
        Life<ConwayCell> l(4, 4);
        l.livingOrDeadCellFrom(0,0,'.');

        CPPUNIT_ASSERT(l.cellGrid[0][0].isAlive == false);
        CPPUNIT_ASSERT(l.cellGrid[0][0].str() == ".");

    }

    ////////////////////////////
    // Life printBoard Tests //
    //////////////////////////

    void testLifePrintBoard(){
        std::ostringstream stream;
        Life<ConwayCell> l(4, 4);

        l.printBoard(stream, 0);
        CPPUNIT_ASSERT(stream.str() == "Generation = 0 Population = 0\n\n....\n....\n....\n....\n\n");

    }

    void testLifePrintBoardFredkin(){
        std::ostringstream stream;
        Life<ConwayCell> l(4, 4);
        l.livingOrDeadCellFrom(0,0,'9');
        l.printBoard(stream, 0);

        CPPUNIT_ASSERT(stream.str() == "Generation = 0 Population = 1\n\n*...\n....\n....\n....\n\n");

    }

    void testLifePrintBoardConway(){
        std::ostringstream stream;
        Life<FredkinCell> l(4, 4);
        l.livingOrDeadCellFrom(0,0,'0');

        l.printBoard(stream, 0);

        CPPUNIT_ASSERT(stream.str() == "Generation = 0 Population = 1\n\n0---\n----\n----\n----\n\n");

    }

    ////////////////////////////
    // Life saveCells Tests //
    //////////////////////////

    void testLifeSaveCells(){
        Life<FredkinCell> l(2,2);
        FredkinCell c;
        FredkinCell c2;
        c.row = 0;
        c.column = 0;
        c2.row = 0;
        c2.column = 1;
        
        l.cellsToSave.push_back(&c);
        l.cellsToSave.push_back(&c2);
        l.saveCells();

        CPPUNIT_ASSERT(c.isAlive);
        CPPUNIT_ASSERT(c2.isAlive);
    }

    void testLifeSaveCellsAlreadyAlive(){
        Life<FredkinCell> l(2,2);
        FredkinCell c;
        FredkinCell c2;
        c.row = 0;
        c.column = 0;
        c2.row = 0;
        c2.column = 1;
        c.isAlive = true;
        c2.isAlive = true;
        l.cellsToSave.push_back(&c);
        l.cellsToSave.push_back(&c2);
        l.saveCells();

        CPPUNIT_ASSERT(c.isAlive);
        CPPUNIT_ASSERT(c2.isAlive);

    }

    void testLifeSaveCellsOneDead(){
        Life<FredkinCell> l(2,2);
        FredkinCell c;
        FredkinCell c2;
        c.row = 0;
        c.column = 0;
        c2.row = 0;
        c2.column = 1;
        c.isAlive = false;
        c2.isAlive = true;
        l.cellsToSave.push_back(&c);
        l.cellsToSave.push_back(&c2);
        l.saveCells();

        CPPUNIT_ASSERT(c.isAlive);
        CPPUNIT_ASSERT(c2.isAlive);

    }

    ////////////////////////////
    // Life killCells Tests //
    //////////////////////////

    void testLifeKillCells(){
        Life<FredkinCell> l(2,2);
        FredkinCell c;
        FredkinCell c2;
        c.row = 0;
        c.column = 0;
        c2.row = 0;
        c2.column = 1;
        
        l.cellsToKill.push_back(&c);
        l.cellsToKill.push_back(&c2);
        l.killCells();

        CPPUNIT_ASSERT(c.isAlive == false);
        CPPUNIT_ASSERT(c2.isAlive == false);
    }

    void testLifeKillCellsAlreadyAlive(){
        Life<FredkinCell> l(2,2);
        FredkinCell c;
        FredkinCell c2;
        c.row = 0;
        c.column = 0;
        c2.row = 0;
        c2.column = 1;
        c.isAlive = true;
        c2.isAlive = true;
        l.cellsToKill.push_back(&c);
        l.cellsToKill.push_back(&c2);
        l.killCells();

        CPPUNIT_ASSERT(c.isAlive == false);
        CPPUNIT_ASSERT(c2.isAlive == false);

    }

    void testLifeKillCellsOneDead(){
        Life<FredkinCell> l(2,2);
        FredkinCell c;
        FredkinCell c2;
        c.row = 0;
        c.column = 0;
        c2.row = 0;
        c2.column = 1;
        c.isAlive = false;
        c2.isAlive = true;
        l.cellsToKill.push_back(&c);
        l.cellsToKill.push_back(&c2);
        l.killCells();

        CPPUNIT_ASSERT(c.isAlive == false);
        CPPUNIT_ASSERT(c2.isAlive == false);

    }

    ///////////////////////////////////////
    // Life aliveNeighborsForCell Tests //
    /////////////////////////////////////

    void testLifeAliveNeigborsForCellConway(){
        Life<ConwayCell> l(9,9);
        for(int i = 0; i < (int)l.cellGrid.size(); i++){
            for(int j = 0; j < (int)l.cellGrid[i].size(); j++){
                l.cellGrid[i][j].makeAlive();
            }
        }
        int aliveNeighbors = l.aliveNeighborsForCell(3,3);

        CPPUNIT_ASSERT(aliveNeighbors == 8);
    }

    void testLifeAliveNeigborsForCellFredkin(){
        Life<FredkinCell> l(9,9);
        for(int i = 0; i < (int)l.cellGrid.size(); i++){
            for(int j = 0; j < (int)l.cellGrid[i].size(); j++){
                l.cellGrid[i][j].makeAlive();
            }
        }
        int aliveNeighbors = l.aliveNeighborsForCell(3,3);

        CPPUNIT_ASSERT(aliveNeighbors == 4);
    }

    void testLifeAliveNeighborsForCellConwayEdge(){
        Life<ConwayCell> l(9,9);
        for(int i = 0; i < (int)l.cellGrid.size(); i++){
            for(int j = 0; j < (int)l.cellGrid[i].size(); j++){
                l.cellGrid[i][j].makeAlive();
            }
        }
        int aliveNeighbors = l.aliveNeighborsForCell(0,0);

        CPPUNIT_ASSERT(aliveNeighbors == 3);
    }

	CPPUNIT_TEST_SUITE(TestLife);
    /********************
     FredkinCell Tests
    ********************/

    ///////////////////////////////////
    // FredkinCell Constructor Tests //
    //////////////////////////////////
    CPPUNIT_TEST(testConwayConstructor);
    CPPUNIT_TEST(testFredkinConstructorTwice);
    CPPUNIT_TEST(testFredkinConstructorMakesDead);
    ///////////////////////////////////
    // FredkinCell toString Tests //
    //////////////////////////////////
    CPPUNIT_TEST(testFredkinCellToStringAlive);
    CPPUNIT_TEST(testFredkinCellToStringDead);
    CPPUNIT_TEST(testFredkinCellToStringGreaterThan10);
    ////////////////////////////////////
    // FredkinCell makeAlive Tests //
    ///////////////////////////////////
    CPPUNIT_TEST(testFredkinCellMakeAliveFromConstruction);
    CPPUNIT_TEST(testFredkinCellMakeAliveFromAlive);
    CPPUNIT_TEST(testFredkinCellMakeAliveFromDead);
    ////////////////////////////////////
    // FredkinCell kill Tests //
    ///////////////////////////////////
    CPPUNIT_TEST(testFredkinCellKillFromConstruction);
    CPPUNIT_TEST(testFredkinCellKillFromAlive);
    CPPUNIT_TEST(testFredkinCellKillFromDead);
    ////////////////////////////////////
    // FredkinCell incrementAge Tests //
    ///////////////////////////////////
    CPPUNIT_TEST(testFredkinCellIncrementAgeInitial);
    CPPUNIT_TEST(testFredkinCellIncrementAgeDead);
    CPPUNIT_TEST(testFredkinCellIncrementAgeGreaterThan9);
    ////////////////////////////////////
    // FredkinCell << operator Tests //
    ///////////////////////////////////
    CPPUNIT_TEST(testFredkinCellGreaterThanGreaterThanOperatorInitial);
    CPPUNIT_TEST(testFredkinCellGreaterThanGreaterThanOperatorDead);
    CPPUNIT_TEST(testFredkinCellGreaterThanGreaterThanOperatorAlive);
    /////////////////////////////
    // FredkinCell clone Tests //
    ////////////////////////////
    CPPUNIT_TEST(testFredkinCellClone);
    CPPUNIT_TEST(testFredkinCellCloneAlive);
    CPPUNIT_TEST(testFredkinCellCloneOld);
    ///////////////////////////////////
    // FredkinCell shouldLive Tests //
    /////////////////////////////////
    CPPUNIT_TEST(testFredkinCellShouldLiveFalse);
    CPPUNIT_TEST(testFredkinCellShouldLiveTrue);
    CPPUNIT_TEST(testFredkinCellShouldLiveAlreadyAlive);

    /********************
     ConwayCell Tests
    ********************/

    // ConwayCell Constructor Tests //
    //////////////////////////////////
    CPPUNIT_TEST(testConwayConstructor);
    CPPUNIT_TEST(testFredkinConstructorTwice);
    CPPUNIT_TEST(testFredkinConstructorMakesDead);
    ///////////////////////////////////
    // ConwayCell toString Tests //
    //////////////////////////////////
    CPPUNIT_TEST(testConwayCellToStringAlive);
    CPPUNIT_TEST(testConwayCellToStringDead);
    CPPUNIT_TEST(testConwayCellToStringAliveThenDead);
    ////////////////////////////////////
    // ConwayCell makeAlive Tests //
    ///////////////////////////////////
    CPPUNIT_TEST(testConwayCellMakeAliveFromConstruction);
    CPPUNIT_TEST(testConwayCellMakeAliveFromAlive);
    CPPUNIT_TEST(testConwayCellMakeAliveFromDead);
    ////////////////////////////////////
    // ConwayCell kill Tests //
    ///////////////////////////////////
    CPPUNIT_TEST(testConwayCellKillFromConstruction);
    CPPUNIT_TEST(testConwayCellKillFromAlive);
    CPPUNIT_TEST(testConwayCellKillFromDead);
    ///////////////////////////////////
    // ConwayCell << operator Tests //
    /////////////////////////////////
    CPPUNIT_TEST(testConwayCellGreaterThanGreaterThanOperatorInitial);
    CPPUNIT_TEST(testConwayCellGreaterThanGreaterThanOperatorDead);
    CPPUNIT_TEST(testConwayCellGreaterThanGreaterThanOperatorAlive);
    /////////////////////////////
    // ConwayCell clone Tests //
    ////////////////////////////
    CPPUNIT_TEST(testConwayCellClone);
    CPPUNIT_TEST(testConwayCellCloneAlive);
    CPPUNIT_TEST(testConwayCellCloneMakeAlive);
    ///////////////////////////////////
    // ConwayCell shouldLive Tests //
    /////////////////////////////////
    CPPUNIT_TEST(testConwayCellShouldLiveFalse);
    CPPUNIT_TEST(testConwayCellShouldLiveTrue);
    CPPUNIT_TEST(testConwayCellShouldLiveEdge);

    /********************
     Cell Tests
    ********************/
     
     /////////////////////////////
    // Cell Constructor Tests //
    ////////////////////////////
    CPPUNIT_TEST(testCellConstructor);
    CPPUNIT_TEST(testCellConstructorSamePointer);
    CPPUNIT_TEST(testCellConstructorIsDynamic);
    //////////////////////////////////
    // Cell Copy Constructor Tests //
    ////////////////////////////////
    CPPUNIT_TEST(testCellCopyConstructor);
    CPPUNIT_TEST(testCellCopyConstructorConwayIsConway);
    CPPUNIT_TEST(testCellCopyConstructorFredkinIsFredkin);

    /********************
     Life Tests
    ********************/

     ////////////////////////////
    // Life Constructor Tests //
    ///////////////////////////
    CPPUNIT_TEST(testLifeConstructor);
    CPPUNIT_TEST(testLifeConstructorDynamicConway);
    CPPUNIT_TEST(testLifeConstructorDynamicFredkin);
    /////////////////////////////////////
    // Life livingOrDeadCellFrom Tests //
    /////////////////////////////////////
    CPPUNIT_TEST(testLifeLivingOrDeadCellFromWithLivingConway);
    CPPUNIT_TEST(testLifeLivingOrDeadCellFromWithDeadConway);
    CPPUNIT_TEST(testLifeLivingOrDeadCellFromWithDeadFredkin);
    CPPUNIT_TEST(testLifeLivingOrDeadCellFromWithLivingFredkin);
    ////////////////////////////
    // Life printBoard Tests //
    //////////////////////////
    CPPUNIT_TEST(testLifePrintBoard);
    CPPUNIT_TEST(testLifePrintBoardConway);
    CPPUNIT_TEST(testLifePrintBoardFredkin);
    ////////////////////////////
    // Life saveCells Tests //
    //////////////////////////
    CPPUNIT_TEST(testLifeSaveCells);
    CPPUNIT_TEST(testLifeSaveCellsAlreadyAlive);
    CPPUNIT_TEST(testLifeSaveCellsOneDead);
    ///////////////////////////
    // Life killCells Tests //
    /////////////////////////
    CPPUNIT_TEST(testLifeKillCells);
    CPPUNIT_TEST(testLifeKillCellsAlreadyAlive);
    CPPUNIT_TEST(testLifeKillCellsOneDead);
    ///////////////////////////////////////
    // Life aliveNeighborsForCell Tests //
    /////////////////////////////////////
    CPPUNIT_TEST(testLifeAliveNeigborsForCellConway);
    CPPUNIT_TEST(testLifeAliveNeigborsForCellFredkin);
    CPPUNIT_TEST(testLifeAliveNeighborsForCellConwayEdge);


	CPPUNIT_TEST_SUITE_END();
};

	int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}