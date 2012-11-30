/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------
#include <stdexcept>
#include <cstdlib>                            // srand
#include <string>
#include <iostream>
#include <sstream>

#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"              // TestFixture
#include "cppunit/TextTestRunner.h"           // TestRunner

#include "./AbstractCell.h"
#include "./ConwayCell.h"
#include "./FredkinCell.h"
#include "./Cell.h"
#include "./Life.h"

using namespace std;

#define ASSERT(b) CPPUNIT_ASSERT(b)

struct TestCoordinate : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    void test_ctor_1() {
        Coordinate c;
        ASSERT(c.row == 0);
        ASSERT(c.col == 0);
    }

    void test_ctor_2() {
        Coordinate c(1);
        ASSERT(c.row == 1);
        ASSERT(c.col == 0);
    }

    void test_ctor_3() {
        Coordinate c(1, 2);
        ASSERT(c.row == 1);
        ASSERT(c.col == 2);
    }

    void test_ctor_4() {
        Coordinate c(-3, 5);
        ASSERT(c.row == -3);
        ASSERT(c.col == 5);
    }

    void test_ctor_5() {
        Coordinate c(-23456, -45678);
        ASSERT(c.row == -23456);
        ASSERT(c.col == -45678);
    }

    // -----------
    // test_equals
    // -----------

    void test_equals_1() {
        Coordinate c;
        ASSERT(c == Coordinate());
        ASSERT(c == Coordinate(0, 0));
    }

    void test_equals_2() {
        Coordinate c(1);
        ASSERT(c == Coordinate(1));
        ASSERT(c == Coordinate(1, 0));
    }

    void test_equals_3() {
        Coordinate c(2, 3);
        ASSERT(c == Coordinate(2, 3));
    }

    void test_equals_4() {
        Coordinate c(-2, -3);
        ASSERT(c == Coordinate(-2, -3));
    }

    void test_equals_5() {
        Coordinate c(-2, -3);
        Coordinate d(-2, -3);
        ASSERT(c == d);
        ASSERT(d == c);
        ASSERT(&c != &d);
    }

    void test_equals_6() {
        ASSERT(Coordinate(1, 1) == Coordinate(1, 1));
    }

    // -----------
    // test_negate
    // -----------

    void test_negate_1() {
        Coordinate c;
        c = -c;
        ASSERT(c.row == 0);
        ASSERT(c.col == 0);
    }

    void test_negate_2() {
        Coordinate c(2);
        c = -c;
        ASSERT(c == Coordinate(-2));
        ASSERT(c == Coordinate(-2, 0));
    }

    void test_negate_3() {
        Coordinate c(4, 5);
        Coordinate d = -c;
        Coordinate e(-4, -5);

        ASSERT(-c == d);
        ASSERT(c == -d);
        ASSERT(-c == e);
        ASSERT(c == -e);
        ASSERT(d == e);
    }

    // --------
    // test_add
    // --------

    void test_add_1() {
        Coordinate c;
        Coordinate d(1, 3);
        Coordinate result(1, 3);

        ASSERT(c + d == result);

        ASSERT(c == Coordinate(0, 0));
        ASSERT(d == Coordinate(1, 3));
    }

    void test_add_2() {
        Coordinate c(1, 2);
        Coordinate d(3, 3);
        Coordinate result(4, 5);

        ASSERT(c + d == result);

        ASSERT(c == Coordinate(1, 2));
        ASSERT(d == Coordinate(3, 3));
    }

    void test_add_3() {
        Coordinate c(4, 2);
        Coordinate d(-1, -1);
        Coordinate result(3, 1);
        Coordinate* p = &c;

        ASSERT(c + d == result);
        ASSERT(p == &c);

        ASSERT(c == Coordinate(4, 2));
        ASSERT(d == Coordinate(-1, -1));
    }

    void test_add_4() {
        Coordinate c(4, 2);
        Coordinate d(-1);
        Coordinate result(3, 2);
        Coordinate* p = &c;

        ASSERT(c + d == result);
        ASSERT(p == &c);

        ASSERT(c == Coordinate(4, 2));
        ASSERT(d == Coordinate(-1, 0));
    }

    // ---------------
    // test_plusEquals
    // ---------------

    void test_addEquals_1() {
        Coordinate c;
        Coordinate d(1, 3);
        Coordinate result(1, 3);

        ASSERT((c += d) == result);

        ASSERT(c == result);
        ASSERT(d == Coordinate(1, 3));
    }

    void test_addEquals_2() {
        Coordinate c(1, 2);
        Coordinate d(3, 3);
        Coordinate result(4, 5);

        ASSERT((c += d) == result);

        ASSERT(c == result);
        ASSERT(d == Coordinate(3, 3));
    }

    void test_addEquals_3() {
        Coordinate c(4, 2);
        Coordinate d(-1, -1);
        Coordinate result(3, 1);
        Coordinate* p = &c;

        ASSERT((c += d) == result);
        ASSERT(p == &c);

        ASSERT(c == result);
        ASSERT(d == Coordinate(-1, -1));
    }

    // --------
    // test_sub
    // --------

    void test_sub_1() {
        Coordinate c;
        Coordinate d(1, 3);
        Coordinate result(-1, -3);

        ASSERT(c - d == result);

        ASSERT(c == Coordinate(0, 0));
        ASSERT(d == Coordinate(1, 3));
    }

    void test_sub_2() {
        Coordinate c(1, 2);
        Coordinate d(3, 3);
        Coordinate result(-2, -1);

        ASSERT(c - d == result);

        ASSERT(c == Coordinate(1, 2));
        ASSERT(d == Coordinate(3, 3));
    }

    void test_sub_3() {
        Coordinate c(4, 2);
        Coordinate d(-1, -1);
        Coordinate result(5, 3);
        Coordinate* p = &c;

        ASSERT(c - d == result);
        ASSERT(p == &c);

        ASSERT(c == Coordinate(4, 2));
        ASSERT(d == Coordinate(-1, -1));
    }

    // ----------------
    // test_minusEquals
    // ----------------

    void test_minusEquals_1() {
        Coordinate c;
        Coordinate d(1, 3);
        Coordinate result(-1, -3);

        ASSERT((c -= d) == result);

        ASSERT(c == result);
        ASSERT(d == Coordinate(1, 3));
    }

    void test_minusEquals_2() {
        Coordinate c(1, 2);
        Coordinate d(3, 3);
        Coordinate result(-2, -1);

        ASSERT((c -= d) == result);

        ASSERT(c == result);
        ASSERT(d == Coordinate(3, 3));
    }

    void test_minusEquals_3() {
        Coordinate c(4, 2);
        Coordinate d(-1, -1);
        Coordinate result(5, 3);
        Coordinate* p = &c;

        ASSERT((c -= d) == result);
        ASSERT(p == &c);

        ASSERT(c == result);
        ASSERT(d == Coordinate(-1, -1));
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCoordinate);
        CPPUNIT_TEST(test_ctor_1);
        CPPUNIT_TEST(test_ctor_2);
        CPPUNIT_TEST(test_ctor_3);
        CPPUNIT_TEST(test_ctor_4);
        CPPUNIT_TEST(test_ctor_5);

        CPPUNIT_TEST(test_equals_1);
        CPPUNIT_TEST(test_equals_2);
        CPPUNIT_TEST(test_equals_3);
        CPPUNIT_TEST(test_equals_4);
        CPPUNIT_TEST(test_equals_5);
        CPPUNIT_TEST(test_equals_6);

        CPPUNIT_TEST(test_negate_1);
        CPPUNIT_TEST(test_negate_2);
        CPPUNIT_TEST(test_negate_3);

        CPPUNIT_TEST(test_add_1);
        CPPUNIT_TEST(test_add_2);
        CPPUNIT_TEST(test_add_3);
        CPPUNIT_TEST(test_add_4);

        CPPUNIT_TEST(test_addEquals_1);
        CPPUNIT_TEST(test_addEquals_2);
        CPPUNIT_TEST(test_addEquals_3);

        CPPUNIT_TEST(test_sub_1);
        CPPUNIT_TEST(test_sub_2);
        CPPUNIT_TEST(test_sub_3);

        CPPUNIT_TEST(test_minusEquals_1);
        CPPUNIT_TEST(test_minusEquals_2);
        CPPUNIT_TEST(test_minusEquals_3);
    CPPUNIT_TEST_SUITE_END();
};

struct TestAbstractCell : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    void test_ctor() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.getLivingNeighborCount() == 0);
        ASSERT(a.isAlive() == false);
    }

    // ------------------------------------------
    // test_neighborCount (increment, set, reset)
    // ------------------------------------------

    void test_neighborCount_1() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.getLivingNeighborCount() == 0);
        a.incrementLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 1);
        a.incrementLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 2);

        a.resetLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 0);

        a.setLivingNeighborCount(6);
        ASSERT(a.getLivingNeighborCount() == 6);
    }

    void test_neighborCount_2() {
        ConwayCell c;
        AbstractCell& a = c;

        a.setLivingNeighborCount(6);
        ASSERT(a.getLivingNeighborCount() == 6);

        a.incrementLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 7);

        a.resetLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 0);
    }

    void test_neighborCount_3() {
        ConwayCell c;
        AbstractCell& a = c;

        a.setLivingNeighborCount(6);
        ASSERT(a.getLivingNeighborCount() == 6);

        a.resetLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 0);

        a.incrementLivingNeighborCount();
        ASSERT(a.getLivingNeighborCount() == 1);
    }

    // --------------------------
    // test_isAlive (die, revive)
    // --------------------------

    void test_isAlive_1() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.isAlive() == false);
        a.revive();
        ASSERT(a.isAlive() == true);
    }

    void test_isAlive_2() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.isAlive() == false);
        a.die();  // should still be dead
        ASSERT(a.isAlive() == false);
    }

    void test_isAlive_3() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.isAlive() == false);
        a.revive();
        ASSERT(a.isAlive() == true);
        a.revive();  // should still be alive
        ASSERT(a.isAlive() == true);
    }

    void test_isAlive_4() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.isAlive() == false);
        a.revive();
        ASSERT(a.isAlive() == true);
        a.die();
        ASSERT(a.isAlive() == false);
        a.die();
        ASSERT(a.isAlive() == false);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestAbstractCell);
        CPPUNIT_TEST(test_ctor);

        CPPUNIT_TEST(test_neighborCount_1);
        CPPUNIT_TEST(test_neighborCount_2);
        CPPUNIT_TEST(test_neighborCount_3);

        CPPUNIT_TEST(test_isAlive_1);
        CPPUNIT_TEST(test_isAlive_2);
        CPPUNIT_TEST(test_isAlive_3);
        CPPUNIT_TEST(test_isAlive_4);
    CPPUNIT_TEST_SUITE_END();
};

struct TestConwayCell : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    void test_ctor_1() {
        ConwayCell c;

        ASSERT(c.getLivingNeighborCount() == 0);
        ASSERT(c.isAlive() == false);
    }

    void test_ctor_2() {
        ConwayCell c(false);

        ASSERT(c.getLivingNeighborCount() == 0);
        ASSERT(c.isAlive() == false);
    }

    void test_ctor_3() {
        ConwayCell c(true);

        ASSERT(c.getLivingNeighborCount() == 0);
        ASSERT(c.isAlive() == true);
    }

    // --------------
    // test_getSymbol
    // --------------

    void test_getSymbol_1() {
        ConwayCell c;

        ASSERT(c.getSymbol() == '.');
        c.revive();
        ASSERT(c.getSymbol() == '*');
        c.die();
        ASSERT(c.getSymbol() == '.');
    }

    void test_getSymbol_2() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.getSymbol() == '.');
        a.revive();
        ASSERT(a.getSymbol() == '*');
    }

    void test_getSymbol_3() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.getSymbol() == '.');
        a.die();  // should still be dead
        ASSERT(a.getSymbol() == '.');
    }

    void test_getSymbol_4() {
        ConwayCell c;
        AbstractCell& a = c;

        ASSERT(a.getSymbol() == '.');
        a.revive();
        ASSERT(a.getSymbol() == '*');
        a.revive();  // should still be alive
        ASSERT(a.getSymbol() == '*');
    }

    // -----------
    // test_evolve
    // -----------

    void test_evolve_1() {
        ConwayCell c;

        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
        ASSERT(c.getSymbol() == '.');
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_2() {
        ConwayCell c;

        ASSERT(!c.isAlive());
        c.setLivingNeighborCount(2);
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_3() {
        ConwayCell c;

        ASSERT(!c.isAlive());
        c.setLivingNeighborCount(3);
        c.evolve();
        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_4() {
        ConwayCell c;

        ASSERT(!c.isAlive());
        c.setLivingNeighborCount(4);
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_5() {
        ConwayCell c;
        c.revive();

        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_6() {
        ConwayCell c;
        c.revive();
        c.setLivingNeighborCount(1);

        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 1);
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_7() {
        ConwayCell c;
        c.revive();
        c.setLivingNeighborCount(2);

        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 2);
        c.evolve();
        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_8() {
        ConwayCell c;
        c.revive();
        c.setLivingNeighborCount(3);

        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 3);
        c.evolve();
        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_9() {
        ConwayCell c;
        c.revive();
        c.setLivingNeighborCount(4);

        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 4);
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    void test_evolve_10() {
        ConwayCell c;
        c.revive();
        c.setLivingNeighborCount(9);

        ASSERT(c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 9);
        c.evolve();
        ASSERT(!c.isAlive());
        ASSERT(c.getLivingNeighborCount() == 0);
    }

    // --------------------
    // test_processNeighbor
    // --------------------

    /**
     * Check that a square of boxes nowhere near the cell has no effect.
     */
    void test_processNeighbor_1() {
        ConwayCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        ConwayCell d;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(5, 5));
                ASSERT(c.getLivingNeighborCount() == 0);
            }
        }
    }

    /**
     * Check all the boxes outside the area of the neighbors we care about.
     */
    void test_processNeighbor_2() {
        ConwayCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        ConwayCell d;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if ((i >= 1 && i <= 3) || (j >= 1 && j <= 3)) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(2, 2));
                ASSERT(c.getLivingNeighborCount() == 0);
            }
        }
    }

    /**
     * Check the adjacent square.
     */
    void test_processNeighbor_3() {
        ConwayCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        ConwayCell d;
        d.revive();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(1, 1));
            }
        }

        ASSERT(c.getLivingNeighborCount() == 8);
    }

    /**
     * Check the adjacent square of cells, and surrounding cells.
     * Only the adjacent cells should have anything to do with it.
     */
    void test_processNeighbor_4() {
        ConwayCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        ConwayCell d;
        d.revive();
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i == 2 && j == 2) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(2, 2));
            }
        }

        ASSERT(c.getLivingNeighborCount() == 8);
    }

    /**
     * Check the + of cells going through (2,2) the location of this cell.
     */
    void test_processNeighbor_5() {
        ConwayCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        ConwayCell d;
        d.revive();
        for (int i = 0; i < 5; ++i) {
            if (i == 2) {
                continue;
            }
            c.processNeighbor(d, Coordinate(i, 2), Coordinate(2, 2));
            c.processNeighbor(d, Coordinate(2, i), Coordinate(2, 2));
        }

        ASSERT(c.getLivingNeighborCount() == 4);
    }

    /**
     * Check the X of cells going through (2,2) the location of this cell.
     */
    void test_processNeighbor_6() {
        ConwayCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        ConwayCell d;
        d.revive();
        for (int i = 0; i < 5; ++i) {
            if (i == 2) {
                continue;
            }
            c.processNeighbor(d, Coordinate(i, i), Coordinate(2, 2));
            c.processNeighbor(d, Coordinate(i, 4 - i), Coordinate(2, 2));
        }

        ASSERT(c.getLivingNeighborCount() == 4);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestConwayCell);
        CPPUNIT_TEST(test_ctor_1);
        CPPUNIT_TEST(test_ctor_2);
        CPPUNIT_TEST(test_ctor_3);

        CPPUNIT_TEST(test_getSymbol_1);
        CPPUNIT_TEST(test_getSymbol_2);
        CPPUNIT_TEST(test_getSymbol_3);
        CPPUNIT_TEST(test_getSymbol_4);

        CPPUNIT_TEST(test_evolve_1);
        CPPUNIT_TEST(test_evolve_2);
        CPPUNIT_TEST(test_evolve_3);
        CPPUNIT_TEST(test_evolve_4);
        CPPUNIT_TEST(test_evolve_5);
        CPPUNIT_TEST(test_evolve_6);
        CPPUNIT_TEST(test_evolve_7);
        CPPUNIT_TEST(test_evolve_8);
        CPPUNIT_TEST(test_evolve_9);
        CPPUNIT_TEST(test_evolve_10);

        CPPUNIT_TEST(test_processNeighbor_1);
        CPPUNIT_TEST(test_processNeighbor_2);
        CPPUNIT_TEST(test_processNeighbor_3);
        CPPUNIT_TEST(test_processNeighbor_4);
        CPPUNIT_TEST(test_processNeighbor_5);
        CPPUNIT_TEST(test_processNeighbor_6);
    CPPUNIT_TEST_SUITE_END();
};

struct TestFredkinCell : CppUnit::TestFixture {
    // ------------------------
    // test_constructor_display
    // ------------------------

    void test_ctor() {
        FredkinCell c;

        ASSERT(c.getLivingNeighborCount() == 0);
        ASSERT(c.isAlive() == false);

        c.revive();
        ASSERT(c.getSymbol() == '0');
    }

    // --------------------
    // test_processNeighbor
    // --------------------

    /**
     * Check that a square of boxes nowhere near the cell has no effect.
     */
    void test_processNeighbor_1() {
        FredkinCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        FredkinCell d;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(5, 5));
                ASSERT(c.getLivingNeighborCount() == 0);
            }
        }
    }

    /**
     * Check all the boxes outside the area of the neighbors we care about.
     */
    void test_processNeighbor_2() {
        FredkinCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        FredkinCell d;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if ((i >= 1 && i <= 3) || (j >= 1 && j <= 3)) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(2, 2));
                ASSERT(c.getLivingNeighborCount() == 0);
            }
        }
    }

    /**
     * Check the adjacent square.
     */
    void test_processNeighbor_3() {
        FredkinCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        FredkinCell d;
        d.revive();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(1, 1));
            }
        }

        ASSERT(c.getLivingNeighborCount() == 4);
    }

    /**
     * Check the adjacent square of cells, and surrounding cells.
     * Only the adjacent cells should have anything to do with it.
     */
    void test_processNeighbor_4() {
        FredkinCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        FredkinCell d;
        d.revive();
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i == 2 && j == 2) {
                    continue;
                }
                c.processNeighbor(d, Coordinate(i, j), Coordinate(2, 2));
            }
        }

        ASSERT(c.getLivingNeighborCount() == 4);
    }

    /**
     * Check the + of cells going through (2,2) the location of this cell.
     */
    void test_processNeighbor_5() {
        FredkinCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        FredkinCell d;
        d.revive();
        for (int i = 0; i < 5; ++i) {
            if (i == 2) {
                continue;
            }
            c.processNeighbor(d, Coordinate(i, 2), Coordinate(2, 2));
            c.processNeighbor(d, Coordinate(2, i), Coordinate(2, 2));
        }

        ASSERT(c.getLivingNeighborCount() == 4);
    }

    /**
     * Check the X of cells going through (2,2) the location of this cell.
     */
    void test_processNeighbor_6() {
        FredkinCell c;
        ASSERT(c.getLivingNeighborCount() == 0);

        FredkinCell d;
        d.revive();
        for (int i = 0; i < 5; ++i) {
            if (i == 2) {
                continue;
            }
            c.processNeighbor(d, Coordinate(i, i), Coordinate(2, 2));
            c.processNeighbor(d, Coordinate(i, 4 - i), Coordinate(2, 2));
        }

        ASSERT(c.getLivingNeighborCount() == 0);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestFredkinCell);
        CPPUNIT_TEST(test_ctor);
        // TODO test the other methods (issue #14)
        CPPUNIT_TEST(test_processNeighbor_1);
        CPPUNIT_TEST(test_processNeighbor_2);
        CPPUNIT_TEST(test_processNeighbor_3);
        CPPUNIT_TEST(test_processNeighbor_4);
        CPPUNIT_TEST(test_processNeighbor_5);
        CPPUNIT_TEST(test_processNeighbor_6);
    CPPUNIT_TEST_SUITE_END();
};

struct TestCell : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    void test_ctor_1() {
        AbstractCell *p = new ConwayCell(true);
        Cell c(p);
        ASSERT(c.isAlive() == true);
        ASSERT(c.getSymbol() == '*');

        p = new FredkinCell(true, 2);
        Cell f(p);
        ASSERT(f.isAlive() == true);
        ASSERT(f.getSymbol() == '2');
    }

    void test_ctor_2() {
        Cell a;
        ASSERT(a.isAlive() == false);
        ASSERT(a.getSymbol() == '.');

        Cell c(true);
        ASSERT(c.isAlive());
        ASSERT(c.getSymbol() == '*');

        Cell d(false);
        ASSERT(a.isAlive() == false);
        ASSERT(a.getSymbol() == '.');
    }

    void test_ctor_3() {
        Cell a('.');
        ASSERT(!a.isAlive());

        Cell b('*');
        ASSERT(b.isAlive());

        Cell c('-');
        ASSERT(!c.isAlive());

        Cell d('4');
        ASSERT(d.isAlive());

        Cell e('+');
        ASSERT(e.isAlive());
    }

    // ------------
    // test_isAlive
    // ------------

    /* tests implied by test_ctor */

    // --------------
    // test_getSymbol
    // --------------

    /* tests implied by test_ctor */

    // -----------
    // test_evolve
    // -----------

    void test_evolve_1() {
        Cell a('.');
        ASSERT(!a.isAlive());
        a.setLivingNeighborCount(3);
        a.evolve();
        ASSERT(a.isAlive());
    }

    void test_evolve_2() {
        Cell a('*');
        ASSERT(a.isAlive());
        a.setLivingNeighborCount(3);
        a.evolve();
        ASSERT(a.isAlive());
    }

    void test_evolve_3() {
        Cell a('-');
        ASSERT(!a.isAlive());
        a.setLivingNeighborCount(2);
        a.evolve();
        ASSERT(!a.isAlive());
    }

    void test_evolve_4() {
        Cell a('0');
        ASSERT(a.isAlive());
        a.setLivingNeighborCount(3);
        a.evolve();
        ASSERT(a.isAlive());
        ASSERT(a.getSymbol() == '1');
    }

    void test_evolve_5() {
        Cell a('1');
        ASSERT(a.isAlive());
        a.setLivingNeighborCount(3);
        a.evolve();
        ASSERT(a.isAlive());
        ASSERT(a.getSymbol() == '*');
    }


    // ---------------------------
    // test_setLivingNeighborCount
    // ---------------------------

    /* test implied by tests of subclasses */

    // --------------------
    // test_processNeighbor
    // --------------------

    /* test implied by tests of subclasses */

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestCell);
        CPPUNIT_TEST(test_ctor_1);
        CPPUNIT_TEST(test_ctor_2);
        CPPUNIT_TEST(test_ctor_3);

        CPPUNIT_TEST(test_evolve_1);
        CPPUNIT_TEST(test_evolve_2);
        CPPUNIT_TEST(test_evolve_3);
        CPPUNIT_TEST(test_evolve_4);
        CPPUNIT_TEST(test_evolve_5);
    CPPUNIT_TEST_SUITE_END();
};

struct TestLife : CppUnit::TestFixture {
    // ----------------
    // test_constructor
    // ----------------

    /**
     * Test default ctor for Conway.
     */
    void test_ctor_1() {
        Life<ConwayCell> life;

        ostringstream str;
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 0.\n");
    }

    /**
     * Simple 1x1 grid of Conways.
     */
    void test_ctor_2() {
        Life<ConwayCell> life(1, 1);

        ostringstream str;
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 0.\n.\n");
    }

    /**
     * Simple 2x2 grid of Conways.
     */
    void test_ctor_3() {
        Life<ConwayCell> life(2, 2);

        ostringstream str;
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 0.\n..\n..\n");
    }

    /**
     * Non-square grid (3x2) of Conways. Should be taller than wide.
     */
    void test_ctor_4() {
        Life<ConwayCell> life(3, 2);

        ostringstream str;
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 0.\n..\n..\n..\n");
    }

    /**
     * Simple 2x2 grid of live Conways.
     */
    void test_ctor_5() {
        Life<ConwayCell> life(2, 2, ConwayCell(true));

        ostringstream str;
        life.display(str);
        ASSERT(life.getPopulation() == 4);
        ASSERT(str.str() == "\nGeneration = 0, Population = 4.\n**\n**\n");
    }


    /**
     * 2x4 grid of live Conways.
     */
    void test_ctor_6() {
        Life<ConwayCell> life(2, 4, ConwayCell(true));

        ostringstream str;
        life.display(str);
        ASSERT(life.getPopulation() == 8);
        ASSERT(str.str() == "\nGeneration = 0, Population = 8.\n****\n****\n");
    }

    // ------------
    // test_setCell
    // ------------

    /**
     * Start with dead cells.
     * Setting dead->alive causes increase in population.
     * Setting dead->dead causes no change in population.
     */
    void test_setCell_1() {
        Life<ConwayCell> life(2, 2);
        ASSERT(life.getPopulation() == 0);

        life.setCell(Coordinate(0, 0), ConwayCell(true));
        ASSERT(life.getPopulation() == 1);

        life.setCell(Coordinate(1, 1), ConwayCell(false));
        ASSERT(life.getPopulation() == 1);
    }

    /**
     * Start with live cells.
     * Setting live->live causes no change in population.
     * Setting live->dead causes decrease in population.
     */
    void test_setCell_2() {
        Life<ConwayCell> life(2, 2, ConwayCell(true));
        ASSERT(life.getPopulation() == 4);

        life.setCell(Coordinate(0, 0), ConwayCell(true));
        ASSERT(life.getPopulation() == 4);

        life.setCell(Coordinate(1, 1), ConwayCell(false));
        ASSERT(life.getPopulation() == 3);
    }

    /**
     * Start with dead cells and set cells to live cells.
     * Check population and display output.
     */
    void test_setCell_3() {
        ostringstream str;
        Life<ConwayCell> life(2, 2);

        ASSERT(life.getPopulation() == 0);

        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 0.\n..\n..\n");
        str.str("");

        life.setCell(Coordinate(0, 0), ConwayCell(true));
        ASSERT(life.getPopulation() == 1);

        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 1.\n*.\n..\n");
        str.str("");

        life.setCell(Coordinate(1, 1), ConwayCell(true));
        ASSERT(life.getPopulation() == 2);

        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 2.\n*.\n.*\n");
    }

    /**
     * Start with live cells and set cells to dead cells.
     * Check population and display output.
     */
    void test_setCell_4() {
        ostringstream str;
        Life<ConwayCell> life(2, 2, ConwayCell(true));

        ASSERT(life.getPopulation() == 4);

        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 4.\n**\n**\n");
        str.str("");

        life.setCell(Coordinate(0, 1), ConwayCell(false));
        ASSERT(life.getPopulation() == 3);

        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 3.\n*.\n**\n");
        str.str("");

        life.setCell(Coordinate(1, 1), ConwayCell(false));
        ASSERT(life.getPopulation() == 2);

        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 2.\n*.\n*.\n");
    }

    /**
     * Start with dead cells and set cells to live cells.
     * Set those same cells back to dead cells later.
     * Check population and display output throughout the process.
     */
    void test_setCell_5() {
        ostringstream str;
        Life<ConwayCell> life(2, 2);

        ASSERT(life.getPopulation() == 0);
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 0.\n..\n..\n");
        str.str("");

        life.setCell(Coordinate(0, 0), ConwayCell(true));
        ASSERT(life.getPopulation() == 1);
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 1.\n*.\n..\n");
        str.str("");

        life.setCell(Coordinate(1, 1), ConwayCell(true));
        ASSERT(life.getPopulation() == 2);
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 2.\n*.\n.*\n");
        str.str("");

        life.setCell(Coordinate(1, 1), ConwayCell(false));
        ASSERT(life.getPopulation() == 1);
        life.display(str);
        ASSERT(str.str() == "\nGeneration = 0, Population = 1.\n*.\n..\n");
    }

    // -----------
    // test_evolve
    // -----------

    /**
     * Evolve a simple still life pattern: 2x2 block.
     *
     * http://en.wikipedia.org/wiki/Conway's_Game_of_Life
     */
    void test_evolve_1() {
        ostringstream str;
        Life<ConwayCell> life(2, 2, ConwayCell(true));

        life.display(str);
        ASSERT(life.getPopulation() == 4);
        ASSERT(life.getGeneration() == 0);
        ASSERT(str.str() == "\nGeneration = 0, Population = 4.\n**\n**\n");
        str.str("");

        life.evolve();

        life.display(str);
        ASSERT(life.getPopulation() == 4);
        ASSERT(life.getGeneration() == 1);
        ASSERT(str.str() == "\nGeneration = 1, Population = 4.\n**\n**\n");
    }

    /**
     * Evolve a simple still life pattern: Beehive.
     *
     * http://en.wikipedia.org/wiki/Conway's_Game_of_Life
     */
    void test_evolve_2() {
        ostringstream str;
        Life<ConwayCell> life(4, 5, ConwayCell(false));

        life.setCell(Coordinate(1, 0), ConwayCell(true));
        life.setCell(Coordinate(1, 3), ConwayCell(true));
        life.setCell(Coordinate(0, 1), ConwayCell(true));
        life.setCell(Coordinate(0, 2), ConwayCell(true));
        life.setCell(Coordinate(2, 1), ConwayCell(true));
        life.setCell(Coordinate(2, 2), ConwayCell(true));

        life.display(str);
        ASSERT(life.getPopulation() == 6);
        ASSERT(life.getGeneration() == 0);
        ASSERT(str.str() == "\nGeneration = 0, Population = 6.\n"
        ".**..\n"
        "*..*.\n"
        ".**..\n"
        ".....\n");
        str.str("");

        life.evolve();

        life.display(str);
        ASSERT(life.getPopulation() == 6);
        ASSERT(life.getGeneration() == 1);
        ASSERT(str.str() == "\nGeneration = 1, Population = 6.\n"
        ".**..\n"
        "*..*.\n"
        ".**..\n"
        ".....\n");
    }

    /**
     * Evolve a simple oscillating pattern: Blinker
     *
     * http://en.wikipedia.org/wiki/Conway's_Game_of_Life
     */
    void test_evolve_3() {
        ostringstream str;
        Life<ConwayCell> life(5, 5, ConwayCell(false));

        life.setCell(Coordinate(2, 1), ConwayCell(true));
        life.setCell(Coordinate(2, 2), ConwayCell(true));
        life.setCell(Coordinate(2, 3), ConwayCell(true));

        life.display(str);
        ASSERT(life.getPopulation() == 3);
        ASSERT(life.getGeneration() == 0);
        ASSERT(str.str() == "\nGeneration = 0, Population = 3.\n"
        ".....\n"
        ".....\n"
        ".***.\n"
        ".....\n"
        ".....\n");
        str.str("");

        life.evolve();

        life.display(str);
        ASSERT(life.getPopulation() == 3);
        ASSERT(life.getGeneration() == 1);
        ASSERT(str.str() == "\nGeneration = 1, Population = 3.\n"
        ".....\n"
        "..*..\n"
        "..*..\n"
        "..*..\n"
        ".....\n");
        str.str("");

        life.evolve();

        life.display(str);
        ASSERT(life.getPopulation() == 3);
        ASSERT(life.getGeneration() == 2);
        ASSERT(str.str() == "\nGeneration = 2, Population = 3.\n"
        ".....\n"
        ".....\n"
        ".***.\n"
        ".....\n"
        ".....\n");
    }

    /**
     * Start with a pattern that reaches a stable population.
     *
     * http://www.math.cornell.edu/~lipa/mec/lesson6.html
     */
    void test_evolve_4() {
        Life<ConwayCell> life(15, 15, ConwayCell(false));

        life.setCell(Coordinate(5, 5), ConwayCell(true));
        life.setCell(Coordinate(5, 6), ConwayCell(true));
        life.setCell(Coordinate(5, 7), ConwayCell(true));
        life.setCell(Coordinate(6, 6), ConwayCell(true));

        ASSERT(life.getGeneration() == 0);
        ASSERT(life.getPopulation() == 4);

        life.evolve(10);

        ASSERT(life.getGeneration() == 10);
        ASSERT(life.getPopulation() == 12);
    }

    // ------------
    // test_display
    // ------------

    /* Tests implied by other unit tests. */

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
        CPPUNIT_TEST(test_ctor_1);
        CPPUNIT_TEST(test_ctor_2);
        CPPUNIT_TEST(test_ctor_3);
        CPPUNIT_TEST(test_ctor_4);
        CPPUNIT_TEST(test_ctor_5);
        CPPUNIT_TEST(test_ctor_6);

        CPPUNIT_TEST(test_setCell_1);
        CPPUNIT_TEST(test_setCell_2);
        CPPUNIT_TEST(test_setCell_3);
        CPPUNIT_TEST(test_setCell_4);
        CPPUNIT_TEST(test_setCell_5);

        CPPUNIT_TEST(test_evolve_1);
        CPPUNIT_TEST(test_evolve_2);
        CPPUNIT_TEST(test_evolve_3);
        CPPUNIT_TEST(test_evolve_4);
    CPPUNIT_TEST_SUITE_END();
};

// TODO TestLifeFredkin
// TODO TestLifeCell

// ----
// main
// ----

int main() {
    using namespace std;

    try {
        ios_base::sync_with_stdio(false);  // turn off sync with C I/O
        cout << "TestLife.c++" << endl;

        CppUnit::TextTestRunner tr;
        tr.addTest(TestCoordinate::suite());
        tr.addTest(TestAbstractCell::suite());
        tr.addTest(TestConwayCell::suite());
        tr.addTest(TestFredkinCell::suite());
        tr.addTest(TestCell::suite());
        tr.addTest(TestLife::suite());
        tr.run();
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    cout << "Done." << endl;
    return 0;
}
