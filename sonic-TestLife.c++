/*
Benjamin Maxfield
bsm762

compile:
  $ g++ -std=c++0x -ldl TestLife.c++ -lcppunit -o TestLife.c++.app
execute:
  $ valgrind TestLife.c++.app &> TestLife.out
*/

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h"  // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"        // TestFixture
#include "cppunit/TextTestRunner.h"       // TestRunner
#include <sstream>
#include <vector>

#define private public
#include "Life.h"
#include "AbstractCell.h"
#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"

using std::ostringstream;


// TestLife
struct TestLife : CppUnit::TestFixture {

  // Test Life

  void testLife1 () {
    Life<ConwayCell> life (1, 1, ConwayCell(true));
    CPPUNIT_ASSERT(life._g[0][0].isAlive());
    CPPUNIT_ASSERT(life.getPop() == 1);
    life.simulate(1);
    CPPUNIT_ASSERT(!life._g[0][0].isAlive());
    CPPUNIT_ASSERT(life.getPop() == 0);
  }

  void testLife2 () {
    Life<FredkinCell> life (1,1,FredkinCell());
    CPPUNIT_ASSERT(!life._g[0][0].isAlive());
    CPPUNIT_ASSERT(life.getPop() == 0);
    life.setCell(0,0,FredkinCell(true, 3));
    CPPUNIT_ASSERT(life._g[0][0].isAlive());
    CPPUNIT_ASSERT(life.getPop() == 1);
  }

  void testLife3 () {
    Life<Cell> life (3,3, new FredkinCell(true, 0));
    std::vector< std::vector< int > > cn(3, std::vector< int >(3, 0));
    std::vector< std::vector< int > > fn(3, std::vector< int >(3, 0));
    life.fillCN(&cn);
    life.fillFN(&fn);
    CPPUNIT_ASSERT(cn[1][1] == 8);
    CPPUNIT_ASSERT(fn[1][1] == 4);

  }

  // Test Cell

  void testCell1 () {
    Cell c (new ConwayCell(true));
    CPPUNIT_ASSERT(c.isAlive());
    c.kill();
    CPPUNIT_ASSERT(!c.isAlive());
    c.spawn();
    CPPUNIT_ASSERT(c.isAlive());
  }

  void testCell2 () {
    Cell c (new FredkinCell(true, 2));
    Cell c2(new FredkinCell(true, 10));
    Cell c3(new FredkinCell(false, 0));
    Cell c4(new ConwayCell(true));
    Cell c5(new ConwayCell(false));
    CPPUNIT_ASSERT(c.print() == '2');
    CPPUNIT_ASSERT(c2.print() == '+');
    CPPUNIT_ASSERT(c3.print() == '-');
    CPPUNIT_ASSERT(c4.print() == '*');
    CPPUNIT_ASSERT(c5.print() == '.');
  }
  
  void testCell3 () {
    Cell c (new ConwayCell(true));
    Cell c2(new FredkinCell(true, 0));
    CPPUNIT_ASSERT(c.eval(1, 0) == false);
    CPPUNIT_ASSERT(c.eval(3, 0) == true);
    CPPUNIT_ASSERT(c2.eval(0, 3) == true);
    CPPUNIT_ASSERT(c2.eval(0, 0) == false);
  }

  // Test ConwayCell

  void testConwayCell1 () {
    ConwayCell c (true);
    CPPUNIT_ASSERT(c.isAlive());
    c.kill();
    CPPUNIT_ASSERT(!c.isAlive());
    c.spawn();
    CPPUNIT_ASSERT(c.isAlive());
  }

  void testConwayCell2 () {
    ConwayCell c (true);
    ConwayCell c2(false);
    CPPUNIT_ASSERT(c.print() == '*');
    CPPUNIT_ASSERT(c2.print() == '.');
  }
  
  void testConwayCell3 () {
    ConwayCell c(true);
    CPPUNIT_ASSERT(c.eval(1, 0) == false);
    CPPUNIT_ASSERT(c.eval(3, 0) == true);
  }

  // Test FredkinCell

  void testFredkinCell1 () {
    FredkinCell c (true, 0);
    CPPUNIT_ASSERT(c.isAlive());
    c.kill();
    CPPUNIT_ASSERT(!c.isAlive());
    c.spawn();
    CPPUNIT_ASSERT(c.isAlive());
  }

  void testFredkinCell2 () {
    FredkinCell c (true, 2);
    FredkinCell c2(true, 10);
    FredkinCell c3(false, 0);
    CPPUNIT_ASSERT(c.print() == '2');
    CPPUNIT_ASSERT(c2.print() == '+');
    CPPUNIT_ASSERT(c3.print() == '-');
  }
  
  void testFredkinCell3 () {
    FredkinCell c (true, 0);
    CPPUNIT_ASSERT(c.eval(0, 3) == true);
    CPPUNIT_ASSERT(c.eval(0, 0) == false);
  }

  
  // -----
  // suite
  // -----

  CPPUNIT_TEST_SUITE(TestLife);
  
  CPPUNIT_TEST(testLife1);
  CPPUNIT_TEST(testLife2);
  CPPUNIT_TEST(testLife3);
  CPPUNIT_TEST(testCell1);
  CPPUNIT_TEST(testCell2);
  CPPUNIT_TEST(testCell3);
  CPPUNIT_TEST(testConwayCell1);
  CPPUNIT_TEST(testConwayCell2);
  CPPUNIT_TEST(testConwayCell3);
  CPPUNIT_TEST(testFredkinCell1);
  CPPUNIT_TEST(testFredkinCell2);
  CPPUNIT_TEST(testFredkinCell3);
  
  CPPUNIT_TEST_SUITE_END();
};

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
  return 0;
}