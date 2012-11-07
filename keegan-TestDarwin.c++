
// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner
#include "Darwin.h"


struct TestDarwin : CppUnit::TestFixture {
    void test_creature_1 () {
        Food f;
        CPPUNIT_ASSERT(f.ascii == 'f');
    }
    void test_creature_2 () {
        EmptyC e;
        CPPUNIT_ASSERT(e.pc == 0);
    }
    void test_creature_3 () {
        Hopper h;
        CPPUNIT_ASSERT(h.pc == 0);
    }
    void test_board_1 () {
        Board b(1,1);
    }
    void test_placeCreature_1 (){
        Board b(10,10);
        b.printBoard();
        Hopper h;
        b.placeCreature(h,4,4,NORTH);
        b.printBoard();
    }
    void test_placeCreature_2 (){
        Board b(10,10);
        b.printBoard();
        Hopper h;
        b.placeCreature(h,0,0,NORTH);
        b.printBoard();
    }
    void test_placeCreature_3 (){
        Board b(10,10);
        b.printBoard();
        Hopper h;
        b.placeCreature(h,9,9,WEST);
        b.printBoard();
    }
    void test_hop_1 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,4,4,NORTH);
        b.printBoard();
        b.hop(4,4);
        b.printBoard();
    }
    void test_hop_2 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,4,4,NORTH);
        b.printBoard();
        b.hop(4,4);
        b.hop(3,4);
        b.printBoard();
    }
    void test_hop_3 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,0,0,NORTH);
        b.printBoard();
        b.hop(0,0);
        b.printBoard();
    }
    void test_direction_1 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,4,4,NORTH);
        b.printBoard();
        b.left(4,4);
        b.hop(4,4);
        b.printBoard();
    }
    void test_direction_2 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,4,4,NORTH);
        b.printBoard();
        b.right(4,4);
        b.hop(4,4);
        b.printBoard();
    }
    void test_direction_3 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,4,4,NORTH);
        b.printBoard();
        b.right(4,4);
        b.right(4,4);
        b.hop(4,4);
        b.printBoard();
    }
    void test_infect_1 () {
        Board b(10,10);
        Hopper h;
        Hopper h1;
        Hopper h2;
        Hopper h3;
        Hopper h4;
        Rover r;
        b.placeCreature(h1,3,4,NORTH);
        b.placeCreature(h2,4,3,NORTH);
        b.placeCreature(h3,5,4,NORTH);
        b.placeCreature(h4,4,5,NORTH);
        b.placeCreature(r,4,4,NORTH);
        b.printBoard();
        b.infect(4,4);
        b.printBoard();
    }
    void test_infect_2 () {
        Board b(10,10);
        Hopper h;
        Hopper h1;
        Hopper h2;
        Hopper h3;
        Hopper h4;
        Rover r;
        b.placeCreature(h1,3,4,NORTH);
        b.placeCreature(h2,4,3,NORTH);
        b.placeCreature(h3,5,4,NORTH);
        b.placeCreature(h4,4,5,NORTH);
        b.placeCreature(r,4,4,WEST);
        b.printBoard();
        b.infect(4,4);
        b.printBoard();
    }
    void test_infect_3 () {
        Board b(10,10);
        Hopper h;
        Hopper h1;
        Hopper h2;
        Hopper h3;
        Hopper h4;
        Rover r;
        b.placeCreature(h1,3,4,NORTH);
        b.placeCreature(h2,4,3,NORTH);
        b.placeCreature(h3,5,4,NORTH);
        b.placeCreature(h4,4,5,NORTH);
        b.placeCreature(r,4,4,SOUTH);
        b.printBoard();
        b.infect(4,4);
        b.printBoard();
    }
    void test_conditional_1 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,0,0,NORTH);
        b.if_wall(0,0,95);
        CPPUNIT_ASSERT(h.pc == 96*2);
        
    }
    void test_conditional_2 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,2,2,NORTH);
        b.if_wall(2,2,95);
        CPPUNIT_ASSERT(h.pc == 2);
        
    }
    void test_conditional_3 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,2,2,NORTH);
        Food f;
        b.placeCreature(f,1,2,NORTH);
        b.if_enemy(2,2,95);
        CPPUNIT_ASSERT(h.pc == 96*2);
        
    }
    void test_advanceTurn_1 () {
        Board b(10,10);
        Hopper h;
        b.placeCreature(h,2,2,NORTH);
        b.printBoard();
        b.advanceTurn();
        b.printBoard();
    }
    void test_advanceTurn_2 () {
        Board b(10,10);
        Hopper h;
        Hopper h1;
        b.placeCreature(h,2,2,NORTH);
        b.placeCreature(h1,2,3,WEST);
        b.printBoard();
        b.advanceTurn();
        b.printBoard();
    }
    void test_advanceTurn_3 () {
        Board b(10,10);
        Rover r;
        Rover r1;
        b.placeCreature(r,2,2,NORTH);
        b.placeCreature(r1,2,3,WEST);
        b.printBoard();
        b.advanceTurn();
        b.printBoard();
    }
    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(test_creature_1);
    CPPUNIT_TEST(test_creature_2);
    CPPUNIT_TEST(test_creature_3);
    CPPUNIT_TEST(test_placeCreature_1);
    CPPUNIT_TEST(test_placeCreature_2);
    CPPUNIT_TEST(test_placeCreature_3);
    CPPUNIT_TEST(test_hop_1);
    CPPUNIT_TEST(test_hop_2);
    CPPUNIT_TEST(test_hop_3);
    CPPUNIT_TEST(test_direction_1);
    CPPUNIT_TEST(test_direction_2);
    CPPUNIT_TEST(test_direction_3);
    CPPUNIT_TEST(test_infect_1);
    CPPUNIT_TEST(test_infect_2);
    CPPUNIT_TEST(test_infect_3);
    CPPUNIT_TEST(test_conditional_1);
    CPPUNIT_TEST(test_conditional_2);
    CPPUNIT_TEST(test_conditional_2);
    CPPUNIT_TEST(test_advanceTurn_1);
    CPPUNIT_TEST(test_advanceTurn_2);
    CPPUNIT_TEST(test_advanceTurn_3);
    CPPUNIT_TEST_SUITE_END();
};

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}