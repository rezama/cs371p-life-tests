//---------------------
// TestingDarwin.c++
// Stephen Cook
//---------------------


/*
Run the program:
% ls /usr/include/cppunit/
...
HelperMacros.h
...
% locate libcppunit.a
/usr/lib/libcppunit.a
% g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.c++.app
% valgrind TestDarwin.c++.app >& TestDarwin.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TextTestRunner

#define private public
#define protected public
#include "Darwin.h"


// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {
    // ----
    // Tests
    // ----

    void test_instruction () {
        using namespace std;
		cout << "Test_instruction: " << endl;
		srand(0);
		
		Instruction i(1);
		CPPUNIT_ASSERT(i._type == Instruction::HOP);
		CPPUNIT_ASSERT(i._line == 0);
	}

    void test_instruction2 () {
        using namespace std;
		cout << "Test_instruction2: " << endl;
		srand(0);
		
		Instruction i(9, 3);
		CPPUNIT_ASSERT(i._type == Instruction::GO);
		CPPUNIT_ASSERT(i._line == 3);
	}

    void test_instruction3 () {
        using namespace std;
		cout << "Test_instruction3: " << endl;
		srand(0);
		
		try{
			Instruction x(999);
			CPPUNIT_ASSERT(false);
		}
		catch(invalid_argument& a)
		{
			CPPUNIT_ASSERT(true);
		}
	}

    void test_add_instruction () {
        using namespace std;
		cout << "Test_add_instruction: " << endl;
		srand(0);
		
		Species s;
		CPPUNIT_ASSERT((int)s._instructions.size() == 0);
	}
    
	void test_add_instruction2 () {
        using namespace std;
		cout << "Test_add_instruction2: " << endl;
		srand(0);
		
		Species s;
		s.add_instruction(Instruction(1));
		CPPUNIT_ASSERT((int)s._instructions.size() == 1);
	}
    void test_add_instruction3 () {
        using namespace std;
		cout << "Test_add_instruction3: " << endl;
		srand(0);
		
		Species s;
		s.add_instruction(Instruction(1));
		s.add_instruction(Instruction(Instruction::GO, 9));
		CPPUNIT_ASSERT((int)s._instructions.size() == 2);
	}

    void test_infect_by () {
        using namespace std;
		cout << "Test_infect_by: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(1, &s);
		
		Species s2('b');
		s2.add_instruction(Instruction(1));	
		s2.add_instruction(Instruction(Instruction::GO, 9));
		Creature b(0, &s2);

		a.infect_by(&b);

		CPPUNIT_ASSERT(a.is_same_species_as(&b));
	}

    void test_infect_by2 () {
        using namespace std;
		cout << "Test_infect_by2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(1, &s);
		
		Species s2('b');
		s2.add_instruction(Instruction(1));	
		s2.add_instruction(Instruction(Instruction::GO, 9));
		Creature b(0, &s2);

		a.infect_by(&b);

		CPPUNIT_ASSERT(a._dir != b._dir);
	}

    void test_infect_by3 () {
        using namespace std;
		cout << "Test_infect_by3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(1, &s);
		
		Species s2('b');
		s2.add_instruction(Instruction(1));	
		s2.add_instruction(Instruction(Instruction::GO, 9));
		Creature b(0, &s2);
	
		a.program_counter = 1;
		a.infect_by(&b);

		CPPUNIT_ASSERT(a.program_counter == 0);
	}

    void test_request_positive () {
        using namespace std;
		cout << "Test_request_positive: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::IF_EMPTY, 0));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
		Creature a(1, &s);
		a.program_counter = 0;

		Instruction i = a.request_positive(true);

		CPPUNIT_ASSERT(i._type == Instruction::IF_EMPTY);
		CPPUNIT_ASSERT(i._line == 0);
		CPPUNIT_ASSERT(a.program_counter == 1);
	}

    void test_request_positive2 () {
        using namespace std;
		cout << "Test_request_positive2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::IF_EMPTY, 0));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
		Creature a(1, &s);
		a.program_counter = 1;

		Instruction i = a.request_positive(true);

		CPPUNIT_ASSERT(i._type == Instruction::HOP);
		CPPUNIT_ASSERT(i._line == 0);
		CPPUNIT_ASSERT(a.program_counter == 0);
	}

    void test_request_positive3 () {
        using namespace std;
		cout << "Test_request_positive3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::IF_EMPTY, 0));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
		Creature a(1, &s);
		a.program_counter = 1;

		Instruction i = a.request_positive(false);

		CPPUNIT_ASSERT(i._type == Instruction::GO);
		CPPUNIT_ASSERT(i._line == 0);
		CPPUNIT_ASSERT(a.program_counter == 2);
	}

    void test_instruction_request () {
        using namespace std;
		cout << "Test_instruction_request: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::IF_EMPTY, 0));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
		Creature a(1, &s);
		a.program_counter = 0;

		Instruction i = a.instruction_request();

		CPPUNIT_ASSERT(i._type == Instruction::HOP);
		CPPUNIT_ASSERT(i._line == 0);
		CPPUNIT_ASSERT(a.program_counter == 0);
	}
    void test_instruction_request2 () {
        using namespace std;
		cout << "Test_instruction_request2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::IF_EMPTY, 0));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
		Creature a(1, &s);
		a.program_counter = 1;

		Instruction i = a.instruction_request();

		CPPUNIT_ASSERT(i._type == Instruction::IF_EMPTY);
		CPPUNIT_ASSERT(i._line == 0);
		CPPUNIT_ASSERT(a.program_counter == 1);
	}
    void test_instruction_request3 () {
        using namespace std;
		cout << "Test_instruction_request3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::IF_EMPTY, 0));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
		Creature a(1, &s);
		a.program_counter = 2;

		Instruction i = a.instruction_request();

		CPPUNIT_ASSERT(i._type == Instruction::GO);
		CPPUNIT_ASSERT(i._line == 0);
		CPPUNIT_ASSERT(a.program_counter == 2);
	}


    void test_same_species () {
        using namespace std;
		cout << "Test_same_species: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(1, &s);
		
		Species s2('b');
		s2.add_instruction(Instruction(1));	
		s2.add_instruction(Instruction(Instruction::GO, 9));
		Creature b(0, &s2);

		CPPUNIT_ASSERT(!a.is_same_species_as(&b));
	}

    void test_same_species2 () {
        using namespace std;
		cout << "Test_same_species2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(1, &s);
		
		Creature b(0, &s);

		CPPUNIT_ASSERT(a.is_same_species_as(&b));
	}

    void test_same_species3 () {
        using namespace std;
		cout << "Test_same_species3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(1, &s);
		
		Species s2('a');
		s2.add_instruction(Instruction(2));	
		Creature b(1, &s2);

		CPPUNIT_ASSERT(!a.is_same_species_as(&b));
	}

    void test_turn () {
        using namespace std;
		cout << "Test_turn: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(Grid::NORTH, &s);


		a.turn(Grid::SOUTH);

		CPPUNIT_ASSERT(a._dir == Grid::SOUTH);
	}

    void test_turn2 () {
        using namespace std;
		cout << "Test_turn2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(Grid::WEST, &s);

		a.turn(3);//turn left

		CPPUNIT_ASSERT(a._dir == Grid::SOUTH);
	}

    void test_turn3 () {
        using namespace std;
		cout << "Test_turn3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
		Creature a(Grid::SOUTH, &s);

		a.turn(Grid::SOUTH + 1); //turn right

		CPPUNIT_ASSERT(a._dir == Grid::WEST);
	}


	void test_randomly_place_creature() {
        using namespace std;
		cout << "Test_randomly_place_creature: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	

		int rows = 1;
		int cols = 1;		

		Grid gr(rows, cols);
		gr.randomly_place_creature(&s);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(creature_count == 1);
	}

	void test_randomly_place_creature2() {
        using namespace std;
		cout << "Test_randomly_place_creature2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	

		int rows = 5;
		int cols = 5;		

		Grid gr(rows, cols);
		gr.randomly_place_creature(&s);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 1);
	}

	void test_randomly_place_creature3() {
        using namespace std;
		cout << "Test_randomly_place_creature3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	

		int rows = 10;
		int cols = 10;		

		Grid gr(rows, cols);
		gr.randomly_place_creature(&s);
		gr.randomly_place_creature(&s);
		gr.randomly_place_creature(&s);
		gr.randomly_place_creature(&s);
		gr.randomly_place_creature(&s);
		gr.randomly_place_creature(&s);
		gr.randomly_place_creature(&s);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 7);
	}

	void test_place_creature() {
        using namespace std;
		cout << "Test_place_creature: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	
	
		int rows = 1;
		int cols = 1;		
		int dir = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == dir);

		CPPUNIT_ASSERT(creature_count == 1);
	}

	void test_place_creature2() {
        using namespace std;
		cout << "Test_place_creature2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(2));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);
		gr.place_creature(2,2,dir+1,&s2);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == dir);
		CPPUNIT_ASSERT(gr._world[2][2]._s == &s2);
		CPPUNIT_ASSERT(gr._world[2][2]._dir == Grid::EAST);

		CPPUNIT_ASSERT(creature_count == 2);
	}

	void test_place_creature3() {
        using namespace std;
		cout << "Test_place_creature3: " << endl;
		srand(0);
		
		Species s('a');
		Species s2('b');
		Species s3('c');
		Species s4('d');
	
		int rows = 10;
		int cols = 10;		

		Grid gr(rows, cols);
		gr.place_creature(0,0,0,&s);
		gr.place_creature(1,4,1,&s2);
		gr.place_creature(6,7,2,&s3);
		gr.place_creature(8,8,3,&s4);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == 0);
		CPPUNIT_ASSERT(gr._world[1][4]._s == &s2);
		CPPUNIT_ASSERT(gr._world[1][4]._dir == 1);
		CPPUNIT_ASSERT(gr._world[6][7]._s == &s3);
		CPPUNIT_ASSERT(gr._world[6][7]._dir == 2);
		CPPUNIT_ASSERT(gr._world[8][8]._s == &s4);
		CPPUNIT_ASSERT(gr._world[8][8]._dir == 3);

		CPPUNIT_ASSERT(creature_count == 4);
	}



	void test_service_request() {
        using namespace std;
		cout << "Test_service_request: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::LEFT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.service_move_request(&gr._world[0][0], 0, 0);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::WEST);
	}

	void test_service_request2() {
        using namespace std;
		cout << "Test_service_request2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.service_move_request(&gr._world[0][0], 0, 0);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::EAST);
		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 1);
	}

	void test_service_request3() {
        using namespace std;
		cout << "Test_service_request3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::INFECT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		int dir2 = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);
		gr.place_creature(0,1,dir2,&s2);

		gr.service_move_request(&gr._world[0][0], 0, 0); //a infects b

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 2);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::EAST);
		CPPUNIT_ASSERT(gr._world[0][0].program_counter == 1);
		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::NORTH);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 0);
	}

	void test_print() {
        using namespace std;
		cout << "Test_print: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::LEFT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.simulate(1,2);
		gr.print_grid();

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::WEST);
	}

	void test_print2() {
        using namespace std;
		cout << "Test_print2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.simulate(1,1);
		gr.print_grid();

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::EAST);
		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 1);
	}


	void test_print3() {
        using namespace std;
		cout << "Test_print3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::INFECT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		int dir2 = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);
		gr.place_creature(0,1,dir2,&s2);

		gr.simulate(1);
		gr.print_grid();

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 2);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::EAST);
		CPPUNIT_ASSERT(gr._world[0][0].program_counter == 1);
		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::NORTH);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 0);
	}

       void test_update() {
        using namespace std;
		cout << "Test_update: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::LEFT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.update_grid();

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::WEST);
	}

	void test_update2() {
        using namespace std;
		cout << "Test_update2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.update_grid();

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::EAST);
		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 1);
	}


	void test_update3() {
        using namespace std;
		cout << "Test_update3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::INFECT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		int dir2 = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);
		gr.place_creature(0,1,dir2,&s2);

		gr.update_grid();

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 2);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::EAST);
		CPPUNIT_ASSERT(gr._world[0][0].program_counter == 1);
		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::NORTH);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 0);
	}
	void test_simulate() {
        using namespace std;
		cout << "Test_simulate: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::LEFT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.simulate(1,2);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::WEST);
	}

	void test_simulate2() {
        using namespace std;
		cout << "Test_simulate2: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::HOP));	
		s.add_instruction(Instruction(Instruction::GO, 0));	
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);

		gr.simulate(2,1);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(gr._world[0][2]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][2]._dir == Grid::EAST);
		CPPUNIT_ASSERT(creature_count == 1);
		CPPUNIT_ASSERT(gr._world[0][2].program_counter == 1);
	}


	void test_simulate3() {
        using namespace std;
		cout << "Test_simulate3: " << endl;
		srand(0);
		
		Species s('a');
		s.add_instruction(Instruction(Instruction::INFECT));	
		s.add_instruction(Instruction(Instruction::GO, 0));	

		Species s2('b');
	
		int rows = 5;
		int cols = 5;		
		int dir = Grid::EAST;
		int dir2 = Grid::NORTH;
		Grid gr(rows, cols);
		gr.place_creature(0,0,dir,&s);
		gr.place_creature(0,1,dir2,&s2);

		gr.simulate(1);

		int creature_count = 0;

		for(int i =0; i<rows; i++)
		{
			for(int j =0; j< cols; j++)
			{
				if(gr._world[i][j]._s != 0)
					creature_count++;
			}
		}

		CPPUNIT_ASSERT(creature_count == 2);
		CPPUNIT_ASSERT(gr._world[0][0]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][0]._dir == Grid::EAST);
		CPPUNIT_ASSERT(gr._world[0][0].program_counter == 1);
		CPPUNIT_ASSERT(gr._world[0][1]._s == &s);
		CPPUNIT_ASSERT(gr._world[0][1]._dir == Grid::NORTH);
		CPPUNIT_ASSERT(gr._world[0][1].program_counter == 0);
	}



    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_instruction);
    CPPUNIT_TEST(test_instruction2);
    CPPUNIT_TEST(test_instruction3);
    CPPUNIT_TEST(test_add_instruction);
    CPPUNIT_TEST(test_add_instruction2);
    CPPUNIT_TEST(test_add_instruction3);
    CPPUNIT_TEST(test_infect_by);
    CPPUNIT_TEST(test_infect_by2);
    CPPUNIT_TEST(test_infect_by3);
    CPPUNIT_TEST(test_request_positive);
    CPPUNIT_TEST(test_request_positive2);
    CPPUNIT_TEST(test_request_positive3);
    CPPUNIT_TEST(test_instruction_request);
    CPPUNIT_TEST(test_instruction_request2);
    CPPUNIT_TEST(test_instruction_request3);
    CPPUNIT_TEST(test_same_species);
    CPPUNIT_TEST(test_same_species2);
    CPPUNIT_TEST(test_same_species3);
    CPPUNIT_TEST(test_turn);
    CPPUNIT_TEST(test_turn2);
    CPPUNIT_TEST(test_turn3);
    CPPUNIT_TEST(test_randomly_place_creature);
    CPPUNIT_TEST(test_randomly_place_creature2);
    CPPUNIT_TEST(test_randomly_place_creature3);
    CPPUNIT_TEST(test_print);
    CPPUNIT_TEST(test_print2);
    CPPUNIT_TEST(test_print3);
    CPPUNIT_TEST(test_place_creature);
    CPPUNIT_TEST(test_place_creature2);
    CPPUNIT_TEST(test_place_creature3);
    CPPUNIT_TEST(test_service_request);
    CPPUNIT_TEST(test_service_request2);
    CPPUNIT_TEST(test_service_request3);
    CPPUNIT_TEST(test_simulate);
    CPPUNIT_TEST(test_simulate2);
    CPPUNIT_TEST(test_simulate3);
    CPPUNIT_TEST(test_update);
    CPPUNIT_TEST(test_update2);
    CPPUNIT_TEST(test_update3);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestDarwom.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
