// ------------------------------
// projects/Darwin/TestLife.c++
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

#include <iostream>  // I/O
#include <fstream>   // file I/O
#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner
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
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
        CPPUNIT_ASSERT(cell.icon() == '.');

    }

    void test_conway2 () {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
        CPPUNIT_ASSERT(cell.icon() == '.');
        cell.tick(3);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '*');
    }

    void test_conway3 () {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
        CPPUNIT_ASSERT(cell.icon() == '.');
        cell.tick(3);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '*');
        cell.tick(1);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '.');
    }

    void test_fredkin1() {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
        CPPUNIT_ASSERT(cell.icon() == '-');

    }

    void test_fredkin2 () {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
        CPPUNIT_ASSERT(cell.icon() == '-');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '1');
    }

    void test_fredkin3 () {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
        CPPUNIT_ASSERT(cell.icon() == '-');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        cell.tick(4);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '-');
    }

    void test_cell1() {
        Cell cell = Cell(new ConwayCell());
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
        CPPUNIT_ASSERT(cell.icon() == '.');
        cell.tick(3);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '*');
        cell.tick(1);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '.');
    }

    void test_cell2 () {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
        CPPUNIT_ASSERT(cell.icon() == '-');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '1');
    }

    void test_cell3 () {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
        CPPUNIT_ASSERT(cell.icon() == '-');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        cell.tick(4);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '-');
    }

    void test_is_alive1() {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(!cell.isAlive());
    }

    void test_is_alive2() {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());
    }

    void test_is_alive3() {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(!cell.isAlive());
    }

    void test_neighbors1() {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
    }

    void test_neighbors2() {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(cell.neighbors().size() == 4);
    }

    void test_neighbors3() {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
    }


    void test_tick1() {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '-');
         cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        cell.tick(4);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '-');
    }

    void test_tick2() {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        cell.tick(4);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '-');
    }

    void test_tick3() {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
        CPPUNIT_ASSERT(cell.icon() == '.');
        cell.tick(3);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '*');
        cell.tick(1);
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '.');
    }

    void test_icon1() {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(cell.icon() == '-');
    }

    void test_icon2() {
        FredkinCell cell = FredkinCell();
        CPPUNIT_ASSERT(cell.icon() == '-');
    }

    void test_icon3() {
        ConwayCell cell = ConwayCell();
        CPPUNIT_ASSERT(cell.icon() == '.');
    }


    void test_clone1() {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(cell.icon() == '-');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        Cell cell_copy(cell);
        CPPUNIT_ASSERT(cell_copy.isAlive());
        CPPUNIT_ASSERT(cell_copy.icon() == '0');
    }


    void test_clone2() {
        Cell cell = Cell(new FredkinCell());
        CPPUNIT_ASSERT(cell.icon() == '-');
        cell.tick(1);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
        Cell cell_copy(cell);
        CPPUNIT_ASSERT(cell_copy.isAlive());
        CPPUNIT_ASSERT(cell_copy.icon() == '0');
        cell_copy.tick(4);
        CPPUNIT_ASSERT(!cell_copy.isAlive());
        CPPUNIT_ASSERT(cell_copy.icon() == '-');
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '0');
    }

    void test_clone3() {
        Cell cell = Cell(new ConwayCell());
        CPPUNIT_ASSERT(!cell.isAlive());
        CPPUNIT_ASSERT(cell.neighbors().size() == 8);
        CPPUNIT_ASSERT(cell.icon() == '.');
        cell.tick(3);
        CPPUNIT_ASSERT(cell.isAlive());
        CPPUNIT_ASSERT(cell.icon() == '*');
        Cell cell_copy(cell);
        CPPUNIT_ASSERT(cell_copy.isAlive());
        CPPUNIT_ASSERT(cell_copy.icon() == '*');
    }

    void test_life1() {
        try {
            std::ifstream input("RunLifeConway.in", std::ios::in);
            std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
            Life<ConwayCell> life = Life<ConwayCell>(grid);
            CPPUNIT_ASSERT(true);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_life2() {
        try {
            Life<FredkinCell> life = Life<FredkinCell>(2, 2);
            CPPUNIT_ASSERT(true);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_life3() {
        try {
            std::ifstream input("RunLife.in", std::ios::in);
            std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
            Life<Cell> life = Life<Cell>(grid);
            life.simulate(10);
            CPPUNIT_ASSERT(true);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_simulate1() {
        Life<ConwayCell> life = Life<ConwayCell>(2, 2);
        try {
            life.simulate(2);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_simulate2() {
        Life<FredkinCell> life = Life<FredkinCell>(2, 2);
        try {
            life.simulate(1);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_simulate3() {
        Life<Cell> life = Life<Cell>(2, 2, Cell(new FredkinCell()));
        try {
            life.simulate(3);
        }
        catch (...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_display1() {
        Life<ConwayCell> life = Life<ConwayCell>(2, 2);
        std::ostringstream w;
        life.display(w, false);
        CPPUNIT_ASSERT(w.str() == "\nGeneration = 0, Population = 0.\n..\n..\n");
    }

    void test_display2() {
        Life<FredkinCell> life = Life<FredkinCell>(2, 2);
        std::ostringstream w;
        life.display(w, false);
        CPPUNIT_ASSERT(w.str() == "\nGeneration = 0, Population = 0.\n--\n--\n");
    }

    void test_display3() {
        Life<Cell> life = Life<Cell>(2, 2, Cell(new FredkinCell(true, 9)));
        std::ostringstream w;
        life.display(w, false);
        CPPUNIT_ASSERT(w.str() == "\nGeneration = 0, Population = 4.\n99\n99\n");
    }


    void test_calculate_neighbors1() {
        Life<FredkinCell> life = Life<FredkinCell>(2, 2);
        life.calculateNeighbors();
        CPPUNIT_ASSERT(life._n[0][0] == 0);
        CPPUNIT_ASSERT(life._n[1][0] == 0);
        CPPUNIT_ASSERT(life._n[0][1] == 0);
        CPPUNIT_ASSERT(life._n[1][1] == 0);
    }

    void test_calculate_neighbors2() {
        Life<ConwayCell> life = Life<ConwayCell>(2, 2, ConwayCell(true));
        life.calculateNeighbors();
        CPPUNIT_ASSERT(life._n[0][0] == 3);
        CPPUNIT_ASSERT(life._n[1][0] == 3);
        CPPUNIT_ASSERT(life._n[0][1] == 3);
        CPPUNIT_ASSERT(life._n[1][1] == 3);
    }

    void test_calculate_neighbors3() {
        Life<FredkinCell> life = Life<FredkinCell>(2, 2, FredkinCell(true, 0));
        life.calculateNeighbors();
        CPPUNIT_ASSERT(life._n[0][0] == 2);
        CPPUNIT_ASSERT(life._n[1][0] == 2);
        CPPUNIT_ASSERT(life._n[0][1] == 2);
        CPPUNIT_ASSERT(life._n[1][1] == 2);
    }

    void test_update_grid1() {
        Life<ConwayCell> life = Life<ConwayCell>(2, 2, ConwayCell(true));
        life.calculateNeighbors();
        CPPUNIT_ASSERT(life._n[0][0] == 3);
        CPPUNIT_ASSERT(life._n[1][0] == 3);
        CPPUNIT_ASSERT(life._n[0][1] == 3);
        CPPUNIT_ASSERT(life._n[1][1] == 3);
        life.updateGrid();
        CPPUNIT_ASSERT(life._n[0][0] == 0);
        CPPUNIT_ASSERT(life._n[1][0] == 0);
        CPPUNIT_ASSERT(life._n[0][1] == 0);
        CPPUNIT_ASSERT(life._n[1][1] == 0);
    }

    void test_update_grid2() {
        Life<ConwayCell> life = Life<ConwayCell>(2, 2);
        life._g[0][0].tick(3);
        CPPUNIT_ASSERT(life._g[0][0].isAlive() == true);
        life.updateGrid();
        CPPUNIT_ASSERT(life._g[0][0].isAlive() == false);
    }

    void test_update_grid3() {
        Life<Cell> life = Life<Cell>(2, 2, Cell(new FredkinCell()));
        life._g[0][0].tick(1);
        CPPUNIT_ASSERT(life._g[0][0].isAlive() == true);
        life.updateGrid();
        CPPUNIT_ASSERT(life._g[0][0].isAlive() == false);
    }

    void test_parse_type1() {
        CPPUNIT_ASSERT(Life<Cell>::parseType('I') == INVALID);
    }

    void test_parse_type2() {
        CPPUNIT_ASSERT(Life<Cell>::parseType('4') == FREDKIN);
    }

    void test_parse_type3() {
        CPPUNIT_ASSERT(Life<Cell>::parseType('*') == CONWAY);
    }

    void test_parse_age1() {
        CPPUNIT_ASSERT(Life<FredkinCell>::parseAge('0') == 0);
    }

    void test_parse_age2() {
        CPPUNIT_ASSERT(Life<FredkinCell>::parseAge('9') == 9);
    }

    void test_parse_age3() {
        CPPUNIT_ASSERT(Life<FredkinCell>::parseAge('4') == 4);
    }

    void test_parse_state1() {
        CPPUNIT_ASSERT(Life<FredkinCell>::parseState('9', FREDKIN) == true);
    }

    void test_parse_state2() {
        CPPUNIT_ASSERT(Life<ConwayCell>::parseState('*', CONWAY) == true);
        CPPUNIT_ASSERT(Life<ConwayCell>::parseState('.', CONWAY) == false);
    }

    void test_parse_state3() {
        CPPUNIT_ASSERT(Life<FredkinCell>::parseState('-', FREDKIN) == false);
    }

    void test_parse_fredkin1() {
        std::ifstream input("RunLifeTest8.in", std::ios::in);
        try {
            std::vector<std::vector<FredkinCell> > grid = Life<FredkinCell>::parseFredkin(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '0');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_fredkin2() {
        std::ifstream input("RunLifeTest9.in", std::ios::in);
        try {
            std::vector<std::vector<FredkinCell> > grid = Life<FredkinCell>::parseFredkin(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '-');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_fredkin3() {
        std::ifstream input("RunLifeFredkin.in", std::ios::in);
        try {
            std::vector<std::vector<FredkinCell> > grid = Life<FredkinCell>::parseFredkin(input);
            CPPUNIT_ASSERT(grid[10][9].icon() == '0');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_conway1() {
        std::ifstream input("RunLifeConway.in", std::ios::in);
        try {
            std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '.');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_conway2() {
        std::ifstream input("RunLifeTest5.in", std::ios::in);
        try {
            std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '*');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_conway3() {
        std::ifstream input("RunLifeTest7.in", std::ios::in);
        try {
            std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
            CPPUNIT_ASSERT(grid[0][5].icon() == '*');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_cell1() {
        std::ifstream input("RunLifeTest8.in", std::ios::in);
        try {
            std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '0');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }

    }

    void test_parse_cell2() {
        std::ifstream input("RunLifeTest10.in", std::ios::in);
        try {
            std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '.');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_parse_cell3() {
        std::ifstream input("RunLifeTest5.in", std::ios::in);
        try {
            std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
            CPPUNIT_ASSERT(grid[0][0].icon() == '*');
        }
        catch(...) {
            CPPUNIT_ASSERT(false);
        }
    }

    void test_valid1() {
        Life<Cell> life = Life<Cell>(2, 2, new FredkinCell());
        CPPUNIT_ASSERT(life.valid(-1,-1) == false);
    }

    void test_valid2() {
        Life<Cell> life = Life<Cell>(2, 2, new FredkinCell());
        CPPUNIT_ASSERT(life.valid(0, 5) == false);
    }

    void test_valid3() {
        Life<Cell> life = Life<Cell>(2, 2, new FredkinCell());
        CPPUNIT_ASSERT(life.valid(1,1) == true);
    }
    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
        CPPUNIT_TEST(test_valid1);
        CPPUNIT_TEST(test_valid2);
        CPPUNIT_TEST(test_valid3);
        CPPUNIT_TEST(test_parse_cell1);
        CPPUNIT_TEST(test_parse_cell2);
        CPPUNIT_TEST(test_parse_cell3);
        CPPUNIT_TEST(test_parse_conway1);
        CPPUNIT_TEST(test_parse_conway2);
        CPPUNIT_TEST(test_parse_conway3);
        CPPUNIT_TEST(test_parse_fredkin1);
        CPPUNIT_TEST(test_parse_fredkin2);
        CPPUNIT_TEST(test_parse_fredkin3);
        CPPUNIT_TEST(test_parse_age1);
        CPPUNIT_TEST(test_parse_age2);
        CPPUNIT_TEST(test_parse_age3);
        CPPUNIT_TEST(test_parse_type1);
        CPPUNIT_TEST(test_parse_type2);
        CPPUNIT_TEST(test_parse_type3);
        CPPUNIT_TEST(test_parse_state1);
        CPPUNIT_TEST(test_parse_state2);
        CPPUNIT_TEST(test_parse_state3);
        CPPUNIT_TEST(test_update_grid1);
        CPPUNIT_TEST(test_update_grid2);
        CPPUNIT_TEST(test_update_grid3);
        CPPUNIT_TEST(test_calculate_neighbors1);
        CPPUNIT_TEST(test_calculate_neighbors2);
        CPPUNIT_TEST(test_calculate_neighbors3);
        CPPUNIT_TEST(test_display1);
        CPPUNIT_TEST(test_display2);
        CPPUNIT_TEST(test_display3);
        CPPUNIT_TEST(test_simulate1);
        CPPUNIT_TEST(test_simulate2);
        CPPUNIT_TEST(test_simulate3);
        CPPUNIT_TEST(test_life1);
        CPPUNIT_TEST(test_life2);
        CPPUNIT_TEST(test_life3);
        CPPUNIT_TEST(test_clone1);
        CPPUNIT_TEST(test_clone2);
        CPPUNIT_TEST(test_clone3);
        CPPUNIT_TEST(test_icon1);
        CPPUNIT_TEST(test_icon2);
        CPPUNIT_TEST(test_icon3);
        CPPUNIT_TEST(test_tick1);
        CPPUNIT_TEST(test_tick2);
        CPPUNIT_TEST(test_tick3);
        CPPUNIT_TEST(test_neighbors1);
        CPPUNIT_TEST(test_neighbors2);
        CPPUNIT_TEST(test_neighbors3);
        CPPUNIT_TEST(test_is_alive1);
        CPPUNIT_TEST(test_is_alive2);
        CPPUNIT_TEST(test_is_alive3);
        CPPUNIT_TEST(test_cell1);
        CPPUNIT_TEST(test_cell2);
        CPPUNIT_TEST(test_cell3);
        CPPUNIT_TEST(test_fredkin1);
        CPPUNIT_TEST(test_fredkin2);
        CPPUNIT_TEST(test_fredkin3);
        CPPUNIT_TEST(test_conway1);
        CPPUNIT_TEST(test_conway2);
        CPPUNIT_TEST(test_conway3);

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