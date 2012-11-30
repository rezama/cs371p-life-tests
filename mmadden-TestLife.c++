// ------------------------------
// projects/Darwin/TestLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
* To test the program:
* g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
* a
*/

// --------
// includes
// --------

#include <iostream> // I/O
#include <fstream> // file I/O
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h" // TestFixture
#include "cppunit/TextTestRunner.h" // TestRunner
#define private public
#define protected public
#define class struct
#include "Life.h"


// ----------
// TestLife
// ----------

struct TestLife : CppUnit::TestFixture {

    void test_conway1() {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(cell._str == '.');

    }

    void test_conway2 () {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(cell._str == '.');
        cell.updateAlive(true);
        CPPUNIT_ASSERT(cell._str == '*');
    }

    void test_conway3 () {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(cell._str == '.');
        cell.updateAlive(true, '*');
        CPPUNIT_ASSERT(cell._str == '*');
        cell.updateAlive(false);
        CPPUNIT_ASSERT(cell._str == '.');
    }

    void test_is_alive1() {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());

    }

    void test_is_alive2 () {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        cell.updateAlive(true);
        CPPUNIT_ASSERT(cell.isAlive());
    }

    void test_is_alive3 () {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        cell.updateAlive(true, '*');
        CPPUNIT_ASSERT(cell.isAlive());;
        cell.updateAlive(false);
        CPPUNIT_ASSERT(!cell.isAlive());
    }

    void test_life_conway1(){
        Life<ConwayCell> l(5, 5, ConwayCell());
        CPPUNIT_ASSERT(!l._map[5][5].isAlive());
    }

    void test_life_conway2(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l._map[5][5] = ConwayCell(true, '*');
        CPPUNIT_ASSERT(l._map[5][5].isAlive());
    }
    void test_life_conway3(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l._map[4][4] = ConwayCell(true, '*');
        l._map[4][4] = ConwayCell(false);
        CPPUNIT_ASSERT(!l._map[4][4].isAlive());
    }

    void test_life_fredkin1(){
        Life<FredkinCell> l(5, 5, FredkinCell());
        CPPUNIT_ASSERT(!l._map[5][5].isAlive());
    }

    void test_life_fredkin2(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l._map[5][5] = FredkinCell(true, '0', 0);
        CPPUNIT_ASSERT(l._map[5][5].isAlive());
    }
    void test_life_fredkin3(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l._map[4][4] = FredkinCell(true, '0', 0);
        l._map[4][4] = FredkinCell(false);
        CPPUNIT_ASSERT(!l._map[4][4].isAlive());
    }

    void test_conway_count_neighbors1(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l._map[5][5].count_neighbors(l._map, 5, 5);
        CPPUNIT_ASSERT(l._map[5][5]._alive_neighbors == 0);
    }
    void test_conway_count_neighbors2(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l._map[5][5] = ConwayCell(true, '*');
        l._map[4][5].count_neighbors(l._map, 4, 5);
        CPPUNIT_ASSERT(l._map[4][5]._alive_neighbors == 1);
    }
    void test_conway_count_neighbors3(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l._map[5][5] = ConwayCell(true, '*');
        l._map[5][4] = ConwayCell(true, '*');
        l._map[3][5] = ConwayCell(true, '*');
        l._map[4][5].count_neighbors(l._map, 4, 5);
        CPPUNIT_ASSERT(l._map[4][5]._alive_neighbors == 3);
    }

    void test_fredkin_count_neighbors1(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l._map[5][5].count_neighbors(l._map, 5, 5);
        CPPUNIT_ASSERT(l._map[5][5]._alive_neighbors == 0);
    }
    void test_fredkin_count_neighbors2(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l._map[5][5] = FredkinCell(true, '0', 0);
        l._map[4][5].count_neighbors(l._map, 4, 5);
        CPPUNIT_ASSERT(l._map[4][5]._alive_neighbors == 1);
    }
    void test_fredkin_count_neighbors3(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l._map[5][5] = FredkinCell(true, '0', 0);
        l._map[4][6] = FredkinCell(true, '0', 0);
        l._map[4][5].count_neighbors(l._map, 4, 5);
        CPPUNIT_ASSERT(l._map[4][5]._alive_neighbors == 2);
    }

    void test_conway_update_status1(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l.updateStatus(5, 5, true);
        CPPUNIT_ASSERT(l._map[5][5].isAlive());
    }
    void test_conway_update_status2(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l.updateStatus(5, 5, true, '*');
        CPPUNIT_ASSERT(l._map[5][5].isAlive());
    }
    void test_conway_update_status3(){
        Life<ConwayCell> l(10, 5, ConwayCell());
        l.updateStatus(5, 5, false);
        CPPUNIT_ASSERT(!l._map[5][5].isAlive());
    }

    void test_fredkin_update_status1(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l.updateStatus(5, 5, true, '1');
        CPPUNIT_ASSERT(l._map[5][5].isAlive());
    }
    void test_fredkin_update_status2(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l.updateStatus(5, 5, true, '1');
        CPPUNIT_ASSERT(l._map[5][5]._age = 1);
    }
    void test_fredkin_update_status3(){
        Life<FredkinCell> l(10, 5, FredkinCell());
        l.updateStatus(5, 5, false);
        CPPUNIT_ASSERT(!l._map[5][5].isAlive());
    }

    void test_conway_to_string1(){
        ConwayCell cc = ConwayCell();
        CPPUNIT_ASSERT(cc.toString() == '.');
    }
    void test_conway_to_string2(){
        ConwayCell cc = ConwayCell(true, '*');
        CPPUNIT_ASSERT(cc.toString() == '*');
    }
    void test_conway_to_string3(){
        ConwayCell fc = ConwayCell();
        CPPUNIT_ASSERT(fc.toString() != '-');
    }

    void test_fredkin_to_string1(){
        FredkinCell cc = FredkinCell();
        CPPUNIT_ASSERT(cc.toString() == '-');
    }
    void test_fredkin_to_string2(){
        FredkinCell cc = FredkinCell(true, '0', 0);
        CPPUNIT_ASSERT(cc.toString() == '0');
    }
    void test_fredkin_to_string3(){
        FredkinCell fc = FredkinCell(true, '1', 1);
        CPPUNIT_ASSERT(fc.toString() == '1');
    }

    void test_update_next1(){
        ConwayCell cc = ConwayCell();
        cc._next = true;
        cc.update_next(); 
        CPPUNIT_ASSERT(cc.isAlive() == true);
    }
    void test_update_next2(){
        ConwayCell cc = ConwayCell();
        cc._next = false;
        cc.update_next(); 
        CPPUNIT_ASSERT(cc.isAlive() == false);
    }
    void test_update_next3(){
        FredkinCell fc = FredkinCell();
        fc._next = true;
        fc.update_next(); 
        CPPUNIT_ASSERT(fc.isAlive() == true);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(test_conway1);
    CPPUNIT_TEST(test_conway2);
    CPPUNIT_TEST(test_conway3);
    CPPUNIT_TEST(test_is_alive1);
    CPPUNIT_TEST(test_is_alive2);
    CPPUNIT_TEST(test_is_alive3);
    CPPUNIT_TEST(test_life_conway1);
    CPPUNIT_TEST(test_life_conway2);
    CPPUNIT_TEST(test_life_conway3);
    CPPUNIT_TEST(test_life_fredkin1);
    CPPUNIT_TEST(test_life_fredkin2);
    CPPUNIT_TEST(test_life_fredkin3);
    CPPUNIT_TEST(test_conway_count_neighbors1);
    CPPUNIT_TEST(test_conway_count_neighbors2);
    CPPUNIT_TEST(test_conway_count_neighbors3);
    CPPUNIT_TEST(test_fredkin_count_neighbors1);
    CPPUNIT_TEST(test_fredkin_count_neighbors2);
    CPPUNIT_TEST(test_fredkin_count_neighbors3);
    CPPUNIT_TEST(test_conway_update_status1);
    CPPUNIT_TEST(test_conway_update_status2);
    CPPUNIT_TEST(test_conway_update_status3);
    CPPUNIT_TEST(test_fredkin_update_status1);
    CPPUNIT_TEST(test_fredkin_update_status2);
    CPPUNIT_TEST(test_fredkin_update_status3);
    CPPUNIT_TEST(test_conway_to_string1);
    CPPUNIT_TEST(test_conway_to_string2);
    CPPUNIT_TEST(test_conway_to_string3);
    CPPUNIT_TEST(test_fredkin_to_string1);
    CPPUNIT_TEST(test_fredkin_to_string2);
    CPPUNIT_TEST(test_fredkin_to_string3);
    CPPUNIT_TEST(test_update_next1);
    CPPUNIT_TEST(test_update_next2);
    CPPUNIT_TEST(test_update_next3);
    CPPUNIT_TEST_SUITE_END();};

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
