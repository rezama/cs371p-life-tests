/**
 * To test the program:
 * g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestLife.c++ -o TestLife.app
 * valgrind TestLife.app >& TestLife.out
 */

// --------
// includes
// --------
#include <string>
#include <iostream>
#include <sstream>

#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"              // TestFixture
#include "cppunit/TextTestRunner.h"           // TestRunner

#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

using namespace std;

struct TestLife : CppUnit::TestFixture {
  // ----------------
  // test_conwaycell
  // ----------------

  void test_cc_1() {
    ConwayCell cc;
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
    cc.make_alive();
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
    cc.step(0);
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
    cc.step(0);
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
    cc.step(3);
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
  }

  void test_cc_2() {
    ConwayCell cc(false);
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
    cc.make_alive();
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
    cc.step(3);
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
    cc.step(0);
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
  }

  void test_cc_3() {
    ConwayCell cc(true);
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
    cc.make_alive();
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
    cc.step(0);
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
    cc.step(0);
    CPPUNIT_ASSERT(cc.alive() == false);
    CPPUNIT_ASSERT(cc.character() == '.');
    cc.step(3);
    CPPUNIT_ASSERT(cc.alive() == true);
    CPPUNIT_ASSERT(cc.character() == '*');
  }

  // ----------------
  // test_fredkincell
  // ----------------

  void test_fc_1() {
    FredkinCell fc;
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.make_alive();
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '0');
    fc.step(0);
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.step(0);
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.step(3);
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '0');
  }

  void test_fc_2() {
    FredkinCell fc(false);
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.make_alive();
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '0');
    fc.step(3);
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '1');
    fc.step(2);
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.step(3);
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '1');
  }

  void test_fc_3() {
    FredkinCell fc(true);
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '0');
    fc.make_alive();
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '0');
    fc.step(0);
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.step(0);
    CPPUNIT_ASSERT(fc.alive() == false);
    CPPUNIT_ASSERT(fc.character() == '-');
    fc.step(3);
    CPPUNIT_ASSERT(fc.alive() == true);
    CPPUNIT_ASSERT(fc.character() == '0');
  }

  // ----------------
  // test_cell
  // ----------------

  void test_c_1() {
    Cell c;
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.make_alive();
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '0');
    c.step(0);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.step(0);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '0');
  }

  void test_c_2() {
    FredkinCell fc(false);
    Cell c(fc.clone());
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.make_alive();
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '0');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '1');
    c.step(2);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '1');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '*');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '*');
    c.step(1);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '.');
  }

  void test_c_3() {
    FredkinCell fc(true);
    Cell c(fc.clone());
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '0');
    c.make_alive();
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '0');
    c.step(0);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.step(0);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '-');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '0');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '1');
    c.step(3);
    CPPUNIT_ASSERT(c.alive() == true);
    CPPUNIT_ASSERT(c.character() == '*');
    c.step(1);
    CPPUNIT_ASSERT(c.alive() == false);
    CPPUNIT_ASSERT(c.character() == '.');
  }

  // ----------------
  // test_cell
  // ----------------

  void test_l_1() {
    Life<ConwayCell> l(2, 2);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == false);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 0.\n..\n..\n") == 0);
    l.make_alive(0, 0);
    CPPUNIT_ASSERT(l.alive(0, 0) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 1.\n*.\n..\n") == 0);
    l.evolve(1);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == false);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 1, Population = 0.\n..\n..\n") == 0);
    l.evolve(2);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == false);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 3, Population = 0.\n..\n..\n") == 0);
  }

  void test_l_2() {
    Life<FredkinCell> l(2, 2);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == false);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 0.\n--\n--\n") == 0);
    l.make_alive(0, 0);
    CPPUNIT_ASSERT(l.alive(0, 0) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 1.\n0-\n--\n") == 0);
    l.evolve(1);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == true);
    CPPUNIT_ASSERT(l.alive(1, 0) == true);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 1, Population = 2.\n-0\n0-\n") == 0);
    l.evolve(2);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == false);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 3, Population = 0.\n--\n--\n") == 0);
  }

  void test_l_3() {
    Life<Cell> l(2, 3);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == false);
    CPPUNIT_ASSERT(l.alive(0, 2) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == false);
    CPPUNIT_ASSERT(l.alive(1, 1) == false);
    CPPUNIT_ASSERT(l.alive(1, 2) == false);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 0.\n---\n---\n") == 0);
    l.make_alive(0, 1);
    CPPUNIT_ASSERT(l.alive(0, 1) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 1.\n-0-\n---\n") == 0);
    l.make_alive(1, 0);
    CPPUNIT_ASSERT(l.alive(1, 0) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 2.\n-0-\n0--\n") == 0);
    l.make_alive(1, 1);
    CPPUNIT_ASSERT(l.alive(1, 1) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 3.\n-0-\n00-\n") == 0);
    l.make_alive(1, 2);
    CPPUNIT_ASSERT(l.alive(1, 2) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 0, Population = 4.\n-0-\n000\n") == 0);
    l.evolve(1);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == true);
    CPPUNIT_ASSERT(l.alive(0, 2) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == true);
    CPPUNIT_ASSERT(l.alive(1, 1) == true);
    CPPUNIT_ASSERT(l.alive(1, 2) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 1, Population = 4.\n-1-\n111\n") == 0);
    l.evolve(1);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == true);
    CPPUNIT_ASSERT(l.alive(0, 2) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == true);
    CPPUNIT_ASSERT(l.alive(1, 1) == true);
    CPPUNIT_ASSERT(l.alive(1, 2) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 2, Population = 4.\n-*-\n***\n") == 0);
    l.evolve(1);
    CPPUNIT_ASSERT(l.alive(0, 0) == false);
    CPPUNIT_ASSERT(l.alive(0, 1) == true);
    CPPUNIT_ASSERT(l.alive(0, 2) == false);
    CPPUNIT_ASSERT(l.alive(1, 0) == true);
    CPPUNIT_ASSERT(l.alive(1, 1) == true);
    CPPUNIT_ASSERT(l.alive(1, 2) == true);
    CPPUNIT_ASSERT(l.print_grid().compare("Generation = 3, Population = 4.\n-*-\n***\n") == 0);
  }

  // -----
  // suite
  // -----

  CPPUNIT_TEST_SUITE(TestLife);
  CPPUNIT_TEST(test_cc_1);
  CPPUNIT_TEST(test_cc_2);
  CPPUNIT_TEST(test_cc_3);
  CPPUNIT_TEST(test_fc_1);
  CPPUNIT_TEST(test_fc_2);
  CPPUNIT_TEST(test_fc_3);
  CPPUNIT_TEST(test_c_1);
  CPPUNIT_TEST(test_c_2);
  CPPUNIT_TEST(test_c_3);
  CPPUNIT_TEST(test_l_1);
  CPPUNIT_TEST(test_l_2);
  CPPUNIT_TEST(test_l_3);
  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main() {
  using namespace std;
  ios_base::sync_with_stdio(false);  // turn off sync with C I/O
  cout << "TestLife.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestLife::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}

