#define private public
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#include <iostream>
#include <stdlib.h>

#ifndef CC_DEF
#define CC_DEF
#include "ConwayCell.h"
#endif

#ifndef FC_DEF
#define FC_DEF
#include "FredkinCell.h"
#endif


#ifndef CELL_DEF
#define CELL_DEF
#include "Cell.h"
#endif


#ifndef LIFE_DEF
#define LIFE_DEF
#include "Life.h"
#endif


struct TestLife : CppUnit::TestFixture {

	////////////////
	// ConwayCell //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// -----------
	// Constructor
	// -----------
	void test_cc_constructor1()
	{
		ConwayCell cc;
		CPPUNIT_ASSERT(cc.getSign() == '.');
	}
	
	void test_cc_constructor2()
	{
		ConwayCell cc;
		CPPUNIT_ASSERT(!cc.isAlive());
	}
	
	void test_cc_constructor3()
	{
		ConwayCell cc;
		CPPUNIT_ASSERT(cc.getSign() == '.');
		CPPUNIT_ASSERT(!cc.isAlive());
	}
	
	// -----------------
	// input_constructor
	// -----------------
	void test_cc_input_constructor1()
	{
		ConwayCell cc('.');
		CPPUNIT_ASSERT(cc.getSign() == '.');
		CPPUNIT_ASSERT(!cc.isAlive());
	}
	
	void test_cc_input_constructor2()
	{
		ConwayCell cc('D');
		CPPUNIT_ASSERT(cc.getSign() == 'D');
		CPPUNIT_ASSERT(cc.isAlive());
	}
	
	void test_cc_input_constructor3()
	{
		ConwayCell cc('*');
		CPPUNIT_ASSERT(cc.getSign() == '*');
		CPPUNIT_ASSERT(cc.isAlive());
	}

	// -------
	// getSign
	// -------
	void test_cc_getSign1()
	{
		ConwayCell cc('.');
		CPPUNIT_ASSERT(cc.getSign() == '.');
	}
	
	void test_cc_getSign2()
	{
		ConwayCell cc;
		CPPUNIT_ASSERT(cc.getSign() == '.');
	}
	
	void test_cc_getSign3()
	{
		ConwayCell cc('*');
		CPPUNIT_ASSERT(cc.getSign() == '*');
	}
	
	// ------------
	// getNextState
	// ------------
	void test_cc_getNextState1()
	{
		ConwayCell cc('.');
		CPPUNIT_ASSERT(cc.getNextState() == false);
	}
	
	void test_cc_getNextState2()
	{
		ConwayCell cc('*');
		CPPUNIT_ASSERT(cc.getNextState() == true);
	}
	
	void test_cc_getNextState3()
	{
		ConwayCell cc;
		CPPUNIT_ASSERT(cc.getNextState() == false);
	}
	
	// -------
	// isAlive
	// -------
	void test_cc_isAlive1()
	{
		ConwayCell cc('*');
		CPPUNIT_ASSERT(cc.isAlive());	
	}
	
	void test_cc_isAlive2()
	{
		ConwayCell cc('D');
		CPPUNIT_ASSERT(cc.isAlive());
	}
	
	void test_cc_isAlive3()
	{
		ConwayCell cc;
		CPPUNIT_ASSERT(!cc.isAlive());
	}
	
	// -----
	// clone
	// -----
	void test_cc_clone1()
	{
		ConwayCell cc1('*');
		ConwayCell* cc2 = cc1.clone();
		CPPUNIT_ASSERT(&cc1 != cc2);
		CPPUNIT_ASSERT(cc2->isAlive());
		CPPUNIT_ASSERT(cc2->getSign() == '*');
	}
	
	void test_cc_clone2()
	{
		ConwayCell cc1('*');
		ConwayCell* cc2 = cc1.clone();
		ConwayCell* cc3 = cc2->clone();
		CPPUNIT_ASSERT(&cc1 != cc3);
		CPPUNIT_ASSERT(cc3->isAlive());
		CPPUNIT_ASSERT(cc3->getSign() == '*');
	}
	
	void test_cc_clone3()
	{
		ConwayCell cc1('.');
		ConwayCell* cc2 = cc1.clone();
		CPPUNIT_ASSERT(&cc1 != cc2);
		CPPUNIT_ASSERT(!cc2->isAlive());
		CPPUNIT_ASSERT(cc2->getSign() == '.');
	}
	
	// -----------
	// update_cell
	// -----------
	void test_cc_update_cell1()
	{
		ConwayCell cc1('*');
		cc1.nextState = false;
		cc1.nextSign = '.';
		cc1.update_cell();
		CPPUNIT_ASSERT(!cc1.isAlive());
		CPPUNIT_ASSERT(cc1.getSign() == '.');
	}
	
	void test_cc_update_cell2()
	{
		ConwayCell cc1('*');
		cc1.nextState = true;
		cc1.nextSign = 'F';
		cc1.update_cell();
		CPPUNIT_ASSERT(cc1.isAlive());
		CPPUNIT_ASSERT(cc1.getSign() == 'F');
	}
	
	void test_cc_update_cell3()
	{
		ConwayCell cc1('*');
		cc1.nextState = true;
		cc1.nextSign = '*';
		cc1.update_cell();
		CPPUNIT_ASSERT(cc1.isAlive());
		CPPUNIT_ASSERT(cc1.getSign() == '*');
	}
	
	// -------------------
	// determine_nextState
	// -------------------
	void test_cc_determine_nextState1()
	{
		istringstream in("*.*\n.*.\n*.*\n");
		Life<ConwayCell> grid(3, 3, in);
		
		ConwayCell cc1 = grid.display_grid[1][0];
		CPPUNIT_ASSERT(!cc1.isAlive());
		CPPUNIT_ASSERT(cc1.getSign() == '.');
		cc1.determine_nextState(1, 0, grid.display_grid);	
		CPPUNIT_ASSERT(cc1.nextState);
		CPPUNIT_ASSERT(cc1.nextSign == '*');
	}
	
	void test_cc_determine_nextState2()
	{
		istringstream in("*.*\n.*.\n*.*\n");
		Life<ConwayCell> grid(3, 3, in);
		
		ConwayCell cc1 = grid.display_grid[1][1];
		CPPUNIT_ASSERT(cc1.isAlive());
		cc1.determine_nextState(1, 1, grid.display_grid);
		CPPUNIT_ASSERT(!cc1.nextState);
	}
	
	void test_cc_determine_nextState3()
	{
		istringstream in("*.*\n.*.\n***\n");
		Life<ConwayCell> grid(3, 3, in);
		
		ConwayCell cc1 = grid.display_grid[2][1];
		CPPUNIT_ASSERT(cc1.isAlive());
		cc1.determine_nextState(2, 1, grid.display_grid);
		CPPUNIT_ASSERT(cc1.nextState);
	}
	
	void test_cc_determine_nextState4()
	{
		istringstream in("*.*\n.*.\n***\n");
		Life<ConwayCell> grid(3, 3, in);
		
		ConwayCell cc1 = grid.display_grid[1][0];
		CPPUNIT_ASSERT(!cc1.isAlive());
		cc1.determine_nextState(1, 0, grid.display_grid);
		CPPUNIT_ASSERT(!cc1.nextState);
	}
	
	
	/////////////////
	// FredkinCell //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// -----------
	// Constructor
	// -----------
	void test_fc_constructor1()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(fc.getSign() == '-');
	}
	
	void test_fc_constructor2()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(!fc.isAlive());
	}
	
	void test_fc_constructor3()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(fc.age == -1);
	}
	
	// -----------------
	// input_constructor
	// -----------------
	void test_fc_input_constructor1()
	{
		FredkinCell fc('0');
		CPPUNIT_ASSERT(fc.getSign() == '0');
		CPPUNIT_ASSERT(fc.age == 0);
		CPPUNIT_ASSERT(fc.isAlive());
	}
	
	void test_fc_input_constructor2()
	{
		FredkinCell fc('5');
		CPPUNIT_ASSERT(fc.getSign() == '5');
		CPPUNIT_ASSERT(fc.age == 5);
		CPPUNIT_ASSERT(fc.isAlive());
	}
	
	void test_fc_input_constructor3()
	{
		FredkinCell fc('-');
		CPPUNIT_ASSERT(fc.getSign() == '-');
		CPPUNIT_ASSERT(fc.age == -1);
		CPPUNIT_ASSERT(!fc.isAlive());
	}
	
	// -------
	// getSign
	// -------
	void test_fc_getSign1()
	{
		FredkinCell fc('-');
		CPPUNIT_ASSERT(fc.getSign() == '-');
	}
	
	void test_fc_getSign2()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(fc.getSign() == '-');
	}
	
	void test_fc_getSign3()
	{
		FredkinCell fc('6');
		CPPUNIT_ASSERT(fc.getSign() == '6');
	}
	
	// ------------
	// getNextState
	// ------------
	void test_fc_getNextState1()
	{
		FredkinCell fc('-');
		CPPUNIT_ASSERT(fc.getNextState() == false);
	}
	
	void test_fc_getNextState2()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(fc.getNextState() == false);
	}
	
	void test_fc_getNextState3()
	{
		FredkinCell fc('6');
		CPPUNIT_ASSERT(fc.getNextState() == true);
	}
	
	// -------
	// isAlive
	// -------
	void test_fc_isAlive1()
	{
		FredkinCell fc('0');
		CPPUNIT_ASSERT(fc.isAlive());	
	}
	
	void test_fc_isAlive2()
	{
		FredkinCell fc('9');
		CPPUNIT_ASSERT(fc.isAlive());
	}
	
	void test_fc_isAlive3()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(!fc.isAlive());
	}
	
	// ------
	// getAge
	// ------
	void test_fc_getAge1()
	{
		FredkinCell fc;
		CPPUNIT_ASSERT(fc.getAge() == -1);
	}
	
	void test_fc_getAge2()
	{
		FredkinCell fc('9');
		CPPUNIT_ASSERT(fc.getAge() == 9);
	}
	
	void test_fc_getAge3()
	{
		FredkinCell fc('3');
		CPPUNIT_ASSERT(fc.getAge() == 3);
	}
	
	// -----
	// clone
	// -----
	void test_fc_clone1()
	{
		FredkinCell fc1('0');
		FredkinCell* fc2 = fc1.clone();
		CPPUNIT_ASSERT(&fc1 != fc2);
		CPPUNIT_ASSERT(fc2->isAlive());
		CPPUNIT_ASSERT(fc2->getSign() == '0');
		CPPUNIT_ASSERT(fc2->age == 0);
	}
	
	void test_fc_clone2()
	{	
		FredkinCell fc1('0');
		FredkinCell* fc2 = fc1.clone();
		FredkinCell* fc3 = fc2->clone();
		CPPUNIT_ASSERT(&fc1 != fc3);
		CPPUNIT_ASSERT(fc3->isAlive());
		CPPUNIT_ASSERT(fc3->getSign() == '0');
		CPPUNIT_ASSERT(fc3->age == 0);
	}
	
	void test_fc_clone3()
	{
		FredkinCell fc1('-');
		FredkinCell* fc2 = fc1.clone();
		CPPUNIT_ASSERT(&fc1 != fc2);
		CPPUNIT_ASSERT(!fc2->isAlive());
		CPPUNIT_ASSERT(fc2->getSign() == '-');
		CPPUNIT_ASSERT(fc2->age == -1);
	}
	
	// -----------
	// update_cell
	// -----------
	void test_fc_update_cell1()
	{
		FredkinCell fc1('-');
		fc1.nextState = true;
		fc1.nextSign = '9';
		fc1.update_cell();
		CPPUNIT_ASSERT(fc1.isAlive());
		CPPUNIT_ASSERT(fc1.getSign() == '9');
	}
	
	void test_fc_update_cell2()
	{
		FredkinCell fc1('9');
		fc1.nextState = false;
		fc1.nextSign = '-';
		fc1.update_cell();
		CPPUNIT_ASSERT(!fc1.isAlive());
		CPPUNIT_ASSERT(fc1.getSign() == '-');
	}
	
	void test_fc_update_cell3()
	{
		FredkinCell fc1('8');
		fc1.nextState = true;
		fc1.nextSign = '9';
		fc1.update_cell();
		CPPUNIT_ASSERT(fc1.isAlive());
		CPPUNIT_ASSERT(fc1.getSign() == '9');
	}
	
	// -------------------
	// determine_nextState
	// -------------------
	void test_fc_determine_nextState1()
	{
		istringstream in("0-0\n-0-\n0-0\n");
		Life<FredkinCell> grid(3, 3, in);
		
		FredkinCell fc1 = grid.display_grid[1][0];
		CPPUNIT_ASSERT(!fc1.isAlive());
		CPPUNIT_ASSERT(fc1.getSign() == '-');
		fc1.determine_nextState(1, 0, grid.display_grid);	
		CPPUNIT_ASSERT(fc1.nextState);
		CPPUNIT_ASSERT(fc1.nextSign == '0');
	}
	
	void test_fc_determine_nextState2()
	{
		istringstream in("0-0\n-0-\n0-0\n");
		Life<FredkinCell> grid(3, 3, in);
		
		FredkinCell fc1 = grid.display_grid[1][1];
		CPPUNIT_ASSERT(fc1.isAlive());
		fc1.determine_nextState(1, 1, grid.display_grid);
		CPPUNIT_ASSERT(!fc1.nextState);
		CPPUNIT_ASSERT(fc1.nextSign == '-');
	}
	
	void test_fc_determine_nextState3()
	{
		istringstream in("0-0\n-0-\n000\n");
		Life<FredkinCell> grid(3, 3, in);
		
		FredkinCell fc1 = grid.display_grid[2][1];
		CPPUNIT_ASSERT(fc1.isAlive());
		fc1.determine_nextState(2, 1, grid.display_grid);
		CPPUNIT_ASSERT(fc1.nextState);
		CPPUNIT_ASSERT(fc1.nextSign == '1');
	}
	
	void test_fc_determine_nextState4()
	{
		istringstream in("0-0\n---\n0-0\n");
		Life<FredkinCell> grid(3, 3, in);
		
		FredkinCell fc1 = grid.display_grid[1][0];
		CPPUNIT_ASSERT(!fc1.isAlive());
		fc1.determine_nextState(1, 0, grid.display_grid);
		CPPUNIT_ASSERT(!fc1.nextState);
	}
	
	//////////////////
	//     Cell     //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// -----------------
	// input_constructor
	// -----------------
	void test_cell_input_constructor1()
	{
		Cell c('0');
		CPPUNIT_ASSERT(c.getSign() == '0');
		CPPUNIT_ASSERT(c.getAge() == 0);
		CPPUNIT_ASSERT(c.isAlive());
	}
	
	void test_cell_input_constructor2()
	{
		Cell c('*');
		CPPUNIT_ASSERT(c.getSign() == '*');
		CPPUNIT_ASSERT(c.getAge() == -2);
		CPPUNIT_ASSERT(c.isAlive());
	}
	
	void test_cell_input_constructor3()
	{
		Cell c('-');
		CPPUNIT_ASSERT(c.getSign() == '-');
		CPPUNIT_ASSERT(c.getAge() == -1);
		CPPUNIT_ASSERT(!c.isAlive());
	}
	
	// ----------------
	// copy_constructor
	// ----------------
	void test_cell_copy_constructor1()
	{
		Cell c('0');
		Cell c2 = c;
		CPPUNIT_ASSERT(&c2 != &c);
		CPPUNIT_ASSERT(c2.handle != c.handle);
		CPPUNIT_ASSERT(c2.getSign() == c.getSign());
		CPPUNIT_ASSERT(c2.getAge() == c.getAge());
		CPPUNIT_ASSERT(c2.isAlive() == c.isAlive());
	}
	
	void test_cell_copy_constructor2()
	{
		Cell c('*');
		Cell c2 = c;
		CPPUNIT_ASSERT(&c2 != &c);
		CPPUNIT_ASSERT(c2.handle != c.handle);
		CPPUNIT_ASSERT(c2.getSign() == c.getSign());
		CPPUNIT_ASSERT(c2.getAge() == c.getAge());
		CPPUNIT_ASSERT(c2.isAlive() == c.isAlive());
	}
	
	void test_cell_copy_constructor3()
	{
		Cell c('.');
		Cell c2 = c;
		CPPUNIT_ASSERT(&c2 != &c);
		CPPUNIT_ASSERT(c2.handle != c.handle);
		CPPUNIT_ASSERT(c2.getSign() == c.getSign());
		CPPUNIT_ASSERT(c2.getAge() == c.getAge());
		CPPUNIT_ASSERT(c2.isAlive() == c.isAlive());
	}
	
	// -------
	// getSign
	// -------
	void test_cell_getSign1()
	{
		Cell c('*');
		CPPUNIT_ASSERT(c.getSign() == '*');
	}
	
	void test_cell_getSign2()
	{
		Cell c('-');
		CPPUNIT_ASSERT(c.getSign() == '-');
	}
	
	void test_cell_getSign3()
	{
		Cell c('6');
		CPPUNIT_ASSERT(c.getSign() == '6');
	}
	
	// ------------
	// getNextState
	// ------------
	void test_cell_getNextState1()
	{
		Cell c('*');
		CPPUNIT_ASSERT(c.getNextState() == true);
	}
	
	void test_cell_getNextState2()
	{
		Cell c('-');
		CPPUNIT_ASSERT(c.getNextState() == false);
	}
	
	void test_cell_getNextState3()
	{
		Cell c('6');
		CPPUNIT_ASSERT(c.getNextState() == true);
	}
	
	// -------
	// isAlive
	// -------
	void test_cell_isAlive1()
	{
		Cell c('0');
		CPPUNIT_ASSERT(c.isAlive());	
	}
	
	void test_cell_isAlive2()
	{
		Cell c('*');
		CPPUNIT_ASSERT(c.isAlive());
	}
	
	void test_cell_isAlive3()
	{
		Cell c('.');
		CPPUNIT_ASSERT(!c.isAlive());
	}
	
	// ------
	// getAge
	// ------
	void test_cell_getAge1()
	{
		Cell c('-');
		CPPUNIT_ASSERT(c.getAge() == -1);
	}
	
	void test_cell_getAge2()
	{
		Cell c('.');
		CPPUNIT_ASSERT(c.getAge() == -2);
	}
	
	void test_cell_getAge3()
	{
		Cell c('3');
		CPPUNIT_ASSERT(c.getAge() == 3);
	}
	
	// -----------------
	// fredkin_to_conway
	// -----------------
	void test_cell_fredkin_to_conway1()
	{
		Cell c1('-');
		c1.fredkin_to_conway();
		CPPUNIT_ASSERT(c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '*');
		CPPUNIT_ASSERT(c1.getAge() == -2);
	}
	
	void test_cell_fredkin_to_conway2()
	{
		Cell c1('+');
		c1.fredkin_to_conway();
		CPPUNIT_ASSERT(c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '*');
		CPPUNIT_ASSERT(c1.getAge() == -2);
	}
	
	void test_cell_fredkin_to_conway3()
	{
		Cell c1('9');
		c1.fredkin_to_conway();
		CPPUNIT_ASSERT(c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '*');
		CPPUNIT_ASSERT(c1.getAge() == -2);
	}
	
	// -----------
	// update_cell
	// -----------
	void test_cell_update_cell1()
	{
		Cell c1('*');
		c1.handle->nextState = true;
		c1.handle->nextSign = '*';
		c1.update_cell();
		CPPUNIT_ASSERT(c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '*');
	}
	
	void test_cell_update_cell2()
	{
		Cell c1('9');
		c1.handle->nextState = false;
		c1.handle->nextSign = '-';
		c1.update_cell();
		CPPUNIT_ASSERT(!c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '-');
	}
	
	void test_cell_update_cell3()
	{
		Cell c1('-');
		c1.handle->nextState = true;
		c1.handle->nextSign = '9';
		c1.update_cell();
		CPPUNIT_ASSERT(c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '9');
	}
	
	// -------------------
	// determine_nextState
	// -------------------
	void test_cell_determine_nextState1()
	{
		istringstream in("0-0\n-0-\n0-0\n");
		Life<Cell> grid(3, 3, in);
		
		Cell c1 = grid.display_grid[1][0];
		CPPUNIT_ASSERT(!c1.isAlive());
		CPPUNIT_ASSERT(c1.getSign() == '-');
		c1.determine_nextState(1, 0, grid.display_grid);	
		CPPUNIT_ASSERT(c1.getNextState());
		CPPUNIT_ASSERT(c1.handle->nextSign == '0');
	}
	
	void test_cell_determine_nextState2()
	{
		istringstream in("*-*\n-0-\n*-*\n");
		Life<Cell> grid(3, 3, in);
		
		Cell c1 = grid.display_grid[1][1];
		CPPUNIT_ASSERT(c1.isAlive());
		c1.determine_nextState(1, 1, grid.display_grid);
		CPPUNIT_ASSERT(!c1.getNextState());
		CPPUNIT_ASSERT(c1.handle->nextSign == '-');
	}
	
	void test_cell_determine_nextState3()
	{
		istringstream in("0-0\n-0-\n0*0\n");
		Life<Cell> grid(3, 3, in);
		
		Cell c1 = grid.display_grid[2][1];
		CPPUNIT_ASSERT(c1.isAlive());
		c1.determine_nextState(2, 1, grid.display_grid);
		CPPUNIT_ASSERT(c1.getNextState());
		CPPUNIT_ASSERT(c1.handle->nextSign == '*');
	}
	
	void test_cell_determine_nextState4()
	{
		istringstream in("*-0\n---\n*-0\n");
		Life<Cell> grid(3, 3, in);
		
		Cell c1 = grid.display_grid[1][0];
		CPPUNIT_ASSERT(!c1.isAlive());
		c1.determine_nextState(1, 0, grid.display_grid);
		CPPUNIT_ASSERT(!c1.getNextState());
	}
	
	////////////////
	//    Life    //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// -----------
	// Constructor
	// -----------
	void test_life_constructor1()
	{
		//create the input stream to pass to the constructor
		istringstream in("*.\n.*");
		Life<ConwayCell> grid(2, 2, in);
		
		CPPUNIT_ASSERT(grid.display_grid[0][0].getSign() == '*');
		CPPUNIT_ASSERT(grid.display_grid[0][1].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[1][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[1][1].getSign() == '*');
	}
	
	void test_life_constructor2()
	{
		//create the input stream to pass to the constructor
		istringstream in(".\n.\n.\n.\n.\n.\n.\n.\n.\n.\n");
		Life<ConwayCell> grid(10, 1, in);
		
		CPPUNIT_ASSERT(grid.display_grid[0][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[1][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[2][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[3][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[4][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[5][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[6][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[7][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[8][0].getSign() == '.');
		CPPUNIT_ASSERT(grid.display_grid[9][0].getSign() == '.');
	}
	
	void test_life_constructor3()
	{
		//create the input stream to pass to the constructor
		istringstream in("*.*\n.*.\n***\n");
		Life<ConwayCell> grid(3, 3, in);
		
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive());
		CPPUNIT_ASSERT(!grid.display_grid[0][1].isAlive());
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive());
		CPPUNIT_ASSERT(grid.display_grid[1][1].getSign() == '*');
		CPPUNIT_ASSERT(!grid.display_grid[1][2].isAlive());
		CPPUNIT_ASSERT(grid.display_grid[1][2].getSign() == '.');
	}
	
	// ----------
	// print_grid
	// ----------
	void test_life_print_grid1()
	{
		//create the input stream to pass to the constructor
		istringstream in("*.*\n.*.\n***\n");
		Life<ConwayCell> grid(3, 3, in);
		grid.print_grid();
	}
	
	void test_life_print_grid2()
	{
		//create the input stream to pass to the constructor
		istringstream in("*\n");
		Life<ConwayCell> grid(1, 1, in);
		grid.print_grid();
	}
	
	void test_life_print_grid3()
	{
		//create the input stream to pass to the constructor
		ifstream in("RunLifeConway.in", ifstream::in);
		char inputLine[10];
		in.getline(inputLine, 10);
		int rows = atoi(inputLine);
		in.getline(inputLine, 10);
		int cols = atoi(inputLine);
		Life<ConwayCell> grid(rows, cols, in);
		grid.print_grid();
	}
	
	// ---------
	// take_turn
	// ---------
	void test_life_take_turn1()
	{
		istringstream in("*.*\n.*.\n***\n");
		Life<ConwayCell> grid(3, 3, in);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 1);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == true);
	}
	
	void test_life_take_turn2()
	{
		istringstream in("*.*\n.*.\n***\n");
		Life<ConwayCell> grid(3, 3, in);
		grid.take_turn();
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 2);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == false);
	}
	
	void test_life_take_turn3()
	{
		istringstream in("*\n");
		Life<ConwayCell> grid(1, 1, in);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == true);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.generation == 5);
	}
	
	void test_life_take_turn4()
	{
		istringstream in("0-0\n-0-\n000\n");
		Life<FredkinCell> grid(3, 3, in);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 1);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == true);
	}
	
	void test_life_take_turn5()
	{
		istringstream in("0-0\n-0-\n000\n");
		Life<FredkinCell> grid(3, 3, in);
		grid.take_turn();
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 2);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == false);
	}
	
	void test_life_take_turn6()
	{
		istringstream in("0*0\n-*.\n0*0\n");
		Life<Cell> grid(3, 3, in);
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 1);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == true);
	}
	
	void test_life_take_turn7()
	{
		istringstream in("0*0\n-*.\n0*0\n");
		Life<Cell> grid(3, 3, in);
		grid.take_turn();
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 2);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == true);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == true);
	}
	
	void test_life_take_turn8()
	{
		istringstream in("---\n-0-\n---\n");
		Life<FredkinCell> grid(3, 3, in);
		grid.take_turn();
		grid.take_turn();
		grid.take_turn();
		grid.take_turn();
		CPPUNIT_ASSERT(grid.generation == 4);
		CPPUNIT_ASSERT(grid.display_grid[0][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[0][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[1][2].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][0].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][1].isAlive() == false);
		CPPUNIT_ASSERT(grid.display_grid[2][2].isAlive() == false);
	}

	// -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
    
    CPPUNIT_TEST(test_cc_constructor1);
    CPPUNIT_TEST(test_cc_constructor2);
    CPPUNIT_TEST(test_cc_constructor3);
    CPPUNIT_TEST(test_cc_input_constructor1);
    CPPUNIT_TEST(test_cc_input_constructor2);
    CPPUNIT_TEST(test_cc_input_constructor3);
    CPPUNIT_TEST(test_cc_getSign1);
    CPPUNIT_TEST(test_cc_getSign2);
    CPPUNIT_TEST(test_cc_getSign3);
    CPPUNIT_TEST(test_cc_getNextState1);
    CPPUNIT_TEST(test_cc_getNextState2);
    CPPUNIT_TEST(test_cc_getNextState3);
    CPPUNIT_TEST(test_cc_isAlive1);
    CPPUNIT_TEST(test_cc_isAlive2);
    CPPUNIT_TEST(test_cc_isAlive3);
    CPPUNIT_TEST(test_cc_clone1);
    CPPUNIT_TEST(test_cc_clone2);
    CPPUNIT_TEST(test_cc_clone3);
    CPPUNIT_TEST(test_cc_update_cell1);
    CPPUNIT_TEST(test_cc_update_cell2);
    CPPUNIT_TEST(test_cc_update_cell3);
    CPPUNIT_TEST(test_cc_determine_nextState1);
    CPPUNIT_TEST(test_cc_determine_nextState2);
    CPPUNIT_TEST(test_cc_determine_nextState3);
    CPPUNIT_TEST(test_cc_determine_nextState4);
    
    
    CPPUNIT_TEST(test_fc_constructor1);
    CPPUNIT_TEST(test_fc_constructor2);
    CPPUNIT_TEST(test_fc_constructor3);
    CPPUNIT_TEST(test_fc_input_constructor1);
    CPPUNIT_TEST(test_fc_input_constructor2);
    CPPUNIT_TEST(test_fc_input_constructor3);
    CPPUNIT_TEST(test_fc_getSign1);
    CPPUNIT_TEST(test_fc_getSign2);
    CPPUNIT_TEST(test_fc_getSign3);
    CPPUNIT_TEST(test_fc_getNextState1);
    CPPUNIT_TEST(test_fc_getNextState2);
    CPPUNIT_TEST(test_fc_getNextState3);
    CPPUNIT_TEST(test_fc_isAlive1);
    CPPUNIT_TEST(test_fc_isAlive2);
    CPPUNIT_TEST(test_fc_isAlive3);
    CPPUNIT_TEST(test_fc_getAge1);
    CPPUNIT_TEST(test_fc_getAge2);
    CPPUNIT_TEST(test_fc_getAge3);
    CPPUNIT_TEST(test_fc_clone1);
    CPPUNIT_TEST(test_fc_clone2);
    CPPUNIT_TEST(test_fc_clone3);
    CPPUNIT_TEST(test_fc_update_cell1);
    CPPUNIT_TEST(test_fc_update_cell2);
    CPPUNIT_TEST(test_fc_update_cell3);
    CPPUNIT_TEST(test_fc_determine_nextState1);
    CPPUNIT_TEST(test_fc_determine_nextState2);
    CPPUNIT_TEST(test_fc_determine_nextState3);
    CPPUNIT_TEST(test_fc_determine_nextState4);
    
    
    CPPUNIT_TEST(test_cell_input_constructor1);
    CPPUNIT_TEST(test_cell_input_constructor2);
    CPPUNIT_TEST(test_cell_input_constructor3);
    CPPUNIT_TEST(test_cell_copy_constructor1);
    CPPUNIT_TEST(test_cell_copy_constructor2);
    CPPUNIT_TEST(test_cell_copy_constructor3);
    CPPUNIT_TEST(test_cell_getSign1);
    CPPUNIT_TEST(test_cell_getSign2);
    CPPUNIT_TEST(test_cell_getSign3);
    CPPUNIT_TEST(test_cell_getNextState1);
    CPPUNIT_TEST(test_cell_getNextState2);
    CPPUNIT_TEST(test_cell_getNextState3);
    CPPUNIT_TEST(test_cell_isAlive1);
    CPPUNIT_TEST(test_cell_isAlive2);
    CPPUNIT_TEST(test_cell_isAlive3);
    CPPUNIT_TEST(test_cell_getAge1);
    CPPUNIT_TEST(test_cell_getAge2);
    CPPUNIT_TEST(test_cell_getAge3);
    CPPUNIT_TEST(test_cell_fredkin_to_conway1);
    CPPUNIT_TEST(test_cell_fredkin_to_conway2);
    CPPUNIT_TEST(test_cell_fredkin_to_conway3);
    CPPUNIT_TEST(test_cell_update_cell1);
    CPPUNIT_TEST(test_cell_update_cell2);
    CPPUNIT_TEST(test_cell_update_cell3);
    CPPUNIT_TEST(test_cell_determine_nextState1);
    CPPUNIT_TEST(test_cell_determine_nextState2);
    CPPUNIT_TEST(test_cell_determine_nextState3);
    CPPUNIT_TEST(test_cell_determine_nextState4);

    
    CPPUNIT_TEST(test_life_constructor1);
    CPPUNIT_TEST(test_life_constructor2);
    CPPUNIT_TEST(test_life_constructor3);
    //CPPUNIT_TEST(test_life_print_grid1);
    //CPPUNIT_TEST(test_life_print_grid2);
    //CPPUNIT_TEST(test_life_print_grid3);
    CPPUNIT_TEST(test_life_take_turn1);
    CPPUNIT_TEST(test_life_take_turn2);
    CPPUNIT_TEST(test_life_take_turn3);
    CPPUNIT_TEST(test_life_take_turn4);
    CPPUNIT_TEST(test_life_take_turn5);
    CPPUNIT_TEST(test_life_take_turn6);
 	CPPUNIT_TEST(test_life_take_turn7);
 	CPPUNIT_TEST(test_life_take_turn8);
 
    CPPUNIT_TEST_SUITE_END();
};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}

