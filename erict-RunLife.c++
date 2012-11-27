// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
    % valgrind RunLife.c++.app > RunLife.out

To configure Doxygen:
    doxygen -g
That creates the file Doxyfile.
Make the following edits:
    EXTRACT_ALL            = YES
    EXTRACT_PRIVATE        = YES
    EXTRACT_STATIC         = YES
    GENERATE_LATEX         = NO

To document the program:
    doxygen Doxyfile
*/

// --------
// includes
// --------

#include <cassert>   // assert
#include <iostream>  // cout, endl
#include <fstream>
#include <stdexcept> // invalid_argument, out_of_range

#include "AbstractCell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
#include "Cell.h"
#include "Life.h"

template <typename T>
void readLife(ifstream& file, Life<T> &lifers, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      char c;
      file >> c;
      if (c == '0' || c == '*') {
        lifers.population++;
        vector<int> v = {3, 3};
        lifers.cellGrid[i][j].liveOrDead(v);
      }
    }
  }
}

void getDimensions(ifstream& file, int &r, int &c) {
  file >> r;
  file >> c;
  assert (r != 0);
  assert (c != 0);
}

// ----
// main
// ----

int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O

    // ------------------
    // Conway Cell 109x69
    // ------------------
    //
    try {
      cout << "*** Life<ConwayCell> 109x69 ***" << endl;

      ifstream read ("RunLifeConway.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<ConwayCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      cout << lifers.drawLife();
      for (int i = 0; i < 283; i++) {
        lifers.runLife();
      }
      cout << lifers.drawLife();

      for (int i = 0; i < 40; i++) {
        lifers.runLife();
      }
      cout << lifers.drawLife();

      for (int i = 0; i < 2500; i++) {
        lifers.runLife();
      }
      cout << lifers.drawLife();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
      cout << "*** Life<FredkinCell> 20x20 ***" << endl;
      ifstream read ("RunLifeFredkin.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<FredkinCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      ofstream file ("RunLifeFredkin.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
      cout << "*** Life<Cell> 20x20 ***" << endl;
      ifstream read ("RunLife.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<Cell> lifers(rows, cols, new FredkinCell());
      readLife(read, lifers, rows, cols);
      ofstream file ("RunLifeCell.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
        lifers.runLife();
        file << lifers.drawLife();
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My10x10ConwayTest
    // ------------------

    try {
      cout << "*** Life<ConwayCell> 10x10 ***" << endl;

      ifstream read ("My10x10ConwayTest.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<ConwayCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      ofstream file ("My10x10ConwayTest.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        for (int i = 0; i < 10; i++) {
          lifers.runLife();
          file << lifers.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My10x10FredkinTest
    // ------------------

    try {
      cout << "*** Life<FredkinCell> 10x10 ***" << endl;

      ifstream read ("My10x10FredkinTest.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<FredkinCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      ofstream file ("My10x10FredkinTest.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        for (int i = 0; i < 10; i++) {
          lifers.runLife();
          file << lifers.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My10x10LifeTest
    // ------------------

    try {
      cout << "*** Life<Cell> 10x10 ***" << endl;

      ifstream read ("My10x10LifeTest.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<ConwayCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      ofstream file ("My10x10LifeTest.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        for (int i = 0; i < 10; i++) {
          lifers.runLife();
          file << lifers.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My20x38ConwayGlider
    // ------------------

    try {
      cout << "*** Life<ConwayCell> 20x38 Glider ***" << endl;

      ifstream read ("My20x38ConwayGlider.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<ConwayCell> lifers1(rows, cols);
      readLife(read, lifers1, rows, cols);
      ofstream file ("My20x38ConwayGlider.out");
      if (file.is_open()) {
        file << lifers1.drawLife();
        for (int i = 0; i < 20; i++) {
          lifers1.runLife();
          file << lifers1.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My5x5ConwayTest
    // ------------------

    try {
      cout << "*** Life<ConwayCell> 5x5 ***" << endl;

      ifstream read ("My5x5ConwayTest.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<ConwayCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      ofstream file ("My5x5ConwayTest.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        for (int i = 0; i < 10; i++) {
          lifers.runLife();
          file << lifers.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My5x5FredkinTest
    // ------------------

    try {
      cout << "*** Life<FredkinCell> 5x5 ***" << endl;

      ifstream read ("My5x5FredkinTest.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<FredkinCell> lifers(rows, cols);
      readLife(read, lifers, rows, cols);
      ofstream file ("My5x5FredkinTest.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        for (int i = 0; i < 10; i++) {
          lifers.runLife();
          file << lifers.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // My5x5LifeTest
    // ------------------

    try {
      cout << "*** Life<Cell> 5x5 ***" << endl;

      ifstream read ("My5x5LifeTest.in");
      int rows = 0;
      int cols = 0;
      getDimensions(read, rows, cols);
      Life<Cell> lifers(rows, cols, new FredkinCell());
      readLife(read, lifers, rows, cols);
      ofstream file ("My5x5LifeTest.out");
      if (file.is_open()) {
        file << lifers.drawLife();
        for (int i = 0; i < 10; i++) {
          lifers.runLife();
          file << lifers.drawLife();
        }
      }
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
