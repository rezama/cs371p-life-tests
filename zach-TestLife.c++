// ------------------------------
// projects/matlab/TestDarwin.c++
// Copyright (C) 2012
// Glenn P. Downing & Jon Tucker
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
#include <stdexcept>

#define private public
#include "Life.h"

// ----------
// TestLife
// ----------

struct TestLife : CppUnit::TestFixture {

    void life_constructor_1() {
      Life<ConwayCell> x(10, 8);
      CPPUNIT_ASSERT(x.neighborGrid.size() == 10);  // extra 2 for moat
      CPPUNIT_ASSERT(x.neighborGrid[0].size() == 8);  // extra 2 for moat
      // cells are unique
      CPPUNIT_ASSERT(&(x.cellGrid[1][1]) != &(x.cellGrid[1][2]));
    }

    void life_constructor_2() {
      Life<ConwayCell> x(8, 10);
      CPPUNIT_ASSERT(x.cellGrid.size() == 8);  // extra 2 for moat
      CPPUNIT_ASSERT(x.cellGrid[0].size() == 10);  // extra 2 for moat
      // cells are unique
      CPPUNIT_ASSERT(&(x.cellGrid[2][2]) != &(x.cellGrid[1][2]));
    }

    void life_constructor_3() {
      Life<Cell> x(5, 5, new ConwayCell());
      CPPUNIT_ASSERT(x.cellGrid.size() == 5);  // extra 2 for moat
      CPPUNIT_ASSERT(x.neighborGrid[0].size() == 5);  // extra 2 for moat
      // cells are unique
      CPPUNIT_ASSERT(&(x.cellGrid[2][2]) != &(x.cellGrid[1][2]));
    }

    void life_run_1() {
      Life<ConwayCell> x(3, 3, ConwayCell());
      x.cellGrid[1][1].alive = true;
      x.population++;
      x.run(1, -1);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].alive);
      CPPUNIT_ASSERT(x.population == 0);
    }

    void life_run_2() {
      Life<FredkinCell> x(3, 3, FredkinCell());
      x.cellGrid[1][1].alive = true;
      x.population++;
      x.run(1, -1);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].alive);
      CPPUNIT_ASSERT(x.cellGrid[1][0].alive);
      CPPUNIT_ASSERT(x.cellGrid[1][2].alive);
      CPPUNIT_ASSERT(x.cellGrid[0][1].alive);
      CPPUNIT_ASSERT(x.cellGrid[2][1].alive);
    }

    void life_run_3() {
      Life<Cell> x(3, 3, new FredkinCell());
      x.cellGrid[1][1]._c->alive = true;
      x.cellGrid[0][1]._c->alive = true;
      x.population++;
      x.run(2, -1);
      std::ostringstream w;
      x.cellGrid[0][1].print(w);
      CPPUNIT_ASSERT(w.str() == "*");
    }

    void life_display_1() {
      Life<ConwayCell> x(3, 3);
      std::ostringstream w;
      x.cellGrid[1][1].alive = true;
      x.population++;
      x.display(w, 0);
      string output = "Generation = 0, Population = 1.\n";
      output += "...\n";
      output += ".*.\n";
      output += "...\n\n";
      CPPUNIT_ASSERT(w.str() == output);
    }

    void life_display_2 () {
      Life<FredkinCell> x(3, 3);
      std::ostringstream w;
      x.cellGrid[1][1].alive = true;
      x.population++;
      x.display(w, 0);
      string output = "Generation = 0, Population = 1.\n";
      output += "---\n";
      output += "-0-\n";
      output += "---\n\n";
      CPPUNIT_ASSERT(w.str() == output);
    }

    void life_display_3 () {
      Life<Cell> x(6, 6, new FredkinCell());
      std::ostringstream w;
      x.cellGrid[2][2]._c->alive = true;
      x.population++;
      x.cellGrid[2][3]._c->alive = true;
      x.population++;
      x.cellGrid[3][1]._c->alive = true;
      x.population++;
      x.cellGrid[3][2]._c->alive = true;
      x.population++;
      x.cellGrid[3][3]._c->alive = true;
      x.population++;
      x.cellGrid[3][4]._c->alive = true;
      x.population++;
      x.run(1, -1);
      x.display(w, 1);
      string output = "Generation = 1, Population = 12.\n";
      output += "------\n";
      output += "--00--\n";
      output += "------\n";
      output += "011110\n";
      output += "-0000-\n";
      output += "------\n\n";
      CPPUNIT_ASSERT(w.str() == output);
    }

    void life_updateNeighbors_1 () {
      Life<ConwayCell> x(3, 3);
      x.cellGrid[1][1].alive = true;
      x.updateNeighbors(1, 1);
      CPPUNIT_ASSERT(x.neighborGrid[2][2][0] == 1);
      CPPUNIT_ASSERT(x.neighborGrid[2][2][1] == 0);
    }

    void life_updateNeighbors_2 () {
      Life<ConwayCell> x(3, 3);
      x.cellGrid[0][0].alive = true;
      x.updateNeighbors(0, 0);
      CPPUNIT_ASSERT(x.neighborGrid[0][0][0] == 0);
      CPPUNIT_ASSERT(x.neighborGrid[0][1][0] == 1);
      CPPUNIT_ASSERT(x.neighborGrid[1][1][1] == 0);
    }

    void life_updateNeighbors_3 () {
      Life<ConwayCell> x(3, 3);
      x.cellGrid[1][0].alive = true;
      x.updateNeighbors(1, 0);  // no live cell here
      CPPUNIT_ASSERT(x.neighborGrid[0][0][0] == 1);
      CPPUNIT_ASSERT(x.neighborGrid[0][0][1] == 1);
    }

    void cell_copy_ctor_1 () {
      Cell c = Cell(new ConwayCell());
      Cell d(c);
      CPPUNIT_ASSERT(d != c);
    }

    void cell_copy_ctor_2 () {
      Cell c = Cell(new ConwayCell());
      Cell d(c);
      CPPUNIT_ASSERT(&d != &c);
    }

    void cell_copy_ctor_3 () {
      Cell c = Cell(0);
      Cell d(c);
      CPPUNIT_ASSERT(!d._c);
    }

    void cell_ptr_ctor_1 () {
      AbstractCell* a = new FredkinCell();
      Cell c(a);
      CPPUNIT_ASSERT(c._c);
    }

    void cell_ptr_ctor_2 () {
      AbstractCell* a = 0;
      Cell c(a);
      CPPUNIT_ASSERT(!c._c);
    }

    void cell_ptr_ctor_3 () {
      Cell c(new FredkinCell());
      Cell d(new ConwayCell());
      CPPUNIT_ASSERT(d != c);
    }

    void cell_dtor_1 () {
      // not implemented - letting Valgrind take care of this
    }

    void cell_dtor_2 () {
      // not implemented - letting Valgrind take care of this
    }

    void cell_dtor_3 () {
      // not implemented - letting Valgrind take care of this
    }

    void cell_transition_1 () {
      Life<Cell> x(3, 3, new ConwayCell());
      x.cellGrid[1][1].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      x.updateNeighbors(1, 1);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].isAlive());
    }

    void cell_transition_2 () {
      Life<Cell> x(3, 3, new FredkinCell());
      x.cellGrid[1][1].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      x.updateNeighbors(1, 1);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].isAlive());
    }

    void cell_transition_3 () {
      Life<Cell> x(3, 3, new FredkinCell());
      x.cellGrid[1][1].comeAlive();
      x.cellGrid[0][2].comeAlive();
      x.cellGrid[1][2].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      x.updateNeighbors(1, 1);
      x.updateNeighbors(0, 2);
      x.updateNeighbors(1, 2);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == "*"); // now a ConwayCell!
    }

    void cell_print_1 () {
      Life<Cell> x(3, 3, new ConwayCell());
      x.cellGrid[1][1].comeAlive();
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == "*");
    }

    void cell_print_2 () {
      Life<Cell> x(3, 3, new ConwayCell());
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == ".");
    }

    void cell_print_3 () {
      Life<Cell> x(3, 3, new FredkinCell());
      x.cellGrid[1][1].comeAlive();
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == "0");
    }

    void cell_comeAlive_1 () {
      Life<Cell> x(3, 3, new FredkinCell());
      x.cellGrid[1][1].comeAlive();
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
    }

    void cell_comeAlive_2 () {
      Life<Cell> x(3, 3, new ConwayCell());
      x.cellGrid[1][1].comeAlive();
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
    }

    void cell_comeAlive_3 () {
      Life<Cell> x(3, 3, new ConwayCell());
      x.cellGrid[1][1].comeAlive();
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == "*");
    }

    void cell_isAlive_1 () {
      Life<Cell> x(3, 3, new ConwayCell());
      x.cellGrid[1][1]._c->alive = true;
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
    }

    void cell_isAlive_2 () {
      Life<Cell> x(3, 3, new FredkinCell());
      x.cellGrid[1][1]._c->alive = true;
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
    }

    void cell_isAlive_3 () {
      Life<Cell> x(3, 3, new FredkinCell());
      CPPUNIT_ASSERT(!x.cellGrid[1][1].isAlive());
    }

    void conway_ctor_1 () {
      ConwayCell c;
      CPPUNIT_ASSERT(!c.alive);
    }

    void conway_ctor_2 () {
      AbstractCell* a  = new ConwayCell();
      CPPUNIT_ASSERT(!a->isAlive());
      delete a;
    }

    void conway_ctor_3 () {
      Life<ConwayCell> x(10, 10, ConwayCell());
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == ".");   // has a dead ConwayCell
    }

    void conway_transition_1 () {
      Life<ConwayCell> x(3, 3, ConwayCell());
      x.cellGrid[1][1].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      x.updateNeighbors(1, 1);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].isAlive());
    }

    void conway_transition_2 () {
      Life<ConwayCell> x(3, 3, ConwayCell());
      x.cellGrid[0][1].comeAlive();
      x.cellGrid[2][1].comeAlive();
      x.cellGrid[1][0].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(!x.cellGrid[1][1].isAlive());
      x.updateNeighbors(0, 1);
      x.updateNeighbors(2, 1);
      x.updateNeighbors(1, 0);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
    }

    void conway_transition_3 () {
      Life<ConwayCell> x(3, 3, ConwayCell());
      x.cellGrid[1][0].comeAlive();
      x.cellGrid[1][1].comeAlive();
      x.cellGrid[1][2].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][0].isAlive());
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      CPPUNIT_ASSERT(x.cellGrid[1][2].isAlive());
      x.updateNeighbors(1, 0);
      x.updateNeighbors(1, 1);
      x.updateNeighbors(1, 2);
      x.cellGrid[1][0].transition(x.neighborGrid[1][0], x.population);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      x.cellGrid[1][2].transition(x.neighborGrid[1][2], x.population);
      CPPUNIT_ASSERT(!x.cellGrid[1][0].isAlive());
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      CPPUNIT_ASSERT(!x.cellGrid[1][2].isAlive());
    }

    void conway_print_1 () {
      ConwayCell c;
      std::ostringstream w;
      c.print(w);
      CPPUNIT_ASSERT(w.str() == ".");
    }

    void conway_print_2 () {
      ConwayCell c;
      c.alive = true;
      std::ostringstream w;
      c.print(w);
      CPPUNIT_ASSERT(w.str() == "*");
    }

    void conway_print_3 () {
      ConwayCell c;
      c.alive = true;
      std::ostringstream w;
      c.print(w);
      c.alive = false;
      c.print(w);
      CPPUNIT_ASSERT(w.str() == "*.");
    }

    void conway_clone_1 () {
      Cell cc(new ConwayCell());
      Cell c(cc);     // Cell(const Cell&) calls _c->clone(), in this case, Conway's
      CPPUNIT_ASSERT(c._c->alive == cc._c->alive);
    }

    void conway_clone_2 () {
      ConwayCell cc;
      Cell c(cc.clone());
      CPPUNIT_ASSERT(c._c->alive == cc.alive);
    }

    void conway_clone_3 () {
      Cell cc(new ConwayCell());
      Cell c(cc);
      Cell d(c);
      CPPUNIT_ASSERT(d._c->alive == cc._c->alive);
    }

    void conway_comeAlive_1 () {
      ConwayCell c;
      c.comeAlive();
      CPPUNIT_ASSERT(c.alive == true);
    }

    void conway_comeAlive_2 () {
      Life<ConwayCell> x(10, 10, ConwayCell());
      CPPUNIT_ASSERT(x.cellGrid[5][5].alive == false);
      x.cellGrid[5][5].comeAlive();
      CPPUNIT_ASSERT(x.cellGrid[5][5].alive == true);
    }

    void conway_comeAlive_3 () {
      Cell c(new ConwayCell());
      c.comeAlive();
      CPPUNIT_ASSERT(c._c->alive == true);
    }

    void conway_isAlive_1 () {
      Life<ConwayCell> x(10, 10, ConwayCell());
      CPPUNIT_ASSERT(!x.cellGrid[5][5].isAlive());
      x.cellGrid[5][5].alive = true;
      CPPUNIT_ASSERT(x.cellGrid[5][5].isAlive());
    }

    void conway_isAlive_2 () {
      ConwayCell c;
      c.alive = true;
      CPPUNIT_ASSERT(c.isAlive());
    }

    void conway_isAlive_3 () {
      Cell c(new ConwayCell());
      c.comeAlive();
      CPPUNIT_ASSERT(c._c->isAlive());
    }

    void fredkin_ctor_1 () {
      FredkinCell f;
      CPPUNIT_ASSERT(!f.alive);
    }

    void fredkin_ctor_2 () {
      AbstractCell* a  = new FredkinCell();
      CPPUNIT_ASSERT(!a->alive);
      delete a;
    }

    void fredkin_ctor_3 () {
      Life<FredkinCell> x(10, 10, FredkinCell());
      std::ostringstream w;
      x.cellGrid[1][1].print(w);
      CPPUNIT_ASSERT(w.str() == "-");   // has a dead FredkinCell
    }

    void fredkin_transition_1 () {
      Life<FredkinCell> x(3, 3, FredkinCell());
      x.cellGrid[1][1].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][1].alive);
      x.updateNeighbors(1, 1);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].alive);
    }

    void fredkin_transition_2 () {
      Life<FredkinCell> x(3, 3, FredkinCell());
      x.cellGrid[1][0].alive = true;
      x.population++;
      x.cellGrid[1][1].alive = true;
      x.population++;
      x.cellGrid[1][2].alive = true;
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][1].alive);
      x.updateNeighbors(1, 0);
      x.updateNeighbors(1, 1);
      x.updateNeighbors(1, 2);
      x.cellGrid[1][1].transition(x.neighborGrid[1][1], x.population);
      CPPUNIT_ASSERT(!x.cellGrid[1][1].alive);
    }

    void fredkin_transition_3 () {
      Life<FredkinCell> x(3, 3, FredkinCell());
      x.cellGrid[1][0].comeAlive();
      x.cellGrid[1][1].comeAlive();
      x.population++;
      CPPUNIT_ASSERT(x.cellGrid[1][0].isAlive());
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
      x.updateNeighbors(1, 0);
      x.updateNeighbors(1, 1);
      x.cellGrid[1][0].transition(x.neighborGrid[1][0], x.population);
      CPPUNIT_ASSERT(x.cellGrid[1][0].isAlive());
      CPPUNIT_ASSERT(x.cellGrid[1][1].isAlive());
    }

    void fredkin_print_1 () {
      FredkinCell f;
      std::ostringstream w;
      f.print(w);
      CPPUNIT_ASSERT(w.str() == "-");
    }

    void fredkin_print_2 () {
      FredkinCell f;
      f.alive = true;
      std::ostringstream w;
      f.print(w);
      CPPUNIT_ASSERT(w.str() == "0");
    }

    void fredkin_print_3 () {
      FredkinCell f;
      f.alive = true;
      std::ostringstream w;
      f.print(w);
      f.alive = false;
      f.print(w);
      CPPUNIT_ASSERT(w.str() == "0-");
    }

    void fredkin_clone_1 () {
      Cell fc(new FredkinCell());
      Cell f(fc);     // Cell(const Cell&) calls _c->clone(), in this case, Fredkin's
      CPPUNIT_ASSERT(f._c->alive == fc._c->alive);
    }

    void fredkin_clone_2 () {
      FredkinCell fc;
      Cell f(fc.clone());
      CPPUNIT_ASSERT(f._c->alive == fc.alive);
    }

    void fredkin_clone_3 () {
      Cell cc(new FredkinCell());
      Cell c(cc);
      Cell d(c);
      CPPUNIT_ASSERT(d._c->alive == cc._c->alive);
    }

    void fredkin_comeAlive_1 () {
      FredkinCell f;
      f.comeAlive();
      CPPUNIT_ASSERT(f.alive == true);
    }

    void fredkin_comeAlive_2 () {
      Life<FredkinCell> x(10, 10, FredkinCell());
      CPPUNIT_ASSERT(x.cellGrid[5][5].alive == false);
      x.cellGrid[5][5].comeAlive();
      CPPUNIT_ASSERT(x.cellGrid[5][5].alive == true);
    }

    void fredkin_comeAlive_3 () {
      Cell c(new FredkinCell());
      c.comeAlive();
      CPPUNIT_ASSERT(c._c->alive == true);
    }

    void fredkin_isAlive_1 () {
      Life<FredkinCell> x(10, 10, FredkinCell());
      CPPUNIT_ASSERT(!x.cellGrid[5][5].isAlive());
      x.cellGrid[5][5].alive = true;
      CPPUNIT_ASSERT(x.cellGrid[5][5].isAlive());
    }

    void fredkin_isAlive_2 () {
      FredkinCell f;
      f.alive = true;
      CPPUNIT_ASSERT(f.isAlive());
    }

    void fredkin_isAlive_3 () {
      Cell c(new FredkinCell());
      c.comeAlive();
      CPPUNIT_ASSERT(c._c->isAlive());
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestLife);
    CPPUNIT_TEST(life_constructor_1);
    CPPUNIT_TEST(life_constructor_2);
    CPPUNIT_TEST(life_constructor_3);
    CPPUNIT_TEST(life_run_1);
    CPPUNIT_TEST(life_run_2);
    CPPUNIT_TEST(life_run_3);
    CPPUNIT_TEST(life_display_1);
    CPPUNIT_TEST(life_display_2);
    CPPUNIT_TEST(life_display_3);
    CPPUNIT_TEST(life_updateNeighbors_1);
    CPPUNIT_TEST(life_updateNeighbors_2);
    CPPUNIT_TEST(life_updateNeighbors_3);
    CPPUNIT_TEST(cell_copy_ctor_1);
    CPPUNIT_TEST(cell_copy_ctor_2);
    CPPUNIT_TEST(cell_copy_ctor_3);
    CPPUNIT_TEST(cell_ptr_ctor_1);
    CPPUNIT_TEST(cell_ptr_ctor_2);
    CPPUNIT_TEST(cell_ptr_ctor_3);
    CPPUNIT_TEST(cell_dtor_1);
    CPPUNIT_TEST(cell_dtor_2);
    CPPUNIT_TEST(cell_dtor_3);
    CPPUNIT_TEST(cell_transition_1);
    CPPUNIT_TEST(cell_transition_2);
    CPPUNIT_TEST(cell_transition_3);
    CPPUNIT_TEST(cell_print_1);
    CPPUNIT_TEST(cell_print_2);
    CPPUNIT_TEST(cell_print_3);
    CPPUNIT_TEST(cell_comeAlive_1);
    CPPUNIT_TEST(cell_comeAlive_2);
    CPPUNIT_TEST(cell_comeAlive_3);
    CPPUNIT_TEST(cell_isAlive_1);
    CPPUNIT_TEST(cell_isAlive_2);
    CPPUNIT_TEST(cell_isAlive_3);

    CPPUNIT_TEST(conway_ctor_1);
    CPPUNIT_TEST(conway_ctor_2);
    CPPUNIT_TEST(conway_ctor_3);
    CPPUNIT_TEST(conway_transition_1);
    CPPUNIT_TEST(conway_transition_2);
    CPPUNIT_TEST(conway_transition_3);
    CPPUNIT_TEST(conway_print_1);
    CPPUNIT_TEST(conway_print_2);
    CPPUNIT_TEST(conway_print_3);
    CPPUNIT_TEST(conway_clone_1);
    CPPUNIT_TEST(conway_clone_2);
    CPPUNIT_TEST(conway_clone_3);
    CPPUNIT_TEST(conway_comeAlive_1);
    CPPUNIT_TEST(conway_comeAlive_2);
    CPPUNIT_TEST(conway_comeAlive_3);
    CPPUNIT_TEST(conway_isAlive_1);
    CPPUNIT_TEST(conway_isAlive_2);
    CPPUNIT_TEST(conway_isAlive_3);

    CPPUNIT_TEST(fredkin_ctor_1);
    CPPUNIT_TEST(fredkin_ctor_2);
    CPPUNIT_TEST(fredkin_ctor_3);
    CPPUNIT_TEST(fredkin_transition_1);
    CPPUNIT_TEST(fredkin_transition_2);
    CPPUNIT_TEST(fredkin_transition_3);
    CPPUNIT_TEST(fredkin_print_1);
    CPPUNIT_TEST(fredkin_print_2);
    CPPUNIT_TEST(fredkin_print_3);
    CPPUNIT_TEST(fredkin_clone_1);
    CPPUNIT_TEST(fredkin_clone_2);
    CPPUNIT_TEST(fredkin_clone_3);
    CPPUNIT_TEST(fredkin_comeAlive_1);
    CPPUNIT_TEST(fredkin_comeAlive_2);
    CPPUNIT_TEST(fredkin_comeAlive_3);
    CPPUNIT_TEST(fredkin_isAlive_1);
    CPPUNIT_TEST(fredkin_isAlive_2);
    CPPUNIT_TEST(fredkin_isAlive_3);

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
