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
#include <vector>
#include <fstream>
#include <sstream>
#include "Life.h"
#include "Cell.h"
#include "ConwayCell.h"
#include "FredkinCell.h"
using namespace std;
    
string fileToString(string filename){
     string out;
     string add;
     ifstream f;
     f.open(filename);
     while(f.good()){
        getline(f,add);
        out += add + "\n";
     }
     return out;
}


// ----
// main
// ----
void generateGrid(vector< vector< char > > &g,ifstream& fin){
    int a,b;
    char in;
    fin >> a;
    fin >> b;
    //cerr << endl << "a is: " << a << " b is: " << b << endl;
    for(int i = 0; i < a; i++){
        vector< char > row;
        for(int j = 0; j < b; j++){
            fin >> in;
            while(in == '\n')
                fin >> in;
            row.push_back(in);
        }
        g.push_back(row);
    }
}
int main () {
    using namespace std;
    ios_base::sync_with_stdio(false); // turn off synchronization with C I/O
    try {
        //read RunLifeConway.in // assume all Conway cells
        vector< vector< char > > grid1;
        ifstream f ("RunLifeConway.in");
        generateGrid(grid1,f);
        f.close();
        ofstream o ("RunLifeConway.out");
        o << "*** Life<ConwayCell> 109x69 ***" << endl;
        Life< ConwayCell > life1(grid1.size(),grid1[0].size(),grid1);
        //Print grid.
        life1.print(o);
        //Simulate 283 moves.
        life1.advanceToTurn(283);
        //Print grid.
        life1.print(o);
        //Simulate 323 moves.
        life1.advanceToTurn(323);
        //Print grid.
        life1.print(o);
        //Simulate 2500 moves.
        life1.advanceToTurn(2823);
        //Print grid.
        life1.print(o);
        o.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ------------------
    // Fredkin Cell 20x20
    // ------------------
    try {
        //read RunLifeFredkin.in // assume all Fredkin cells
        vector< vector< char > > grid1;
        ifstream f ("RunLifeFredkin.in");
        generateGrid(grid1,f);
        f.close();
        ofstream o ("RunLifeFredkin.out");
        o << "*** Life<FredkinCell> 20x20 ***" << endl;
        Life< FredkinCell > life1(grid1.size(),grid1[0].size(),grid1);
        //Print grid.
        life1.print(o);
        //Simulate 2 moves.
        life1.advanceTurn();
        life1.print(o);
        life1.advanceTurn();
        life1.print(o);
        //Print every grid.
        o.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ----------
    // Cell 20x20
    // ----------
    try {
        
        //read RunLife.in // assume all Fredkin cells
        vector< vector< char > > grid1;
        ifstream f ("RunLife.in");
        generateGrid(grid1,f);
        f.close();
        ofstream o ("RunLife.out");
        o << "*** Life<Cell> 20x20 ***" << endl;
        Life< Cell > life1(grid1.size(),grid1[0].size(),grid1);
        //Print grid.
        life1.print(o);
        //Simulate 5 moves.
        for(int i = 0; i < 5; i++){
            life1.advanceTurn();
            //Print every grid.
            life1.print(o);
        }
        o.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    // ------
    // Test 4 - 6 Conway
    // ------
    for(int i = 4; i < 7; i ++){
        stringstream s;
        stringstream so;
        s << "test" << i << ".in";
        so << "test" << i << ".out";
        vector< vector< char > > grid1;
        ifstream f (s.str());
        generateGrid(grid1,f);
        f.close();
        ofstream o (so.str());
        o << so.str() << " - Five Turns" << endl;
        Life< ConwayCell > life1(grid1.size(),grid1[0].size(),grid1);
        //Print grid.
        life1.print(o);
        //Simulate 5 moves.
        for(int i = 0; i < 5; i++){
            life1.advanceTurn();
            //Print every grid.
            life1.print(o);
        }
        o.close();
    }
    // ------
    // Test 7 - 8 Fredkin
    // ------
    for(int i = 7; i < 9; i ++){
        stringstream s;
        stringstream so;
        s << "test" << i << ".in";
        so << "test" << i << ".out";
        vector< vector< char > > grid1;
        ifstream f (s.str());
        generateGrid(grid1,f);
        f.close();
        ofstream o (so.str());
        o << so.str() << " - Five Turns" << endl;
        Life< FredkinCell > life1(grid1.size(),grid1[0].size(),grid1);
        //Print grid.
        life1.print(o);
        //Simulate 5 moves.
        for(int i = 0; i < 5; i++){
            life1.advanceTurn();
            //Print every grid.
            life1.print(o);
        }
        o.close();
    }
    
    // ------
    // Test 9 - 10 Cell
    // ------
    for(int i = 9; i < 11; i ++){
        stringstream s;
        stringstream so;
        s << "test" << i << ".in";
        so << "test" << i << ".out";
        vector< vector< char > > grid1;
        ifstream f (s.str());
        generateGrid(grid1,f);
        f.close();
        ofstream o (so.str());
        o << so.str() << " - Five Turns" << endl;
        Life< Cell > life1(grid1.size(),grid1[0].size(),grid1);
        //Print grid.
        life1.print(o);
        //Simulate 5 moves.
        for(int i = 0; i < 5; i++){
            life1.advanceTurn();
            //Print every grid.
            life1.print(o);
        }
        o.close();
    }
    return 0;}
