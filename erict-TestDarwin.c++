// --------------------------------
// Copyright (C) 2012
// Eric Thompson - my own damn self
// --------------------------------

/*
To test the program:
    % g++ -pedantic -std=c++0x -lcppunit -ldl -Wall TestDarwin.c++ -o TestDarwin.c++.app
    % valgrind TestDarwin.c++.app >& TestDarwin.c++.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // ==
#include <vector>
#include <stdlib.h>

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"             // TestFixture
#include "cppunit/TextTestRunner.h"          // TextTestRunner

#define private public

#include "Darwin.h"

using namespace std;

// -----------
// TestDarwin
// -----------

struct TestDarwin : CppUnit::TestFixture {

    // -----
    // tests
    // -----

    // ---------
    // spec_con1
    // ---------

    void spec_con1() {
      const vector<int> v = {0};
      const vector<int> l = {0};
      Species sp(v, l, 'a');
      CPPUNIT_ASSERT(v[0] == 0);
      CPPUNIT_ASSERT(&v == &sp.program);
      CPPUNIT_ASSERT(&l == &sp.lines);
      CPPUNIT_ASSERT(sp.image == 'a');
    }

    // ---------
    // spec_con2
    // ---------

    void spec_con2() {
      const vector<int> v(5, 10);
      const vector<int> l(5, 5);
      Species sp(v, l, 'a');
      for (int i = 0; i < 5; i++ ) {
        CPPUNIT_ASSERT(sp.program[i] == 10);
        CPPUNIT_ASSERT(sp.lines[i] == 5);
      }
      CPPUNIT_ASSERT(&v == &sp.program);
      CPPUNIT_ASSERT(&l == &sp.lines);
    }
        
    // ---------
    // spec_con3
    // ---------

    void spec_con3() {
      const vector<int> v;
      const vector<int> l;
      Species sp(v, l, 'a');
      CPPUNIT_ASSERT(&v == &sp.program);
      CPPUNIT_ASSERT(&l == &sp.lines);
    }
        
    // ---------
    // spec_con4
    // ---------

    void spec_con4() {
      const vector<int> v1 = {9, hop};
      const vector<int> l1 = {1, 2};
      const vector<int> v2 = {3, 7, 4};
      const vector<int> l2 = {0, 3, 5};
      Species sp1(v1, l1, 'a');
      Species sp3(v1, l1, 'b');
      Species sp2(v2, l2, 'c');
      CPPUNIT_ASSERT(&v1 == &sp1.program);
      CPPUNIT_ASSERT(&l1 == &sp1.lines);
      CPPUNIT_ASSERT(&v2 == &sp2.program);
      CPPUNIT_ASSERT(&l2 == &sp2.lines);
      CPPUNIT_ASSERT(&sp3.program == &sp1.program);
      CPPUNIT_ASSERT(&sp3.lines == &sp1.lines);
      CPPUNIT_ASSERT(&sp2.program != &sp1.program);
      CPPUNIT_ASSERT(&sp3.lines != &sp2.lines);
    }

    // ---------
    // crea_con1
    // ---------

    void crea_con1() {
      const vector<int> v = {0, 3, 4};
      const vector<int> l = {0, 1, 3};
      Species sp(v, l, 'a');
      Creature c(&sp, 1, 0);
      CPPUNIT_ASSERT(c.programCounter == 1);
      CPPUNIT_ASSERT(c.spec->image == 'a');
      CPPUNIT_ASSERT(c.direction == 0);
      CPPUNIT_ASSERT(c.spec == &sp);
      CPPUNIT_ASSERT(&((*(c.spec)).lines) == &sp.lines);
    }

    // ---------
    // crea_con2
    // ---------

    void crea_con2() {
      const vector<int> v = {0, 3, 4};
      const vector<int> l = {0, 1, 3};
      Species sp(v, l, 'a');
      Creature c1(&sp, 0, 0);
      Creature c2(&sp, 0, 0);
      CPPUNIT_ASSERT(c1.programCounter == 0);
      CPPUNIT_ASSERT(c1.spec->image == 'a');
      CPPUNIT_ASSERT(c1.direction == 0);
      CPPUNIT_ASSERT(c1.spec == &sp);
      CPPUNIT_ASSERT(&((*(c1.spec)).lines) == &sp.lines);
      CPPUNIT_ASSERT(c2.programCounter == 0);
      CPPUNIT_ASSERT(c2.spec->image == 'a');
      CPPUNIT_ASSERT(c2.direction == 0);
      CPPUNIT_ASSERT(c2.spec == &sp);
      CPPUNIT_ASSERT(&((*(c2.spec)).lines) == &sp.lines);
      CPPUNIT_ASSERT(c1.spec == c2.spec);
    }
        
    // ---------
    // crea_con3
    // ---------

    void crea_con3() {
      const vector<int> v1 = {0, 3, 4};
      const vector<int> l1 = {0, 1, 3};
      const vector<int> v2 = {1, 5, 7};
      const vector<int> l2 = {1, 2, 3};
      Species sp1(v1, l1, 'a');
      Species sp2(v2, l2, 'b');
      Creature c1(&sp1, 0, 0);
      Creature c2(&sp2, 0, 0);
      CPPUNIT_ASSERT(c1.programCounter == 0);
      CPPUNIT_ASSERT(c1.spec->image == 'a');
      CPPUNIT_ASSERT(c1.direction == 0);
      CPPUNIT_ASSERT(c1.spec == &sp1);
      CPPUNIT_ASSERT(&((*(c1.spec)).lines) == &sp1.lines);
      CPPUNIT_ASSERT(c2.programCounter == 0);
      CPPUNIT_ASSERT(c2.spec->image == 'b');
      CPPUNIT_ASSERT(c2.direction == 0);
      CPPUNIT_ASSERT(c2.spec == &sp2);
      CPPUNIT_ASSERT(&((*(c2.spec)).program) == &sp2.program);
      CPPUNIT_ASSERT(c1.spec != c2.spec);
    }

    // ---------
    // dk_con1
    // ---------

    void dk_con1() {
      DungeonKeeper d(0, 0);
      CPPUNIT_ASSERT(d.map.size() == 0);
    }

    // ---------
    // dk_con2
    // ---------

    void dk_con2() {
      DungeonKeeper d(1, 1);
      CPPUNIT_ASSERT(d.map.size() == 1);
      CPPUNIT_ASSERT(d.map[0].size() == 1);
      CPPUNIT_ASSERT(d.map[0][0] == -1);
    }
        
    // ---------
    // dk_con3
    // ---------

    void dk_con3() {
      DungeonKeeper d(4, 4);
      CPPUNIT_ASSERT(d.map.size() == 4);
      CPPUNIT_ASSERT(d.map[0].size() == 4);
      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          CPPUNIT_ASSERT(d.map[i][j] == -1);
    }

    // ---------
    // makeC1
    // ---------

    void makeC1() {
      DungeonKeeper d(1, 1);
      vector<int> v1 = {0, 1, 4, 5};
      vector<int> v2 = {0, 1, 2, 3};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      CPPUNIT_ASSERT(d.map[0][0] == 0);
      CPPUNIT_ASSERT(d.creatureList.size() == 1);
      CPPUNIT_ASSERT(d.creatureList[0].spec->image == 'a');
      CPPUNIT_ASSERT(d.creatureList[0].spec == &s);
    }

    // ---------
    // makeC2
    // ---------

    void makeC2() {
      DungeonKeeper d(1, 2);
      vector<int> v1 = {0, 1, 4, 5};
      vector<int> v2 = {0, 1, 2, 3};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      d.makeCreature(&s, 0, 0, 1);
      CPPUNIT_ASSERT(d.map[0][0] == 0);
      CPPUNIT_ASSERT(d.map[0][1] == 1);
      CPPUNIT_ASSERT(d.creatureList.size() == 2);
      CPPUNIT_ASSERT(d.creatureList[0].spec->image == 'a');
      CPPUNIT_ASSERT(d.creatureList[0].spec == &s);
      CPPUNIT_ASSERT(d.creatureList[1].spec->image == 'a');
      CPPUNIT_ASSERT(d.creatureList[1].spec == &s);
    }
        
    // ---------
    // makeC3
    // ---------

    void makeC3() {
      DungeonKeeper d(1, 2);
      vector<int> v1 = {0, 1, 4, 5};
      vector<int> v2 = {0, 1, 2, 3};
      Species s1(v1, v2, 'a');
      Species s2(v1, v2, 'b');
      d.makeCreature(&s1, 0, 0, 0);
      d.makeCreature(&s2, 0, 0, 1);
      CPPUNIT_ASSERT(d.map[0][0] == 0);
      CPPUNIT_ASSERT(d.map[0][1] == 1);
      CPPUNIT_ASSERT(d.creatureList.size() == 2);
      CPPUNIT_ASSERT(d.creatureList[0].spec->image == 'a');
      CPPUNIT_ASSERT(d.creatureList[0].spec == &s1);
      CPPUNIT_ASSERT(d.creatureList[1].spec->image == 'b');
      CPPUNIT_ASSERT(d.creatureList[1].spec == &s2);
      CPPUNIT_ASSERT(d.creatureList[1].spec != d.creatureList[0].spec);
    }

    // ---------
    // draw1
    // ---------

    void draw1() {
      DungeonKeeper d(1, 1);
      vector<int> v1 = {0, 1, 4, 5};
      vector<int> v2 = {0, 1, 2, 3};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      string str1 = d.drawMap();
      string str2 = "Turn = 0.\n  0\n0 a\n";
      CPPUNIT_ASSERT(str1.compare(str2) == 0);
    }

    // ---------
    // draw2
    // ---------

    void draw2() {
      DungeonKeeper d(0, 0);
      string str1 = d.drawMap();
      string str2 = "Turn = 0.\n";
      CPPUNIT_ASSERT(str1.compare(str2) == 0);
    }
        
    // ---------
    // draw3
    // ---------

    void draw3() {
      DungeonKeeper d(10, 10);
      vector<int> v1 = {0, 1, 4, 5};
      vector<int> v2 = {0, 1, 2, 3};
      Species s1(v1, v2, 'a');
      Species s2(v1, v2, 'b');
      d.makeCreature(&s1, 0, 3, 2);
      d.makeCreature(&s2, 0, 4, 7);
      string str1 = d.drawMap();
      string str2 = "Turn = 0.\n  0123456789\n";
      str2 += "0 ..........\n";
      str2 += "1 ..........\n";
      str2 += "2 ..........\n";
      str2 += "3 ..a.......\n";
      str2 += "4 .......b..\n";
      str2 += "5 ..........\n";
      str2 += "6 ..........\n";
      str2 += "7 ..........\n";
      str2 += "8 ..........\n";
      str2 += "9 ..........\n";
      CPPUNIT_ASSERT(str1.compare(str2) == 0);
    }

    // ---------
    // uMap1
    // ---------

    void uMap1() {
      DungeonKeeper d(3, 3);
      d.updateMap();
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
          CPPUNIT_ASSERT(d.map[i][j] == -1);
    }

    // ---------
    // uMap2
    // ---------

    void uMap2() {
      DungeonKeeper d(3, 3);
      vector<int> v1 = {-1};
      vector<int> v2 = {0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      d.updateMap();
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 0);
      CPPUNIT_ASSERT(d.round == 1);
    }
        
    // ---------
    // uMap3
    // ---------

    void uMap3() {
      DungeonKeeper d(1, 2);
      vector<int> v1 = {-1};
      vector<int> v2 = {0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      d.makeCreature(&s, 0, 0, 1);
      d.updateMap();
      d.updateMap();
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 0);
      CPPUNIT_ASSERT(d.creatureList[1].programCounter == 0);
      CPPUNIT_ASSERT(d.round == 2);
    }

    // ---------
    // nSpace1
    // ---------

    void nSpace1() {
      DungeonKeeper d(3, 3);
      vector<int> v1 = {-1};
      vector<int> v2 = {0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      int r, c, ans;
      ans = d.nextSpace(d.creatureList[0], 0, 0, r, c);
      CPPUNIT_ASSERT(ans == -2);
      CPPUNIT_ASSERT(r == 0);
      CPPUNIT_ASSERT(c == 0);
    }
        
    // ---------
    // nSpace2
    // ---------

    void nSpace2() {
      DungeonKeeper d(1, 2);
      vector<int> v1 = {-1};
      vector<int> v2 = {0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 0);
      d.makeCreature(&s, 3, 0, 1);
      int r, c, ans;
      ans = d.nextSpace(d.creatureList[1], 0, 1, r, c);
      CPPUNIT_ASSERT(ans == 0);
      CPPUNIT_ASSERT(r == 0);
      CPPUNIT_ASSERT(c == 1);
    }

    // ---------
    // nSpace3
    // ---------

    void nSpace3() {
      DungeonKeeper d(3, 3);
      vector<int> v1 = {-1};
      vector<int> v2 = {0};
      Species s(v1, v2, 'b');
      d.makeCreature(&s, 2, 0, 1);
      int r, c, ans;
      ans = d.nextSpace(d.creatureList[0], 0, 1, r, c);
      CPPUNIT_ASSERT(ans == -1);
      CPPUNIT_ASSERT(r == 1);
      CPPUNIT_ASSERT(c == 1);
    }

    // ---------
    // actionHop1
    // ---------

    void actionHop1() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {hop, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 1, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[0][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 1);
    }
        
    // ---------
    // actionHop2
    // ---------

    void actionHop2() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {hop, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 1);
      d.takeAction(d.creatureList[0], 0, 1);
      CPPUNIT_ASSERT(d.map[0][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 1);
    }
        
    // ---------
    // actionHop3
    // ---------

    void actionHop3() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {hop, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 0, 1);
      d.makeCreature(&s, 0, 1, 1);
      d.takeAction(d.creatureList[1], 1, 1);
      CPPUNIT_ASSERT(d.map[0][1] == 0);
      CPPUNIT_ASSERT(d.map[1][1] == 1);
      CPPUNIT_ASSERT(d.creatureList[1].programCounter == 1);
    }

    // ---------
    // actionLeft
    // ---------

    void actionLeft() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {ileft, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 1, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[1][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 1);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 3);
    }
    
    // ---------
    // actionRight
    // ---------

    void actionRight() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {iright, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 1, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[1][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 1);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 1);
    }
    
    // ---------
    // actionInfect1
    // ---------

    void actionInfect1() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {infect, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 1, 1);
      vector<int> v21 = {0, 1};
      vector<int> v11 = {iright, go, 0};
      Species s1(v11, v21, 'b');
      d.makeCreature(&s1, 0, 0, 1);
      d.takeAction(d.creatureList[1], 0, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[1][1] == 0);
      CPPUNIT_ASSERT(d.map[0][1] == 1);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 1);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 0);
      CPPUNIT_ASSERT(d.creatureList[1].programCounter == 0);
      CPPUNIT_ASSERT(d.creatureList[1].direction == 1);
      CPPUNIT_ASSERT(d.creatureList[1].spec == &s);
      CPPUNIT_ASSERT(d.creatureList[1].spec == d.creatureList[0].spec);
    }

    // ---------
    // actionInfect2
    // ---------

    void actionInfect2() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 1};
      vector<int> v1 = {infect, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 1, 1, 1);
      vector<int> v21 = {0, 1};
      vector<int> v11 = {iright, go, 0};
      Species s1(v11, v21, 'b');
      d.makeCreature(&s1, 1, 1, 2);
      d.takeAction(d.creatureList[1], 0, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[1][1] == 0);
      CPPUNIT_ASSERT(d.map[1][2] == 1);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 1);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 1);
      CPPUNIT_ASSERT(d.creatureList[1].programCounter == 0);
      CPPUNIT_ASSERT(d.creatureList[1].direction == 2);
      CPPUNIT_ASSERT(d.creatureList[1].spec == &s);
      CPPUNIT_ASSERT(d.creatureList[1].spec == d.creatureList[0].spec);
    }

    // ---------
    // actionIfempty1
    // ---------

    void actionIfempty1() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 2, 3, 5, 6};
      vector<int> v1 = {if_empty, 3, ileft, go, 0, hop, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 1, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[0][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 4);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 0);
    }
    
    // ---------
    // actionIfempty2
    // ---------

    void actionIfempty2() {
      DungeonKeeper d(3, 3);
      vector<int> v2  = {0, 2, 3, 5, 6};
      vector<int> v1 = {if_empty, 3, ileft, go, 0, hop, go, 0};
      Species s(v1, v2, 'a');
      d.makeCreature(&s, 0, 1, 1);
      d.takeAction(d.creatureList[0], 1, 1);
      CPPUNIT_ASSERT(d.map[0][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 4);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 0);
      d.takeAction(d.creatureList[0], 0, 1);
      CPPUNIT_ASSERT(d.map[0][1] == 0);
      CPPUNIT_ASSERT(d.creatureList[0].programCounter == 2);
      CPPUNIT_ASSERT(d.creatureList[0].direction == 3);
    }

    // -----
    // suite
    // -----

    CPPUNIT_TEST_SUITE(TestDarwin);
    CPPUNIT_TEST(spec_con1);
    CPPUNIT_TEST(spec_con2);
    CPPUNIT_TEST(spec_con3);
    CPPUNIT_TEST(spec_con4);
    CPPUNIT_TEST(crea_con1);
    CPPUNIT_TEST(crea_con2);
    CPPUNIT_TEST(crea_con3);
    CPPUNIT_TEST(dk_con1);
    CPPUNIT_TEST(dk_con2);
    CPPUNIT_TEST(dk_con3);
    CPPUNIT_TEST(makeC1);
    CPPUNIT_TEST(makeC2);
    CPPUNIT_TEST(makeC3);
    CPPUNIT_TEST(draw1);
    CPPUNIT_TEST(draw2);
    CPPUNIT_TEST(draw3);
    CPPUNIT_TEST(uMap1);
    CPPUNIT_TEST(uMap2);
    CPPUNIT_TEST(uMap3);
    CPPUNIT_TEST(nSpace1);
    CPPUNIT_TEST(nSpace2);
    CPPUNIT_TEST(nSpace3);
    // these are all in the same method so repetitive tests are unnecessary
    // 3 test minimum met (way more than 3)
    CPPUNIT_TEST(actionHop1);
    CPPUNIT_TEST(actionHop2);
    CPPUNIT_TEST(actionHop3);
    CPPUNIT_TEST(actionLeft);
    CPPUNIT_TEST(actionRight);
    CPPUNIT_TEST(actionInfect1);
    CPPUNIT_TEST(actionInfect2);
    CPPUNIT_TEST(actionIfempty1);
    CPPUNIT_TEST(actionIfempty2);
    CPPUNIT_TEST_SUITE_END();};

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false);  // turn off synchronization with C I/O
    cout << "TestDarwin.c++" << endl;

    CppUnit::TextTestRunner tr;
    tr.addTest(TestDarwin::suite());
    tr.run();

    cout << "Done." << endl;
    return 0;}
