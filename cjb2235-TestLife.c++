// --------------------------
// projects/life/TestLife.c++
// Copyright (C) 2012
// --------------------------

/**
 * To test the program:
 *     g++ -std=c++0x -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#define private public
#define protected public
#include "Life.h"
#include "AbstractCell.h"
#include "FredkinCell.h"
#include "ConwayCell.h"
#include "Cell.h"

// --------------
// TestConwayCell
// --------------
struct TestConwayCell : CppUnit::TestFixture {

    // -------------------
    // get_valid_neighbors
    // -------------------
    void test_get_valid_neighbors () {
        ConwayCell c;
        const std::vector<direction_t> ans = {WEST, NORTHWEST, NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST};
        const std::vector<direction_t> r   = c.get_valid_neighbors();

        CPPUNIT_ASSERT(ans.at(0) == r.at(0));
        CPPUNIT_ASSERT(ans.at(1) == r.at(1));
        CPPUNIT_ASSERT(ans.at(2) == r.at(2));
        CPPUNIT_ASSERT(ans.at(3) == r.at(3));
        CPPUNIT_ASSERT(ans.at(4) == r.at(4));
        CPPUNIT_ASSERT(ans.at(5) == r.at(5));
        CPPUNIT_ASSERT(ans.at(6) == r.at(6));
        CPPUNIT_ASSERT(ans.at(7) == r.at(7));
    }

    // -----------
    // constructor
    // -----------
    void test_constructor_1 () {
        ConwayCell cc;
        CPPUNIT_ASSERT(false == cc._isAlive);
    }

    void test_constructor_2 () {
        ConwayCell cc(true);
        CPPUNIT_ASSERT(true == cc._isAlive);
    }

    void test_constructor_3 () {
        ConwayCell cc(false);
        CPPUNIT_ASSERT(false == cc._isAlive);
    }

    // -----
    // write
    // -----
    void test_write_1 () {
        ConwayCell cc(true);
        CPPUNIT_ASSERT(true == cc._isAlive);
        std::ostringstream w;
        cc.write(w);
        CPPUNIT_ASSERT("*" == w.str());
    }

    void test_write_2 () {
        ConwayCell cc(false);
        CPPUNIT_ASSERT(false == cc._isAlive);
        std::ostringstream w;
        cc.write(w);
        CPPUNIT_ASSERT("." == w.str());
    }

    // ------
    // equals
    // ------
    void test_equals_1 () {
        ConwayCell c1(false);
        CPPUNIT_ASSERT(c1.equals(c1));
    }

    void test_equals_2 () {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(c1.equals(c1));
    }

    void test_equals_3 () {
        ConwayCell c1(true);
        ConwayCell c2(true);
        CPPUNIT_ASSERT(c1.equals(c2));
    }

    void test_equals_4 () {
        ConwayCell c1(false);
        ConwayCell c2(false);
        CPPUNIT_ASSERT(c1.equals(c2));
    }

    void test_equals_5 () {
        ConwayCell c1(true);
        ConwayCell c2(false);
        CPPUNIT_ASSERT(!c1.equals(c2));
        CPPUNIT_ASSERT(!c2.equals(c1));
    }

    // -----------
    // operator <<
    // -----------
    void test_operatorll_1 () {
        ConwayCell cc(true);
        CPPUNIT_ASSERT(true == cc._isAlive);
        std::ostringstream w;
        w << cc;
        CPPUNIT_ASSERT("*" == w.str());
    }

    void test_operatorll_2 () {
        ConwayCell cc(false);
        CPPUNIT_ASSERT(false == cc._isAlive);
        std::ostringstream w;
        w << cc;
        CPPUNIT_ASSERT("." == w.str());
    }

    // -----------
    // operator ==
    // -----------
    void test_operatoreq_1 () {
        ConwayCell c1(false);
        CPPUNIT_ASSERT(c1 == c1);
    }

    void test_operatoreq_2 () {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(c1 == c1);
    }

    void test_operatoreq_3 () {
        ConwayCell c1(true);
        ConwayCell c2(true);
        CPPUNIT_ASSERT(c1 == c2);
    }

    void test_operatoreq_4 () {
        ConwayCell c1(false);
        ConwayCell c2(false);
        CPPUNIT_ASSERT(c1 == c2);
    }

    void test_operatoreq_5 () {
        ConwayCell c1(true);
        ConwayCell c2(false);
        CPPUNIT_ASSERT(!(c1 == c2));
        CPPUNIT_ASSERT(!(c2 == c1));
    }

    // -----------
    // operator !=
    // -----------
    void test_operatorneq_1 () {
        ConwayCell c1(false);
        CPPUNIT_ASSERT(!(c1 != c1));
    }

    void test_operatorneq_2 () {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(!(c1 != c1));
    }

    void test_operatorneq_3 () {
        ConwayCell c1(true);
        ConwayCell c2(true);
        CPPUNIT_ASSERT(!(c1 != c2));
    }

    void test_operatorneq_4 () {
        ConwayCell c1(false);
        ConwayCell c2(false);
        CPPUNIT_ASSERT(!(c1 != c2));
    }

    void test_operatorneq_5 () {
        ConwayCell c1(true);
        ConwayCell c2(false);
        CPPUNIT_ASSERT(c1 != c2);
        CPPUNIT_ASSERT(c2 != c1);
    }

    // ------
    // evolve
    // ------
    void test_evolve_d_0 () {
        unsigned int neighbors = 0;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_1 () {
        unsigned int neighbors = 1;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_2 () {
        unsigned int neighbors = 2;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_3 () {
        unsigned int neighbors = 3;
        bool isAlive = false;
        const bool result  = true;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_4 () {
        unsigned int neighbors = 4;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_5 () {
        unsigned int neighbors = 5;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_6 () {
        unsigned int neighbors = 6;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_7 () {
        unsigned int neighbors = 7;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_d_8 () {
        unsigned int neighbors = 8;
        bool isAlive = false;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_0 () {
        unsigned int neighbors = 0;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_1 () {
        unsigned int neighbors = 1;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_2 () {
        unsigned int neighbors = 2;
        bool isAlive = true;
        const bool result  = true;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_3 () {
        unsigned int neighbors = 3;
        bool isAlive = true;
        const bool result  = true;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_4 () {
        unsigned int neighbors = 4;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_5 () {
        unsigned int neighbors = 5;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_6 () {
        unsigned int neighbors = 6;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_7 () {
        unsigned int neighbors = 7;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    void test_evolve_a_8 () {
        unsigned int neighbors = 8;
        bool isAlive = true;
        const bool result  = false;

        ConwayCell c(isAlive);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
    }

    CPPUNIT_TEST_SUITE(TestConwayCell);
    CPPUNIT_TEST(test_get_valid_neighbors);

    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);

    CPPUNIT_TEST(test_write_1);
    CPPUNIT_TEST(test_write_2);

    CPPUNIT_TEST(test_equals_1);
    CPPUNIT_TEST(test_equals_2);
    CPPUNIT_TEST(test_equals_3);
    CPPUNIT_TEST(test_equals_4);
    CPPUNIT_TEST(test_equals_5);

    CPPUNIT_TEST(test_operatorll_1);
    CPPUNIT_TEST(test_operatorll_2);

    CPPUNIT_TEST(test_operatoreq_1);
    CPPUNIT_TEST(test_operatoreq_2);
    CPPUNIT_TEST(test_operatoreq_3);
    CPPUNIT_TEST(test_operatoreq_4);
    CPPUNIT_TEST(test_operatoreq_5);

    CPPUNIT_TEST(test_operatorneq_1);
    CPPUNIT_TEST(test_operatorneq_2);
    CPPUNIT_TEST(test_operatorneq_3);
    CPPUNIT_TEST(test_operatorneq_4);
    CPPUNIT_TEST(test_operatorneq_5);
    
    CPPUNIT_TEST(test_evolve_d_0);
    CPPUNIT_TEST(test_evolve_d_1);
    CPPUNIT_TEST(test_evolve_d_2);
    CPPUNIT_TEST(test_evolve_d_3);
    CPPUNIT_TEST(test_evolve_d_4);
    CPPUNIT_TEST(test_evolve_d_5);
    CPPUNIT_TEST(test_evolve_d_6);
    CPPUNIT_TEST(test_evolve_d_7);
    CPPUNIT_TEST(test_evolve_d_8);
    CPPUNIT_TEST(test_evolve_a_0);
    CPPUNIT_TEST(test_evolve_a_1);
    CPPUNIT_TEST(test_evolve_a_2);
    CPPUNIT_TEST(test_evolve_a_3);
    CPPUNIT_TEST(test_evolve_a_4);
    CPPUNIT_TEST(test_evolve_a_5);
    CPPUNIT_TEST(test_evolve_a_6);
    CPPUNIT_TEST(test_evolve_a_7);
    CPPUNIT_TEST(test_evolve_a_8);

    CPPUNIT_TEST_SUITE_END();
};

// ---------------
// TestFredkinCell
// ---------------
struct TestFredkinCell : CppUnit::TestFixture {

    // -------------------
    // get_valid_neighbors
    // -------------------
    void test_get_valid_neighbors () {
        FredkinCell c;
        const std::vector<direction_t> ans = {WEST, NORTH, EAST, SOUTH};
        const std::vector<direction_t> r   = c.get_valid_neighbors();

        CPPUNIT_ASSERT(ans.at(0) == r.at(0));
        CPPUNIT_ASSERT(ans.at(1) == r.at(1));
        CPPUNIT_ASSERT(ans.at(2) == r.at(2));
        CPPUNIT_ASSERT(ans.at(3) == r.at(3));
    }

    // -----------
    // constructor
    // -----------
    void test_constructor_1 () {
        FredkinCell fc;
        CPPUNIT_ASSERT(0 == fc._age);
        CPPUNIT_ASSERT(false == fc._isAlive);
    }

    void test_constructor_2 () {
        FredkinCell fc(true);
        CPPUNIT_ASSERT(0 == fc._age);
        CPPUNIT_ASSERT(true == fc._isAlive);
    }

    void test_constructor_3 () {
        FredkinCell fc(false);
        CPPUNIT_ASSERT(0 == fc._age);
        CPPUNIT_ASSERT(false == fc._isAlive);
    }

    void test_constructor_4 () {
        FredkinCell fc(false,3);
        CPPUNIT_ASSERT(3 == fc._age);
        CPPUNIT_ASSERT(false == fc._isAlive);
    }

    void test_constructor_5 () {
        FredkinCell fc(true,7);
        CPPUNIT_ASSERT(7 == fc._age);
        CPPUNIT_ASSERT(true == fc._isAlive);
    }

    // -----
    // write
    // -----
    void test_write_1 () {
        FredkinCell fc(true,0);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("0" == w.str());
    }

    void test_write_2 () {
        FredkinCell fc(false,0);
        CPPUNIT_ASSERT(false == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("-" == w.str());
    }

    void test_write_3 () {
        FredkinCell fc(false,5);
        CPPUNIT_ASSERT(false == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("-" == w.str());
    }

    void test_write_4 () {
        FredkinCell fc(true,5);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("5" == w.str());
    }

    void test_write_5 () {
        FredkinCell fc(true,9);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("9" == w.str());
    }

    void test_write_6 () {
        FredkinCell fc(true,10);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("+" == w.str());
    }

    void test_write_7 () {
        FredkinCell fc(true,37);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        fc.write(w);
        CPPUNIT_ASSERT("+" == w.str());
    }

    // ------
    // equals
    // ------
    void test_equals_1 () {
        FredkinCell c1(false,0);
        CPPUNIT_ASSERT(c1.equals(c1));
    }

    void test_equals_2 () {
        FredkinCell c1(true,0);
        CPPUNIT_ASSERT(c1.equals(c1));
    }

    void test_equals_3 () {
        FredkinCell c1(true);
        FredkinCell c2(true);
        CPPUNIT_ASSERT(c1.equals(c2));
    }

    void test_equals_4 () {
        FredkinCell c1(false);
        FredkinCell c2(false);
        CPPUNIT_ASSERT(c1.equals(c2));
    }

    void test_equals_5 () {
        FredkinCell c1(true,2);
        FredkinCell c2(false,2);
        CPPUNIT_ASSERT(!c1.equals(c2));
        CPPUNIT_ASSERT(!c2.equals(c1));
    }

    void test_equals_3b () {
        FredkinCell c1(true,5);
        FredkinCell c2(true,12);
        CPPUNIT_ASSERT(!c1.equals(c2));
    }

    void test_equals_4b () {
        FredkinCell c1(false,3);
        FredkinCell c2(false,4);
        CPPUNIT_ASSERT(!c1.equals(c2));
    }

    // -----------
    // operator <<
    // -----------
    void test_operatorll_1 () {
        FredkinCell cc(true,0);
        CPPUNIT_ASSERT(true == cc._isAlive);
        std::ostringstream w;
        w << cc;
        CPPUNIT_ASSERT("0" == w.str());
    }

    void test_operatorll_2 () {
        FredkinCell cc(false);
        CPPUNIT_ASSERT(false == cc._isAlive);
        std::ostringstream w;
        w << cc;
        CPPUNIT_ASSERT("-" == w.str());
    }

    void test_operatorll_3 () {
        FredkinCell fc(false,5);
        CPPUNIT_ASSERT(false == fc._isAlive);
        std::ostringstream w;
        w << fc;
        CPPUNIT_ASSERT("-" == w.str());
    }

    void test_operatorll_4 () {
        FredkinCell fc(true,5);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        w << fc;
        CPPUNIT_ASSERT("5" == w.str());
    }

    void test_operatorll_5 () {
        FredkinCell fc(true,9);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        w << fc;
        CPPUNIT_ASSERT("9" == w.str());
    }

    void test_operatorll_6 () {
        FredkinCell fc(true,10);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        w << fc;
        CPPUNIT_ASSERT("+" == w.str());
    }

    void test_operatorll_7 () {
        FredkinCell fc(true,37);
        CPPUNIT_ASSERT(true == fc._isAlive);
        std::ostringstream w;
        w << fc;
        CPPUNIT_ASSERT("+" == w.str());
    }
    // -----------
    // operator ==
    // -----------
    void test_operatoreq_1 () {
        FredkinCell c1(false);
        CPPUNIT_ASSERT(c1 == c1);
    }

    void test_operatoreq_2 () {
        FredkinCell c1(true);
        CPPUNIT_ASSERT(c1 == c1);
    }

    void test_operatoreq_3 () {
        FredkinCell c1(true);
        FredkinCell c2(true);
        CPPUNIT_ASSERT(c1 == c2);
    }

    void test_operatoreq_4 () {
        FredkinCell c1(false);
        FredkinCell c2(false);
        CPPUNIT_ASSERT(c1 == c2);
    }

    void test_operatoreq_5 () {
        FredkinCell c1(true);
        FredkinCell c2(false);
        CPPUNIT_ASSERT(!(c1 == c2));
        CPPUNIT_ASSERT(!(c2 == c1));
    }

    void test_operatoreq_3b () {
        FredkinCell c1(true,5);
        FredkinCell c2(true,12);
        CPPUNIT_ASSERT(!(c1 == c2));
    }

    void test_operatoreq_4b () {
        FredkinCell c1(false,3);
        FredkinCell c2(false,4);
        CPPUNIT_ASSERT(!(c1 == c2));
    }
    // -----------
    // operator !=
    // -----------
    void test_operatorneq_1 () {
        FredkinCell c1(false);
        CPPUNIT_ASSERT(!(c1 != c1));
    }

    void test_operatorneq_2 () {
        FredkinCell c1(true);
        CPPUNIT_ASSERT(!(c1 != c1));
    }

    void test_operatorneq_3 () {
        FredkinCell c1(true);
        FredkinCell c2(true);
        CPPUNIT_ASSERT(!(c1 != c2));
    }

    void test_operatorneq_4 () {
        FredkinCell c1(false);
        FredkinCell c2(false);
        CPPUNIT_ASSERT(!(c1 != c2));
    }

    void test_operatorneq_5 () {
        FredkinCell c1(true);
        FredkinCell c2(false);
        CPPUNIT_ASSERT(c1 != c2);
        CPPUNIT_ASSERT(c2 != c1);
    }

    void test_operatorneq_3b () {
        FredkinCell c1(true,5);
        FredkinCell c2(true,12);
        CPPUNIT_ASSERT(c1 != c2);
    }

    void test_operatorneq_4b () {
        FredkinCell c1(false,3);
        FredkinCell c2(false,4);
        CPPUNIT_ASSERT(c1 != c2);
    }

    // ------
    // evolve
    // ------
    void test_evolve_d_0 () {
        unsigned int neighbors = 0;
        bool isAlive = false;
        const bool result  = false;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_d_1 () {
        unsigned int neighbors = 1;
        bool isAlive = false;
        const bool result  = true;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_d_2 () {
        unsigned int neighbors = 2;
        bool isAlive = false;
        const bool result  = false;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_d_3 () {
        unsigned int neighbors = 3;
        bool isAlive = false;
        const bool result  = true;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_d_4 () {
        unsigned int neighbors = 4;
        bool isAlive = false;
        const bool result  = false;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_a_0 () {
        unsigned int neighbors = 0;
        bool isAlive = true;
        const bool result  = false;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_a_1 () {
        unsigned int neighbors = 1;
        bool isAlive = true;
        const bool result  = true;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(4 == c._age);
    }

    void test_evolve_a_2 () {
        unsigned int neighbors = 2;
        bool isAlive = true;
        const bool result  = false;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_evolve_a_3 () {
        unsigned int neighbors = 3;
        bool isAlive = true;
        const bool result  = true;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(4 == c._age);
    }

    void test_evolve_a_4 () {
        unsigned int neighbors = 4;
        bool isAlive = true;
        const bool result  = false;

        FredkinCell c(isAlive,3);
        c.evolve(neighbors);
        CPPUNIT_ASSERT(result == c._isAlive);
        CPPUNIT_ASSERT(3 == c._age);
    }

    void test_operatoreq_diff_1 () {
        FredkinCell f(false,0);
        ConwayCell  c(false);
        CPPUNIT_ASSERT(f != c);
        CPPUNIT_ASSERT(c != f);
    }

    void test_operatoreq_diff_2 () {
        FredkinCell f(false,3);
        ConwayCell  c(false);
        CPPUNIT_ASSERT(f != c);
        CPPUNIT_ASSERT(c != f);
    }

    void test_operatoreq_diff_3 () {
        FredkinCell f(true,0);
        ConwayCell  c(true);
        CPPUNIT_ASSERT(f != c);
        CPPUNIT_ASSERT(c != f);
    }

    void test_operatoreq_diff_4 () {
        FredkinCell f(true,3);
        ConwayCell  c(true);
        CPPUNIT_ASSERT(f != c);
        CPPUNIT_ASSERT(c != f);
    }

    CPPUNIT_TEST_SUITE(TestFredkinCell);
    CPPUNIT_TEST(test_get_valid_neighbors);
    
    CPPUNIT_TEST(test_constructor_1);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_3);
    CPPUNIT_TEST(test_constructor_4);
    CPPUNIT_TEST(test_constructor_5);
    
    CPPUNIT_TEST(test_write_1);
    CPPUNIT_TEST(test_write_2);
    CPPUNIT_TEST(test_write_3);
    CPPUNIT_TEST(test_write_4);
    CPPUNIT_TEST(test_write_5);
    CPPUNIT_TEST(test_write_6);
    CPPUNIT_TEST(test_write_7);
    
    CPPUNIT_TEST(test_equals_1);
    CPPUNIT_TEST(test_equals_2);
    CPPUNIT_TEST(test_equals_3);
    CPPUNIT_TEST(test_equals_4);
    CPPUNIT_TEST(test_equals_5);
    CPPUNIT_TEST(test_equals_3b);
    CPPUNIT_TEST(test_equals_4b);
    
    CPPUNIT_TEST(test_operatorll_1);
    CPPUNIT_TEST(test_operatorll_2);
    CPPUNIT_TEST(test_operatorll_3);
    CPPUNIT_TEST(test_operatorll_4);
    CPPUNIT_TEST(test_operatorll_5);
    CPPUNIT_TEST(test_operatorll_6);
    CPPUNIT_TEST(test_operatorll_7);
    
    CPPUNIT_TEST(test_operatoreq_1);
    CPPUNIT_TEST(test_operatoreq_2);
    CPPUNIT_TEST(test_operatoreq_3);
    CPPUNIT_TEST(test_operatoreq_4);
    CPPUNIT_TEST(test_operatoreq_5);
    CPPUNIT_TEST(test_operatoreq_3b);
    CPPUNIT_TEST(test_operatoreq_4b);
    
    CPPUNIT_TEST(test_operatorneq_1);
    CPPUNIT_TEST(test_operatorneq_2);
    CPPUNIT_TEST(test_operatorneq_3);
    CPPUNIT_TEST(test_operatorneq_4);
    CPPUNIT_TEST(test_operatorneq_5);
    CPPUNIT_TEST(test_operatorneq_3b);
    CPPUNIT_TEST(test_operatorneq_4b);
    
    CPPUNIT_TEST(test_evolve_d_0);
    CPPUNIT_TEST(test_evolve_d_1);
    CPPUNIT_TEST(test_evolve_d_2);
    CPPUNIT_TEST(test_evolve_d_3);
    CPPUNIT_TEST(test_evolve_d_4);
    CPPUNIT_TEST(test_evolve_a_0);
    CPPUNIT_TEST(test_evolve_a_1);
    CPPUNIT_TEST(test_evolve_a_2);
    CPPUNIT_TEST(test_evolve_a_3);
    CPPUNIT_TEST(test_evolve_a_4);

    CPPUNIT_TEST(test_operatoreq_diff_1);
    CPPUNIT_TEST(test_operatoreq_diff_2);
    CPPUNIT_TEST(test_operatoreq_diff_3);
    CPPUNIT_TEST(test_operatoreq_diff_4);

    CPPUNIT_TEST_SUITE_END();
};

// --------
// TestCell
// --------
struct TestCell : CppUnit::TestFixture {
    void test_constructor_1 () {

    }

    CPPUNIT_TEST_SUITE(TestCell);

    CPPUNIT_TEST_SUITE_END();
};

// ---------
// TestWorld
// ---------
template <typename T>
struct TestWorld : CppUnit::TestFixture {

    // -------------
    // find_adjacent
    // -------------
    void test_find_adjacent_NORTH () {
        const direction_t d = NORTH;
        const coordinate_t ans = {3,4};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_NORTHEAST () {
        const direction_t d = NORTHEAST;
        const coordinate_t ans = {3,5};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_EAST () {
        const direction_t d = EAST;
        const coordinate_t ans = {4,5};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_SOUTHEAST () {
        const direction_t d = SOUTHEAST;
        const coordinate_t ans = {5,5};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_SOUTH () {
        const direction_t d = SOUTH;
        const coordinate_t ans = {5,4};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_SOUTHWEST () {
        const direction_t d = SOUTHWEST;
        const coordinate_t ans = {5,3};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_WEST () {
        const direction_t d = WEST;
        const coordinate_t ans = {4,3};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    void test_find_adjacent_NORTHWEST () {
        const direction_t d = NORTHWEST;
        const coordinate_t ans = {3,3};

        coordinate_t cp = {4,4};
        coordinate_t cn = World<T>::find_adjacent(cp, d);
        CPPUNIT_ASSERT(ans == cn);
    }

    // -----------
    // constructor
    // -----------
    void test_constructor () {
        World<T> t(1,1);
        T c;
        CPPUNIT_ASSERT(1 == t._rows);
        CPPUNIT_ASSERT(1 == t._columns);
        CPPUNIT_ASSERT(c == t._grid[0][0]);
    }    

    void test_constructor_2 () {
        T c(true);
        World<T> t(1,1,c);
        CPPUNIT_ASSERT(1 == t._rows);
        CPPUNIT_ASSERT(1 == t._columns);
        CPPUNIT_ASSERT(c == t._grid[0][0]);
        CPPUNIT_ASSERT(&c != &t._grid[0][0]);
    }

    void test_constructor_invalid_1 () {
        try {
            World<T> t(0,1);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) { /*nothing to be done*/ }
    }

    void test_constructor_invalid_2 () {
        try {
            World<T> t(1,0);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) { /*nothing to be done*/ }
    }

    // ------------
    // is_in_bounds
    // ------------
    void test_is_in_bounds_1 () {
        World<T> A(10,6);
        coordinate_t c = {0,0};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_2 () {
        World<T> A(10,6);
        coordinate_t c = {9,0};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_3 () {
        World<T> A(10,6);
        coordinate_t c = {0,5};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_4 () {
        World<T> A(10,6);
        coordinate_t c = {9,5};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_in_bounds_5 () {
        World<T> A(10,6);
        coordinate_t c = {3,2};
        CPPUNIT_ASSERT(A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_1 () {
        World<T> A(5,9);
        coordinate_t c = {-1,0};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_2 () {
        World<T> A(5,9);
        coordinate_t c = {0,-1};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_3 () {
        World<T> A(5,9);
        coordinate_t c = {-1,-1};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_4 () {
        World<T> A(5,9);
        coordinate_t c = {5,0};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_5 () {
        World<T> A(5,9);
        coordinate_t c = {0,9};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_6 () {
        World<T> A(5,9);
        coordinate_t c = {5,9};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    void test_is_not_in_bounds_7 () {
        World<T> A(5,9);
        coordinate_t c = {14,18};
        CPPUNIT_ASSERT(!A.is_in_bounds(c));
    }

    // -------
    // replace
    // -------
    void test_replace_1 () {
        World<T> A(3,3);
        T c(true);

        CPPUNIT_ASSERT(c != A._grid[1][1]);
        A.replace(1,1,c);
        CPPUNIT_ASSERT(c == A._grid[1][1]);
        CPPUNIT_ASSERT(&c != &A._grid[1][1]);
    }

    void test_replace_2 () {
        T c(true);
        World<T> A(3,3,c);
        T d(false);

        CPPUNIT_ASSERT(c == A._grid[1][1]);
        A.replace(1,1,d);
        CPPUNIT_ASSERT(d == A._grid[1][1]);
        CPPUNIT_ASSERT(&d != &A._grid[1][1]);
    }

    CPPUNIT_TEST_SUITE(TestWorld);
    CPPUNIT_TEST(test_find_adjacent_NORTH);
    CPPUNIT_TEST(test_find_adjacent_NORTHEAST);
    CPPUNIT_TEST(test_find_adjacent_EAST);
    CPPUNIT_TEST(test_find_adjacent_SOUTHEAST);
    CPPUNIT_TEST(test_find_adjacent_SOUTH);
    CPPUNIT_TEST(test_find_adjacent_SOUTHWEST);
    CPPUNIT_TEST(test_find_adjacent_WEST);
    CPPUNIT_TEST(test_find_adjacent_NORTHWEST);

    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_constructor_2);
    CPPUNIT_TEST(test_constructor_invalid_1);
    CPPUNIT_TEST(test_constructor_invalid_2);

    CPPUNIT_TEST(test_is_in_bounds_1);
    CPPUNIT_TEST(test_is_in_bounds_2);
    CPPUNIT_TEST(test_is_in_bounds_3);
    CPPUNIT_TEST(test_is_in_bounds_4);
    CPPUNIT_TEST(test_is_in_bounds_5);
    CPPUNIT_TEST(test_is_not_in_bounds_1);
    CPPUNIT_TEST(test_is_not_in_bounds_2);
    CPPUNIT_TEST(test_is_not_in_bounds_3);
    CPPUNIT_TEST(test_is_not_in_bounds_4);
    CPPUNIT_TEST(test_is_not_in_bounds_5);
    CPPUNIT_TEST(test_is_not_in_bounds_6);
    CPPUNIT_TEST(test_is_not_in_bounds_7);

    CPPUNIT_TEST(test_replace_1);
    CPPUNIT_TEST(test_replace_2);

    CPPUNIT_TEST_SUITE_END();
};

// --------
// TestLife
// --------
template <typename T>
struct TestLife : CppUnit::TestFixture {
    // -----------
    // constructor
    // -----------
    void test_constructor () {
        Life<T> t(1,1);
        T c;
        CPPUNIT_ASSERT(1 == t._rows);
        CPPUNIT_ASSERT(1 == t._columns);
        CPPUNIT_ASSERT(1 == t._world._rows);
        CPPUNIT_ASSERT(1 == t._world._columns);
        CPPUNIT_ASSERT(c == t._world._grid[0][0]);
    }

    void test_constructor_invalid_1 () {
        try {
            Life<T> t(0,1);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) { /*nothing to be done*/ }
    }

    void test_constructor_invalid_2 () {
        try {
            Life<T> t(1,0);
            CPPUNIT_ASSERT(false);
        } catch (std::invalid_argument&) { /*nothing to be done*/ }
    }

    // --------------
    // checked_update
    // --------------
    void test_checked_update_cc_1 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        t.checked_update(1,1);
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_checked_update_cc_2 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[0][0]._isAlive = true;
        t.checked_update(0,0);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][2]);
    }

    void test_checked_update_cc_3 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[2][1]._isAlive = true;
        t.checked_update(2,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_checked_update_cc_4 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.checked_update(1,1);
        t.checked_update(2,1);
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][2]);
    }

    void test_checked_update_fc_1 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        t.checked_update(1,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][2]);
    }

    void test_checked_update_fc_2 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[0][0]._isAlive = true;
        t.checked_update(0,0);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][2]);
    }

    void test_checked_update_fc_3 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[2][1]._isAlive = true;
        t.checked_update(2,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_checked_update_fc_4 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.checked_update(1,1);
        t.checked_update(2,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_checked_update_fc_5 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][0]._isAlive = true;
        w._grid[1][2]._isAlive = true;
        t.checked_update(1,0);
        t.checked_update(1,2);
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    // ----------------
    // unchecked_update
    // ----------------
    void test_unchecked_update_cc_1 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        t.unchecked_update(1,1);
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_unchecked_update_cc_2 () {
        Life<ConwayCell> t(4,3);
        World<ConwayCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.unchecked_update(1,1);
        t.unchecked_update(2,1);
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][2]);
    }

    void test_unchecked_update_fc_1 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        t.unchecked_update(1,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][2]);
    }

    void test_unchecked_update_fc_2 () {
        Life<FredkinCell> t(4,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.unchecked_update(1,1);
        t.unchecked_update(2,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[3][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[3][2]);
    }

    // ----------------
    // update_neighbors
    // ----------------
    void test_update_neighbors_cc_1 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.update_neighbors();
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][2]);
    }

    void test_update_neighbors_cc_2 () {
        Life<ConwayCell> t(4,3);
        World<ConwayCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.update_neighbors();
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(2 == t._neighbors[2][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][2]);
    }

    void test_update_neighbors_cc_3 () {
        Life<ConwayCell> t(3,3);
        World<ConwayCell>& w = t._world;
        w._grid[0][0]._isAlive = true;
        w._grid[0][2]._isAlive = true;
        w._grid[2][2]._isAlive = true;
        w._grid[2][0]._isAlive = true;
        w._grid[1][1]._isAlive = true;
        t.update_neighbors();
        CPPUNIT_ASSERT(1 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(3 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(3 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(4 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(3 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(3 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_update_neighbors_fc_1 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.update_neighbors();
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
    }

    void test_update_neighbors_fc_2 () {
        Life<FredkinCell> t(4,3);
        World<FredkinCell>& w = t._world;
        w._grid[1][1]._isAlive = true;
        w._grid[2][1]._isAlive = true;
        t.update_neighbors();
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(1 == t._neighbors[2][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[3][0]);
        CPPUNIT_ASSERT(1 == t._neighbors[3][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[3][2]);
    }

    void test_update_neighbors_fc_3 () {
        Life<FredkinCell> t(3,3);
        World<FredkinCell>& w = t._world;
        w._grid[0][0]._isAlive = true;
        w._grid[0][2]._isAlive = true;
        w._grid[2][2]._isAlive = true;
        w._grid[2][0]._isAlive = true;
        w._grid[1][1]._isAlive = true;
        t.update_neighbors();
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        CPPUNIT_ASSERT(3 == t._neighbors[0][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(3 == t._neighbors[1][0]);
        CPPUNIT_ASSERT(0 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(3 == t._neighbors[1][2]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(3 == t._neighbors[2][1]);
        CPPUNIT_ASSERT(0 == t._neighbors[2][2]);
    }

    // ---------------
    // clear_neighbors
    // ---------------
    void test_clear_neighbors_1 () {
        Life<T> t(1,1);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        t._neighbors[0][0] = 4;
        CPPUNIT_ASSERT(4 == t._neighbors[0][0]);
        t.clear_neighbors();
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
    }

    void test_clear_neighbors_2 () {
        Life<T> t(1,5);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        t._neighbors[0][2] = 5;
        t._neighbors[0][4] = 2;
        CPPUNIT_ASSERT(5 == t._neighbors[0][2]);
        CPPUNIT_ASSERT(2 == t._neighbors[0][4]);
        t.clear_neighbors();
        for (size_t i = 0; i < 5; ++i) {
            CPPUNIT_ASSERT(0 == t._neighbors[0][i]);
        }
    }

    void test_clear_neighbors_3 () {
        Life<T> t(5,2);
        CPPUNIT_ASSERT(0 == t._neighbors[0][0]);
        t._neighbors[2][0] = 5;
        t._neighbors[4][0] = 2;
        t._neighbors[1][1] = 3;
        t._neighbors[3][1] = 7;
        CPPUNIT_ASSERT(5 == t._neighbors[2][0]);
        CPPUNIT_ASSERT(2 == t._neighbors[4][0]);
        CPPUNIT_ASSERT(3 == t._neighbors[1][1]);
        CPPUNIT_ASSERT(7 == t._neighbors[3][1]);
        t.clear_neighbors();
        for (size_t r = 0; r < 5; ++r) {
            for (size_t c = 0; c < 2; ++c) {
                CPPUNIT_ASSERT(0 == t._neighbors[r][c]);
            }
        }
    }

    // ---
    // set
    // ---
    void test_set_1 () {
        Life<T> t(3,3);
        T c(true);
        World<T>& A = t._world;

        CPPUNIT_ASSERT(c != A._grid[1][1]);
        t.set(1,1,c);
        CPPUNIT_ASSERT(c == A._grid[1][1]);
        CPPUNIT_ASSERT(&c != &A._grid[1][1]);
    }

    void test_set_2 () {
        T c(true);
        Life<T> t(3,3,c);
        T d(false);
        World<T>& A = t._world;

        CPPUNIT_ASSERT(c == A._grid[1][1]);
        t.set(1,1,d);
        CPPUNIT_ASSERT(d == A._grid[1][1]);
        CPPUNIT_ASSERT(&d != &A._grid[1][1]);
    }

    CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(test_constructor);
    CPPUNIT_TEST(test_constructor_invalid_1);
    CPPUNIT_TEST(test_constructor_invalid_2);
    
    CPPUNIT_TEST(test_checked_update_cc_1);
    CPPUNIT_TEST(test_checked_update_cc_2);
    CPPUNIT_TEST(test_checked_update_cc_3);
    CPPUNIT_TEST(test_checked_update_cc_4);
    CPPUNIT_TEST(test_checked_update_fc_1);
    CPPUNIT_TEST(test_checked_update_fc_2);
    CPPUNIT_TEST(test_checked_update_fc_3);
    CPPUNIT_TEST(test_checked_update_fc_4);
    CPPUNIT_TEST(test_checked_update_fc_5);

    CPPUNIT_TEST(test_unchecked_update_cc_1);
    CPPUNIT_TEST(test_unchecked_update_cc_2);
    CPPUNIT_TEST(test_unchecked_update_fc_1);
    CPPUNIT_TEST(test_unchecked_update_fc_2);

    CPPUNIT_TEST(test_update_neighbors_cc_1);
    CPPUNIT_TEST(test_update_neighbors_cc_2);
    CPPUNIT_TEST(test_update_neighbors_cc_3);
    CPPUNIT_TEST(test_update_neighbors_fc_1);
    CPPUNIT_TEST(test_update_neighbors_fc_2);
    CPPUNIT_TEST(test_update_neighbors_fc_3);

    CPPUNIT_TEST(test_clear_neighbors_1);
    CPPUNIT_TEST(test_clear_neighbors_2);
    CPPUNIT_TEST(test_clear_neighbors_3);

    CPPUNIT_TEST(test_set_1);
    CPPUNIT_TEST(test_set_2);

    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    cout << "\nTestConwayCell::suite()" << endl;
    CppUnit::TextTestRunner tcc;
    tcc.addTest(TestConwayCell::suite());
    tcc.run();

    cout << "\nTestFredkinCell::suite()" << endl;
    CppUnit::TextTestRunner tfc;
    tfc.addTest(TestFredkinCell::suite());
    tfc.run();

    cout << "\nTestWorld::suite()" << endl;
    CppUnit::TextTestRunner tw;
    tw.addTest(TestWorld<ConwayCell>::suite());
    tw.addTest(TestWorld<FredkinCell>::suite());
    tw.run();

    cout << "\nTestLife::suite()" << endl;
    CppUnit::TextTestRunner tl;
    tl.addTest(TestLife<ConwayCell>::suite());
    tl.addTest(TestLife<FredkinCell>::suite());
    tl.run();

    cout << "Done." << endl;
    return 0;
}
