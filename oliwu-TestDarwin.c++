// --------
// includes
// --------

#include "cppunit/extensions/HelperMacros.h"
#include "cppunit/TestFixture.h"
#include "cppunit/TextTestRunner.h"
#include <cstdlib>

#define private public
#include "Darwin.h"

// ----------
// TestDarwin
// ----------

struct TestDarwin : CppUnit::TestFixture {


  // -------------------
  // Species Constructor
  // -------------------
 
  void test_species_cons1 () {
    std::vector<commands> b(1);
    std::vector<int> j(1);
    const Species s('s', b, j);
    CPPUNIT_ASSERT(s.sign == 's');
    CPPUNIT_ASSERT(s.brain.size() == 1);
    CPPUNIT_ASSERT(s.jump.size() == 1);
  }

  void test_species_cons2 () {
    std::vector<commands> b(2);
    std::vector<int> j(2);
    const Species s('t', b, j);;
    CPPUNIT_ASSERT(s.sign == 't');
    CPPUNIT_ASSERT(s.brain.size() == 2);
    CPPUNIT_ASSERT(s.jump.size() == 2);
  }

  void test_species_cons3 () {
    std::vector<commands> b(3);
    std::vector<int> j(3);
    const Species s('u', b, j);
    CPPUNIT_ASSERT(s.sign == 'u');
    CPPUNIT_ASSERT(s.brain.size() == 3);
    CPPUNIT_ASSERT(s.jump.size() == 3);
  }

  // --------------------
  // Creature Constructor
  // --------------------
    
  void test_creature_cons1 () {
    std::vector<commands> b(1);
    std::vector<int> j(1);
    const Species s('s', b, j);
    const Species* csp = &s;
    Creature c(EAST, csp);
    CPPUNIT_ASSERT(c.type->sign == 's');
    CPPUNIT_ASSERT(c.direction == 1);
    CPPUNIT_ASSERT(c.pc == 0);
    CPPUNIT_ASSERT(c.turn == 0);
    CPPUNIT_ASSERT(c.type == &s);
  }

  void test_creature_cons2 () {
    std::vector<commands> b;
    std::vector<int> j;
    const Species s('s', b, j);
    const Species* csp = &s;
    Creature c1(SOUTH, csp);
    Creature c2(WEST, csp);
    CPPUNIT_ASSERT(c1.direction == 2);
    CPPUNIT_ASSERT(c2.direction == 3);
    CPPUNIT_ASSERT(c1.type == &s && c1.type == c2.type);
  }

  void test_creature_cons3 () {
    std::vector<commands> b;
    std::vector<int> j;
    const Species s('s', b, j);
    const Species s1('1', b, j);
    const Species* csp = &s;
    Creature c(NORTH, csp);
    csp = &s1;
    Creature c1(NORTH, csp);
    Creature c2(NORTH, csp);
    CPPUNIT_ASSERT(c.direction == 0);
    CPPUNIT_ASSERT(c.type == &s);
    CPPUNIT_ASSERT(c2.type == &s1 && c2.type == c1.type);
  }

  // ------------------
  // Master Class Tests 
  // ------------------
  // --------
  // new_game 
  // --------

  void test_master_board_1x1 () {
    Master k = Master();
    k.new_game (1, 1);
    CPPUNIT_ASSERT(k.board.size() == 1);
    CPPUNIT_ASSERT(k.board[0].size() == 1);
  }
      
  void test_master_board_22x2 () {
    Master k = Master();
    k.new_game (22, 2);
    CPPUNIT_ASSERT(k.board.size() == 22);
    CPPUNIT_ASSERT(k.board[0].size() == 2);
  }
 
  void test_master_board_2x22 () {
    Master k = Master();
    k.new_game (2, 22);
    CPPUNIT_ASSERT(k.board.size() == 2);
    CPPUNIT_ASSERT(k.board[0].size() == 22);
  }
 
  // ----------
  // draw_board 
  // ----------

  void test_master_draw_1x1 () {
    std::ostringstream w;
    Master k = Master();
    k.new_game (1, 1);
    k.draw_board(w);
    std::string r = w.str();
    std::string b = "Turn = 0.\n  0\n0 .\n\n";
    CPPUNIT_ASSERT(b.compare(r) == 0);
  }
      
  void test_master_draw_22x2 () {
    std::ostringstream w;
    Master k = Master();
    k.new_game (22, 2);
    k.draw_board(w);
    std::string r = w.str();
    std::string b = "Turn = 0.\n  01\n0 ..\n1 ..\n2 ..\n3 ..\n4 ..\n5 ..\n6 ..\n7 ..\n8 ..\n9 ..\n0 ..\n1 ..\n2 ..\n3 ..\n4 ..\n5 ..\n6 ..\n7 ..\n8 ..\n9 ..\n0 ..\n1 ..\n\n";
    CPPUNIT_ASSERT(b.compare(r) == 0);
  }
 
  void test_master_draw_2x22 () {
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 22);
    k.draw_board(w);
    std::string r = w.str();
    std::string b = "Turn = 0.\n  0123456789012345678901\n0 ......................\n1 ......................\n\n";
    CPPUNIT_ASSERT(b.compare(r) == 0);
  }
 
  // --------------
  // spawn_creature 
  // --------------

  void test_master_spawn_1 () {
    Master k = Master();
    k.new_game (1,1);
    k.spawn_creature (HOPPER, NORTH, 0, 0);
    CPPUNIT_ASSERT(k.board[0][0] == 0);
    CPPUNIT_ASSERT(k.players[0].type == HOPPER);
    CPPUNIT_ASSERT(k.players[0].direction == NORTH);
  }

  void test_master_spawn_2 () {
    Master k = Master();
    k.new_game (2,1);
    k.spawn_creature (HOPPER, NORTH, 0, 0);
    k.spawn_creature (HOPPER, SOUTH, 1, 0);
    CPPUNIT_ASSERT(k.board[0][0] == 0);
    CPPUNIT_ASSERT(k.board[1][0] == 1);
    CPPUNIT_ASSERT(k.players[0].type == HOPPER);
    CPPUNIT_ASSERT(k.players[1].type == HOPPER);
    CPPUNIT_ASSERT(&k.players[0] != &k.players[1]);
  }

  void test_master_spawn_3 () {
    Master k = Master();
    k.new_game (1,3);
    k.spawn_creature (FOOD, NORTH, 0, 0);
    k.spawn_creature (ROVER, EAST, 0, 1);
    k.spawn_creature (TRAP, WEST, 0, 2);
    CPPUNIT_ASSERT(k.board[0][0] == 0);
    CPPUNIT_ASSERT(k.board[0][1] == 1);
    CPPUNIT_ASSERT(k.board[0][2] == 2);
    CPPUNIT_ASSERT(k.players[0].type == FOOD);
    CPPUNIT_ASSERT(k.players[1].type == ROVER);
    CPPUNIT_ASSERT(k.players[2].type == TRAP);
    CPPUNIT_ASSERT(k.players[0].direction == NORTH);
    CPPUNIT_ASSERT(k.players[1].direction == EAST);
    CPPUNIT_ASSERT(k.players[2].direction == WEST);
  }

  // -------
  // execute 
  // -------

  void test_master_execute_aroundtheworld_cw () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 2);
    k.spawn_creature (TESTCW, EAST, 0, 0);
    k.execute(w, 7, 4);
    std::string a = "Turn = 0.\n  01\n0 *.\n1 ..\n\nTurn = 4.\n  01\n0 ..\n1 .*\n\nTurn = 7.\n  01\n0 *.\n1 ..\n\n";
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
  }

  void test_master_execute_aroundtheworld_ccw () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 2);
    k.spawn_creature (TESTCCW, WEST, 0, 1);
    k.execute(w, 7, 4);
    std::string a = "Turn = 0.\n  01\n0 .x\n1 ..\n\nTurn = 4.\n  01\n0 ..\n1 x.\n\nTurn = 7.\n  01\n0 .x\n1 ..\n\n";
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
  }

  void test_master_execute_roadblock () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 3);
    k.spawn_creature (TESTCW, EAST, 0, 0);
    k.spawn_creature (FOOD, NORTH, 0, 2);
    k.execute(w, 7, 4);
    std::string a = "Turn = 0.\n  012\n0 *.f\n1 ...\n\nTurn = 4.\n  012\n0 ..f\n1 .*.\n\nTurn = 7.\n  012\n0 *.f\n1 ...\n\n";
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
  }

  void test_master_execute_itsatrap () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 2);
    k.spawn_creature (FOOD, NORTH, 0, 1);
    k.spawn_creature (TRAP, NORTH, 0, 0);
    k.execute(w, 5, 5);
    std::string a = "Turn = 0.\n  01\n0 tf\n1 ..\n\nTurn = 5.\n  01\n0 tt\n1 ..\n\n";
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
    CPPUNIT_ASSERT(true);
  }

  void test_master_execute_LRUDorder () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (3, 8);
    k.spawn_creature (HOPPER, WEST, 0, 6);
    k.spawn_creature (HOPPER, EAST, 1, 0);
    k.spawn_creature (HOPPER, EAST, 2, 2);
    k.spawn_creature (ROVER, WEST, 0, 7);
    k.spawn_creature (ROVER, WEST, 1, 7);
    k.spawn_creature (ROVER, EAST, 2, 0);
    k.execute(w, 8, 8);
    std::string a = "Turn = 0.\n  01234567\n0 ......hr\n1 h......r\n2 r.h.....\n\nTurn = 8.\n  01234567\n0 rr......\n1 ........\n2 ..rr..rr\n\n";
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
    CPPUNIT_ASSERT(true);
  }

  void test_master_execute_rvf () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (4, 4);
    k.spawn_creature (FOOD, NORTH, 0, 3);
    k.spawn_creature (FOOD, NORTH, 2, 1);
    k.spawn_creature (FOOD, NORTH, 3, 3);
    k.spawn_creature (HOPPER, SOUTH, 0, 2);
    k.spawn_creature (ROVER, EAST, 0, 0);
    k.execute(w, 10, 10);
    std::string a = "Turn = 0.\n  0123\n0 r.hf\n1 ....\n2 .f..\n3 ...f\n\nTurn = 10.\n  0123\n0 ...r\n1 r...\n2 r...\n3 r.r.\n\n";
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
    CPPUNIT_ASSERT(true);
  }

  // ----
  // ping
  // ----

  void test_master_ping_wall () {
    Master k = Master();
    k.new_game (1, 1);
    k.spawn_creature (FOOD, NORTH, 0, 0);
    status a = WALL;
    std::vector<status> r = k.ping (0, 0);
    CPPUNIT_ASSERT(r[0] == a && r[1] == a && r[2] == a && r[3] == a);
  }

  void test_master_ping_enemy () {
    Master k = Master();
    k.new_game (3, 3);
    k.spawn_creature (FOOD, NORTH, 1, 1);
    k.spawn_creature (TRAP, NORTH, 0, 1);
    k.spawn_creature (TRAP, EAST, 1, 2);
    k.spawn_creature (TRAP, SOUTH, 2, 1);
    k.spawn_creature (TRAP, WEST, 1, 0);
    status a = ENEMY;
    std::vector<status> r = k.ping (1, 1);
    CPPUNIT_ASSERT(r[0] == a && r[1] == a && r[2] == a && r[3] == a);
  }

  void test_master_ping_friend () {
    Master k = Master();
    k.new_game (3, 3);
    k.spawn_creature (FOOD, NORTH, 1, 1);
    k.spawn_creature (FOOD, NORTH, 0, 1);
    k.spawn_creature (FOOD, EAST, 1, 2);
    k.spawn_creature (FOOD, SOUTH, 2, 1);
    k.spawn_creature (FOOD, WEST, 1, 0);
    status a = FRIEND;
    std::vector<status> r = k.ping (1, 1);
    CPPUNIT_ASSERT(r[0] == a && r[1] == a && r[2] == a && r[3] == a);
  }

  void test_master_ping_empty () {
    Master k = Master();
    k.new_game (3, 3);
    k.spawn_creature (FOOD, NORTH, 1, 1);
    status a = EMPTY;
    std::vector<status> r = k.ping (1, 1);
    CPPUNIT_ASSERT(r[0] == a && r[1] == a && r[2] == a && r[3] == a);
  }

  // ------
  // gameon
  // ------

  void test_master_gameon_roadblock () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 3);
    k.spawn_creature (TESTCW, EAST, 0, 0);
    k.spawn_creature (FOOD, NORTH, 0, 2);
    std::string a = "Turn = 0.\n  012\n0 *.f\n1 ...\n\nTurn = 1.\n  012\n0 .*f\n1 ...\n\nTurn = 2.\n  012\n0 .*f\n1 ...\n\n";
    k.gameon(w, 2);
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
  }

  void test_master_gameon_itsatrap () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (2, 2);
    k.spawn_creature (FOOD, NORTH, 0, 1);
    k.spawn_creature (TRAP, WEST, 0, 0);
    std::string a = "Turn = 0.\n  01\n0 tf\n1 ..\n\nTurn = 2.\n  01\n0 tf\n1 ..\n\nTurn = 4.\n  01\n0 tt\n1 ..\n\n";
    k.gameon(w, 4, 2);
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
    CPPUNIT_ASSERT(true);
  }

  void test_master_gameon_LRUDorder () {
    srand(0);
    std::ostringstream w;
    Master k = Master();
    k.new_game (3, 8);
    k.spawn_creature (HOPPER, WEST, 0, 6);
    k.spawn_creature (HOPPER, EAST, 1, 0);
    k.spawn_creature (HOPPER, EAST, 2, 2);
    k.spawn_creature (ROVER, WEST, 0, 7);
    k.spawn_creature (ROVER, WEST, 1, 7);
    k.spawn_creature (ROVER, EAST, 2, 0);
    std::string a = "Turn = 0.\n  01234567\n0 ......hr\n1 h......r\n2 r.h.....\n\nTurn = 8.\n  01234567\n0 rr......\n1 ........\n2 ..rr..rr\n\n";
    k.gameon(w, 8, 8);
    std::string r = w.str();
    CPPUNIT_ASSERT(a.compare(r) == 0);
    CPPUNIT_ASSERT(true);
  }


  CPPUNIT_TEST_SUITE(TestDarwin);

  CPPUNIT_TEST(test_species_cons1);
  CPPUNIT_TEST(test_species_cons2);
  CPPUNIT_TEST(test_species_cons3);

  CPPUNIT_TEST(test_creature_cons1);
  CPPUNIT_TEST(test_creature_cons2);
  CPPUNIT_TEST(test_creature_cons3);

  CPPUNIT_TEST(test_master_board_1x1);
  CPPUNIT_TEST(test_master_board_22x2);
  CPPUNIT_TEST(test_master_board_2x22);
  CPPUNIT_TEST(test_master_draw_1x1);
  CPPUNIT_TEST(test_master_draw_22x2);
  CPPUNIT_TEST(test_master_draw_2x22);
  CPPUNIT_TEST(test_master_spawn_1);
  CPPUNIT_TEST(test_master_spawn_2);
  CPPUNIT_TEST(test_master_spawn_3);
  CPPUNIT_TEST(test_master_execute_aroundtheworld_cw);
  CPPUNIT_TEST(test_master_execute_aroundtheworld_ccw);
  CPPUNIT_TEST(test_master_execute_roadblock);
  CPPUNIT_TEST(test_master_execute_itsatrap);
  CPPUNIT_TEST(test_master_execute_LRUDorder);
  CPPUNIT_TEST(test_master_execute_rvf);
  CPPUNIT_TEST(test_master_ping_wall);
  CPPUNIT_TEST(test_master_ping_enemy);
  CPPUNIT_TEST(test_master_ping_friend);
  CPPUNIT_TEST(test_master_ping_empty);
  CPPUNIT_TEST(test_master_gameon_roadblock);
  CPPUNIT_TEST(test_master_gameon_itsatrap);
  CPPUNIT_TEST(test_master_gameon_LRUDorder);
  
  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
  using namespace std;
  ios_base::sync_with_stdio(false);

  cout << "TestDarwin.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestDarwin::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}
