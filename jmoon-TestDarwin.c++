// ------------------------------
// projects/Darwin/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing
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
#define private public
#define protected public
#define class struct
#include "Darwin.h"
typedef DarwinWorld::Creature Creature;
// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {

	void test_DarwinWorld_1(){
	DarwinWorld x;
	CPPUNIT_ASSERT(x._map.size() ==0);
	CPPUNIT_ASSERT(x._maxTurns == 0);
	}
	void test_DarwinWorld_2(){
	DarwinWorld x(2,2,2,1);
	CPPUNIT_ASSERT(x._map.size() == 2);
	CPPUNIT_ASSERT(x._map[0].size() == 2);
	CPPUNIT_ASSERT(x._maxTurns == 2);
	
	}
	void test_DarwinWorld_3(){
	DarwinWorld x;
	DarwinWorld y(2,2,2,1);
	x=y;
	CPPUNIT_ASSERT(x._map.size() == 2);
	CPPUNIT_ASSERT(x._map[1][1] ==NULL);
	}

	void test_Creature_1(){
	Creature x;
	CPPUNIT_ASSERT(x._row == 0);
	CPPUNIT_ASSERT(x._column == 0);
	CPPUNIT_ASSERT(x._world == NULL);
	}
	void test_Creature_2(){
	DarwinWorld x(2,2,2,1);
	Creature y(0,0,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(y._direction == NORTH);
	CPPUNIT_ASSERT(y._species == FOOD);
	}
	void test_Creature_3(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD, &x);
	CPPUNIT_ASSERT(x._map[1][1]!=NULL);
	}
	void test_isEmpty_1(){
	DarwinWorld x(2,2,2,1);
	CPPUNIT_ASSERT(x.isEmpty(1,1));
	}
	void test_isEmpty_2(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(!x.isEmpty(1,1));

	}
	void test_isEmpty_3(){
		DarwinWorld x(2,2,2,1);
	CPPUNIT_ASSERT(!x.isEmpty(2,1));
	}
	void test_isWall_1(){
		DarwinWorld x(2,2,2,1);
	CPPUNIT_ASSERT(!x.isWall(0,1));
	}
	void test_isWall_2(){
		DarwinWorld x(2,2,2,1);
	CPPUNIT_ASSERT(x.isWall(2,1));
	}
	void test_isWall_3(){
		DarwinWorld x(2,2,2,1);
	CPPUNIT_ASSERT(x.isWall(-1,1));
	}
	void test_hop_1(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(!x.isEmpty(1,1));
	CPPUNIT_ASSERT(x.isEmpty(0,1));
	CPPUNIT_ASSERT(y._row==1 && y._column==1);
	y.hop();
	CPPUNIT_ASSERT(!x.isEmpty(0,1));
	CPPUNIT_ASSERT(x.isEmpty(1,1));
	CPPUNIT_ASSERT(y._row==0 && y._column==1);
	}
	void test_hop_2(){
	DarwinWorld x(2,2,2,1);
	Creature y(0,0,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(!x.isEmpty(0,0));
	CPPUNIT_ASSERT(y._row==0 && y._column==0);
	y.hop();
	CPPUNIT_ASSERT(!x.isEmpty(0,0));
	CPPUNIT_ASSERT(y._row==0 && y._column==0);
	}
	void test_hop_3(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	Creature z(0,1,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(!x.isEmpty(1,1));
	CPPUNIT_ASSERT(!x.isEmpty(0,1));
	y.hop();
	CPPUNIT_ASSERT(y._row==1 && y._column==1);
	CPPUNIT_ASSERT(!x.isEmpty(1,1));
	}
	void test_left_right_1(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(y._direction==NORTH);
	y.left();
	CPPUNIT_ASSERT(y._direction==WEST);
	}
	void test_left_right_2(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(y._direction==NORTH);
	y.left();
	y.left();
	CPPUNIT_ASSERT(y._direction==SOUTH);
	}
	void test_left_right_3(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	CPPUNIT_ASSERT(y._direction==NORTH);
	y.right();
	CPPUNIT_ASSERT(y._direction==EAST);
	}
	
	void test_infect_1(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	Creature z(0,1,NORTH,ROVER,&x);
	CPPUNIT_ASSERT(z._species==ROVER);
	y.infect();
	CPPUNIT_ASSERT(z._species==FOOD);
	}
	void test_infect_2(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	Creature z(0,1,SOUTH,ROVER,&x);
	CPPUNIT_ASSERT(y._species==FOOD);
	z.infect();
	CPPUNIT_ASSERT(y._species==ROVER);
	}
	void test_infect_3(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	Creature z(0,1,NORTH,ROVER,&x);
	z.left();
	z.left();
	CPPUNIT_ASSERT(z._programCounter==2);
	CPPUNIT_ASSERT(z._species==ROVER);
	y.infect();
	CPPUNIT_ASSERT(z._species==FOOD);
	CPPUNIT_ASSERT(z._programCounter==0);
	}
	void test_ifEmpty_1(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	Creature z(0,1,SOUTH,ROVER,&x);
	z.ifEmpty(5);
	CPPUNIT_ASSERT(z._programCounter==1);
	}
	void test_ifEmpty_2(){
	DarwinWorld x(2,2,2,1);
	Creature z(0,1,SOUTH,ROVER,&x);
	z.ifEmpty(5);
	CPPUNIT_ASSERT(z._programCounter==5);
	}
	void test_ifEmpty_3(){
	DarwinWorld x(2,2,2,1);
	Creature z(0,1,NORTH,ROVER,&x);
	z.ifEmpty(5);
	CPPUNIT_ASSERT(z._programCounter==1);
	}
	void test_ifEnemy_1(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,FOOD,&x);
	Creature z(0,1,SOUTH,ROVER,&x);
	z.ifEnemy(5);
	CPPUNIT_ASSERT(z._programCounter==5);
	}
	void test_ifEnemy_2(){
	DarwinWorld x(2,2,2,1);
	Creature y(1,1,NORTH,ROVER,&x);
	Creature z(0,1,SOUTH,ROVER,&x);
	z.ifEnemy(5);
	CPPUNIT_ASSERT(z._programCounter==1);
	}
	void test_ifEnemy_3(){
	DarwinWorld x(2,2,2,1);
	Creature z(0,1,NORTH,ROVER,&x);
	z.ifEnemy(5);
	CPPUNIT_ASSERT(z._programCounter==1);
	}
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_DarwinWorld_1);
    CPPUNIT_TEST(test_DarwinWorld_2);
    CPPUNIT_TEST(test_DarwinWorld_3);
	 CPPUNIT_TEST(test_Creature_1);
	 CPPUNIT_TEST(test_Creature_2);
	 CPPUNIT_TEST(test_Creature_3);
	 CPPUNIT_TEST(test_isEmpty_1);
	 CPPUNIT_TEST(test_isEmpty_2);
	 CPPUNIT_TEST(test_isEmpty_3);
	 CPPUNIT_TEST(test_isWall_1);
	 CPPUNIT_TEST(test_isWall_2);
	 CPPUNIT_TEST(test_isWall_3);
	 CPPUNIT_TEST(test_hop_1);
	 CPPUNIT_TEST(test_hop_2);
	 CPPUNIT_TEST(test_hop_3);
	 CPPUNIT_TEST(test_left_right_1);
	 CPPUNIT_TEST(test_left_right_2);
	 CPPUNIT_TEST(test_left_right_3);
	 CPPUNIT_TEST(test_infect_1);
	 CPPUNIT_TEST(test_infect_2);
	 CPPUNIT_TEST(test_infect_3);
	 CPPUNIT_TEST(test_ifEmpty_1);
	 CPPUNIT_TEST(test_ifEmpty_2);
	 CPPUNIT_TEST(test_ifEmpty_3);
	 CPPUNIT_TEST(test_ifEnemy_1);
 	 CPPUNIT_TEST(test_ifEnemy_2);
	 CPPUNIT_TEST(test_ifEnemy_3);

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