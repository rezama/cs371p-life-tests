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
#include <cstdlib>
#include <string>

#define private public
#include "Life.h"


template <typename T>
void print (ofstream& w, Life<T>& life) {
  w << "\n\nGeneration = " << life._gen << ", Population = " << life._pop << ".";

  for (size_t r = 0; r < life._rows; r++) {
    w << "\n";
    for (size_t c = 0; c < life._cols; c++) {
      w << life._board[r][c].motherfuckingstatus();
    }
  }
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

    try {
        cout << "*** Life<ConwayCell> 109x69 ***" << endl;
        
        // read RunLifeConway.in // assume all Conway cells
        ifstream file ("RunLifeConway.in");
        ofstream myfile ("RunLifeConway.out");
        int rows, cols;
        file >> rows >> cols;
        Life<ConwayCell> life (rows, cols, ConwayCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '*') {
              life._board[row][i] = ConwayCell (true);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<ConwayCell> 109x69 ***";
        print (myfile, life);
        life.simulate (283);
        print (myfile, life);
        life.simulate (40);
        print (myfile, life);
        life.simulate (2500);
        print (myfile, life);
        
        myfile.close();
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
        
        ifstream file ("RunLifeFredkin.in");
        ofstream myfile ("RunLifeFredkin.out");
        int rows, cols;
        file >> rows >> cols;
        Life<FredkinCell> life (rows, cols, FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = FredkinCell (true, 0);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<FredkinCell> 20x20 ***";
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        myfile.close();        
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
        
        ifstream file ("RunLife.in");
        ofstream myfile ("RunLife.out");
        int rows, cols;
        file >> rows >> cols;
        Life<Cell> life (rows, cols, new FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = Cell (new FredkinCell (true, 0));
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<Cell> 20x20 ***";
        print (myfile, life);
        for (int i = 0; i < 5; i++) {
          life.simulate (1);
          print (myfile, life);
        }
        myfile.close(); 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ---------------
    // Conway - Beacon
    // ---------------

    try {
        cout << "*** Life<ConwayCell> Beacon ***" << endl;
        
        ifstream file ("beacon.in");
        ofstream myfile ("beacon.out");
        int rows, cols;
        file >> rows >> cols;
        Life<ConwayCell> life (rows, cols, ConwayCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '*') {
              life._board[row][i] = ConwayCell (true);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<ConwayCell> Beacon ***";
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -------------
    // Conway - Toad 
    // -------------

    try {
        cout << "*** Life<ConwayCell> Toad ***" << endl;
        
        ifstream file ("toad.in");
        ofstream myfile ("toad.out");
        int rows, cols;
        file >> rows >> cols;
        Life<ConwayCell> life (rows, cols, ConwayCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '*') {
              life._board[row][i] = ConwayCell (true);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<ConwayCell> Toad ***";
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        life.simulate (1);
        print (myfile, life);
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // -------------------
    // ConwayCell - Glider 
    // -------------------

    try {
        cout << "*** Life<ConwayCell> Glider ***" << endl;
        
        ifstream file ("glider.in");
        ofstream myfile ("glider.out");
        int rows, cols;
        file >> rows >> cols;
        Life<ConwayCell> life (rows, cols, ConwayCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '*') {
              life._board[row][i] = ConwayCell (true);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<ConwayCell> Glider ***";
        print (myfile, life);
        for (int i = 0; i < 4; i++) {
          life.simulate (1);
          print (myfile, life);
        }
        for (int i = 0; i < 4; i++) {
          life.simulate (4);
          print (myfile, life);
        }
        for (int i = 0; i < 4; i++) {
          life.simulate (8);
          print (myfile, life);
        }
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ----------------
    // Conway - Diehard
    // ----------------

    try {
        cout << "*** Life<ConwayCell> Diehard ***" << endl;
        
        ifstream file ("diehard.in");
        ofstream myfile ("diehard.out");
        int rows, cols;
        file >> rows >> cols;
        Life<ConwayCell> life (rows, cols, ConwayCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '*') {
              life._board[row][i] = ConwayCell (true);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<ConwayCell> Diehard ***";
        print (myfile, life);
        for (int i = 0; i < 4; i++) {
          life.simulate (30);
          print (myfile, life);
        }
        life.simulate (6);
        for (int i = 0; i < 5; i++) {
          life.simulate (1);
          print (myfile, life);
        }
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // -------------
    // Fredkin - Box
    // -------------

    try {
        cout << "*** Life<FredkinCell> Box ***" << endl;
        
        ifstream file ("fredkinBox.in");
        ofstream myfile ("fredkinBox.out");
        int rows, cols;
        file >> rows >> cols;
        Life<FredkinCell> life (rows, cols, FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = FredkinCell (true, 0);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<FredkinCell> Box ***";
        print (myfile, life);
        for (int i = 0; i < 6; i++) { 
          life.simulate (1);
          print (myfile, life);
        }
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin - Triangle
    // ------------------

    try {
        cout << "*** Life<FredkinCell> Triangle ***" << endl;
        
        ifstream file ("fredkinTriangle.in");
        ofstream myfile ("fredkinTriangle.out");
        int rows, cols;
        file >> rows >> cols;
        Life<FredkinCell> life (rows, cols, FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = FredkinCell (true, 0);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<FredkinCell> Triangle ***";
        print (myfile, life);
        for (int i = 0; i < 6; i++) { 
          life.simulate (1);
          print (myfile, life);
        }
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ---------------
    // Fredkin - Rings
    // ---------------

    try {
        cout << "*** Life<FredkinCell> Box ***" << endl;
        
        ifstream file ("fredkinRings.in");
        ofstream myfile ("fredkinRings.out");
        int rows, cols;
        file >> rows >> cols;
        Life<FredkinCell> life (rows, cols, FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = FredkinCell (true, 0);
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<FredkinCell> Rings ***";
        print (myfile, life);
        for (int i = 0; i < 6; i++) { 
          life.simulate (1);
          print (myfile, life);
        }
        
        myfile.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell - Box
    // ----------

    try {
        cout << "*** Life<Cell> Box ***" << endl;
        
        ifstream file ("fredkinBox.in");
        ofstream myfile ("cellBox.out");
        int rows, cols;
        file >> rows >> cols;
        Life<Cell> life (rows, cols, new FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = Cell (new FredkinCell (true, 0));
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<Cell> Box ***";
        print (myfile, life);
        for (int i = 0; i < 6; i++) {
          life.simulate (1);
          print (myfile, life);
        }
        myfile.close(); 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ---------------
    // Cell - Triangle
    // ---------------

    try {
        cout << "*** Life<Cell> Triangle ***" << endl;
        
        ifstream file ("fredkinTriangle.in");
        ofstream myfile ("cellTriangle.out");
        int rows, cols;
        file >> rows >> cols;
        Life<Cell> life (rows, cols, new FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = Cell (new FredkinCell (true, 0));
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<Cell> Triangle ***";
        print (myfile, life);
        for (int i = 0; i < 6; i++) {
          life.simulate (1);
          print (myfile, life);
        }
        myfile.close(); 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    // ------------
    // Cell - Rings
    // ------------

    try {
        cout << "*** Life<Cell> Rings ***" << endl;
        
        ifstream file ("fredkinRings.in");
        ofstream myfile ("cellRings.out");
        int rows, cols;
        file >> rows >> cols;
        Life<Cell> life (rows, cols, new FredkinCell());

        string line;
        size_t row = 0;
        while (file.good()) {
          getline (file, line);
          for (size_t i = 0; i < line.length(); i++) {
            if (line[i] == '0') {
              life._board[row][i] = Cell (new FredkinCell (true, 0));
              life._pop++;
            }
          }
          row++;
        }
        file.close();

        myfile << "*** Life<Cell> Rings ***";
        print (myfile, life);
        for (int i = 0; i < 6; i++) {
          life.simulate (1);
          print (myfile, life);
        }
        myfile.close(); 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
