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

// --------
// TestLife
// --------

struct TestLife : CppUnit::TestFixture {


  // ----------------------
  // ConwayCell Constructor
  // ----------------------
 
  void test_conway_cons1 () {
    ConwayCell cc (false);
    CPPUNIT_ASSERT (!cc._living);
  }

  void test_conway_cons2 () {
    ConwayCell cc (true);
    CPPUNIT_ASSERT (cc._living);
  }

  void test_conway_cons3 () {
    ConwayCell cc1 (true);
    ConwayCell cc2 (true);
    CPPUNIT_ASSERT (&cc1 != &cc2);
    CPPUNIT_ASSERT (cc1._living == cc2._living);
  }
  
  // -----------------
  // ConwayCell status
  // -----------------

  void test_conway_mfs1 () {
    ConwayCell cc (false);
    char mfs = cc.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs == '.');
  }

  void test_conway_mfs2 () {
    ConwayCell cc (true);
    char mfs = cc.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs == '*');
  }

  void test_conway_mfs3 () {
    ConwayCell cc1 (false);
    ConwayCell cc2 (false);
    char mfs1 = cc1.motherfuckingstatus();
    char mfs2 = cc2.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs1 == mfs2);
  }

  // ----------------------
  // ConwayCell DeadOrAlive 
  // ----------------------

  void test_conway_doa1 () {
    ConwayCell cc (false);
    vector<int> n (2, 3); 
    int nstat = cc.doa (n);
    CPPUNIT_ASSERT (nstat == 0);
  }

  void test_conway_doa2 () {
    ConwayCell cc (false);
    vector<int> n (2, 8); 
    int nstat = cc.doa (n);
    CPPUNIT_ASSERT (nstat == -1);
  }

  void test_conway_doa3 () {
    ConwayCell cc (true);
    vector<int> n (2, 1); 
    int nstat = cc.doa (n);
    CPPUNIT_ASSERT (nstat == -1);
  }

  void test_conway_doa4 () {
    ConwayCell cc (true);
    vector<int> n (2, 3); 
    int nstat = cc.doa (n);
    CPPUNIT_ASSERT (nstat == 0);
  }
  
  void test_conway_doa5 () {
    ConwayCell cc (true);
    vector<int> n (2, 2); 
    int nstat = cc.doa (n);
    CPPUNIT_ASSERT (nstat == 0);
  }

  void test_conway_doa6 () {
    ConwayCell cc (true);
    vector<int> n (2, 4); 
    int nstat = cc.doa (n);
    CPPUNIT_ASSERT (nstat == -1);
  }

  // ----------------
  // ConwayCell clone
  // ----------------

  void test_conway_clone1 () {
    ConwayCell cc (true);
    ConwayCell* cclone = cc.clone();
    CPPUNIT_ASSERT (cclone != &cc);
    CPPUNIT_ASSERT (cclone->_living);
    delete cclone;
  }

  void test_conway_clone2 () {
    ConwayCell cc (false);
    ConwayCell* cclone = cc.clone();
    char ccstat = cc.motherfuckingstatus();
    char cccstat = cclone->motherfuckingstatus();
    CPPUNIT_ASSERT (cclone != &cc);
    CPPUNIT_ASSERT (ccstat == cccstat);
    CPPUNIT_ASSERT (ccstat == '.');
    delete cclone;
  }

  void test_conway_clone3 () {
    ConwayCell cc (true);
    ConwayCell* cclone = cc.clone();
    char ccstat = cc.motherfuckingstatus();
    char cccstat = cclone->motherfuckingstatus();
    CPPUNIT_ASSERT (cclone != &cc);
    CPPUNIT_ASSERT (ccstat == cccstat);
    CPPUNIT_ASSERT (ccstat == '*');
    delete cclone;
  }

  // -----------------------
  // FredkinCell Constructor
  // -----------------------
    
  void test_fred_cons1 () {
    FredkinCell fc (true, 1);
    CPPUNIT_ASSERT (fc._living);
    CPPUNIT_ASSERT (fc._age == 1);
  }

  void test_fred_cons2 () {
    FredkinCell fc (false, 0);
    CPPUNIT_ASSERT (!fc._living);
    CPPUNIT_ASSERT (fc._age == 0);
  }

  void test_fred_cons3 () {
    FredkinCell fc1 (true, 10);
    FredkinCell fc2 (true, 10);
    CPPUNIT_ASSERT (&fc1 != &fc2);
    CPPUNIT_ASSERT (fc1._living == fc2._living);
    CPPUNIT_ASSERT (fc1._age == fc2._age);
  }
  
  // ------------------
  // FredkinCell status
  // ------------------

  void test_fred_mfs1 () {
    FredkinCell fc1 (false, 44);
    FredkinCell fc2 (false, 10);
    FredkinCell fc3 (false, 9);
    char mfs1 = fc1.motherfuckingstatus();
    char mfs2 = fc2.motherfuckingstatus();
    char mfs3 = fc3.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs1 == '-');
    CPPUNIT_ASSERT (mfs1 == mfs2 && mfs2 == mfs3);
  }

  void test_fred_mfs2 () {
    FredkinCell fc1 (true, 0);
    FredkinCell fc2 (true, 9);
    char mfs1 = fc1.motherfuckingstatus();
    char mfs2 = fc2.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs1 == '0');
    CPPUNIT_ASSERT (mfs2 == '9');
  }

  void test_fred_mfs3 () {
    FredkinCell fc1 (true, 69);
    FredkinCell fc2 (false, 69);
    char mfs1 = fc1.motherfuckingstatus();
    char mfs2 = fc2.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs1 == '+');
    CPPUNIT_ASSERT (mfs2 == '-');
  }

  // -----------------------
  // FredkinCell DeadOrAlive
  // -----------------------

  void test_fred_doa1 () {
    FredkinCell fc (false, 0);
    vector<int> n (2, 3); 
    int nstat = fc.doa (n);
    CPPUNIT_ASSERT (nstat == 0);
  }

  void test_fred_doa2 () {
    FredkinCell fc (false, 3);
    vector<int> n (2, 1); 
    int nstat = fc.doa (n);
    CPPUNIT_ASSERT (nstat == 3);
  }

  void test_fred_doa3 () {
    FredkinCell fc (true, 0);
    vector<int> n (2, 0); 
    int nstat = fc.doa (n);
    CPPUNIT_ASSERT (nstat == -1);
  }

  void test_fred_doa4 () {
    FredkinCell fc (true, 1);
    vector<int> n (2, 2); 
    int nstat = fc.doa (n);
    CPPUNIT_ASSERT (nstat == -1);
  }

  void test_fred_doa5 () {
    FredkinCell fc (true, 2);
    vector<int> n (2, 4); 
    int nstat = fc.doa (n);
    CPPUNIT_ASSERT (nstat == -1);
  }

  void test_fred_doa6 () {
    FredkinCell fc (true, 9);
    vector<int> n (2, 1); 
    int nstat = fc.doa (n);
    CPPUNIT_ASSERT (nstat == 10);
  }

  // -------------
  // Fredkin clone
  // -------------
   
  void test_fred_clone1 () {
    FredkinCell fc (false, 0);
    FredkinCell* fclone = fc.clone();
    CPPUNIT_ASSERT (fclone != &fc);
    CPPUNIT_ASSERT (fclone->_age == fc._age);
    CPPUNIT_ASSERT (fclone->_age == 0);
    CPPUNIT_ASSERT (!fclone->_living);
    delete fclone;
  }
 
  void test_fred_clone2 () {
    FredkinCell fc (true, 69);
    FredkinCell* fclone = fc.clone();
    CPPUNIT_ASSERT (fclone != &fc);
    CPPUNIT_ASSERT (fclone->_age == fc._age);
    CPPUNIT_ASSERT (fc._age == 69);
    CPPUNIT_ASSERT (fclone->_living);
    delete fclone;
  }

  void test_fred_clone3 () {
    FredkinCell fc (true, 1);
    FredkinCell* fclone = fc.clone();
    CPPUNIT_ASSERT (fclone != &fc);
    CPPUNIT_ASSERT (fclone->_age == fc._age);
    CPPUNIT_ASSERT (fclone->_age == 1);
    vector<int> n (2, 0);
    vector<int> nn (2, 1);
    fc.doa(n);
    fclone->doa(nn);
    CPPUNIT_ASSERT (fc._age == 1);
    CPPUNIT_ASSERT (fclone->_age == 2);
    CPPUNIT_ASSERT (!fc._living);
    CPPUNIT_ASSERT (fclone->_living);
    delete fclone;
  }

  // ------------------------
  // Cell Default Constructor
  // ------------------------
    
  void test_cell_cons1 () {
    FredkinCell* fc = new FredkinCell (true, 0);
    Cell c (fc);
    CPPUNIT_ASSERT (c._ptr == fc);
  }

  void test_cell_cons2 () {
    ConwayCell* cc = new ConwayCell (true);
    Cell c (cc);
    CPPUNIT_ASSERT (c._ptr == cc);
  }

  void test_cell_cons3 () {
    FredkinCell* fc = new FredkinCell (true, 0);
    ConwayCell* cc = new ConwayCell (true);
    Cell c1 (fc);
    Cell c2 (cc);
    CPPUNIT_ASSERT (c1._ptr != c2._ptr);
  }

  // ---------------------
  // Cell Copy Constructor
  // ---------------------
    
  void test_cell_ccons1 () {
    FredkinCell* fc = new FredkinCell (true, 0);
    Cell c1 (fc);
    Cell c2 (c1);
    CPPUNIT_ASSERT (c1._ptr != c2._ptr);
  }

  void test_cell_ccons2 () {
    ConwayCell* cc = new ConwayCell (true);
    Cell c1 (cc);
    Cell c2 (c1);
    CPPUNIT_ASSERT (c1._ptr != c2._ptr);
  }

  void test_cell_ccons3 () {
    FredkinCell* fc = new FredkinCell (false, 0);
    Cell c1 (fc);
    Cell c2 (c1);
    Cell c3 (c2);
    CPPUNIT_ASSERT (c3._ptr != c2._ptr);
  }


  // --------------------
  // Cell Copy Assignment 
  // --------------------
 
  void test_cell_cacons1 () {
    FredkinCell* fc = new FredkinCell (false, 0);
    Cell c1 (new FredkinCell ());
    Cell c2 (fc);
    c2 = c1;
    CPPUNIT_ASSERT (c1._ptr != c2._ptr);
  }

  void test_cell_cacons2 () {
    ConwayCell* cc = new ConwayCell (true);
    Cell c1 (new ConwayCell (true));
    Cell c2 (cc);
    c2 = c1;
    CPPUNIT_ASSERT (c1._ptr != c2._ptr);
  }

  void test_cell_cacons3 () {
    FredkinCell* fc = new FredkinCell (true, 69);
    Cell c1 (new FredkinCell (false, 0));
    Cell c2 (new FredkinCell (false, 96));
    Cell c3 (fc);
    c1 = c2 = c3;
    CPPUNIT_ASSERT (c3._ptr != c2._ptr);
    CPPUNIT_ASSERT (c1._ptr != c2._ptr);
    CPPUNIT_ASSERT (c1.pulse() && c2.pulse() && c3.pulse());
  }
 
  // -----------
  // Cell status
  // -----------

  void test_cell_mfs1 () {
    FredkinCell* fc = new FredkinCell (false, 44);
    Cell c (fc);
    char mfs = c.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs == '-');
  }

  void test_cell_mfs2 () {
    ConwayCell* cc1 = new ConwayCell (true);
    ConwayCell* cc2 = new ConwayCell (false);
    Cell c1 (cc1);
    Cell c2 (cc2);
    char mfs1 = c1.motherfuckingstatus();
    char mfs2 = c2.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs1 == '*');
    CPPUNIT_ASSERT (mfs2 == '.');
  }

  void test_cell_mfs3 () {
    FredkinCell* fc1 = new FredkinCell (true, 69);
    FredkinCell* fc2 = new FredkinCell (true, 9);
    Cell c1 (fc1);
    Cell c2 (fc2);
    char mfs1 = c1.motherfuckingstatus();
    char mfs2 = c2.motherfuckingstatus();
    CPPUNIT_ASSERT (mfs1 == '+');
    CPPUNIT_ASSERT (mfs2 == '9');
  }

  // ----------------
  // Cell DeadOrAlive
  // ----------------

  void test_cell_doa1 () {
    Cell c (new FredkinCell());
    CPPUNIT_ASSERT (c.motherfuckingstatus() == '-');
    vector<int> n (2, 1);
    c.doa(n);
    CPPUNIT_ASSERT (c.motherfuckingstatus() == '0');
  }

  void test_cell_doa2 () {
    Cell c (new FredkinCell(true, 1));
    CPPUNIT_ASSERT (c.motherfuckingstatus() == '1');
    vector<int> n (2, 1);
    c.doa(n);
    CPPUNIT_ASSERT (c.motherfuckingstatus() == '*');
  }

  void test_cell_doa3 () {
    Cell c (new ConwayCell(true));
    CPPUNIT_ASSERT (c.motherfuckingstatus() == '*');
    vector<int> n (2, 1);
    c.doa(n);
    CPPUNIT_ASSERT (c.motherfuckingstatus() == '.');
  }

  // ----------
  // Cell pulse
  // ----------

  void test_cell_pulse1 () {
    Cell c (new FredkinCell());
    CPPUNIT_ASSERT (!c.pulse());
  }
 
  void test_cell_pulse2 () {
    Cell c (new FredkinCell(true, 0));
    CPPUNIT_ASSERT (c.pulse());
  }
 
  void test_cell_pulse3 () {
    Cell c (new ConwayCell());
    CPPUNIT_ASSERT (!c.pulse());
  }
 
  void test_cell_pulse4 () {
    Cell c (new ConwayCell(true));
    CPPUNIT_ASSERT (c.pulse());
  }

  // ----------------
  // List Constructor
  // ----------------

  void test_list_cons1 () {
    Life<ConwayCell> life (1, 1, ConwayCell());
    CPPUNIT_ASSERT (life._rows == life._cols);
    CPPUNIT_ASSERT (life._rows == 1);
    CPPUNIT_ASSERT (life._gen == life._pop);
    CPPUNIT_ASSERT (life._gen == 0);
    CPPUNIT_ASSERT (life._board[0][0].motherfuckingstatus() == '.');
  }

  void test_list_cons2 () {
    Life<FredkinCell> life (1, 1, FredkinCell());
    CPPUNIT_ASSERT (life._board[0][0].motherfuckingstatus() == '-');
  }

  void test_list_cons3 () {
    Life<Cell> life (1, 1, new FredkinCell(true, 1));
    CPPUNIT_ASSERT (life._board[0][0].motherfuckingstatus() == '1');
    vector<int> n (2, 1);
    life._board[0][0].doa(n);
    CPPUNIT_ASSERT (life._board[0][0].motherfuckingstatus() == '*');
  }

  // ---------------------
  // List Neighbor Counter
  // ---------------------

  void test_list_neighbor1 () {
    Life<ConwayCell> l (2, 2, ConwayCell());
    l.neighbor_counter (0, 0);
    CPPUNIT_ASSERT (l._neighbors[0][0][0] == 0);
    CPPUNIT_ASSERT (l._neighbors[0][0][1] == 0);
  }

  void test_list_neighbor2 () {
    Life<ConwayCell> l (2, 2, ConwayCell(true));
    l.neighbor_counter (0, 0);
    CPPUNIT_ASSERT (l._neighbors[0][0][0] == 2);
    CPPUNIT_ASSERT (l._neighbors[0][0][1] == 3);
  }

  void test_list_neighbor3 () {
    Life<Cell> l (3, 3, new FredkinCell(true, 0));
    l.neighbor_counter (1, 1);
    CPPUNIT_ASSERT (l._neighbors[1][1][0] == 4);
    CPPUNIT_ASSERT (l._neighbors[1][1][1] == 8);
  }

  // --------------
  // List Simulator
  // --------------
  
  void test_list_sim1 () {
    Life<ConwayCell> l (2, 2, ConwayCell(true));
    l._board[0][0] = ConwayCell(false);
    l._pop = 3;
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '.');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 4);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '*');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 4);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        CPPUNIT_ASSERT (l._board[i][j].motherfuckingstatus() == '*');
      }
    }
  }

  void test_list_sim2 () {
    Life<FredkinCell> l (2, 2, FredkinCell(true, 0));
    l._board[0][0] = FredkinCell();
    l._pop = 3;
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '0');
    CPPUNIT_ASSERT (l._board[1][0].motherfuckingstatus() == '0');
    CPPUNIT_ASSERT (l._board[1][1].motherfuckingstatus() == '0');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 2);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '1');
    CPPUNIT_ASSERT (l._board[1][0].motherfuckingstatus() == '1');
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 0);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        CPPUNIT_ASSERT (l._board[i][j].motherfuckingstatus() == '-');
      }
    }
  }

  void test_list_sim3 () {
    Life<Cell> l (2, 2, new FredkinCell(true, 1));
    l._board[0][0] = new FredkinCell();
    l._pop = 3;
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '1');
    CPPUNIT_ASSERT (l._board[1][0].motherfuckingstatus() == '1');
    CPPUNIT_ASSERT (l._board[1][1].motherfuckingstatus() == '1');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 2);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '*');
    CPPUNIT_ASSERT (l._board[1][0].motherfuckingstatus() == '*');
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 0);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '.');
    CPPUNIT_ASSERT (l._board[1][0].motherfuckingstatus() == '.');
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '-');
  }
 
  void test_list_sim4 () {
    Life<FredkinCell> l (1, 2, FredkinCell(true, 0));
    l._pop = 2;
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '0');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '0');
    l.simulate (9);
    CPPUNIT_ASSERT (l._pop == 2);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '9');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '9');
    l.simulate ();
    CPPUNIT_ASSERT (l._pop == 2);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '+');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '+');
    l.simulate (9);
    CPPUNIT_ASSERT (l._pop == 2);
    CPPUNIT_ASSERT (l._board[0][0].motherfuckingstatus() == '+');
    CPPUNIT_ASSERT (l._board[0][1].motherfuckingstatus() == '+');
  }
   
  
  CPPUNIT_TEST_SUITE(TestLife);

  CPPUNIT_TEST(test_conway_cons1);
  CPPUNIT_TEST(test_conway_cons2);
  CPPUNIT_TEST(test_conway_cons3);
  CPPUNIT_TEST(test_conway_mfs1);
  CPPUNIT_TEST(test_conway_mfs2);
  CPPUNIT_TEST(test_conway_mfs3);
  CPPUNIT_TEST(test_conway_doa1);
  CPPUNIT_TEST(test_conway_doa2);
  CPPUNIT_TEST(test_conway_doa3);
  CPPUNIT_TEST(test_conway_doa4);
  CPPUNIT_TEST(test_conway_doa5);
  CPPUNIT_TEST(test_conway_doa6);
  CPPUNIT_TEST(test_conway_clone1);
  CPPUNIT_TEST(test_conway_clone2);
  CPPUNIT_TEST(test_conway_clone3);

  CPPUNIT_TEST(test_fred_cons1);
  CPPUNIT_TEST(test_fred_cons2);
  CPPUNIT_TEST(test_fred_cons3);
  CPPUNIT_TEST(test_fred_mfs1);
  CPPUNIT_TEST(test_fred_mfs2);
  CPPUNIT_TEST(test_fred_mfs3);
  CPPUNIT_TEST(test_fred_doa1);
  CPPUNIT_TEST(test_fred_doa2);
  CPPUNIT_TEST(test_fred_doa3);
  CPPUNIT_TEST(test_fred_doa4);
  CPPUNIT_TEST(test_fred_doa5);
  CPPUNIT_TEST(test_fred_doa6);
  CPPUNIT_TEST(test_fred_clone1);
  CPPUNIT_TEST(test_fred_clone2);
  CPPUNIT_TEST(test_fred_clone3);

  CPPUNIT_TEST(test_cell_cons1);
  CPPUNIT_TEST(test_cell_cons2);
  CPPUNIT_TEST(test_cell_cons3);
  CPPUNIT_TEST(test_cell_ccons1);
  CPPUNIT_TEST(test_cell_ccons2);
  CPPUNIT_TEST(test_cell_ccons3);
  CPPUNIT_TEST(test_cell_cacons1);
  CPPUNIT_TEST(test_cell_cacons2);
  CPPUNIT_TEST(test_cell_cacons3);
  CPPUNIT_TEST(test_cell_mfs1);
  CPPUNIT_TEST(test_cell_mfs2);
  CPPUNIT_TEST(test_cell_mfs3);
  CPPUNIT_TEST(test_cell_doa1);
  CPPUNIT_TEST(test_cell_doa2);
  CPPUNIT_TEST(test_cell_doa3);
  CPPUNIT_TEST(test_cell_pulse1);
  CPPUNIT_TEST(test_cell_pulse2);
  CPPUNIT_TEST(test_cell_pulse3);
  CPPUNIT_TEST(test_cell_pulse4);

  CPPUNIT_TEST(test_list_cons1);
  CPPUNIT_TEST(test_list_cons2);
  CPPUNIT_TEST(test_list_cons3);
  CPPUNIT_TEST(test_list_neighbor1);
  CPPUNIT_TEST(test_list_neighbor2);
  CPPUNIT_TEST(test_list_neighbor3);
  CPPUNIT_TEST(test_list_sim1);
  CPPUNIT_TEST(test_list_sim2);
  CPPUNIT_TEST(test_list_sim3);
  CPPUNIT_TEST(test_list_sim4);

  CPPUNIT_TEST_SUITE_END();
};

// ----
// main
// ----

int main () {
  using namespace std;
  ios_base::sync_with_stdio(false);

  cout << "TestLife.c++" << endl;

  CppUnit::TextTestRunner tr;
  tr.addTest(TestLife::suite());
  tr.run();

  cout << "Done." << endl;
  return 0;
}
