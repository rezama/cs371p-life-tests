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
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeConway.in");
        output.open("RunLifeConway.out");
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

        Life<ConwayCell> l(input);

        l.printLife(output);
        l.display();
        l.run(283);
        l.printLife(output);
        l.display();
        l.run(40);
        l.printLife(output);
        l.display();
        l.run(2500);
        l.printLife(output);
        l.display();
        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ------------------
    // Fredkin Cell 20x20
    // ------------------

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeFredkin.in");
        output.open("RunLifeFredkin.out");
        cout << "*** Life<FredkinCell> 20x20 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        Life<FredkinCell> f(input);

        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();

        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // Cell 20x20
    // ----------

    try {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        std::ifstream input;
        std::ofstream output;
        input.open("RunLife.in");
        output.open("RunLifeCell.out");
        cout << "*** Life<Cell> 20x20 ***" << endl;
        /*
        read RunLifeCell.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        Life<FredkinCell> l(input);

        l.printLife(output);
        l.display();
        l.run(1);
        l.printLife(output);
        l.display();
        l.run(1);
        l.printLife(output);
        l.display();
        l.run(1);
        l.printLife(output);
        l.display();
        l.run(1);
        l.printLife(output);
        l.display();
        l.run(1);
        l.printLife(output);
        l.display();

        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeConway1.in");
        output.open("RunLifeConway1.out");
        cout << "*** Life<ConwayCell> 5x5 ***" << endl;
        /*
        read RunLifeConway1.in // assume all Conway cells
        Print grid.
        Simulate 260 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        */
        Life<ConwayCell> l(input);

        l.printLife(output);
        l.display();
        l.run(10);
        l.printLife(output);
        l.display();
        l.run(10);
        l.printLife(output);
        l.display();
        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeConway2.in");
        output.open("RunLifeConway2.out");
        cout << "*** Life<ConwayCell> 10x10 ***" << endl;
        /*
        read RunLifeConway1.in // assume all Conway cells
        Print grid.
        Simulate 260 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        */
        Life<ConwayCell> l(input);

        l.printLife(output);
        l.display();
        l.run(5);
        l.printLife(output);
        l.display();
        l.run(5);
        l.printLife(output);
        l.display();
        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeConway3.in");
        output.open("RunLifeConway3.out");
        cout << "*** Life<ConwayCell> 100x100 ***" << endl;
        /*
        read RunLifeConway1.in // assume all Conway cells
        Print grid.
        Simulate 260 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        */
        Life<ConwayCell> l(input);

        l.printLife(output);
        l.display();
        l.run(10);
        l.printLife(output);
        l.display();
        l.run(10);
        l.printLife(output);
        l.display();
        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeConway4.in");
        output.open("RunLifeConway4.out");
        cout << "*** Life<ConwayCell> 25x25 ***" << endl;
        /*
        read RunLifeConway1.in // assume all Conway cells
        Print grid.
        Simulate 260 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        */
        Life<ConwayCell> l(input);

        l.printLife(output);
        l.display();
        l.run(20);
        l.printLife(output);
        l.display();
        l.run(20);
        l.printLife(output);
        l.display();
        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}
        
    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeConway5.in");
        output.open("RunLifeConway5.out");
        cout << "*** Life<ConwayCell> 37x10 ***" << endl;
        /*
        read RunLifeConway1.in // assume all Conway cells
        Print grid.
        Simulate 260 moves.
        Print grid.
        Simulate 40 moves.
        Print grid.
        */
        Life<ConwayCell> l(input);

        l.printLife(output);
        l.display();
        l.run(20);
        l.printLife(output);
        l.display();
        l.run(20);
        l.printLife(output);
        l.display();
        input.close();
        output.close();
    }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeFredkin1.in");
        output.open("RunLifeFredkin1.out");
        cout << "*** Life<FredkinCell> 5x5 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        Life<FredkinCell> f(input);

        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();

        input.close();
        output.close();
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeFredkin2.in");
        output.open("RunLifeFredkin2.out");
        cout << "*** Life<FredkinCell> 10x10 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        Life<FredkinCell> f(input);

        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();

        input.close();
        output.close();
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeFredkin3.in");
        output.open("RunLifeFredkin3.out");
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        Life<FredkinCell> f(input);

        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();

        input.close();
        output.close();
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeFredkin4.in");
        output.open("RunLifeFredkin4.out");
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        Life<FredkinCell> f(input);

        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();

        input.close();
        output.close();
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    try {
        std::ifstream input;
        std::ofstream output;
        input.open("RunLifeFredkin5.in");
        output.open("RunLifeFredkin5.out");
        cout << "*** Life<FredkinCell> 50x50 ***" << endl;
        /*
        read RunLifeFredkin.in // assume all Fredkin cells
        Print grid.
        Simulate 2 moves.
        Print every grid.
        */
        Life<FredkinCell> f(input);

        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(1);
        f.printLife(output);
        f.display();
        f.run(10);
        f.printLife(output);
        f.display();
        f.run(100);
        f.printLife(output);
        f.display();

        input.close();
        output.close();
    }catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}
