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
#include <iostream>  // I/O
#include <fstream>   // file I/O
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
        std::ifstream input("RunLifeConway.in", ios::in);
        std::ofstream output("RunLifeConway.out", ios::out);
        output << "*** Life<ConwayCell> 109x69 ***" << endl;
        std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
        Life<ConwayCell> life = Life<ConwayCell>(grid);

        life.display(output);
        life.simulate(283);
        life.display(output);
        life.simulate(40);
        life.display(output);
        life.simulate(2500);
        life.display(output);
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
        std::ifstream input("RunLifeFredkin.in", ios::in);
        std::ofstream output("RunLifeFredkin.out", ios::out);
        output << "*** Life<FredkinCell> 20x20 ***" << endl;
        std::vector<std::vector<FredkinCell> > grid = Life<FredkinCell>::parseFredkin(input);
        Life<FredkinCell> life = Life<FredkinCell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
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
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLife.in", ios::in);
        std::ofstream output("RunLife.out", ios::out);
        output << "*** Life<Cell> 20x20 ***" << endl;
        std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
        Life<Cell> life = Life<Cell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
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

        std::ifstream input("RunLifeCell.in", ios::in);
        std::ofstream output("RunLifeCell.out", ios::out);
        output << "*** Life<Cell> 20x20 ***" << endl;
        std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
        Life<Cell> life = Life<Cell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}




    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<ConwayCell> 4x4 ***" << endl;
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLifeTest5.in", ios::in);
        std::ofstream output("RunLifeTest5.out", ios::out);
        output << "*** Life<ConwayCell> 4x4 ***" << endl;
        std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
        Life<ConwayCell> life = Life<ConwayCell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<ConwayCell> 10x80 ***" << endl;
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLifeTest6.in", ios::in);
        std::ofstream output("RunLifeTest6.out", ios::out);
        output << "*** Life<ConwayCell> 10x80 ***" << endl;
        std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
        Life<ConwayCell> life = Life<ConwayCell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(2);
        life.display(output);
        life.simulate(2);
        life.display(output);
        life.simulate(2);
        life.display(output);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<ConwayCell> 10x80 ***" << endl;
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLifeTest7.in", ios::in);
        std::ofstream output("RunLifeTest7.out", ios::out);
        output << "*** Life<ConwayCell> 10x80 ***" << endl;
        std::vector<std::vector<ConwayCell> > grid = Life<ConwayCell>::parseConway(input);
        Life<ConwayCell> life = Life<ConwayCell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(2);
        life.display(output);
        life.simulate(2);
        life.display(output);
        life.simulate(2);
        life.display(output);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<FredkinCell> 10x80***" << endl;
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLifeTest8.in", ios::in);
        std::ofstream output("RunLifeTest8.out", ios::out);
        output << "*** Life<FredkinCell> 10x80 ***" << endl;
        std::vector<std::vector<FredkinCell> > grid = Life<Cell>::parseFredkin(input);
        Life<FredkinCell> life = Life<FredkinCell>(grid);

        life.display(output);
        life.simulate(10);
        life.display(output);
        life.simulate(10);
        life.display(output);
        life.simulate(5);
        life.display(output);
        life.simulate(5);
        life.display(output);
        life.simulate(100);
        life.display(output);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



    // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<FredkinCell> 10x8 ***" << endl;
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLifeTest9.in", ios::in);
        std::ofstream output("RunLifeTest9.out", ios::out);
        output << "*** Life<FredkinCell> 10x8 ***" << endl;
        std::vector<std::vector<FredkinCell> > grid = Life<FredkinCell>::parseFredkin(input);
        Life<FredkinCell> life = Life<FredkinCell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);

        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}



        // ----------
    // Cell 20x20
    // ----------

    try {
        cout << "*** Life<Cell> 12x80 ***" << endl;
        /*
        read RunLife.in // assume all Fredkin cells
        Print grid.
        Simulate 5 moves.
        Print every grid.
        */
        std::ifstream input("RunLifeTest10.in", ios::in);
        std::ofstream output("RunLifeTest10.out", ios::out);
        output << "*** Life<Cell> 12x80 ***" << endl;
        std::vector<std::vector<Cell> > grid = Life<Cell>::parseCell(input);
        Life<Cell> life = Life<Cell>(grid);

        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(1);
        life.display(output);
        life.simulate(10);
        life.display(output);
        life.simulate(100);
        life.display(output);
        life.simulate(500);
        life.display(output);
        }
    catch (const invalid_argument&) {
        assert(false);}
    catch (const out_of_range&) {
        assert(false);}

    return 0;}



