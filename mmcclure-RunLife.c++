// -------------------------
// projects/life/RunLife.c++
// Copyright (C) 2012
// Glenn P. Downing
// -------------------------

/*
To run the program:
    % g++ -pedantic -std=c++0x -Wall RunLife.c++ -o RunLife.c++.app
    % valgrind RunLife.c++.app >& RunLife.out

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

#include "Life.h"

/**
 * Helper function to get the header from our file.
 *
 * @param f File stream.
 * @param rows Rows in the grid.
 * @param cols Cols in the grid.
 */
void getHeader(ifstream& f, int& rows, int &cols) {
    istringstream iss;
    istringstream iss2;
    string line;

    getline(f, line);
    iss.str(line);
    iss >> rows;

    getline(f, line);
    iss2.str(line);
    iss2 >> cols;
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
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 283 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        Simulate 2500 moves.
        Print grid.
        */
        ifstream    f("RunLifeConway.in");
        
        if (f.is_open()) {
            string              line;
            int                 rows, cols;

            getHeader(f, rows, cols);
            
            if (!f.eof()) {
                ConwayCell          cw;
                Life<ConwayCell>    l(rows, cols, cw.clone());
                
                for (int j = 1; j < rows + 1; j++) {
                    istringstream iss;
                    
                    getline(f, line);
                    iss.str(line);
                    
                    for (int i = 1; i < cols + 1; i++) {
                        iss >> l._world._m[j][i];
                    }
                }
                
                l.simulate(0);
                l.simulate(283);
                l.simulate(40);
                l.simulate(2500);
            }
            f.close();
            cout << endl;
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // CowayCell nxn
    // ----------
    
    try {
        /*
         Print grid.
         Simulate 5 moves.
         Print every grid.
         */
        const char * conwayTests[] = {
            "RunLifeConwayTest1.in",
            "RunLifeConwayTest2.in",
            "RunLifeConwayTest3.in",
            "RunLifeConwayTest4.in",
            "RunLifeConwayTest5.in",
            "RunLifeConwayTest6.in",
            "RunLifeConwayTest7.in",
            "RunLifeConwayTest8.in",
            "RunLifeConwayTest9.in",
            "RunLifeConwayTest10.in"
        };
        
        for (int i = 0; i < 10; i++) {            
            ifstream    f(conwayTests[i]);
            
            if (f.is_open()) {
                string      line;
                int         rows, cols;
                
                getHeader(f, rows, cols);
                
                if (!f.eof()) {
                    ConwayCell        cw;
                    Life<ConwayCell>  l(rows, cols, cw.clone());
                    
                    cout << "*** Life<ConwayCell> " << rows << "x" << cols << " ***" << endl;
                    
                    for (int j = 1; j < rows + 1; j++) {
                        istringstream iss;
                        
                        getline(f, line);
                        iss.str(line);
                        
                        for (int i = 1; i < cols + 1; i++) {
                            iss >> l._world._m[j][i];
                        }
                    }
                    
                    l.simulate(0);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);                
                }
                f.close();
                cout << endl;
            }
        }
        
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
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        ifstream    f("RunLifeFredkin.in");
        
        if (f.is_open()) {
            string              line;
            int                 rows, cols;
 
            getHeader(f, rows, cols);
            
            if (!f.eof()) {
                FredkinCell        fk;
                Life<FredkinCell>  l(rows, cols, fk.clone());
                
                for (int j = 1; j < rows + 1; j++) {
                    istringstream iss;
                    
                    getline(f, line);
                    iss.str(line);
                    
                    for (int i = 1; i < cols + 1; i++) {
                        iss >> l._world._m[j][i];
                    }
                }
                
                l.simulate(0);
                l.simulate(1);
                l.simulate(1);                
            }
            f.close();
            cout << endl;
        }
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // FredkinCell nxn
    // ----------
    
    try {
        /*
         Print grid.
         Simulate 5 moves.
         Print every grid.
         */
        const char * fredkinTests[] = {
            "RunLifeFredkinTest1.in",
            "RunLifeFredkinTest2.in",
            "RunLifeFredkinTest3.in",
            "RunLifeFredkinTest4.in",
            "RunLifeFredkinTest5.in",
            "RunLifeFredkinTest6.in",
            "RunLifeFredkinTest7.in",
            "RunLifeFredkinTest8.in",
            "RunLifeFredkinTest9.in",
            "RunLifeFredkinTest10.in"
        };
        
        for (int i = 0; i < 10; i++) {            
            ifstream    f(fredkinTests[i]);
            
            if (f.is_open()) {
                string      line;
                int         rows, cols;
                
                getHeader(f, rows, cols);
                
                if (!f.eof()) {
                    FredkinCell        fk;
                    Life<FredkinCell>  l(rows, cols, fk.clone());
                    
                    cout << "*** Life<FredkinCell> " << rows << "x" << cols << " ***" << endl;
                    
                    for (int j = 1; j < rows + 1; j++) {
                        istringstream iss;
                        
                        getline(f, line);
                        iss.str(line);
                        
                        for (int i = 1; i < cols + 1; i++) {
                            iss >> l._world._m[j][i];
                        }
                    }
                    
                    l.simulate(0);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);                
                }
                f.close();
                cout << endl;
            }
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
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        ifstream    f("RunLife.in");
        
        if (f.is_open()) {
            string      line;
            int         rows, cols;

            getHeader(f, rows, cols);
            
            if (!f.eof()) {
                FredkinCell    fk;
                Life<Cell>     l(rows, cols,
                                 (AbstractCell<Cell> *)fk.clone());
                
                for (int j = 1; j < rows + 1; j++) {
                    istringstream iss;
                    
                    getline(f, line);
                    iss.str(line);
                    
                    for (int i = 1; i < cols + 1; i++) {
                        iss >> l._world._m[j][i];
                    }
                }
                
                l.simulate(0);
                l.simulate(1);
                l.simulate(1);
                l.simulate(1);
                l.simulate(1);
                l.simulate(1);                
            }
            f.close();
            cout << endl;
        }        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell nxn
    // ----------
    
    try {
        /*
         Print grid.
         Simulate 5 moves.
         Print every grid.
         */
        const char * cellTests[] = {
            "RunLifeTest1.in",
            "RunLifeTest2.in",
            "RunLifeTest3.in",
            "RunLifeTest4.in",
            "RunLifeTest5.in",
            "RunLifeTest6.in",
            "RunLifeTest7.in",
            "RunLifeTest8.in",
            "RunLifeTest9.in",
            "RunLifeTest10.in"
        };
        
        for (int i = 0; i < 10; i++) {            
            ifstream    f(cellTests[i]);
        
            if (f.is_open()) {
                string      line;
                int         rows, cols;
                         
                getHeader(f, rows, cols);
                
                if (!f.eof()) {
                    FredkinCell c;
                    Life<Cell>  l(rows, cols, (AbstractCell<Cell> *)c.clone());
                    
                    cout << "*** Life<Cell> " << rows << "x" << cols << " ***" << endl;

                    for (int j = 1; j < rows + 1; j++) {
                        istringstream iss;
                        
                        getline(f, line);
                        iss.str(line);
                        
                        for (int i = 1; i < cols + 1; i++) {
                            iss >> l._world._m[j][i];
                        }
                    }

                    l.simulate(0);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);
                    l.simulate(1);                
                }
                f.close();
                cout << endl;
            }
        }
        
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
    
    return 0;}
