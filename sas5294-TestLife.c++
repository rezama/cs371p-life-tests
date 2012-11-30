// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"
#include <cstdlib>

#define private public
#define protected public
#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

/*
 * g++ -ansi -pedantic -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 * valgrind TestLife.app &> TestLife.out
 *
 */

// --------
// TestLife
// --------

struct TestLife : CppUnit::TestFixture 
{

  // ----------------------
  // ConwayCell Constructor
  // ----------------------
 
  void test_conway_constuctor () 
  {
    ConwayCell cc;
    CPPUNIT_ASSERT (!cc.alive());
  }
  
  // -----------------------
  // FredkinCell Constructor
  // -----------------------
 
  void test_fredkin_constructor () 
  {
    FredkinCell fc;
    CPPUNIT_ASSERT (!fc.alive());
  }

  // ----------------
  // Cell Constructor
  // ----------------
 
  void test_cell_constructor () 
  {
    Cell c;
    CPPUNIT_ASSERT (!c.alive());
  }  

  // ----------------
  // ConwayCell Clone
  // ----------------

  void test_conway_clone () 
  {
    ConwayCell cc;
    AbstractCell* ccc = cc.clone();
    CPPUNIT_ASSERT (dynamic_cast<ConwayCell*>(ccc) != &cc);
  }

  // -----------------
  // FredkinCell Clone
  // -----------------

  void test_fredkin_clone () 
  {
    FredkinCell fc;
    AbstractCell* fcc = fc.clone();
    CPPUNIT_ASSERT (dynamic_cast<FredkinCell*>(fcc) != &fc);
  }

  // -----------------------
  // ConwayCell Change State
  // -----------------------

  void test_conway_change_state () 
  {
    ConwayCell cc;
    cc.change_state('*');
    CPPUNIT_ASSERT (cc.alive());
  }

  // ------------------------
  // FredkinCell Change State
  // ------------------------

  void test_fredkin_change_state () 
  {
    FredkinCell fc;
    fc.change_state('0');
    CPPUNIT_ASSERT (fc.alive());
  }

  // -----------------
  // Cell Change State
  // -----------------

  void test_cell_change_state () 
  {
    Cell c;
    c.change_state('0');
    CPPUNIT_ASSERT (c.alive());
  }

  // -----------------
  // ConwayCell Evolve
  // -----------------

  void test_conway_evolve () 
  {
    ConwayCell cc;
    cc.change_state('*');
    cc.evolve(0);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('*');
    cc.evolve(1);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('*');
    cc.evolve(2);
    CPPUNIT_ASSERT (cc.alive());
    cc.change_state('*');
    cc.evolve(3);
    CPPUNIT_ASSERT (cc.alive());
    cc.change_state('*');
    cc.evolve(4);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('*');
    cc.evolve(5);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('*');
    cc.evolve(6);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('*');
    cc.evolve(7);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('*');
    cc.evolve(8);
    CPPUNIT_ASSERT (!cc.alive());

    cc.change_state('.');
    cc.evolve(0);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(1);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(2);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(3);
    CPPUNIT_ASSERT (cc.alive());
    cc.change_state('.');
    cc.evolve(4);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(5);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(6);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(7);
    CPPUNIT_ASSERT (!cc.alive());
    cc.change_state('.');
    cc.evolve(8);
    CPPUNIT_ASSERT (!cc.alive());
  }

  // ------------------
  // FredkinCell Evolve
  // ------------------

  void test_fredkin_evolve () 
  {
    FredkinCell fc;
    fc.change_state('0');
    fc.evolve(0);
    CPPUNIT_ASSERT (!fc.alive());
    fc.change_state('0');
    fc.evolve(1);
    CPPUNIT_ASSERT (fc.alive());
    fc.change_state('0');
    fc.evolve(2);
    CPPUNIT_ASSERT (!fc.alive());
    fc.change_state('0');
    fc.evolve(3);
    CPPUNIT_ASSERT (fc.alive());
    fc.change_state('0');
    fc.evolve(4);
    CPPUNIT_ASSERT (!fc.alive());

    fc.change_state('-');
    fc.evolve(0);
    CPPUNIT_ASSERT (!fc.alive());
    fc.change_state('-');
    fc.evolve(1);
    CPPUNIT_ASSERT (fc.alive());
    fc.change_state('-');
    fc.evolve(2);
    CPPUNIT_ASSERT (!fc.alive());
    fc.change_state('-');
    fc.evolve(3);
    CPPUNIT_ASSERT (fc.alive());
    fc.change_state('-');
    fc.evolve(4);
    CPPUNIT_ASSERT (!fc.alive());
  }

  // -----------
  // Cell Evolve
  // -----------

  void test_cell_evolve () 
  {
    Cell c;

    c.change_state('0');
    c.evolve(0);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('0');
    c.evolve(1);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('0');
    c.evolve(2);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('0');
    c.evolve(3);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('0');
    c.evolve(4);
    CPPUNIT_ASSERT (!c.alive());

    c.change_state('-');
    c.evolve(0);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('-');
    c.evolve(1);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('-');
    c.evolve(2);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('-');
    c.evolve(3);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('-');
    c.evolve(4);
    CPPUNIT_ASSERT (!c.alive());

    c.change_state('*');
    c.evolve(0);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('*');
    c.evolve(1);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('*');
    c.evolve(2);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('*');
    c.evolve(3);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('*');
    c.evolve(4);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('*');
    c.evolve(5);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('*');
    c.evolve(6);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('*');
    c.evolve(7);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('*');
    c.evolve(8);
    CPPUNIT_ASSERT (!c.alive());

    c.change_state('.');
    c.evolve(0);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(1);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(2);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(3);
    CPPUNIT_ASSERT (c.alive());
    c.change_state('.');
    c.evolve(4);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(5);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(6);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(7);
    CPPUNIT_ASSERT (!c.alive());
    c.change_state('.');
    c.evolve(8);
    CPPUNIT_ASSERT (!c.alive());
  }

  // ------------
  // Conway Print
  // ------------

  void test_conway_print () 
  {
    ConwayCell cc;
    CPPUNIT_ASSERT (cc.print() == '.');
  }

  void test_conway_print2 () 
  {
    ConwayCell cc;
    cc.change_state('*');
    CPPUNIT_ASSERT (cc.print() == '*');
  }

  // -------------
  // Fredkin Print
  // -------------

  void test_fredkin_print () 
  {
    FredkinCell fc;
    CPPUNIT_ASSERT (fc.print() == '-');
  }

  void test_fredkin_print2 () 
  {
    FredkinCell fc;
    fc.change_state('0');
    CPPUNIT_ASSERT (fc.print() == '0');
  }

  void test_fredkin_print3 () 
  {
    FredkinCell fc;
    fc.change_state('9');
    fc.evolve(1);
    CPPUNIT_ASSERT (fc.print() == '+');
  }

  // ----------
  // Cell Print
  // ----------

  void test_cell_print () 
  {
    Cell c;
    CPPUNIT_ASSERT (c.print() == '-');
  }

  void test_cell_print2 () 
  {
    Cell c;
    c.change_state('0');
    CPPUNIT_ASSERT (c.print() == '0');
  }

  void test_cell_print3 () 
  {
    Cell c;
    c.change_state('1');
    c.evolve(1);
    CPPUNIT_ASSERT (c.print() == '*');
  }

  // -------------------------
  // Conway Neighbors Contains
  // -------------------------

  void test_conway_neighbors_contains () 
  {
    ConwayCell cc;
    CPPUNIT_ASSERT (cc.neighbors_contains(-1, -1));
  }

  void test_conway_neighbors_contains2 () 
  {
    ConwayCell cc;
    CPPUNIT_ASSERT (cc.neighbors_contains(0, 1));
  }

  void test_conway_neighbors_contains3 () 
  {
    ConwayCell cc;
    CPPUNIT_ASSERT (cc.neighbors_contains(1, 1));
  }

  // -------------------------
  // Fredkin Neighbors Contains
  // -------------------------

  void test_fredkin_neighbors_contains () 
  {
    FredkinCell fc;
    CPPUNIT_ASSERT (!fc.neighbors_contains(-1, -1));
  }

  void test_fredkin_neighbors_contains2 () 
  {
    FredkinCell fc;
    CPPUNIT_ASSERT (fc.neighbors_contains(0, 1));
  }

  void test_fredkin_neighbors_contains3 () 
  {
    FredkinCell fc;
    CPPUNIT_ASSERT (!fc.neighbors_contains(1, 1));
  }

  // -------------------------
  // Cell Neighbors Contains
  // -------------------------

  void test_cell_neighbors_contains () 
  {
    Cell c;
    CPPUNIT_ASSERT (!c.neighbors_contains(-1, -1));
  }

  void test_cell_neighbors_contains2 () 
  {
    Cell c;
    CPPUNIT_ASSERT (c.neighbors_contains(0, 1));
  }

  void test_cell_neighbors_contains3 () 
  {
    Cell c;
    CPPUNIT_ASSERT (!c.neighbors_contains(1, 1));
  }

  CPPUNIT_TEST_SUITE(TestLife);

  CPPUNIT_TEST(test_conway_constuctor);
  CPPUNIT_TEST(test_fredkin_constructor);
  CPPUNIT_TEST(test_cell_constructor);
  CPPUNIT_TEST(test_conway_clone);
  CPPUNIT_TEST(test_fredkin_clone);
  CPPUNIT_TEST(test_conway_change_state);
  CPPUNIT_TEST(test_fredkin_change_state);
  CPPUNIT_TEST(test_cell_change_state);
  CPPUNIT_TEST(test_conway_evolve);
  CPPUNIT_TEST(test_fredkin_evolve);
  CPPUNIT_TEST(test_cell_evolve);
  CPPUNIT_TEST(test_conway_print);
  CPPUNIT_TEST(test_conway_print2);
  CPPUNIT_TEST(test_fredkin_print);
  CPPUNIT_TEST(test_fredkin_print2);
  CPPUNIT_TEST(test_fredkin_print3);
  CPPUNIT_TEST(test_cell_print);
  CPPUNIT_TEST(test_cell_print2);
  CPPUNIT_TEST(test_cell_print3);
  CPPUNIT_TEST(test_conway_neighbors_contains);
  CPPUNIT_TEST(test_conway_neighbors_contains2);
  CPPUNIT_TEST(test_conway_neighbors_contains3);
  CPPUNIT_TEST(test_fredkin_neighbors_contains);
  CPPUNIT_TEST(test_fredkin_neighbors_contains2);
  CPPUNIT_TEST(test_fredkin_neighbors_contains3);
  CPPUNIT_TEST(test_cell_neighbors_contains);
  CPPUNIT_TEST(test_cell_neighbors_contains2);
  CPPUNIT_TEST(test_cell_neighbors_contains3);

  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () 
{
  using namespace std;
  ios_base::sync_with_stdio(false);

  cout << "TestLife.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestLife::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}