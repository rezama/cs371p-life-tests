// ------------------------------
// projects/matlab/TestLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 *     valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
#define private public

#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

// ----------
// TestLife
// ----------

struct TestLife : CppUnit::TestFixture {
    // ----------------
    // Test Conway
    // ----------------

    void test_conway_constructor() {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(c1.getState() == '*');
    }

    void test_conway_get_state_1() {
        ConwayCell c1;
        CPPUNIT_ASSERT(c1.getState() == '.');
    }

    void test_conway_next_state_1() {
        ConwayCell c1;
        CPPUNIT_ASSERT(c1.getState() == '.');
        c1.nextState(3);
        CPPUNIT_ASSERT(c1.getState() == '*');
    }

    void test_conway_next_state_2() {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(c1.getState() == '*');
        c1.nextState(1);
        CPPUNIT_ASSERT(c1.getState() == '.');
    }

    void test_conway_next_state_3() {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(c1.getState() == '*');
        c1.nextState(4);
        CPPUNIT_ASSERT(c1.getState() == '.');
    }

    void test_conway_clone_1() {
        ConwayCell c1(true);
        AbstractCell *clone = c1.clone();
        CPPUNIT_ASSERT( clone->isAlive());
        CPPUNIT_ASSERT( &c1 != clone);
        delete (clone);
        CPPUNIT_ASSERT( c1.isAlive());
    }

    void test_conway_clone_2() {
        ConwayCell c1(false);
        AbstractCell *clone = c1.clone();
        CPPUNIT_ASSERT( !clone->isAlive());
        CPPUNIT_ASSERT( &c1 != clone);
        delete (clone);
        CPPUNIT_ASSERT( !c1.isAlive());
    }

    void test_conway_clone_3() {
        ConwayCell c1(true);
        AbstractCell *clone_1 = c1.clone();
        AbstractCell *clone_2 = clone_1->clone();
        CPPUNIT_ASSERT( clone_1->isAlive());
        CPPUNIT_ASSERT( clone_2->isAlive());
        CPPUNIT_ASSERT( &c1 != clone_1 && clone_2 != clone_1);
        delete (clone_1);
        delete (clone_2);
        CPPUNIT_ASSERT( c1.isAlive());
    }

    void test_conway_numNeighbor() {
        ConwayCell c1(true);
        CPPUNIT_ASSERT(c1.numNeighbor() == 8);
        Cell cc = new ConwayCell();
        CPPUNIT_ASSERT(cc.numNeigbor() == 8);
    }
////////////////////////////////////////////////////////
    void test_fredkin_constructor() {
        FredkinCell c1(true);
        CPPUNIT_ASSERT(c1.getState() == '0');
    }

    void test_fredkin_get_state_1() {
        FredkinCell c1;
        CPPUNIT_ASSERT(c1.getState() == '-');
    }

    void test_fredkin_next_state_1() {
        FredkinCell c1;
        CPPUNIT_ASSERT(c1.getState() == '-');
        c1.nextState(3);
        CPPUNIT_ASSERT(c1.getState() == '0');
    }

    void test_fredkin_next_state_2() {
        FredkinCell c1(true);
        CPPUNIT_ASSERT(c1.getState() == '0');
        c1.nextState(1);
        CPPUNIT_ASSERT(c1.getState() == '1');
    }

    void test_fredkin_next_state_3() {
        FredkinCell c1(true);
        CPPUNIT_ASSERT(c1.getState() == '0');
        c1.nextState(3);
        CPPUNIT_ASSERT(c1.getState() == '1');
    }

    void test_fredkin_clone_1() {
        FredkinCell c1(true);
        AbstractCell *clone = c1.clone();
        CPPUNIT_ASSERT( clone->isAlive());
        CPPUNIT_ASSERT( &c1 != clone);
        delete (clone);
        CPPUNIT_ASSERT( c1.isAlive());
    }

    void test_fredkin_clone_2() {
        FredkinCell c1(false);
        AbstractCell *clone = c1.clone();
        CPPUNIT_ASSERT( !clone->isAlive());
        CPPUNIT_ASSERT( &c1 != clone);
        delete (clone);
        CPPUNIT_ASSERT( !c1.isAlive());
    }

    void test_fredkin_clone_3() {
        FredkinCell c1(true);
        AbstractCell *clone_1 = c1.clone();
        AbstractCell *clone_2 = clone_1->clone();
        CPPUNIT_ASSERT( clone_1->isAlive());
        CPPUNIT_ASSERT( clone_2->isAlive());
        CPPUNIT_ASSERT( &c1 != clone_1 && clone_2 != clone_1);
        delete (clone_1);
        delete (clone_2);
        CPPUNIT_ASSERT( c1.isAlive());
    }

    void test_fredkin_numNeighbor() {
        FredkinCell c1(true);
        CPPUNIT_ASSERT(c1.numNeighbor() == 4);
        Cell cc = new FredkinCell();
        CPPUNIT_ASSERT(cc.numNeigbor() == 4);
    }
///////////////////////////////////////////////////////
    void test_cell_default_constructor_1() {
        Cell c1; // Assuming FredkinCell
        CPPUNIT_ASSERT(c1.getState() == '-');
        c1.nextState(3);
        CPPUNIT_ASSERT(c1.getState() == '0');
    }

    void test_cell_default_constructor_2() {
        Cell c1('+');
        AbstractCell *clone = c1.clone();
        CPPUNIT_ASSERT( clone->isAlive());
        delete (clone);
        CPPUNIT_ASSERT( c1.isAlive());
    }

    void test_cell_default_constructor_3() {
        Cell c1('+');
        AbstractCell *clone_1 = c1.clone();
        AbstractCell *clone_2 = clone_1->clone();
        CPPUNIT_ASSERT( clone_1->isAlive());
        CPPUNIT_ASSERT( clone_2->isAlive());
        CPPUNIT_ASSERT( clone_2 != clone_1);
        delete (clone_1);
        delete (clone_2);
        CPPUNIT_ASSERT( c1.isAlive());
    }

    void test_cell_constructor_1() {
        Cell cc = new ConwayCell(true);
        CPPUNIT_ASSERT(cc.isAlive());
        Cell c1(cc);
        CPPUNIT_ASSERT(c1.isAlive());
        CPPUNIT_ASSERT( cc._p_cell != c1._p_cell);
    }

    void test_cell_constructor_2() {
        Cell cc = new ConwayCell();
        CPPUNIT_ASSERT(!cc.isAlive());
        Cell c1(cc);
        CPPUNIT_ASSERT(!c1.isAlive());
        CPPUNIT_ASSERT( cc._p_cell != c1._p_cell);
    }

    void test_cell_constructor_3() {
        Cell cc = new FredkinCell();
        CPPUNIT_ASSERT(!cc.isAlive());
        Cell c1(cc);
        CPPUNIT_ASSERT(!c1.isAlive());
        CPPUNIT_ASSERT( cc._p_cell != c1._p_cell);
    }

    void test_cell_copy_assignment_1() {
        Cell c1 = new ConwayCell('.');
        Cell c2 = new ConwayCell('*');
        CPPUNIT_ASSERT(c2.getState() == '*');
        c2 = c1;
        CPPUNIT_ASSERT(c2.getState() == '.');
        CPPUNIT_ASSERT(c2._p_cell != c1._p_cell);
    }

    void test_cell_copy_assignment_2() {
        Cell c1 = new FredkinCell('-');
        Cell c2 = new FredkinCell('+');
        CPPUNIT_ASSERT(c2.getState() == '0');
        c2 = c1;
        CPPUNIT_ASSERT(c2.getState() == '-');
        CPPUNIT_ASSERT(c2._p_cell != c1._p_cell);
    }

    void test_cell_copy_assignment_3() {
        Cell c1 = new FredkinCell('9');
        Cell c2 = new FredkinCell('-');
        CPPUNIT_ASSERT(c2.getState() == '-');
        c2 = c1;
        CPPUNIT_ASSERT(c2.getState() == '0');
        CPPUNIT_ASSERT(c2._p_cell != c1._p_cell);
    }

    void test_cell_get_state_1() {
        Cell c = new ConwayCell();
        CPPUNIT_ASSERT(c.getState() == '.');
    }

    void test_cell_get_state_2() {
        Cell c = new FredkinCell();
        CPPUNIT_ASSERT(c.getState() == '-');
    }

    void test_cell_get_state_3() {
        Cell c = new FredkinCell(true);
        CPPUNIT_ASSERT(c.getState() == '0');
    }

    void test_cell_get_state_4() {
        Cell c = new ConwayCell(true);
        CPPUNIT_ASSERT(c.getState() == '*');
    }
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

    void test_life_constructor_1() {
        Life<Cell> life(3, 3);
        life.countNeighbor();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                CPPUNIT_ASSERT(life._numNeighbor[i][j] == 0);
            }
        }
    }

    void test_life_countNeighbor_1() {
        Life<ConwayCell> life(3, 3);
        life.countNeighbor();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                CPPUNIT_ASSERT(life._numNeighbor[i][j] == 0);
            }
    }

    void test_life_countNeighbor_2() {
        Life<ConwayCell> life(3, 3);

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                life._grid[i][j]._p_cell->nextState(3);
            }

        life.countNeighbor();

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    CPPUNIT_ASSERT(life._numNeighbor[i][j] == 8);
                } else if ((i + j) % 2 == 1) {
                    CPPUNIT_ASSERT(life._numNeighbor[i][j] == 5);
                } else
                    CPPUNIT_ASSERT(life._numNeighbor[i][j] == 3);
            }
    }

    void test_life_countNeighbor_3() {
        Life<FredkinCell> life(3, 3);

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                life._grid[i][j]._p_cell->nextState(3);
            }

        life.countNeighbor();

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                if (i == 1 && j == 1) {
                    CPPUNIT_ASSERT(life._numNeighbor[i][j] == 4);
                } else if ((i + j) % 2 == 1) {
                    CPPUNIT_ASSERT(life._numNeighbor[i][j] == 3);
                } else
                    CPPUNIT_ASSERT(life._numNeighbor[i][j] == 2);
            }
    }

    // -----
    // suite
    // -----

CPPUNIT_TEST_SUITE(TestLife);
        CPPUNIT_TEST(test_conway_constructor);
        CPPUNIT_TEST(test_conway_get_state_1);
        CPPUNIT_TEST(test_conway_next_state_1);
        CPPUNIT_TEST(test_conway_next_state_2);
        CPPUNIT_TEST(test_conway_next_state_3);
        CPPUNIT_TEST(test_conway_clone_1);
        CPPUNIT_TEST(test_conway_clone_2);
        CPPUNIT_TEST(test_conway_clone_3);
        CPPUNIT_TEST(test_conway_numNeighbor);

        CPPUNIT_TEST(test_fredkin_constructor);
        CPPUNIT_TEST(test_fredkin_get_state_1);
        CPPUNIT_TEST(test_fredkin_next_state_1);
        CPPUNIT_TEST(test_fredkin_next_state_2);
        CPPUNIT_TEST(test_fredkin_next_state_3);
        CPPUNIT_TEST(test_fredkin_clone_1);
        CPPUNIT_TEST(test_fredkin_clone_2);
        CPPUNIT_TEST(test_fredkin_clone_3);
        CPPUNIT_TEST(test_fredkin_numNeighbor);

        CPPUNIT_TEST(test_cell_default_constructor_1);
        CPPUNIT_TEST(test_cell_default_constructor_2);
        CPPUNIT_TEST(test_cell_default_constructor_3);
        CPPUNIT_TEST(test_cell_constructor_1);
        CPPUNIT_TEST(test_cell_constructor_2);
        CPPUNIT_TEST(test_cell_constructor_3);
        CPPUNIT_TEST(test_cell_copy_assignment_1);
        CPPUNIT_TEST(test_cell_copy_assignment_2);
        CPPUNIT_TEST(test_cell_copy_assignment_3);
        CPPUNIT_TEST(test_cell_get_state_1);
        CPPUNIT_TEST(test_cell_get_state_2);
        CPPUNIT_TEST(test_cell_get_state_3);
        CPPUNIT_TEST(test_cell_get_state_4);

        CPPUNIT_TEST(test_life_countNeighbor_1);
        CPPUNIT_TEST(test_life_countNeighbor_2);
        CPPUNIT_TEST(test_life_countNeighbor_3);
        CPPUNIT_TEST(test_life_constructor_1);
    CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestLife.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestLife::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;
}
