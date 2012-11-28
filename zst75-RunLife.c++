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
#include <fstream>
#include "Life.h" 

/*#include "AbstractCell.h"
#include "ConwayCell.h"
#include "Cell.h"*/
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
        ifstream file;
        file.open ("RunLifeConway.in");
        Life<ConwayCell> conwayLifeSim(file);
        conwayLifeSim.print();
        conwayLifeSim.simulate(283);
        conwayLifeSim.print();
        conwayLifeSim.simulate(40);
        conwayLifeSim.print();
        conwayLifeSim.simulate(2177);
        conwayLifeSim.print();
        file.close();
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
        
        
        
    // ------------------
    // Conway Cell 109x69
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 109x69 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 2000 moves.
        Print grid.*/
        
        ifstream file;
        file.open ("RunLifeConway.in");
        Life<ConwayCell> conwayLifeSim(file);
        conwayLifeSim.print();
        conwayLifeSim.simulate(2000);
        conwayLifeSim.print();
        file.close();
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ------------------
    // Conway Cell 50x50
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 50x50 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 2000 moves.
        Print grid.*/
        
        ifstream file;
        file.open ("RunLifeConway5050.in");
        Life<ConwayCell> conwayLifeSim(file);
        conwayLifeSim.print();
        conwayLifeSim.simulate(2000);
        conwayLifeSim.print();
        file.close();
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}        
        
    // ------------------
    // Conway Cell 50x50
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 50x50 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 5 moves.
        Print grid.*/
        
        ifstream file;
        file.open ("RunLifeConway5050.in");
        Life<ConwayCell> conwayLifeSim(file);
        conwayLifeSim.print();
        conwayLifeSim.simulate(5);
        conwayLifeSim.print();
        file.close();
        
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ------------------
    // Conway Cell 50x50
    // ------------------

    try {
        cout << "*** Life<ConwayCell> 50x50 ***" << endl;
        /*
        read RunLifeConway.in // assume all Conway cells
        Print grid.
        Simulate 10 moves.
        Print grid.*/
        
        ifstream file;
        file.open ("RunLifeConway5050.in");
        Life<ConwayCell> conwayLifeSim(file);
        conwayLifeSim.print();
        conwayLifeSim.simulate(10);
        conwayLifeSim.print();
        file.close();
        
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
        ifstream file;
        file.open ("RunLifeFredkin.in");
        Life<FredkinCell> fredkinLifeSim(file);
        fredkinLifeSim.print();
        fredkinLifeSim.simulate(1);
        fredkinLifeSim.print();
        fredkinLifeSim.simulate(1);
        fredkinLifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ------------------
    // Fredkin Cell 50x50
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 20 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLifeFredkin5050.in");
        Life<FredkinCell> fredkinLifeSim(file);
        fredkinLifeSim.print();
        fredkinLifeSim.simulate(20);
        fredkinLifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
              
    // ------------------
    // Fredkin Cell 50x50
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 100 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLifeFredkin5050.in");
        Life<FredkinCell> fredkinLifeSim(file);
        fredkinLifeSim.print();
        fredkinLifeSim.simulate(100);
        fredkinLifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ------------------
    // Fredkin Cell 50x50
    // ------------------

    try {
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 50 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLifeFredkin5050.in");
        Life<FredkinCell> fredkinLifeSim(file);
        fredkinLifeSim.print();
        fredkinLifeSim.simulate(50);
        fredkinLifeSim.print();
        file.close();
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
        ifstream file;
        file.open ("RunLife.in");
        Life<Cell> lifeSim(file);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 50x50
    // ----------

    try {
        cout << "*** Life<Cell> 50x50 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 100 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLife5050.in");
        Life<Cell> lifeSim(file);
        lifeSim.print();
        lifeSim.simulate(100);
        lifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    // ----------
    // Cell 50x50
    // ----------

    try {
        cout << "*** Life<Cell> 50x50 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 50 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLife5050.in");
        Life<Cell> lifeSim(file);
        lifeSim.print();
        lifeSim.simulate(50);
        lifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}  
 
    // ----------
    // Cell 50x50
    // ----------

    try {
        cout << "*** Life<Cell> 50x50 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 200 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLife5050.in");
        Life<Cell> lifeSim(file);
        lifeSim.print();
        lifeSim.simulate(200);
        lifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}   
        
    // ----------
    // Cell 50x50
    // ----------

    try {
        cout << "*** Life<Cell> 50x50 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 500 moves.
        Print grid.
        */
        ifstream file;
        file.open ("RunLife5050.in");
        Life<Cell> lifeSim(file);
        lifeSim.print();
        lifeSim.simulate(500);
        lifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}                     
    
    
    // ----------
    // Cell 5x5
    // ----------

    try {
        cout << "*** Life<Cell> 5x5 ***" << endl;
        ifstream file;
        file.open ("RunLife5x5.in");
        Life<Cell> lifeSim(file);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        lifeSim.simulate(1);
        lifeSim.print();
        file.close();
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}                     
    return 0;}    
    
