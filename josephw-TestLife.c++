// ------------------------------
// projects/life/TestLife.c++
// Copyright (C) 2012
// Joseph S. Wang
// Based off template by Glenn P. Downing
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

#include <iostream>
#include <sstream>
#include <string>

#define private public
#include "Life.h"

// --------
// TestLife
// --------

struct TestLife : CppUnit::TestFixture {
    // ----------
    // test_life_conway
    // ----------

    void test_life_conway_1 () {
        std::istringstream r("1\n1\n.");
        Life<ConwayCell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 1);
        CPPUNIT_ASSERT(x._m[0][0].size() == 1);
        CPPUNIT_ASSERT(x._r == 1);
        CPPUNIT_ASSERT(x._c == 1);
        CPPUNIT_ASSERT(x._m[0][0][0].getType() == CONWAY);
        CPPUNIT_ASSERT(x._m[0][0][0].isAlive() == false);
    }

    void test_life_conway_2 () {
        std::istringstream r("1\n2\n.*");
        Life<ConwayCell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 1);
        CPPUNIT_ASSERT(x._m[0][0].size() == 2);
        CPPUNIT_ASSERT(x._r == 1);
        CPPUNIT_ASSERT(x._c == 2);
        CPPUNIT_ASSERT(x._m[0][0][0].getType() == CONWAY);
        CPPUNIT_ASSERT(x._m[0][0][0].isAlive() == false);
        CPPUNIT_ASSERT(x._m[0][0][1].getType() == CONWAY);
        CPPUNIT_ASSERT(x._m[0][0][1].isAlive() == true);
    }

    void test_life_conway_3 () {
        std::istringstream r("3\n5\n******\n*****\n*****");
        Life<ConwayCell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 3);
        for (int i=0; i<3; ++i)
            CPPUNIT_ASSERT(x._m[0][i].size() == 5);
        CPPUNIT_ASSERT(x._r == 3);
        CPPUNIT_ASSERT(x._c == 5);
        for (int i=0; i<3; ++i) {
            for (int j=0; j<5; ++j) {
                CPPUNIT_ASSERT(x._m[0][i][j].getType() == CONWAY);
                CPPUNIT_ASSERT(x._m[0][i][j].isAlive() == true);
            }
        }
    }

    // ----------
    // test_life_fredkin
    // ----------

    void test_life_fredkin_1 () {
        std::istringstream r("1\n1\n-");
        Life<FredkinCell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 1);
        CPPUNIT_ASSERT(x._m[0][0].size() == 1);
        CPPUNIT_ASSERT(x._r == 1);
        CPPUNIT_ASSERT(x._c == 1);
        CPPUNIT_ASSERT(x._m[0][0][0].getType() == FREDKIN);
        CPPUNIT_ASSERT(x._m[0][0][0].isAlive() == false);
    }

    void test_life_fredkin_2 () {
        std::istringstream r("1\n2\n-0");
        Life<FredkinCell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 1);
        CPPUNIT_ASSERT(x._m[0][0].size() == 2);
        CPPUNIT_ASSERT(x._r == 1);
        CPPUNIT_ASSERT(x._c == 2);
        CPPUNIT_ASSERT(x._m[0][0][0].getType() == FREDKIN);
        CPPUNIT_ASSERT(x._m[0][0][0].isAlive() == false);
        CPPUNIT_ASSERT(x._m[0][0][1].getType() == FREDKIN);
        CPPUNIT_ASSERT(x._m[0][0][1].isAlive() == true);
    }

    void test_life_fredkin_3 () {
        std::istringstream r("3\n5\n00000\n00000\n00000");
        Life<FredkinCell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 3);
        for (int i=0; i<3; ++i)
            CPPUNIT_ASSERT(x._m[0][i].size() == 5);
        CPPUNIT_ASSERT(x._r == 3);
        CPPUNIT_ASSERT(x._c == 5);
        for (int i=0; i<3; ++i) {
            for (int j=0; j<5; ++j) {
                CPPUNIT_ASSERT(x._m[0][i][j].getType() == FREDKIN);
                CPPUNIT_ASSERT(x._m[0][i][j].isAlive() == true);
            }
        }
    }

    // ----------
    // test_life_cell
    // ----------

    void test_life_cell_1 () {
        std::istringstream r("1\n1\n.");
        Life<Cell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 1);
        CPPUNIT_ASSERT(x._m[0][0].size() == 1);
        CPPUNIT_ASSERT(x._r == 1);
        CPPUNIT_ASSERT(x._c == 1);
        CPPUNIT_ASSERT(x._m[0][0][0].getType() == CONWAY);
        CPPUNIT_ASSERT(x._m[0][0][0].isAlive() == false);
    }

    void test_life_cell_2 () {
        std::istringstream r("1\n2\n.-");
        Life<Cell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 1);
        CPPUNIT_ASSERT(x._m[0][0].size() == 2);
        CPPUNIT_ASSERT(x._r == 1);
        CPPUNIT_ASSERT(x._c == 2);
        CPPUNIT_ASSERT(x._m[0][0][0].getType() == CONWAY);
        CPPUNIT_ASSERT(x._m[0][0][0].isAlive() == false);
        CPPUNIT_ASSERT(x._m[0][0][1].getType() == FREDKIN);
        CPPUNIT_ASSERT(x._m[0][0][1].isAlive() == false);
    }

    void test_life_cell_3 () {
        std::istringstream r("3\n5\n*****\n*****\n00000");
        Life<Cell> x(r);
        CPPUNIT_ASSERT(x._m[0].size() == 3);
        for (int i=0; i<3; ++i)
            CPPUNIT_ASSERT(x._m[0][i].size() == 5);
        CPPUNIT_ASSERT(x._r == 3);
        CPPUNIT_ASSERT(x._c == 5);
        for (int i=0; i<2; ++i) {
            for (int j=0; j<5; ++j) {
                CPPUNIT_ASSERT(x._m[0][i][j].getType() == CONWAY);
                CPPUNIT_ASSERT(x._m[0][i][j].isAlive() == true);
            }
        }
        for (int j=0; j<5; ++j) {
            CPPUNIT_ASSERT(x._m[0][2][j].getType() == FREDKIN);
            CPPUNIT_ASSERT(x._m[0][2][j].isAlive() == true);
        }
    }

    // ----------
    // test_cellread
    // ----------

    void test_cellread_1 () {
        std::istringstream r("1\n1\n.");
        Life<ConwayCell> x(r);

        CPPUNIT_ASSERT(x._pop == 0);
        std::istringstream r2(".");
        ConwayCell y = x.cellRead(r2);
        CPPUNIT_ASSERT(x._pop == 0);
        CPPUNIT_ASSERT(y.getType() == CONWAY);
        CPPUNIT_ASSERT(y.isAlive() == false);

        std::istringstream r3("*");
        ConwayCell y2 = x.cellRead(r3);
        CPPUNIT_ASSERT(x._pop == 1);
        CPPUNIT_ASSERT(y2.getType() == CONWAY);
        CPPUNIT_ASSERT(y2.isAlive() == true);
    }

    void test_cellread_2 () {
        std::istringstream r("1\n1\n-");
        Life<FredkinCell> x(r);

        CPPUNIT_ASSERT(x._pop == 0);
        std::istringstream r2("-");
        FredkinCell y = x.cellRead(r2);
        CPPUNIT_ASSERT(x._pop == 0);
        CPPUNIT_ASSERT(y.getType() == FREDKIN);
        CPPUNIT_ASSERT(y.isAlive() == false);

        std::istringstream r3("0");
        FredkinCell y2 = x.cellRead(r3);
        CPPUNIT_ASSERT(x._pop == 1);
        CPPUNIT_ASSERT(y2.getType() == FREDKIN);
        CPPUNIT_ASSERT(y2.isAlive() == true);
        CPPUNIT_ASSERT(y2.getAge() == 0);

        std::istringstream r4("1");
        FredkinCell y3 = x.cellRead(r4);
        CPPUNIT_ASSERT(x._pop == 2);
        CPPUNIT_ASSERT(y3.getType() == FREDKIN);
        CPPUNIT_ASSERT(y3.isAlive() == true);
        CPPUNIT_ASSERT(y3.getAge() == 1);
    }

    void test_cellread_3 () {
        std::istringstream r("1\n1\n.");
        Life<Cell> x(r);

        CPPUNIT_ASSERT(x._pop == 0);
        std::istringstream r2(".");
        Cell y = x.cellRead(r2);
        CPPUNIT_ASSERT(x._pop == 0);
        CPPUNIT_ASSERT(y.getType() == CONWAY);
        CPPUNIT_ASSERT(y.isAlive() == false);

        std::istringstream r3("-");
        Cell y2 = x.cellRead(r3);
        CPPUNIT_ASSERT(x._pop == 0);
        CPPUNIT_ASSERT(y2.getType() == FREDKIN);
        CPPUNIT_ASSERT(y2.isAlive() == false);

        std::istringstream r4("1");
        Cell y3 = x.cellRead(r4);
        CPPUNIT_ASSERT(x._pop == 1);
        CPPUNIT_ASSERT(y3.getType() == FREDKIN);
        CPPUNIT_ASSERT(y3.isAlive() == true);
        CPPUNIT_ASSERT(dynamic_cast<FredkinCell*>(y3.get())->getAge() == 1);
    }

    // ----------
    // test_print
    // ----------
    void test_print_1 () {
        std::istringstream r("1\n2\n.*");
        Life<ConwayCell> x(r);

        std::ostringstream w;
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Generation = 0, Population = 1.\n.*\n\n");
    }

    void test_print_2 () {
        std::istringstream r("1\n11\n-0123456789");
        Life<FredkinCell> x(r);

        std::ostringstream w;
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Generation = 0, Population = 10.\n-0123456789\n\n");
    }

    void test_print_3 () {
        std::istringstream r("1\n13\n.*-0123456789");
        Life<Cell> x(r);

        std::ostringstream w;
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Generation = 0, Population = 11.\n.*-0123456789\n\n");
    }

    // ----------
    // test_simulate
    // ----------
    void test_simulate_1 () {
        std::istringstream r("1\n2\n.*");
        Life<ConwayCell> x(r);

        x.simulate(1);
        std::ostringstream w;
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Generation = 1, Population = 0.\n..\n\n");
    }

    void test_simulate_2 () {
        std::istringstream r("1\n2\n-0");
        Life<FredkinCell> x(r);

        x.simulate(1);
        std::ostringstream w;
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Generation = 1, Population = 1.\n0-\n\n");
    }

    void test_simulate_3 () {
        std::istringstream r("1\n4\n.*-0");
        Life<Cell> x(r);

        x.simulate(1);
        std::ostringstream w;
        x.print(w);
        CPPUNIT_ASSERT(w.str() == "Generation = 1, Population = 0.\n..--\n\n");
    }

    // ----------
    // test_abstract_isAlive
    // ----------

    void test_abstract_isAlive_1 () {
        ConwayCell x(true);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_abstract_isAlive_2 () {
        FredkinCell x(false);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_abstract_isAlive_3 () {
        Cell x(new ConwayCell(false));
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    // ----------
    // test_abstract_aliveToggle
    // ----------

    void test_abstract_aliveToggle_1 () {
        ConwayCell x(true);
        x.aliveToggle();
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_abstract_aliveToggle_2 () {
        FredkinCell x(false);
        x.aliveToggle();
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_abstract_aliveToggle_3 () {
        Cell x(new ConwayCell(false));
        x.aliveToggle();
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    // ----------
    // test_abstract_setAlive
    // ----------

    void test_abstract_setAlive_1 () {
        ConwayCell x(true);
        x.setAlive(false);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_abstract_setAlive_2 () {
        FredkinCell x(false);
        x.setAlive(true);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_abstract_setAlive_3 () {
        Cell x(new ConwayCell(false));
        x.setAlive(true);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    // ----------
    // test_abstract_getType
    // ----------

    void test_abstract_getType_1 () {
        ConwayCell x(true);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
    }

    void test_abstract_getType_2 () {
        FredkinCell x(false);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
    }

    void test_abstract_getType_3 () {
        Cell x(new ConwayCell(false));
        CPPUNIT_ASSERT(x.getType() == CONWAY);
    }

    // ----------
    // test_abstract_get
    // ----------

    void test_abstract_get_1 () {
        ConwayCell x(true);
        CPPUNIT_ASSERT(x.get() == &x);
    }

    void test_abstract_get_2 () {
        FredkinCell x(false);
        CPPUNIT_ASSERT(x.get() == &x);
    }

    void test_abstract_get_3 () {
        Cell x(new ConwayCell(false));
        CPPUNIT_ASSERT(x.get() == x._p);
    }

    // ----------
    // test_ConwayCell
    // ----------

    void test_ConwayCell_1 () {
        ConwayCell x(false);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_ConwayCell_2 () {
        ConwayCell x(true);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    // ----------
    // test_ConwayCell_read
    // ----------

    void test_ConwayCell_read_1 () {
        std::istringstream r(".");
        ConwayCell x(true);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_ConwayCell_read_2 () {
        std::istringstream r("*");
        ConwayCell x(false);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_ConwayCell_read_3 () {
        std::istringstream r("*.");
        ConwayCell x(false);
        x.read(r);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    // ----------
    // test_ConwayCell_write
    // ----------
    
    void test_ConwayCell_write_1 () {
        ConwayCell x(true);
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "*");
    }

    void test_ConwayCell_write_2 () {
        ConwayCell x(false);
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == ".");
    }

    // ----------
    // test_ConwayCell_copy
    // ----------

    void test_ConwayCell_copy_1 () {
        ConwayCell x(true), y(false);
        x = y;
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_ConwayCell_copy_2 () {
        ConwayCell x(false), y(true);
        x = y;
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_ConwayCell_copy_3 () {
        ConwayCell x(false), y(false);
        x = y;
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    // ----------
    // test_FredkinCell
    // ----------

    void test_FredkinCell_1 () {
        FredkinCell x(false);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_FredkinCell_2 () {
        FredkinCell x(true, 0);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    void test_FredkinCell_3 () {
        FredkinCell x(true, 2);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(x.getAge() == 2);
    }

    // ----------
    // test_FredkinCell_read
    // ----------

    void test_FredkinCell_read_1 () {
        std::istringstream r("-");
        FredkinCell x(true);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_FredkinCell_read_2 () {
        std::istringstream r("0");
        FredkinCell x(false);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    void test_FredkinCell_read_3 () {
        std::istringstream r("4");
        FredkinCell x(false);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(x.getAge() == 4);
    }

    // ----------
    // test_FredkinCell_write
    // ----------

    void test_FredkinCell_write_1 () {
        FredkinCell x(false);
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "-");
    }

    void test_FredkinCell_write_2 () {
        FredkinCell x(true, 0);
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "0");
    }

    void test_FredkinCell_write_3 () {
        FredkinCell x(true, 4);
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "4");
    }

    void test_FredkinCell_write_4 () {
        FredkinCell x(true, 12);
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "+");
    }

    // ----------
    // test_FredkinCell_copy
    // ----------

    void test_FredkinCell_copy_1 () {
        FredkinCell x(true, 0), y(false);
        x = y;
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_FredkinCell_copy_2 () {
        FredkinCell x(false), y(true, 0);
        x = y;
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    void test_FredkinCell_copy_3 () {
        FredkinCell x(false), y(true, 3);
        x = y;
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(x.getAge() == 3);
    }

    // ----------
    // test_FredkinCell_getAge
    // ----------

    void test_FredkinCell_getAge_1 () {
        FredkinCell x(true, 0);
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    void test_FredkinCell_getAge_2 () {
        FredkinCell x(true, 4);
        CPPUNIT_ASSERT(x.getAge() == 4);
    }

    void test_FredkinCell_getAge_3 () {
        FredkinCell x(true, 23);
        CPPUNIT_ASSERT(x.getAge() == 23);
    }

    // ----------
    // test_FredkinCell_resetAge
    // ----------

    void test_FredkinCell_resetAge_1 () {
        FredkinCell x(true, 0);
        x.resetAge();
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    void test_FredkinCell_resetAge_2 () {
        FredkinCell x(true, 4);
        x.resetAge();
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    void test_FredkinCell_resetAge_3 () {
        FredkinCell x(true, 23);
        x.resetAge();
        CPPUNIT_ASSERT(x.getAge() == 0);
    }

    // ----------
    // test_FredkinCell_incrementAge
    // ----------

    void test_FredkinCell_incrementAge_1 () {
        FredkinCell x(true, 0);
        x.incrementAge();
        CPPUNIT_ASSERT(x.getAge() == 1);
    }

    void test_FredkinCell_incrementAge_2 () {
        FredkinCell x(true, 4);
        x.incrementAge();
        CPPUNIT_ASSERT(x.getAge() == 5);
    }

    void test_FredkinCell_incrementAge_3 () {
        FredkinCell x(true, 23);
        x.incrementAge();
        CPPUNIT_ASSERT(x.getAge() == 24);
    }

    // ----------
    // test_Cell
    // ----------

    void test_Cell_1 () {
        Cell x(new ConwayCell(false));
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_Cell_2 () {
        Cell x(new ConwayCell(true));
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_3 () {
        Cell x(new FredkinCell(false));
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    // ----------
    // test_Cell_read
    // ----------

    void test_Cell_read_1 () {
        std::istringstream r(".");
        Cell x(NULL);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_Cell_read_2 () {
        std::istringstream r("*");
        Cell x(NULL);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_read_3 () {
        std::istringstream r("1");
        Cell x(NULL);
        x.read(r);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(dynamic_cast<FredkinCell*>(x.get())->getAge() == 1);
    }

    // ----------
    // test_Cell_write
    // ----------

    void test_Cell_write_1 () {
        Cell x(new ConwayCell(false));
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == ".");
    }

    void test_Cell_write_2 () {
        Cell x(new FredkinCell(false));
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "-");
    }

    void test_Cell_write_3 () {
        Cell x(new FredkinCell(true, 4));
        std::ostringstream w;
        x.write(w);
        CPPUNIT_ASSERT(w.str() == "4");
    }

    // ----------
    // test_Cell_copy
    // ----------

    void test_Cell_copy_1 () {
        Cell x(new ConwayCell(false)), y(new ConwayCell(true));
        x = y;
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_copy_2 () {
        Cell x(new FredkinCell(true, 0)), y(new FredkinCell(false));
        x = y;
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_Cell_copy_3 () {
        Cell x(new FredkinCell(false)), y(new FredkinCell(true, 3));
        x = y;
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == true);
        CPPUNIT_ASSERT(dynamic_cast<FredkinCell*>(x.get())->getAge() == 3);
    }

    // ----------
    // test_Cell_isAlive
    // ----------

    void test_Cell_isAlive_1 () {
        Cell x(new ConwayCell(false));
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_Cell_isAlive_2 () {
        Cell x(new ConwayCell(true));
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_isAlive_3 () {
        Cell x(new FredkinCell(false));
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    // ----------
    // test_Cell_aliveToggle
    // ----------

    void test_Cell_aliveToggle_1 () {
        Cell x(new ConwayCell(false));
        x.aliveToggle();
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_aliveToggle_2 () {
        Cell x(new ConwayCell(true));
        x.aliveToggle();
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_Cell_aliveToggle_3 () {
        Cell x(new FredkinCell(true, 2));
        x.aliveToggle();
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    // ----------
    // test_Cell_setAlive
    // ----------

    void test_Cell_setAlive_1 () {
        Cell x(new ConwayCell(false));
        x.setAlive(true);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_setAlive_2 () {
        Cell x(new ConwayCell(true));
        x.setAlive(false);
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }

    void test_Cell_setAlive_3 () {
        Cell x(new FredkinCell(true, 0));
        x.setAlive(false);
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
        CPPUNIT_ASSERT(x.isAlive() == false);
    }
    // ----------
    // test_Cell_getType
    // ----------

    void test_Cell_getType_1 () {
        Cell x(new ConwayCell(false));
        CPPUNIT_ASSERT(x.getType() == CONWAY);
    }

    void test_Cell_getType_2 () {
        Cell x(new FredkinCell(false));
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
    }

    void test_Cell_getType_3 () {
        Cell x(new FredkinCell(true, 9));
        CPPUNIT_ASSERT(x.getType() == FREDKIN);
    }

    // ----------
    // test_Cell_convert
    // ----------

    void test_Cell_convert_1 () {
        Cell x(new FredkinCell(false));
        x.convert();
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_convert_2 () {
        Cell x(new FredkinCell(false));
        x.convert();
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    void test_Cell_convert_3 () {
        Cell x(new FredkinCell(true, 9));
        x.convert();
        CPPUNIT_ASSERT(x.getType() == CONWAY);
        CPPUNIT_ASSERT(x.isAlive() == true);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(test_life_conway_1);
    CPPUNIT_TEST(test_life_conway_2);
    CPPUNIT_TEST(test_life_conway_3);
    CPPUNIT_TEST(test_life_fredkin_1);
    CPPUNIT_TEST(test_life_fredkin_2);
    CPPUNIT_TEST(test_life_fredkin_3);
    CPPUNIT_TEST(test_life_cell_1);
    CPPUNIT_TEST(test_life_cell_2);
    CPPUNIT_TEST(test_life_cell_3);
    CPPUNIT_TEST(test_cellread_1);
    CPPUNIT_TEST(test_cellread_2);
    CPPUNIT_TEST(test_cellread_3);
    CPPUNIT_TEST(test_print_1);
    CPPUNIT_TEST(test_print_2);
    CPPUNIT_TEST(test_print_3);
    CPPUNIT_TEST(test_simulate_1);
    CPPUNIT_TEST(test_simulate_2);
    CPPUNIT_TEST(test_simulate_3);
    CPPUNIT_TEST(test_abstract_isAlive_1);
    CPPUNIT_TEST(test_abstract_isAlive_2);
    CPPUNIT_TEST(test_abstract_isAlive_3);
    CPPUNIT_TEST(test_abstract_aliveToggle_1);
    CPPUNIT_TEST(test_abstract_aliveToggle_2);
    CPPUNIT_TEST(test_abstract_aliveToggle_3);
    CPPUNIT_TEST(test_abstract_setAlive_1);
    CPPUNIT_TEST(test_abstract_setAlive_2);
    CPPUNIT_TEST(test_abstract_setAlive_3);
    CPPUNIT_TEST(test_abstract_getType_1);
    CPPUNIT_TEST(test_abstract_getType_2);
    CPPUNIT_TEST(test_abstract_getType_3);
    CPPUNIT_TEST(test_abstract_get_1);
    CPPUNIT_TEST(test_abstract_get_2);
    CPPUNIT_TEST(test_abstract_get_3);
    CPPUNIT_TEST(test_ConwayCell_1);
    CPPUNIT_TEST(test_ConwayCell_2);
    CPPUNIT_TEST(test_ConwayCell_read_1);
    CPPUNIT_TEST(test_ConwayCell_read_2);
    CPPUNIT_TEST(test_ConwayCell_read_3);
    CPPUNIT_TEST(test_ConwayCell_write_1);
    CPPUNIT_TEST(test_ConwayCell_write_2);
    CPPUNIT_TEST(test_ConwayCell_copy_1);
    CPPUNIT_TEST(test_ConwayCell_copy_2);
    CPPUNIT_TEST(test_ConwayCell_copy_3);
    CPPUNIT_TEST(test_FredkinCell_1);
    CPPUNIT_TEST(test_FredkinCell_2);
    CPPUNIT_TEST(test_FredkinCell_3);
    CPPUNIT_TEST(test_FredkinCell_read_1);
    CPPUNIT_TEST(test_FredkinCell_read_2);
    CPPUNIT_TEST(test_FredkinCell_read_3);
    CPPUNIT_TEST(test_FredkinCell_write_1);
    CPPUNIT_TEST(test_FredkinCell_write_2);
    CPPUNIT_TEST(test_FredkinCell_write_3);
    CPPUNIT_TEST(test_FredkinCell_write_4);
    CPPUNIT_TEST(test_FredkinCell_copy_1);
    CPPUNIT_TEST(test_FredkinCell_copy_2);
    CPPUNIT_TEST(test_FredkinCell_copy_3);
    CPPUNIT_TEST(test_FredkinCell_getAge_1);
    CPPUNIT_TEST(test_FredkinCell_getAge_2);
    CPPUNIT_TEST(test_FredkinCell_getAge_3);
    CPPUNIT_TEST(test_FredkinCell_resetAge_1);
    CPPUNIT_TEST(test_FredkinCell_resetAge_2);
    CPPUNIT_TEST(test_FredkinCell_resetAge_3);
    CPPUNIT_TEST(test_FredkinCell_incrementAge_1);
    CPPUNIT_TEST(test_FredkinCell_incrementAge_2);
    CPPUNIT_TEST(test_FredkinCell_incrementAge_3);
    CPPUNIT_TEST(test_Cell_1);
    CPPUNIT_TEST(test_Cell_2);
    CPPUNIT_TEST(test_Cell_3);
    CPPUNIT_TEST(test_Cell_read_1);
    CPPUNIT_TEST(test_Cell_read_2);
    CPPUNIT_TEST(test_Cell_read_3);
    CPPUNIT_TEST(test_Cell_write_1);
    CPPUNIT_TEST(test_Cell_write_2);
    CPPUNIT_TEST(test_Cell_write_3);
    CPPUNIT_TEST(test_Cell_copy_1);
    CPPUNIT_TEST(test_Cell_copy_2);
    CPPUNIT_TEST(test_Cell_copy_3);
    CPPUNIT_TEST(test_Cell_isAlive_1);
    CPPUNIT_TEST(test_Cell_isAlive_2);
    CPPUNIT_TEST(test_Cell_isAlive_3);
    CPPUNIT_TEST(test_Cell_aliveToggle_1);
    CPPUNIT_TEST(test_Cell_aliveToggle_2);
    CPPUNIT_TEST(test_Cell_aliveToggle_3);
    CPPUNIT_TEST(test_Cell_setAlive_1);
    CPPUNIT_TEST(test_Cell_setAlive_2);
    CPPUNIT_TEST(test_Cell_setAlive_3);
    CPPUNIT_TEST(test_Cell_getType_1);
    CPPUNIT_TEST(test_Cell_getType_2);
    CPPUNIT_TEST(test_Cell_getType_3);
    CPPUNIT_TEST(test_Cell_convert_1);
    CPPUNIT_TEST(test_Cell_convert_2);
    CPPUNIT_TEST(test_Cell_convert_3);

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