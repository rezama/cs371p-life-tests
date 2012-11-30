
/**
To test the program:
g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
valgrind TestLife.app >& TestLife.out
vi TestLife.out

 */
 
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include <exception>
#include "Life.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"

struct TestLife : CppUnit::TestFixture {

    void testChangeGenerationConwayAliveToDead()
    {
        ConwayCell c(true);
        c.changeGeneration(1);
        
        CPPUNIT_ASSERT(c.isAlive() == false);
    }
    
    void testChangeGenerationConwayAliveToAlive()
    {
        ConwayCell c(true);
        c.changeGeneration(2);
        
        CPPUNIT_ASSERT(c.isAlive() == true);    
    }
    
    void testChangeGenerationConwayDeadToDead()
    {
        ConwayCell c(false);
        c.changeGeneration(1);
        
        CPPUNIT_ASSERT(c.isAlive() == false);    
    }
    
    void testChangeGenerationConwayDeadToAlive()
    {
        ConwayCell c(false);
        c.changeGeneration(3);
        
        CPPUNIT_ASSERT(c.isAlive() == true);    
    }
    
    void testChangeGenerationFredkinAliveToDead()
    {
        FredkinCell c(true,0);
        c.changeGeneration(0);
        
        CPPUNIT_ASSERT(c.isAlive() == false);
    }
    
    void testChangeGenerationFredkinAliveToAlive()
    {
        FredkinCell c(true,0);
        c.changeGeneration(1);
        
        CPPUNIT_ASSERT(c.isAlive() == true);    
    }
    
    void testChangeGenerationFredkinDeadToDead()
    {
        FredkinCell c(false,0);
        c.changeGeneration(2);
        
        CPPUNIT_ASSERT(c.isAlive() == false);    
    }
    
    void testChangeGenerationFredkinDeadToAlive()
    {
        FredkinCell c(false,0);
        c.changeGeneration(1);
        
        CPPUNIT_ASSERT(c.isAlive() == true);    
    }
    
    void testChangeGenerationCellFredkinToConway()
    {
        Cell c(new FredkinCell(true,1));
        c.changeGeneration(1);
        
        CPPUNIT_ASSERT(c.isAlive() == true);    
        CPPUNIT_ASSERT(c.getSymbol() == '*');   
    }
    
    void testBecomeAliveCellConway()
    {
        Cell c(new ConwayCell(false));
        c.becomeAlive();
        
        CPPUNIT_ASSERT(c.isAlive() == true);
    }
    
    void testBecomeDeadCellConway()
    {
        Cell c(new ConwayCell(true));
        c.becomeDead();
        
        CPPUNIT_ASSERT(c.isAlive() == false);
    }
    
    void testBecomeAliveCellFredkin()
    {
        Cell c(new FredkinCell(false,0));
        c.becomeAlive();
        
        CPPUNIT_ASSERT(c.isAlive() == true);
    }
    
    void testBecomeDeadCellFredkin()
    {
        Cell c(new FredkinCell(true,0));
        c.becomeDead();
        
        CPPUNIT_ASSERT(c.isAlive() == false);
    }
    
    void testLifeGetPopulation()
    {
        Life<ConwayCell> l(5,5);
        ConwayCell c(true);
        l.put(c,2,2);
        
        CPPUNIT_ASSERT(l.getPopulation() == 1);
    }
    
    void testLifeGetPopulationMixed()
    {
        Life<Cell> l(2,2, Cell(new FredkinCell(false,0)));
        l._cells[1][1].becomeAlive();
        CPPUNIT_ASSERT(l.getPopulation() == 1);
    }
	
	void testCanSeeConway()
	{
		ConwayCell c(true);
		CPPUNIT_ASSERT(c.canSee(0));
		CPPUNIT_ASSERT(c.canSee(1));
		CPPUNIT_ASSERT(c.canSee(2));
		CPPUNIT_ASSERT(c.canSee(3));
		CPPUNIT_ASSERT(c.canSee(4));
		CPPUNIT_ASSERT(c.canSee(5));
		CPPUNIT_ASSERT(c.canSee(6));
		CPPUNIT_ASSERT(c.canSee(7));
		
	}
	
	void testCanSeeFredkin()
	{
		FredkinCell c(true,0);
		CPPUNIT_ASSERT(c.canSee(0));
		CPPUNIT_ASSERT(!c.canSee(1));
		CPPUNIT_ASSERT(c.canSee(2));
		CPPUNIT_ASSERT(!c.canSee(3));
		CPPUNIT_ASSERT(c.canSee(4));
		CPPUNIT_ASSERT(!c.canSee(5));
		CPPUNIT_ASSERT(c.canSee(6));
		CPPUNIT_ASSERT(!c.canSee(7));
		
	}
	
	void testCanSeeCellConway()
	{
		Cell c (new ConwayCell(true));
		CPPUNIT_ASSERT(c.canSee(0));
		CPPUNIT_ASSERT(c.canSee(1));
		CPPUNIT_ASSERT(c.canSee(2));
		CPPUNIT_ASSERT(c.canSee(3));
		CPPUNIT_ASSERT(c.canSee(4));
		CPPUNIT_ASSERT(c.canSee(5));
		CPPUNIT_ASSERT(c.canSee(6));
		CPPUNIT_ASSERT(c.canSee(7));
		
	}
	
	void testCanSeeCellFredkin()
	{
		Cell c (new FredkinCell(true,0));
		CPPUNIT_ASSERT(c.canSee(0));
		CPPUNIT_ASSERT(!c.canSee(1));
		CPPUNIT_ASSERT(c.canSee(2));
		CPPUNIT_ASSERT(!c.canSee(3));
		CPPUNIT_ASSERT(c.canSee(4));
		CPPUNIT_ASSERT(!c.canSee(5));
		CPPUNIT_ASSERT(c.canSee(6));
		CPPUNIT_ASSERT(!c.canSee(7));
		
	}

    CPPUNIT_TEST_SUITE(TestLife);
        CPPUNIT_TEST(testChangeGenerationConwayAliveToDead);
        CPPUNIT_TEST(testChangeGenerationConwayAliveToAlive);
        CPPUNIT_TEST(testChangeGenerationConwayDeadToDead);
        CPPUNIT_TEST(testChangeGenerationConwayDeadToAlive);
        CPPUNIT_TEST(testChangeGenerationFredkinAliveToDead);
        CPPUNIT_TEST(testChangeGenerationFredkinAliveToAlive);
        CPPUNIT_TEST(testChangeGenerationFredkinDeadToDead);
        CPPUNIT_TEST(testChangeGenerationFredkinDeadToAlive);
        CPPUNIT_TEST(testChangeGenerationCellFredkinToConway);
        CPPUNIT_TEST(testBecomeAliveCellConway);
        CPPUNIT_TEST(testBecomeDeadCellConway);
        CPPUNIT_TEST(testBecomeAliveCellFredkin);
        CPPUNIT_TEST(testBecomeDeadCellFredkin);
        
        CPPUNIT_TEST(testLifeGetPopulation);
        CPPUNIT_TEST(testLifeGetPopulationMixed);
		
		CPPUNIT_TEST(testCanSeeConway);
		CPPUNIT_TEST(testCanSeeFredkin);
		CPPUNIT_TEST(testCanSeeCellConway);
		CPPUNIT_TEST(testCanSeeCellFredkin);
		
		
    CPPUNIT_TEST_SUITE_END();

};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}