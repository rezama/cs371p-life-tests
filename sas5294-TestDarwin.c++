// ------------------------------
// TestDarwin.c++
// Copyright (C) 2012
// Spencer Sullivan
// ------------------------------

/**
 * To test the program:
 *     g++ -ansi -pedantic -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.app
 *     valgrind TestDarwin.app >& TestDarwin.out
 */

// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TestRunner

#include <string>
#define private public
#include "Darwin.h"

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture 
{
    // -----------
    // test_grid
    // -----------

    void test_grid1 () 
    {
      Grid<3, 4> a;
      CPPUNIT_ASSERT(a.num_r == 3);
      CPPUNIT_ASSERT(a.num_c == 4);
    }
    
    void test_grid2() 
    {
      Grid<1, 1> b;
      CPPUNIT_ASSERT(b.num_r == 1);
      CPPUNIT_ASSERT(b.num_c == 1);
    }
    
    void test_grid3() 
    {
      Grid<100, 90> c;
      CPPUNIT_ASSERT(c.num_r == 100);
      CPPUNIT_ASSERT(c.num_c == 90);
    }
    
    //--------------
    // test_species
    //--------------
    
    void test_species1 () 
    {
      Species x('x');
      CPPUNIT_ASSERT(x.name = 'x');    
    }
    
    void test_species2 () 
    {
      Species x('y');
      x.add_instruction("go 1");
      x.add_instruction("go 0");
      CPPUNIT_ASSERT(x[1].compare("go 0") == 0);    
    }
       
    void test_species3 () 
    {
      Species x('x');
      Species y('y');
      CPPUNIT_ASSERT(x != y);    
    }
    
    //--------------
    // test_creature
    //--------------

    void test_creature1() 
    {
      Species s1('s');
      s1.add_instruction("go 1");
      s1.add_instruction("go 0");
      Creature c1(s1, 0);
      CPPUNIT_ASSERT(c1.next().compare("go 1") == 0);
      ++c1.pc;
      CPPUNIT_ASSERT(c1.next().compare("go 0") == 0);
      CPPUNIT_ASSERT(c1.species.name == 's');
      CPPUNIT_ASSERT(c1.direction == 0);
    }

    void test_creature2() 
    {
      Species s1('s');
      Creature c1(s1, 0);
      c1.left();
      CPPUNIT_ASSERT(c1.species.name == 's');
      CPPUNIT_ASSERT(c1.direction == 3);
    }

    void test_creature3() 
    {
      Species s1('s');
      Creature c1(s1, 3);
      c1.right();
      CPPUNIT_ASSERT(c1.species.name == 's');
      CPPUNIT_ASSERT(c1.direction == 4);
    }

    //--------------
    // test_next
    //--------------

    void test_next1() 
    {
      CPPUNIT_ASSERT((Grid<1,1>::next_r(1, 1) == 0));
    }

    void test_next2() 
    {
      CPPUNIT_ASSERT((Grid<1, 1>::next_r(1, 2) == 1));
    }

    void test_next3() 
    {
      CPPUNIT_ASSERT((Grid<1, 1>::next_c(1, 2) == 2));
    }

    //--------------
    // test_facing
    //--------------
    
    void test_facing1() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      g.change(0, 0, c);
      CPPUNIT_ASSERT(!g.facing_wall(0, 0));
      CPPUNIT_ASSERT(g.facing_empty(0, 0));
      CPPUNIT_ASSERT(!g.facing_enemy(0, 0));
    }

    void test_facing2() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      Creature c2(s, 0);
      g.change(0, 0, c);
      g.change(0, 1, c2);
      CPPUNIT_ASSERT(!g.facing_wall(0, 0));
      CPPUNIT_ASSERT(!g.facing_empty(0, 0));
      CPPUNIT_ASSERT(!g.facing_enemy(0, 0));
    }
    
    void test_facing3() 
    {
      Grid<1, 1> g;
      Species s('s');
      Creature c(s, 2);
      g.change(0, 0, c);
      CPPUNIT_ASSERT(g.facing_wall(0, 0));
      CPPUNIT_ASSERT(!g.facing_empty(0, 0));
      CPPUNIT_ASSERT(!g.facing_enemy(0, 0));
    }

    //--------------
    // test_hop
    //--------------

    void test_hop1() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      g.change(0, 0, c);
      g.hop(0, 0);
      CPPUNIT_ASSERT(g._g[0][0] == 0);
      CPPUNIT_ASSERT(g._g[0][1] != 0);
    }

    void test_hop2() 
    {
      Grid<1, 1> g;
      Species s('s');
      Creature c(s, 2);
      g.change(0, 0, c);
      g.hop(0, 0);
      CPPUNIT_ASSERT(g._g[0][0] != 0);
    }

    void test_hop3() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      Creature c2(s, 0);
      g.change(0, 0, c);
      g.change(0, 1, c2);
      g.hop(0, 0);
      CPPUNIT_ASSERT(g._g[0][0] != 0);
      CPPUNIT_ASSERT(g._g[0][1] != 0);
    }

    //--------------
    // test_infect
    //--------------

    void test_infect1() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      g.change(0, 0, c);
      g.infect(0, 0);
      CPPUNIT_ASSERT(g._g[0][0] != 0);
      CPPUNIT_ASSERT(g._g[0][1] == 0);
    }

    void test_infect2() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      Creature c2(s, 0);
      g.change(0, 0, c);
      g.change(0, 1, c2);
      g.infect(0, 0);
      CPPUNIT_ASSERT(!(g._g[0][0]->species != g._g[0][1]->species));
    }

    void test_infect3() 
    {
      Grid<1, 2> g;
      Species s('s');
      Species s2('t');
      Creature c(s, 2);
      Creature c2(s2, 0);
      g.change(0, 0, c);
      g.change(0, 1, c2);
      g.infect(0, 0);
      CPPUNIT_ASSERT(!(g._g[0][0]->species != g._g[0][1]->species));
    }


    //--------------
    // test_infect
    //--------------

    void test_change1() 
    {
      Grid<1, 1> g;
      Species s('s');
      Creature c(s, 2);
      CPPUNIT_ASSERT(g._g[0][0] == 0);
      g.change(0, 0, c);
      CPPUNIT_ASSERT(g._g[0][0] != 0);
    }

    void test_change2() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      Creature c2(s, 0);
      CPPUNIT_ASSERT(g._g[0][0] == 0);
      CPPUNIT_ASSERT(g._g[0][1] == 0);
      g.change(0, 0, c);
      g.change(0, 1, c2);
      CPPUNIT_ASSERT(g._g[0][0] != 0);
      CPPUNIT_ASSERT(g._g[0][1] != 0);
    }

    void test_change3() 
    {
      Grid<1, 2> g;
      Species s('s');
      Creature c(s, 2);
      Creature c2(s, 0);
      CPPUNIT_ASSERT(g._g[0][0] == 0);
      CPPUNIT_ASSERT(g._g[0][1] == 0);
      g.change(0, 0, c);
      CPPUNIT_ASSERT(g._g[0][0] != 0);
      CPPUNIT_ASSERT(g._g[0][1] == 0);
    }


    CPPUNIT_TEST_SUITE(TestDarwin);  
    CPPUNIT_TEST(test_grid1);  
    CPPUNIT_TEST(test_grid2);  
    CPPUNIT_TEST(test_grid3);  
    CPPUNIT_TEST(test_species1);  
    CPPUNIT_TEST(test_species2);  
    CPPUNIT_TEST(test_species3);  
    CPPUNIT_TEST(test_creature1);  
    CPPUNIT_TEST(test_creature2);  
    CPPUNIT_TEST(test_creature3);  
    CPPUNIT_TEST(test_next1);  
    CPPUNIT_TEST(test_next2);  
    CPPUNIT_TEST(test_next3);  
    CPPUNIT_TEST(test_facing1);  
    CPPUNIT_TEST(test_facing2);  
    CPPUNIT_TEST(test_facing3);  
    CPPUNIT_TEST(test_hop1);  
    CPPUNIT_TEST(test_hop2);  
    CPPUNIT_TEST(test_hop3);  
    CPPUNIT_TEST(test_infect1);  
    CPPUNIT_TEST(test_infect2);  
    CPPUNIT_TEST(test_infect3);  
    CPPUNIT_TEST(test_change1);  
    CPPUNIT_TEST(test_change2);  
    CPPUNIT_TEST(test_change3);  
    
    CPPUNIT_TEST_SUITE_END();
  };
  
// ----
// main
// ----

int main () 
{
  using namespace std;
  ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
  cout << "TestDarwin.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestDarwin::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}

