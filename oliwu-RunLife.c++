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
#include <stdexcept> // invalid_argument, out_of_range
#include <string>

#define private public
#include "Life.h"
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
        ifstream file;
        ofstream myfile;
        file.open ("RunLifeConway.in");
        myfile.open ("RunLifeConway.out");
        int dims[2];
        dimensions (file, dims);

        Life<ConwayCell> life (dims[0], dims[1], ConwayCell());

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
        life.print (myfile);
        life.simulate (283);
        life.print (myfile);
        life.simulate (40);
        life.print (myfile);
        life.simulate (2500);
        life.print (myfile);
        
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
        
        // read RunLifeFredkin.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("RunLifeFredkin.in");
        myfile.open ("RunLifeFredkin.out");
        int dims[2];
        dimensions (file, dims);

        Life<FredkinCell> life (dims[0], dims[1], FredkinCell());

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
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
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
        
        // read RunLife.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("RunLife.in");
        myfile.open ("RunLife.out");
        int dims[2];
        dimensions (file, dims);

        Life<Cell> life (dims[0], dims[1], new FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 5; i++) {
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLifeConway.in // assume all Conway cells
        ifstream file;
        ofstream myfile;
        file.open ("beacon.in");
        myfile.open ("beacon.out");
        int dims[2];
        dimensions (file, dims);

        Life<ConwayCell> life (dims[0], dims[1], ConwayCell());

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
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        
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
        
        // read RunLifeConway.in // assume all Conway cells
        ifstream file;
        ofstream myfile;
        file.open ("toad.in");
        myfile.open ("toad.out");
        int dims[2];
        dimensions (file, dims);

        Life<ConwayCell> life (dims[0], dims[1], ConwayCell());

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
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        life.simulate (1);
        life.print (myfile);
        
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
        
        // read RunLifeConway.in // assume all Conway cells
        ifstream file;
        ofstream myfile;
        file.open ("glider.in");
        myfile.open ("glider.out");
        int dims[2];
        dimensions (file, dims);

        Life<ConwayCell> life (dims[0], dims[1], ConwayCell());

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
        life.print (myfile);
        for (int i = 0; i < 4; i++) {
          life.simulate (1);
          life.print (myfile);
        }
        for (int i = 0; i < 4; i++) {
          life.simulate (4);
          life.print (myfile);
        }
        for (int i = 0; i < 4; i++) {
          life.simulate (8);
          life.print (myfile);
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
        
        // read RunLifeConway.in // assume all Conway cells
        ifstream file;
        ofstream myfile;
        file.open ("diehard.in");
        myfile.open ("diehard.out");
        int dims[2];
        dimensions (file, dims);

        Life<ConwayCell> life (dims[0], dims[1], ConwayCell());

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
        life.print (myfile);
        for (int i = 0; i < 4; i++) {
          life.simulate (30);
          life.print (myfile);
        }
        life.simulate (6);
        for (int i = 0; i < 5; i++) {
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLifeFredkin.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("fredkinBox.in");
        myfile.open ("fredkinBox.out");
        int dims[2];
        dimensions (file, dims);

        Life<FredkinCell> life (dims[0], dims[1], FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 6; i++) { 
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLifeFredkin.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("fredkinTriangle.in");
        myfile.open ("fredkinTriangle.out");
        int dims[2];
        dimensions (file, dims);

        Life<FredkinCell> life (dims[0], dims[1], FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 6; i++) { 
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLifeFredkin.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("fredkinRings.in");
        myfile.open ("fredkinRings.out");
        int dims[2];
        dimensions (file, dims);

        Life<FredkinCell> life (dims[0], dims[1], FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 6; i++) { 
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLife.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("fredkinBox.in");
        myfile.open ("cellBox.out");
        int dims[2];
        dimensions (file, dims);

        Life<Cell> life (dims[0], dims[1], new FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 6; i++) {
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLife.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("fredkinTriangle.in");
        myfile.open ("cellTriangle.out");
        int dims[2];
        dimensions (file, dims);

        Life<Cell> life (dims[0], dims[1], new FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 6; i++) {
          life.simulate (1);
          life.print (myfile);
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
        
        // read RunLife.in // assume all Fredkin cells
        ifstream file;
        ofstream myfile;
        file.open ("fredkinRings.in");
        myfile.open ("cellRings.out");
        int dims[2];
        dimensions (file, dims);

        Life<Cell> life (dims[0], dims[1], new FredkinCell());

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
        life.print (myfile);
        for (int i = 0; i < 6; i++) {
          life.simulate (1);
          life.print (myfile);
        }
        myfile.close(); 
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}


    return 0;}
